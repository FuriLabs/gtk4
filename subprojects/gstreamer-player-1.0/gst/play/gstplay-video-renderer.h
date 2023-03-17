/* GStreamer
 *
 * Copyright (C) 2014-2015 Sebastian Dröge <sebastian@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __GTL_GST_PLAY_VIDEO_RENDERER_H__
#define __GTL_GST_PLAY_VIDEO_RENDERER_H__

#include <gst/gst.h>
#include <gst/play/gstplay-types.h>

G_BEGIN_DECLS

/**
 * GtkGstPlayVideoRenderer:
 * Since: 1.20
 */
typedef struct _GstPlayVideoRenderer GtkGstPlayVideoRenderer;
typedef struct _GstPlayVideoRendererInterface GtkGstPlayVideoRendererInterface;

#define GST_TYPE_PLAY_VIDEO_RENDERER                (gtk_gst_play_video_renderer_get_type ())
#define GTL_GST_PLAY_VIDEO_RENDERER(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_PLAY_VIDEO_RENDERER, GtkGstPlayVideoRenderer))
#define GST_IS_PLAY_VIDEO_RENDERER(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_PLAY_VIDEO_RENDERER))

/**
 * GTL_GST_PLAY_VIDEO_RENDERER_GET_INTERFACE:
 * Since: 1.20
 */
#define GTL_GST_PLAY_VIDEO_RENDERER_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), GST_TYPE_PLAY_VIDEO_RENDERER, GtkGstPlayVideoRendererInterface))

struct _GstPlayVideoRendererInterface {
  GTypeInterface parent_iface;

  GstElement * (*create_video_sink) (GtkGstPlayVideoRenderer * self, GtkGstPlay * play);
};

#ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGstPlayVideoRenderer, g_object_unref)
#endif

GTL_GST_PLAY_API
GType        gtk_gst_play_video_renderer_get_type       (void);

G_END_DECLS

#endif /* __GTL_GST_PLAY_VIDEO_RENDERER_H__ */
