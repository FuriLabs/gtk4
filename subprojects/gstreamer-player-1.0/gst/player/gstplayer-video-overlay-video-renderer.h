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

#ifndef __GTK_GST_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER_H__
#define __GTK_GST_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER_H__

#include <gst/player/gstplayer-types.h>
#include <gst/player/gstplayer-video-renderer.h>

G_BEGIN_DECLS

typedef struct _GtkGstPlayerVideoOverlayVideoRenderer
    GtkGstPlayerVideoOverlayVideoRenderer;
typedef struct _GtkGstPlayerVideoOverlayVideoRendererClass
    GtkGstPlayerVideoOverlayVideoRendererClass;

#define GST_TYPE_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER             (gtk_gst_player_video_overlay_video_renderer_get_type ())
#define GST_IS_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER))
#define GST_IS_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER))
#define GTK_GST_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER, GtkGstPlayerVideoOverlayVideoRendererClass))
#define GTK_GST_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER, GtkGstPlayerVideoOverlayVideoRenderer))
#define GTK_GST_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER, GtkGstPlayerVideoOverlayVideoRendererClass))
#define GTK_GST_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER_CAST(obj)        ((GtkGstPlayerVideoOverlayVideoRenderer*)(obj))

GTK_GST_PLAYER_API
GType gtk_gst_player_video_overlay_video_renderer_get_type (void);

GTK_GST_PLAYER_API
GtkGstPlayerVideoRenderer * gtk_gst_player_video_overlay_video_renderer_new (gpointer window_handle);

GTK_GST_PLAYER_API
GtkGstPlayerVideoRenderer * gtk_gst_player_video_overlay_video_renderer_new_with_sink (gpointer window_handle, GstElement * video_sink);

GTK_GST_PLAYER_API
void gtk_gst_player_video_overlay_video_renderer_set_window_handle (GtkGstPlayerVideoOverlayVideoRenderer * self, gpointer window_handle);

GTK_GST_PLAYER_API
gpointer gtk_gst_player_video_overlay_video_renderer_get_window_handle (GtkGstPlayerVideoOverlayVideoRenderer * self);

GTK_GST_PLAYER_API
void gtk_gst_player_video_overlay_video_renderer_expose (GtkGstPlayerVideoOverlayVideoRenderer * self);

GTK_GST_PLAYER_API
void gtk_gst_player_video_overlay_video_renderer_set_render_rectangle (GtkGstPlayerVideoOverlayVideoRenderer * self, gint x, gint y, gint width, gint height);

GTK_GST_PLAYER_API
void gtk_gst_player_video_overlay_video_renderer_get_render_rectangle (GtkGstPlayerVideoOverlayVideoRenderer * self, gint *x, gint *y, gint *width, gint *height);

G_END_DECLS

#endif /* __GTK_GST_PLAYER_VIDEO_OVERLAY_VIDEO_RENDERER_H__ */
