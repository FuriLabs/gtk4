uniform sampler2D u_source;
uniform mat4 u_projection;
uniform mat4 u_modelview;
uniform float u_alpha;
uniform vec4 u_viewport;
uniform vec4[3] u_clip_rect;

#if defined(GSK_LEGACY)
_OUT_ vec4 outputColor;
#elif !defined(GSK_GLES)
_OUT_ vec4 outputColor;
#endif

_IN_ vec2 vUv;


GskRoundedRect gsk_decode_rect(_GSK_ROUNDED_RECT_UNIFORM_ r)
{
  GskRoundedRect rect;
#if defined(GSK_GLES) || defined(GSK_LEGACY)
  rect = GskRoundedRect(r[0], r[1], r[2]);
#else
  rect = r;
#endif

  return rect;
}

float
gsk_ellipsis_dist (vec2 p, vec2 radius)
{
  vec2 p0 = p / radius;
  vec2 p1 = 2.0 * p0 / radius;

  return (dot(p0, p0) - 1.0) / length (p1);
}

float
gsk_ellipsis_coverage (vec2 point, vec2 center, vec2 radius)
{
  float d = gsk_ellipsis_dist (point - center, radius);
  return clamp (0.5 - d, 0.0, 1.0);
}

float
gsk_rounded_rect_coverage (GskRoundedRect r, vec2 p)
{
  if (p.x < r.bounds.x || p.x >= r.bounds.z ||
      p.y < r.bounds.y || p.y >= r.bounds.w)
    return 0.0;

  vec2 ref_tl = r.corner_points1.xy;
  vec2 ref_tr = r.corner_points1.zw;
  vec2 ref_br = r.corner_points2.xy;
  vec2 ref_bl = r.corner_points2.zw;

  if (p.x >= ref_tl.x && p.x >= ref_bl.x &&
      p.x <= ref_tr.x && p.x <= ref_br.x)
    return 1.0;

  if (p.y >= ref_tl.y && p.y >= ref_tr.y &&
      p.y <= ref_bl.y && p.y <= ref_br.y)
    return 1.0;

  vec2 rad_tl = r.corner_points1.xy - r.bounds.xy;
  vec2 rad_tr = r.corner_points1.zw - r.bounds.zy;
  vec2 rad_br = r.corner_points2.xy - r.bounds.zw;
  vec2 rad_bl = r.corner_points2.zw - r.bounds.xw;

  float d_tl = gsk_ellipsis_coverage(p, ref_tl, rad_tl);
  float d_tr = gsk_ellipsis_coverage(p, ref_tr, rad_tr);
  float d_br = gsk_ellipsis_coverage(p, ref_br, rad_br);
  float d_bl = gsk_ellipsis_coverage(p, ref_bl, rad_bl);

  vec4 corner_coverages = 1.0 - vec4(d_tl, d_tr, d_br, d_bl);

  bvec4 is_out = bvec4(p.x < ref_tl.x && p.y < ref_tl.y,
                       p.x > ref_tr.x && p.y < ref_tr.y,
                       p.x > ref_br.x && p.y > ref_br.y,
                       p.x < ref_bl.x && p.y > ref_bl.y);

  return 1.0 - dot(vec4(is_out), corner_coverages);
}

float
gsk_rect_coverage (vec4 r, vec2 p)
{
  if (p.x >= r.z || p.x < r.x ||
      p.y >= r.w || p.y < r.y)
    return 0.0;

  return 1.0;
}

float
gsk_circle_coverage (vec4 r, vec2 p)
{
  float x_min = step(r.x, p.x);
  float y_min = step(r.y, p.y);
  float x_max = step(p.x, r.z - 1.0);
  float y_max = step(p.y, r.w - 1.0);

  if (x_min * y_min * x_max * y_max == 0.0)
    return 0.0;

  vec2 center = vec2(r.x + r.z, r.y - 1.0 + r.w - 1.0) / 2.0;
  float radius = (r.z - r.x - 2.0) / 2.0;

  float distance_squared = dot(p - center, p - center);
  if (distance_squared <= radius * radius)
    return 1.0;

  // TODO: anti-aliasing is not implemented yet
  return 0.0;
}

float gsk_symmetric_rounded_rect_coverage(GskRoundedRect r, vec2 p) {
  if (p.x < r.bounds.x || p.y < r.bounds.y ||
      p.x >= r.bounds.z || p.y >= r.bounds.w)
    return 0.0;

  vec2 ref_tl = r.corner_points1.xy;
  vec2 ref_br = r.corner_points2.xy;

  if (p.x >= ref_tl.x && p.y >= ref_tl.y &&
      p.x <= ref_br.x && p.y <= ref_br.y)
    return 1.0;

  if (p.x >= ref_tl.x && p.x <= ref_br.x &&
      (p.y < ref_tl.y || p.y > ref_br.y))
    return 1.0;

  vec2 center = (r.bounds.xy + r.bounds.zw) * 0.5;
  vec2 reflected_p = abs(p - center) + center;

  // We are now pretending to be in the bottom right corner of the rect.
  // We could actually probably do this higher up and save some calculations/branches. TODO!

  // Fill in the middle part where there are no corners.
  if (reflected_p.y < ref_br.y)
    return 1.0;

  return gsk_ellipsis_coverage(reflected_p, ref_br, ref_br - r.bounds.zw);
}

vec4 GskTexture(sampler2D sampler, vec2 texCoords) {
#if defined(GSK_GLES) || defined(GSK_LEGACY)
  return texture2D(sampler, texCoords);
#else
  return texture(sampler, texCoords);
#endif
}

#ifdef GSK_GL3
layout(origin_upper_left) in vec4 gl_FragCoord;
#endif

vec2 gsk_get_frag_coord() {
  vec2 fc = gl_FragCoord.xy;

#ifdef GSK_GL3
  fc += u_viewport.xy;
#else
  fc.x += u_viewport.x;
  fc.y = (u_viewport.y + u_viewport.w) - fc.y;
#endif

  return fc;
}

void gskSetOutputColor(vec4 color) {
  vec4 result;

#if defined(NO_CLIP)
  result = color;
#else
  float coverage = 1.0;

#if defined(CIRCLE_CLIP)
  coverage = gsk_circle_coverage(gsk_get_bounds(u_clip_rect),
                                 gsk_get_frag_coord());
#elif defined(SYMMETRIC_CLIP)
  coverage = gsk_symmetric_rounded_rect_coverage(gsk_create_rect(u_clip_rect),
                                                 gsk_get_frag_coord());
#elif defined(RECT_CLIP)
  coverage = gsk_rect_coverage(gsk_get_bounds(u_clip_rect),
                               gsk_get_frag_coord());
#else
  coverage = gsk_rounded_rect_coverage(gsk_create_rect(u_clip_rect),
                                       gsk_get_frag_coord());
#endif

  result = color * coverage;
#endif

#if defined(GSK_GLES) || defined(GSK_LEGACY)
  gl_FragColor = result;
#else
  outputColor = result;
#endif
}

void gskSetScaledOutputColor(vec4 color, float alpha) {
  vec4 result;
#if defined(NO_CLIP)
  result = color * alpha;
#else
  float coverage = 1.0;

#if defined(CIRCLE_CLIP)
  coverage = gsk_circle_coverage(gsk_get_bounds(u_clip_rect),
                                 gsk_get_frag_coord());
#elif defined(SYMMETRIC_CLIP)
  coverage = gsk_symmetric_rounded_rect_coverage(gsk_create_rect(u_clip_rect),
                                                 gsk_get_frag_coord());
  result = color * (alpha * coverage);
#elif defined(RECT_CLIP)
  coverage = gsk_rect_coverage(gsk_get_bounds(u_clip_rect),
                               gsk_get_frag_coord());

#else
  coverage = gsk_rounded_rect_coverage(gsk_create_rect(u_clip_rect),
                                       gsk_get_frag_coord());
#endif

  result = color * alpha * coverage;
#endif

#if defined(GSK_GLES) || defined(GSK_LEGACY)
  gl_FragColor = result;
#else
  outputColor = result;
#endif
}
