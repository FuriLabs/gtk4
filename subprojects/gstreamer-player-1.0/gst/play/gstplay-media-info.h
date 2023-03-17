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

#ifndef __GTL_GST_PLAY_MEDIA_INFO_H__
#define __GTL_GST_PLAY_MEDIA_INFO_H__

#include <gst/gst.h>
#include <gst/play/play-prelude.h>

G_BEGIN_DECLS

/**
 * GST_TYPE_PLAY_STREAM_INFO:
 * Since: 1.20
 */
#define GST_TYPE_PLAY_STREAM_INFO \
  (gtk_gst_play_stream_info_get_type ())
#define GTL_GST_PLAY_STREAM_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAY_STREAM_INFO,GtkGstPlayStreamInfo))
#define GTL_GST_PLAY_STREAM_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAY_STREAM_INFO,GtkGstPlayStreamInfo))
#define GST_IS_PLAY_STREAM_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAY_STREAM_INFO))
#define GST_IS_PLAY_STREAM_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAY_STREAM_INFO))

/**
 * GtkGstPlayStreamInfo:
 *
 * Base structure for information concerning a media stream. Depending on
 * the stream type, one can find more media-specific information in
 * #GtkGstPlayVideoInfo, #GtkGstPlayAudioInfo, #GtkGstPlaySubtitleInfo.
 * Since: 1.20
 */
typedef struct _GstPlayStreamInfo GtkGstPlayStreamInfo;
typedef struct _GstPlayStreamInfoClass GtkGstPlayStreamInfoClass;

GTL_GST_PLAY_API
GType         gtk_gst_play_stream_info_get_type (void);

GTL_GST_PLAY_API
gint          gtk_gst_play_stream_info_get_index (const GtkGstPlayStreamInfo *info);

GTL_GST_PLAY_API
const gchar*  gtk_gst_play_stream_info_get_stream_type (const GtkGstPlayStreamInfo *info);

GTL_GST_PLAY_API
GstTagList*   gtk_gst_play_stream_info_get_tags  (const GtkGstPlayStreamInfo *info);

GTL_GST_PLAY_API
GstCaps*      gtk_gst_play_stream_info_get_caps  (const GtkGstPlayStreamInfo *info);

GTL_GST_PLAY_API
const gchar*  gtk_gst_play_stream_info_get_codec (const GtkGstPlayStreamInfo *info);

/**
 * GST_TYPE_PLAY_VIDEO_INFO:
 * Since: 1.20
 */
#define GST_TYPE_PLAY_VIDEO_INFO \
  (gtk_gst_play_video_info_get_type ())
#define GTL_GST_PLAY_VIDEO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAY_VIDEO_INFO, GtkGstPlayVideoInfo))
#define GTL_GST_PLAY_VIDEO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((obj),GST_TYPE_PLAY_VIDEO_INFO, GtkGstPlayVideoInfoClass))
#define GST_IS_PLAY_VIDEO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAY_VIDEO_INFO))
#define GST_IS_PLAY_VIDEO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((obj),GST_TYPE_PLAY_VIDEO_INFO))

/**
 * GtkGstPlayVideoInfo:
 *
 * #GtkGstPlayStreamInfo specific to video streams.
 * Since: 1.20
 */
typedef struct _GstPlayVideoInfo GtkGstPlayVideoInfo;
typedef struct _GstPlayVideoInfoClass GtkGstPlayVideoInfoClass;

GTL_GST_PLAY_API
GType         gtk_gst_play_video_info_get_type (void);

GTL_GST_PLAY_API
gint          gtk_gst_play_video_info_get_bitrate     (const GtkGstPlayVideoInfo * info);

GTL_GST_PLAY_API
gint          gtk_gst_play_video_info_get_max_bitrate (const GtkGstPlayVideoInfo * info);

GTL_GST_PLAY_API
gint          gtk_gst_play_video_info_get_width       (const GtkGstPlayVideoInfo * info);

GTL_GST_PLAY_API
gint          gtk_gst_play_video_info_get_height      (const GtkGstPlayVideoInfo * info);

GTL_GST_PLAY_API
void          gtk_gst_play_video_info_get_framerate   (const GtkGstPlayVideoInfo * info,
                                                     gint * fps_n,
                                                     gint * fps_d);

GTL_GST_PLAY_API
void          gtk_gst_play_video_info_get_pixel_aspect_ratio (const GtkGstPlayVideoInfo * info,
                                                            guint * par_n,
                                                            guint * par_d);

/**
 * GST_TYPE_PLAY_AUDIO_INFO:
 * Since: 1.20
 */
#define GST_TYPE_PLAY_AUDIO_INFO \
  (gtk_gst_play_audio_info_get_type ())
#define GTL_GST_PLAY_AUDIO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAY_AUDIO_INFO, GtkGstPlayAudioInfo))
#define GTL_GST_PLAY_AUDIO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAY_AUDIO_INFO, GtkGstPlayAudioInfoClass))
#define GST_IS_PLAY_AUDIO_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAY_AUDIO_INFO))
#define GST_IS_PLAY_AUDIO_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAY_AUDIO_INFO))

/**
 * GtkGstPlayAudioInfo:
 *
 * #GtkGstPlayStreamInfo specific to audio streams.
 * Since: 1.20
 */
typedef struct _GstPlayAudioInfo GtkGstPlayAudioInfo;
typedef struct _GstPlayAudioInfoClass GtkGstPlayAudioInfoClass;

GTL_GST_PLAY_API
GType         gtk_gst_play_audio_info_get_type (void);

GTL_GST_PLAY_API
gint          gtk_gst_play_audio_info_get_channels    (const GtkGstPlayAudioInfo* info);

GTL_GST_PLAY_API
gint          gtk_gst_play_audio_info_get_sample_rate (const GtkGstPlayAudioInfo* info);

GTL_GST_PLAY_API
gint          gtk_gst_play_audio_info_get_bitrate     (const GtkGstPlayAudioInfo* info);

GTL_GST_PLAY_API
gint          gtk_gst_play_audio_info_get_max_bitrate (const GtkGstPlayAudioInfo* info);

GTL_GST_PLAY_API
const gchar*  gtk_gst_play_audio_info_get_language    (const GtkGstPlayAudioInfo* info);

/**
 * GST_TYPE_PLAY_SUBTITLE_INFO:
 * Since: 1.20
 */
#define GST_TYPE_PLAY_SUBTITLE_INFO \
  (gtk_gst_play_subtitle_info_get_type ())
#define GTL_GST_PLAY_SUBTITLE_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAY_SUBTITLE_INFO, GtkGstPlaySubtitleInfo))
#define GTL_GST_PLAY_SUBTITLE_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAY_SUBTITLE_INFO,GtkGstPlaySubtitleInfoClass))
#define GST_IS_PLAY_SUBTITLE_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAY_SUBTITLE_INFO))
#define GST_IS_PLAY_SUBTITLE_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAY_SUBTITLE_INFO))

/**
 * GtkGstPlaySubtitleInfo:
 *
 * #GtkGstPlayStreamInfo specific to subtitle streams.
 * Since: 1.20
 */
typedef struct _GstPlaySubtitleInfo GtkGstPlaySubtitleInfo;
typedef struct _GstPlaySubtitleInfoClass GtkGstPlaySubtitleInfoClass;

GTL_GST_PLAY_API
GType         gtk_gst_play_subtitle_info_get_type (void);

GTL_GST_PLAY_API
const gchar * gtk_gst_play_subtitle_info_get_language (const GtkGstPlaySubtitleInfo* info);

/**
 * GST_TYPE_PLAY_MEDIA_INFO:
 * Since: 1.20
 */
#define GST_TYPE_PLAY_MEDIA_INFO \
  (gtk_gst_play_media_info_get_type())
#define GTL_GST_PLAY_MEDIA_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_PLAY_MEDIA_INFO,GtkGstPlayMediaInfo))
#define GTL_GST_PLAY_MEDIA_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_PLAY_MEDIA_INFO,GtkGstPlayMediaInfoClass))
#define GST_IS_PLAY_MEDIA_INFO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_PLAY_MEDIA_INFO))
#define GST_IS_PLAY_MEDIA_INFO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_PLAY_MEDIA_INFO))

/**
 * GtkGstPlayMediaInfo:
 *
 * Structure containing the media information of a URI.
 * Since: 1.20
 */
typedef struct _GstPlayMediaInfo GtkGstPlayMediaInfo;
typedef struct _GstPlayMediaInfoClass GtkGstPlayMediaInfoClass;

#ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGstPlayMediaInfo, g_object_unref)
#endif

GTL_GST_PLAY_API
GType         gtk_gst_play_media_info_get_type (void);

GTL_GST_PLAY_API
const gchar * gtk_gst_play_media_info_get_uri (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
gboolean      gtk_gst_play_media_info_is_seekable (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
gboolean      gtk_gst_play_media_info_is_live (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
GstClockTime  gtk_gst_play_media_info_get_duration (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
GList*        gtk_gst_play_media_info_get_stream_list (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
guint         gtk_gst_play_media_info_get_number_of_streams (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
GList*        gtk_gst_play_media_info_get_video_streams (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
guint         gtk_gst_play_media_info_get_number_of_video_streams (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
GList*        gtk_gst_play_media_info_get_audio_streams (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
guint         gtk_gst_play_media_info_get_number_of_audio_streams (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
GList*        gtk_gst_play_media_info_get_subtitle_streams (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
guint         gtk_gst_play_media_info_get_number_of_subtitle_streams (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
GstTagList*   gtk_gst_play_media_info_get_tags (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
const gchar*  gtk_gst_play_media_info_get_title (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
const gchar*  gtk_gst_play_media_info_get_container_format (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_API
GstSample*    gtk_gst_play_media_info_get_image_sample (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_DEPRECATED_FOR(gtk_gst_play_media_info_get_video_streams)
GList*        gtk_gst_play_get_video_streams    (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_DEPRECATED_FOR(gtk_gst_play_media_info_get_audio_streams)
GList*        gtk_gst_play_get_audio_streams    (const GtkGstPlayMediaInfo *info);

GTL_GST_PLAY_DEPRECATED_FOR(gtk_gst_play_media_info_get_subtitle_streams)
GList*        gtk_gst_play_get_subtitle_streams (const GtkGstPlayMediaInfo *info);

G_END_DECLS

#endif /* __GTL_GST_PLAY_MEDIA_INFO_H */
