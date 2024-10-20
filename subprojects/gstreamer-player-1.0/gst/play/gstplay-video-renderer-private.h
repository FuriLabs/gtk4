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

#ifndef __GTL_GST_PLAY_VIDEO_RENDERER_PRIVATE_H__
#define __GTL_GST_PLAY_VIDEO_RENDERER_PRIVATE_H__

#include <gst/play/gstplay-video-renderer.h>

G_BEGIN_DECLS

G_GNUC_INTERNAL GstElement * gtk_gst_play_video_renderer_create_video_sink (GtkGstPlayVideoRenderer *
    self, GtkGstPlay * play);

G_END_DECLS

#endif /* __GTL_GST_PLAY_VIDEO_RENDERER_PRIVATE_H__ */
