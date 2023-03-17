/* GStreamer
 *
 * Copyright (C) 2015 Brijesh Singh <brijesh.ksingh@gmail.com>
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

#include "gstplayer-media-info.h"

#ifndef __GTK_GST_PLAYER_MEDIA_INFO_PRIVATE_H__
#define __GTK_GST_PLAYER_MEDIA_INFO_PRIVATE_H__

#include <gst/play/gstplay-media-info.h>

struct _GtkGstPlayerStreamInfo
{
  GObject parent;

  gint stream_index;
  GtkGstPlayStreamInfo *info;
};

struct _GtkGstPlayerStreamInfoClass
{
  GObjectClass parent_class;
};

struct _GtkGstPlayerSubtitleInfo
{
  GtkGstPlayerStreamInfo parent;

  GtkGstPlaySubtitleInfo *info;
};

struct _GtkGstPlayerSubtitleInfoClass
{
  GtkGstPlayerStreamInfoClass parent_class;
};

struct _GtkGstPlayerAudioInfo
{
  GtkGstPlayerStreamInfo parent;

  GtkGstPlayAudioInfo *info;
};

struct _GtkGstPlayerAudioInfoClass
{
  GtkGstPlayerStreamInfoClass parent_class;
};

struct _GtkGstPlayerVideoInfo
{
  GtkGstPlayerStreamInfo parent;

  GtkGstPlayVideoInfo *info;
};

struct _GtkGstPlayerVideoInfoClass
{
  GtkGstPlayerStreamInfoClass parent_class;
};

struct _GtkGstPlayerMediaInfo
{
  GObject parent;

  GList *stream_list;
  GList *audio_stream_list;
  GList *video_stream_list;
  GList *subtitle_stream_list;
  GtkGstPlayMediaInfo *info;
};

struct _GtkGstPlayerMediaInfoClass
{
  GObjectClass parent_class;
};

G_GNUC_INTERNAL GtkGstPlayerMediaInfo*   gtk_gst_player_media_info_new
                                      (void);
G_GNUC_INTERNAL GtkGstPlayerMediaInfo*   gtk_gst_player_media_info_copy
                                      (GtkGstPlayerMediaInfo *ref);
G_GNUC_INTERNAL GtkGstPlayerStreamInfo*  gtk_gst_player_stream_info_new
                                      (gint stream_index, GType type);
G_GNUC_INTERNAL GtkGstPlayerStreamInfo*  gtk_gst_player_stream_info_wrapped
                                      (GtkGstPlayStreamInfo * info);
G_GNUC_INTERNAL GtkGstPlayerStreamInfo*  gtk_gst_player_stream_info_copy
                                      (GtkGstPlayerStreamInfo *ref);

G_GNUC_INTERNAL GtkGstPlayerMediaInfo*   gtk_gst_player_media_info_wrapped
                                      (GtkGstPlayMediaInfo *info);
G_GNUC_INTERNAL GtkGstPlayerAudioInfo*   gtk_gst_player_audio_info_wrapped
                                      (GtkGstPlayAudioInfo *info);
G_GNUC_INTERNAL GtkGstPlayerVideoInfo*   gtk_gst_player_video_info_wrapped
                                      (GtkGstPlayVideoInfo *info);
G_GNUC_INTERNAL GtkGstPlayerSubtitleInfo*  gtk_gst_player_subtitle_info_wrapped
                                        (GtkGstPlaySubtitleInfo *info);

#endif /* __GTK_GST_PLAYER_MEDIA_INFO_PRIVATE_H__ */
