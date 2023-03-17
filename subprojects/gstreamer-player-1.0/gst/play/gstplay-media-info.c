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

/**
 * SECTION:gstplay-mediainfo
 * @title: GtkGstPlayMediaInfo
 * @short_description: Play Media Information
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstplay-media-info.h"
#include "gstplay-media-info-private.h"

/* Per-stream information */
G_DEFINE_ABSTRACT_TYPE (GtkGstPlayStreamInfo, gtk_gst_play_stream_info, G_TYPE_OBJECT);

static void
gtk_gst_play_stream_info_init (GtkGstPlayStreamInfo * sinfo)
{
  sinfo->stream_index = -1;
}

static void
gtk_gst_play_stream_info_finalize (GObject * object)
{
  GtkGstPlayStreamInfo *sinfo = GTL_GST_PLAY_STREAM_INFO (object);

  g_free (sinfo->codec);
  g_free (sinfo->stream_id);

  if (sinfo->caps)
    gst_caps_unref (sinfo->caps);

  if (sinfo->tags)
    gst_tag_list_unref (sinfo->tags);

  G_OBJECT_CLASS (gtk_gst_play_stream_info_parent_class)->finalize (object);
}

static void
gtk_gst_play_stream_info_class_init (GtkGstPlayStreamInfoClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->finalize = gtk_gst_play_stream_info_finalize;
}

/**
 * gtk_gst_play_stream_info_get_index:
 * @info: a #GtkGstPlayStreamInfo
 *
 * Function to get stream index from #GtkGstPlayStreamInfo instance or -1 if
 * unknown.
 *
 * Returns: the stream index of this stream.
 * Since: 1.20
 */
gint
gtk_gst_play_stream_info_get_index (const GtkGstPlayStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_STREAM_INFO (info), -1);

  return info->stream_index;
}

/**
 * gtk_gst_play_stream_info_get_stream_type:
 * @info: a #GtkGstPlayStreamInfo
 *
 * Function to return human readable name for the stream type
 * of the given @info (ex: "audio", "video", "subtitle")
 *
 * Returns: a human readable name
 * Since: 1.20
 */
const gchar *
gtk_gst_play_stream_info_get_stream_type (const GtkGstPlayStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_STREAM_INFO (info), NULL);

  if (GST_IS_PLAY_VIDEO_INFO (info))
    return "video";
  else if (GST_IS_PLAY_AUDIO_INFO (info))
    return "audio";
  else
    return "subtitle";
}

/**
 * gtk_gst_play_stream_info_get_tags:
 * @info: a #GtkGstPlayStreamInfo
 *
 * Returns: (transfer none) (nullable): the tags contained in this stream.
 * Since: 1.20
 */
GstTagList *
gtk_gst_play_stream_info_get_tags (const GtkGstPlayStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_STREAM_INFO (info), NULL);

  return info->tags;
}

/**
 * gtk_gst_play_stream_info_get_codec:
 * @info: a #GtkGstPlayStreamInfo
 *
 * A string describing codec used in #GtkGstPlayStreamInfo.
 *
 * Returns: (nullable): codec string or %NULL on unknown.
 * Since: 1.20
 */
const gchar *
gtk_gst_play_stream_info_get_codec (const GtkGstPlayStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_STREAM_INFO (info), NULL);

  return info->codec;
}

/**
 * gtk_gst_play_stream_info_get_caps:
 * @info: a #GtkGstPlayStreamInfo
 *
 * Returns: (nullable) (transfer none): the #GstCaps of the stream or %NULL if
 * unknown.
 * Since: 1.20
 */
GstCaps *
gtk_gst_play_stream_info_get_caps (const GtkGstPlayStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_STREAM_INFO (info), NULL);

  return info->caps;
}

/* Video information */
G_DEFINE_TYPE (GtkGstPlayVideoInfo, gtk_gst_play_video_info,
    GST_TYPE_PLAY_STREAM_INFO);

static void
gtk_gst_play_video_info_init (GtkGstPlayVideoInfo * info)
{
  info->width = -1;
  info->height = -1;
  info->framerate_num = 0;
  info->framerate_denom = 1;
  info->par_num = 1;
  info->par_denom = 1;
}

static void
gtk_gst_play_video_info_class_init (G_GNUC_UNUSED GtkGstPlayVideoInfoClass * klass)
{
  /* nothing to do here */
}

/**
 * gtk_gst_play_video_info_get_width:
 * @info: a #GtkGstPlayVideoInfo
 *
 * Returns: the width of video in #GtkGstPlayVideoInfo or -1 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_video_info_get_width (const GtkGstPlayVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_VIDEO_INFO (info), -1);

  return info->width;
}

/**
 * gtk_gst_play_video_info_get_height:
 * @info: a #GtkGstPlayVideoInfo
 *
 * Returns: the height of video in #GtkGstPlayVideoInfo or -1 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_video_info_get_height (const GtkGstPlayVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_VIDEO_INFO (info), -1);

  return info->height;
}

/**
 * gtk_gst_play_video_info_get_framerate:
 * @info: a #GtkGstPlayVideoInfo
 * @fps_n: (out): Numerator of frame rate
 * @fps_d: (out): Denominator of frame rate
 *
 * Since: 1.20
 */
void
gtk_gst_play_video_info_get_framerate (const GtkGstPlayVideoInfo * info,
    gint * fps_n, gint * fps_d)
{
  g_return_if_fail (GST_IS_PLAY_VIDEO_INFO (info));

  *fps_n = info->framerate_num;
  *fps_d = info->framerate_denom;
}

/**
 * gtk_gst_play_video_info_get_pixel_aspect_ratio:
 * @info: a #GtkGstPlayVideoInfo
 * @par_n: (out): numerator
 * @par_d: (out): denominator
 *
 * Returns the pixel aspect ratio in @par_n and @par_d
 *
 * Since: 1.20
 */
void
gtk_gst_play_video_info_get_pixel_aspect_ratio (const GtkGstPlayVideoInfo * info,
    guint * par_n, guint * par_d)
{
  g_return_if_fail (GST_IS_PLAY_VIDEO_INFO (info));

  *par_n = info->par_num;
  *par_d = info->par_denom;
}

/**
 * gtk_gst_play_video_info_get_bitrate:
 * @info: a #GtkGstPlayVideoInfo
 *
 * Returns: the current bitrate of video in #GtkGstPlayVideoInfo or -1 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_video_info_get_bitrate (const GtkGstPlayVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_VIDEO_INFO (info), -1);

  return info->bitrate;
}

/**
 * gtk_gst_play_video_info_get_max_bitrate:
 * @info: a #GtkGstPlayVideoInfo
 *
 * Returns: the maximum bitrate of video in #GtkGstPlayVideoInfo or -1 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_video_info_get_max_bitrate (const GtkGstPlayVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_VIDEO_INFO (info), -1);

  return info->max_bitrate;
}

/* Audio information */
G_DEFINE_TYPE (GtkGstPlayAudioInfo, gtk_gst_play_audio_info,
    GST_TYPE_PLAY_STREAM_INFO);

static void
gtk_gst_play_audio_info_init (GtkGstPlayAudioInfo * info)
{
  info->channels = 0;
  info->sample_rate = 0;
  info->bitrate = -1;
  info->max_bitrate = -1;
}

static void
gtk_gst_play_audio_info_finalize (GObject * object)
{
  GtkGstPlayAudioInfo *info = GTL_GST_PLAY_AUDIO_INFO (object);

  g_free (info->language);

  G_OBJECT_CLASS (gtk_gst_play_audio_info_parent_class)->finalize (object);
}

static void
gtk_gst_play_audio_info_class_init (GtkGstPlayAudioInfoClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->finalize = gtk_gst_play_audio_info_finalize;
}

/**
 * gtk_gst_play_audio_info_get_language:
 * @info: a #GtkGstPlayAudioInfo
 *
 * Returns: (nullable): the language of the stream, or %NULL if unknown.
 * Since: 1.20
 */
const gchar *
gtk_gst_play_audio_info_get_language (const GtkGstPlayAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_AUDIO_INFO (info), NULL);

  return info->language;
}

/**
 * gtk_gst_play_audio_info_get_channels:
 * @info: a #GtkGstPlayAudioInfo
 *
 * Returns: the number of audio channels in #GtkGstPlayAudioInfo or 0 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_audio_info_get_channels (const GtkGstPlayAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_AUDIO_INFO (info), 0);

  return info->channels;
}

/**
 * gtk_gst_play_audio_info_get_sample_rate:
 * @info: a #GtkGstPlayAudioInfo
 *
 * Returns: the audio sample rate in #GtkGstPlayAudioInfo or 0 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_audio_info_get_sample_rate (const GtkGstPlayAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_AUDIO_INFO (info), 0);

  return info->sample_rate;
}

/**
 * gtk_gst_play_audio_info_get_bitrate:
 * @info: a #GtkGstPlayAudioInfo
 *
 * Returns: the audio bitrate in #GtkGstPlayAudioInfo or -1 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_audio_info_get_bitrate (const GtkGstPlayAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_AUDIO_INFO (info), -1);

  return info->bitrate;
}

/**
 * gtk_gst_play_audio_info_get_max_bitrate:
 * @info: a #GtkGstPlayAudioInfo
 *
 * Returns: the audio maximum bitrate in #GtkGstPlayAudioInfo or -1 if unknown.
 * Since: 1.20
 */
gint
gtk_gst_play_audio_info_get_max_bitrate (const GtkGstPlayAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_AUDIO_INFO (info), -1);

  return info->max_bitrate;
}

/* Subtitle information */
G_DEFINE_TYPE (GtkGstPlaySubtitleInfo, gtk_gst_play_subtitle_info,
    GST_TYPE_PLAY_STREAM_INFO);

static void
gtk_gst_play_subtitle_info_init (G_GNUC_UNUSED GtkGstPlaySubtitleInfo * info)
{
  /* nothing to do */
}

static void
gtk_gst_play_subtitle_info_finalize (GObject * object)
{
  GtkGstPlaySubtitleInfo *info = GTL_GST_PLAY_SUBTITLE_INFO (object);

  g_free (info->language);

  G_OBJECT_CLASS (gtk_gst_play_subtitle_info_parent_class)->finalize (object);
}

static void
gtk_gst_play_subtitle_info_class_init (GtkGstPlaySubtitleInfoClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->finalize = gtk_gst_play_subtitle_info_finalize;
}

/**
 * gtk_gst_play_subtitle_info_get_language:
 * @info: a #GtkGstPlaySubtitleInfo
 *
 * Returns: (nullable): the language of the stream, or %NULL if unknown.
 * Since: 1.20
 */
const gchar *
gtk_gst_play_subtitle_info_get_language (const GtkGstPlaySubtitleInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_SUBTITLE_INFO (info), NULL);

  return info->language;
}

/* Global media information */
G_DEFINE_TYPE (GtkGstPlayMediaInfo, gtk_gst_play_media_info, G_TYPE_OBJECT);

static void
gtk_gst_play_media_info_init (GtkGstPlayMediaInfo * info)
{
  info->duration = -1;
  info->is_live = FALSE;
  info->seekable = FALSE;
}

static void
gtk_gst_play_media_info_finalize (GObject * object)
{
  GtkGstPlayMediaInfo *info = GTL_GST_PLAY_MEDIA_INFO (object);

  g_free (info->uri);

  if (info->tags)
    gst_tag_list_unref (info->tags);

  g_free (info->title);

  g_free (info->container);

  if (info->image_sample)
    gst_sample_unref (info->image_sample);

  if (info->audio_stream_list)
    g_list_free (info->audio_stream_list);

  if (info->video_stream_list)
    g_list_free (info->video_stream_list);

  if (info->subtitle_stream_list)
    g_list_free (info->subtitle_stream_list);

  if (info->stream_list)
    g_list_free_full (info->stream_list, g_object_unref);

  G_OBJECT_CLASS (gtk_gst_play_media_info_parent_class)->finalize (object);
}

static void
gtk_gst_play_media_info_class_init (GtkGstPlayMediaInfoClass * klass)
{
  GObjectClass *oclass = (GObjectClass *) klass;

  oclass->finalize = gtk_gst_play_media_info_finalize;
}

static GtkGstPlayVideoInfo *
gtk_gst_play_video_info_new (void)
{
  return g_object_new (GST_TYPE_PLAY_VIDEO_INFO, NULL);
}

static GtkGstPlayAudioInfo *
gtk_gst_play_audio_info_new (void)
{
  return g_object_new (GST_TYPE_PLAY_AUDIO_INFO, NULL);
}

static GtkGstPlaySubtitleInfo *
gtk_gst_play_subtitle_info_new (void)
{
  return g_object_new (GST_TYPE_PLAY_SUBTITLE_INFO, NULL);
}

static GtkGstPlayStreamInfo *
gtk_gst_play_video_info_copy (GtkGstPlayVideoInfo * ref)
{
  GtkGstPlayVideoInfo *ret;

  ret = gtk_gst_play_video_info_new ();

  ret->width = ref->width;
  ret->height = ref->height;
  ret->framerate_num = ref->framerate_num;
  ret->framerate_denom = ref->framerate_denom;
  ret->par_num = ref->par_num;
  ret->par_denom = ref->par_denom;
  ret->bitrate = ref->bitrate;
  ret->max_bitrate = ref->max_bitrate;

  return (GtkGstPlayStreamInfo *) ret;
}

static GtkGstPlayStreamInfo *
gtk_gst_play_audio_info_copy (GtkGstPlayAudioInfo * ref)
{
  GtkGstPlayAudioInfo *ret;

  ret = gtk_gst_play_audio_info_new ();

  ret->sample_rate = ref->sample_rate;
  ret->channels = ref->channels;
  ret->bitrate = ref->bitrate;
  ret->max_bitrate = ref->max_bitrate;

  if (ref->language)
    ret->language = g_strdup (ref->language);

  return (GtkGstPlayStreamInfo *) ret;
}

static GtkGstPlayStreamInfo *
gtk_gst_play_subtitle_info_copy (GtkGstPlaySubtitleInfo * ref)
{
  GtkGstPlaySubtitleInfo *ret;

  ret = gtk_gst_play_subtitle_info_new ();
  if (ref->language)
    ret->language = g_strdup (ref->language);

  return (GtkGstPlayStreamInfo *) ret;
}

GtkGstPlayStreamInfo *
gtk_gst_play_stream_info_copy (GtkGstPlayStreamInfo * ref)
{
  GtkGstPlayStreamInfo *info = NULL;

  if (!ref)
    return NULL;

  if (GST_IS_PLAY_VIDEO_INFO (ref))
    info = gtk_gst_play_video_info_copy ((GtkGstPlayVideoInfo *) ref);
  else if (GST_IS_PLAY_AUDIO_INFO (ref))
    info = gtk_gst_play_audio_info_copy ((GtkGstPlayAudioInfo *) ref);
  else
    info = gtk_gst_play_subtitle_info_copy ((GtkGstPlaySubtitleInfo *) ref);

  info->stream_index = ref->stream_index;
  if (ref->tags)
    info->tags = gst_tag_list_ref (ref->tags);
  if (ref->caps)
    info->caps = gst_caps_copy (ref->caps);
  if (ref->codec)
    info->codec = g_strdup (ref->codec);
  if (ref->stream_id)
    info->stream_id = g_strdup (ref->stream_id);

  return info;
}

GtkGstPlayMediaInfo *
gtk_gst_play_media_info_copy (GtkGstPlayMediaInfo * ref)
{
  GList *l;
  GtkGstPlayMediaInfo *info;

  if (!ref)
    return NULL;

  info = gtk_gst_play_media_info_new (ref->uri);
  info->duration = ref->duration;
  info->seekable = ref->seekable;
  info->is_live = ref->is_live;
  if (ref->tags)
    info->tags = gst_tag_list_ref (ref->tags);
  if (ref->title)
    info->title = g_strdup (ref->title);
  if (ref->container)
    info->container = g_strdup (ref->container);
  if (ref->image_sample)
    info->image_sample = gst_sample_ref (ref->image_sample);

  for (l = ref->stream_list; l != NULL; l = l->next) {
    GtkGstPlayStreamInfo *s;

    s = gtk_gst_play_stream_info_copy ((GtkGstPlayStreamInfo *) l->data);
    info->stream_list = g_list_append (info->stream_list, s);

    if (GST_IS_PLAY_AUDIO_INFO (s))
      info->audio_stream_list = g_list_append (info->audio_stream_list, s);
    else if (GST_IS_PLAY_VIDEO_INFO (s))
      info->video_stream_list = g_list_append (info->video_stream_list, s);
    else
      info->subtitle_stream_list =
          g_list_append (info->subtitle_stream_list, s);
  }

  return info;
}

GtkGstPlayStreamInfo *
gtk_gst_play_stream_info_new (gint stream_index, GType type)
{
  GtkGstPlayStreamInfo *info = NULL;

  if (type == GST_TYPE_PLAY_AUDIO_INFO)
    info = (GtkGstPlayStreamInfo *) gtk_gst_play_audio_info_new ();
  else if (type == GST_TYPE_PLAY_VIDEO_INFO)
    info = (GtkGstPlayStreamInfo *) gtk_gst_play_video_info_new ();
  else
    info = (GtkGstPlayStreamInfo *) gtk_gst_play_subtitle_info_new ();

  info->stream_index = stream_index;

  return info;
}

GtkGstPlayMediaInfo *
gtk_gst_play_media_info_new (const gchar * uri)
{
  GtkGstPlayMediaInfo *info;

  g_return_val_if_fail (uri != NULL, NULL);

  info = g_object_new (GST_TYPE_PLAY_MEDIA_INFO, NULL);
  info->uri = g_strdup (uri);

  return info;
}

/**
 * gtk_gst_play_media_info_get_uri:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: the URI associated with #GtkGstPlayMediaInfo.
 * Since: 1.20
 */
const gchar *
gtk_gst_play_media_info_get_uri (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->uri;
}

/**
 * gtk_gst_play_media_info_is_seekable:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: %TRUE if the media is seekable.
 * Since: 1.20
 */
gboolean
gtk_gst_play_media_info_is_seekable (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), FALSE);

  return info->seekable;
}

/**
 * gtk_gst_play_media_info_is_live:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: %TRUE if the media is live.
 * Since: 1.20
 */
gboolean
gtk_gst_play_media_info_is_live (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), FALSE);

  return info->is_live;
}

/**
 * gtk_gst_play_media_info_get_stream_list:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayStreamInfo): A #GList of
 * matching #GtkGstPlayStreamInfo.
 * Since: 1.20
 */
GList *
gtk_gst_play_media_info_get_stream_list (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->stream_list;
}

/**
 * gtk_gst_play_media_info_get_video_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayVideoInfo): A #GList of
 * matching #GtkGstPlayVideoInfo.
 * Since: 1.20
 */
GList *
gtk_gst_play_media_info_get_video_streams (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->video_stream_list;
}

/**
 * gtk_gst_play_media_info_get_subtitle_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlaySubtitleInfo): A #GList of
 * matching #GtkGstPlaySubtitleInfo.
 * Since: 1.20
 */
GList *
gtk_gst_play_media_info_get_subtitle_streams (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->subtitle_stream_list;
}

/**
 * gtk_gst_play_media_info_get_audio_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayAudioInfo): A #GList of
 * matching #GtkGstPlayAudioInfo.
 * Since: 1.20
 */
GList *
gtk_gst_play_media_info_get_audio_streams (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->audio_stream_list;
}

/**
 * gtk_gst_play_media_info_get_duration:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: duration of the media.
 * Since: 1.20
 */
GstClockTime
gtk_gst_play_media_info_get_duration (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), -1);

  return info->duration;
}

/**
 * gtk_gst_play_media_info_get_tags:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (nullable): the tags contained in media info.
 * Since: 1.20
 */
GstTagList *
gtk_gst_play_media_info_get_tags (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->tags;
}

/**
 * gtk_gst_play_media_info_get_title:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (nullable): the media title or %NULL if unknown.
 * Since: 1.20
 */
const gchar *
gtk_gst_play_media_info_get_title (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->title;
}

/**
 * gtk_gst_play_media_info_get_container_format:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (nullable): the container format or %NULL if unknown.
 * Since: 1.20
 */
const gchar *
gtk_gst_play_media_info_get_container_format (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->container;
}

/**
 * gtk_gst_play_media_info_get_image_sample:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Function to get the image (or preview-image) stored in taglist.
 * Application can use `gst_sample_*_()` API's to get caps, buffer etc.
 *
 * Returns: (nullable) (transfer none): GstSample or %NULL.
 * Since: 1.20
 */
GstSample *
gtk_gst_play_media_info_get_image_sample (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), NULL);

  return info->image_sample;
}

/**
 * gtk_gst_play_media_info_get_number_of_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: number of total streams.
 * Since: 1.20
 */
guint
gtk_gst_play_media_info_get_number_of_streams (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), 0);

  return g_list_length (info->stream_list);
}

/**
 * gtk_gst_play_media_info_get_number_of_video_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: number of video streams.
 * Since: 1.20
 */
guint
gtk_gst_play_media_info_get_number_of_video_streams (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), 0);

  return g_list_length (info->video_stream_list);
}

/**
 * gtk_gst_play_media_info_get_number_of_audio_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: number of audio streams.
 * Since: 1.20
 */
guint
gtk_gst_play_media_info_get_number_of_audio_streams (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), 0);

  return g_list_length (info->audio_stream_list);
}

/**
 * gtk_gst_play_media_info_get_number_of_subtitle_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: number of subtitle streams.
 * Since: 1.20
 */
guint gtk_gst_play_media_info_get_number_of_subtitle_streams
    (const GtkGstPlayMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAY_MEDIA_INFO (info), 0);

  return g_list_length (info->subtitle_stream_list);
}

/**
 * gtk_gst_play_get_video_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayVideoInfo): A #GList of
 * matching #GtkGstPlayVideoInfo.
 * Since: 1.20
 */
#ifndef GST_REMOVE_DEPRECATED
GList *
gtk_gst_play_get_video_streams (const GtkGstPlayMediaInfo * info)
{
  return gtk_gst_play_media_info_get_video_streams (info);
}
#endif

/**
 * gtk_gst_play_get_audio_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayAudioInfo): A #GList of
 * matching #GtkGstPlayAudioInfo.
 * Since: 1.20
 */
#ifndef GST_REMOVE_DEPRECATED
GList *
gtk_gst_play_get_audio_streams (const GtkGstPlayMediaInfo * info)
{
  return gtk_gst_play_media_info_get_audio_streams (info);
}
#endif

/**
 * gtk_gst_play_get_subtitle_streams:
 * @info: a #GtkGstPlayMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlaySubtitleInfo): A #GList of
 * matching #GtkGstPlaySubtitleInfo.
 * Since: 1.20
 */
#ifndef GST_REMOVE_DEPRECATED
GList *
gtk_gst_play_get_subtitle_streams (const GtkGstPlayMediaInfo * info)
{
  return gtk_gst_play_media_info_get_subtitle_streams (info);
}
#endif
