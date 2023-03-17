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

#ifndef __GTK_GST_PLAYER_MEDIA_INFO_H__
#define __GTK_GST_PLAYER_MEDIA_INFO_H__

#include <gst/gst.h>
#include <gst/player/player-prelude.h>

G_BEGIN_DECLS

#define GST_TYPE_PLAYER_STREAM_INFO \
  (gtk_gst_player_stream_info_get_type ())
#define GTK_GST_PLAYER_STREAM_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAYER_STREAM_INFO,GtkGstPlayerStreamInfo))
#define GTK_GST_PLAYER_STREAM_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAYER_STREAM_INFO,GtkGstPlayerStreamInfo))
#define GST_IS_PLAYER_STREAM_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAYER_STREAM_INFO))
#define GST_IS_PLAYER_STREAM_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAYER_STREAM_INFO))

/**
 * GtkGstPlayerStreamInfo:
 *
 * Base structure for information concerning a media stream. Depending on
 * the stream type, one can find more media-specific information in
 * #GtkGstPlayerVideoInfo, #GtkGstPlayerAudioInfo, #GtkGstPlayerSubtitleInfo.
 */
typedef struct _GtkGstPlayerStreamInfo GtkGstPlayerStreamInfo;
typedef struct _GtkGstPlayerStreamInfoClass GtkGstPlayerStreamInfoClass;

GTK_GST_PLAYER_API
GType         gtk_gst_player_stream_info_get_type (void);

GTK_GST_PLAYER_API
gint          gtk_gst_player_stream_info_get_index (const GtkGstPlayerStreamInfo *info);

GTK_GST_PLAYER_API
const gchar*  gtk_gst_player_stream_info_get_stream_type (const GtkGstPlayerStreamInfo *info);

GTK_GST_PLAYER_API
GstTagList*   gtk_gst_player_stream_info_get_tags  (const GtkGstPlayerStreamInfo *info);

GTK_GST_PLAYER_API
GstCaps*      gtk_gst_player_stream_info_get_caps  (const GtkGstPlayerStreamInfo *info);

GTK_GST_PLAYER_API
const gchar*  gtk_gst_player_stream_info_get_codec (const GtkGstPlayerStreamInfo *info);

#define GST_TYPE_PLAYER_VIDEO_INFO \
  (gtk_gst_player_video_info_get_type ())
#define GTK_GST_PLAYER_VIDEO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAYER_VIDEO_INFO, GtkGstPlayerVideoInfo))
#define GTK_GST_PLAYER_VIDEO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((obj),GST_TYPE_PLAYER_VIDEO_INFO, GtkGstPlayerVideoInfoClass))
#define GST_IS_PLAYER_VIDEO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAYER_VIDEO_INFO))
#define GST_IS_PLAYER_VIDEO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((obj),GST_TYPE_PLAYER_VIDEO_INFO))

/**
 * GtkGstPlayerVideoInfo:
 *
 * #GtkGstPlayerStreamInfo specific to video streams.
 */
typedef struct _GtkGstPlayerVideoInfo GtkGstPlayerVideoInfo;
typedef struct _GtkGstPlayerVideoInfoClass GtkGstPlayerVideoInfoClass;

GTK_GST_PLAYER_API
GType         gtk_gst_player_video_info_get_type (void);

GTK_GST_PLAYER_API
gint          gtk_gst_player_video_info_get_bitrate     (const GtkGstPlayerVideoInfo * info);

GTK_GST_PLAYER_API
gint          gtk_gst_player_video_info_get_max_bitrate (const GtkGstPlayerVideoInfo * info);

GTK_GST_PLAYER_API
gint          gtk_gst_player_video_info_get_width       (const GtkGstPlayerVideoInfo * info);

GTK_GST_PLAYER_API
gint          gtk_gst_player_video_info_get_height      (const GtkGstPlayerVideoInfo * info);

GTK_GST_PLAYER_API
void          gtk_gst_player_video_info_get_framerate   (const GtkGstPlayerVideoInfo * info,
                                                     gint * fps_n,
                                                     gint * fps_d);

GTK_GST_PLAYER_API
void          gtk_gst_player_video_info_get_pixel_aspect_ratio (const GtkGstPlayerVideoInfo * info,
                                                            guint * par_n,
                                                            guint * par_d);

#define GST_TYPE_PLAYER_AUDIO_INFO \
  (gtk_gst_player_audio_info_get_type ())
#define GTK_GST_PLAYER_AUDIO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAYER_AUDIO_INFO, GtkGstPlayerAudioInfo))
#define GTK_GST_PLAYER_AUDIO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAYER_AUDIO_INFO, GtkGstPlayerAudioInfoClass))
#define GST_IS_PLAYER_AUDIO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAYER_AUDIO_INFO))
#define GST_IS_PLAYER_AUDIO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAYER_AUDIO_INFO))

/**
 * GtkGstPlayerAudioInfo:
 *
 * #GtkGstPlayerStreamInfo specific to audio streams.
 */
typedef struct _GtkGstPlayerAudioInfo GtkGstPlayerAudioInfo;
typedef struct _GtkGstPlayerAudioInfoClass GtkGstPlayerAudioInfoClass;

GTK_GST_PLAYER_API
GType         gtk_gst_player_audio_info_get_type (void);

GTK_GST_PLAYER_API
gint          gtk_gst_player_audio_info_get_channels    (const GtkGstPlayerAudioInfo* info);

GTK_GST_PLAYER_API
gint          gtk_gst_player_audio_info_get_sample_rate (const GtkGstPlayerAudioInfo* info);

GTK_GST_PLAYER_API
gint          gtk_gst_player_audio_info_get_bitrate     (const GtkGstPlayerAudioInfo* info);

GTK_GST_PLAYER_API
gint          gtk_gst_player_audio_info_get_max_bitrate (const GtkGstPlayerAudioInfo* info);

GTK_GST_PLAYER_API
const gchar*  gtk_gst_player_audio_info_get_language    (const GtkGstPlayerAudioInfo* info);

#define GST_TYPE_PLAYER_SUBTITLE_INFO \
  (gtk_gst_player_subtitle_info_get_type ())
#define GTK_GST_PLAYER_SUBTITLE_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAYER_SUBTITLE_INFO, GtkGstPlayerSubtitleInfo))
#define GTK_GST_PLAYER_SUBTITLE_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAYER_SUBTITLE_INFO,GtkGstPlayerSubtitleInfoClass))
#define GST_IS_PLAYER_SUBTITLE_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAYER_SUBTITLE_INFO))
#define GST_IS_PLAYER_SUBTITLE_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAYER_SUBTITLE_INFO))

/**
 * GtkGstPlayerSubtitleInfo:
 *
 * #GtkGstPlayerStreamInfo specific to subtitle streams.
 */
typedef struct _GtkGstPlayerSubtitleInfo GtkGstPlayerSubtitleInfo;
typedef struct _GtkGstPlayerSubtitleInfoClass GtkGstPlayerSubtitleInfoClass;

GTK_GST_PLAYER_API
GType         gtk_gst_player_subtitle_info_get_type (void);

GTK_GST_PLAYER_API
const gchar * gtk_gst_player_subtitle_info_get_language (const GtkGstPlayerSubtitleInfo* info);

#define GST_TYPE_PLAYER_MEDIA_INFO \
  (gtk_gst_player_media_info_get_type())
#define GTK_GST_PLAYER_MEDIA_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAYER_MEDIA_INFO,GtkGstPlayerMediaInfo))
#define GTK_GST_PLAYER_MEDIA_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAYER_MEDIA_INFO,GtkGstPlayerMediaInfoClass))
#define GST_IS_PLAYER_MEDIA_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAYER_MEDIA_INFO))
#define GST_IS_PLAYER_MEDIA_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAYER_MEDIA_INFO))

/**
 * GtkGstPlayerMediaInfo:
 *
 * Structure containing the media information of a URI.
 */
typedef struct _GtkGstPlayerMediaInfo GtkGstPlayerMediaInfo;
typedef struct _GtkGstPlayerMediaInfoClass GtkGstPlayerMediaInfoClass;

GTK_GST_PLAYER_API
GType         gtk_gst_player_media_info_get_type (void);

GTK_GST_PLAYER_API
const gchar * gtk_gst_player_media_info_get_uri (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
gboolean      gtk_gst_player_media_info_is_seekable (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
gboolean      gtk_gst_player_media_info_is_live (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
GstClockTime  gtk_gst_player_media_info_get_duration (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
GList*        gtk_gst_player_media_info_get_stream_list (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
guint         gtk_gst_player_media_info_get_number_of_streams (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
GList*        gtk_gst_player_media_info_get_video_streams (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
guint         gtk_gst_player_media_info_get_number_of_video_streams (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
GList*        gtk_gst_player_media_info_get_audio_streams (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
guint         gtk_gst_player_media_info_get_number_of_audio_streams (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
GList*        gtk_gst_player_media_info_get_subtitle_streams (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
guint         gtk_gst_player_media_info_get_number_of_subtitle_streams (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
GstTagList*   gtk_gst_player_media_info_get_tags (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
const gchar*  gtk_gst_player_media_info_get_title (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
const gchar*  gtk_gst_player_media_info_get_container_format (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_API
GstSample*    gtk_gst_player_media_info_get_image_sample (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_DEPRECATED_FOR(gtk_gst_player_media_info_get_video_streams)
GList*        gtk_gst_player_get_video_streams    (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_DEPRECATED_FOR(gtk_gst_player_media_info_get_audio_streams)
GList*        gtk_gst_player_get_audio_streams    (const GtkGstPlayerMediaInfo *info);

GTK_GST_PLAYER_DEPRECATED_FOR(gtk_gst_player_media_info_get_subtitle_streams)
GList*        gtk_gst_player_get_subtitle_streams (const GtkGstPlayerMediaInfo *info);

G_END_DECLS

#endif /* __GTK_GST_PLAYER_MEDIA_INFO_H */
