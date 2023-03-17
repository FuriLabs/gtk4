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
 * SECTION:gstplayer-mediainfo
 * @title: GtkGstPlayerMediaInfo
 * @short_description: Player Media Information
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstplayer-media-info.h"
#include "gstplayer-media-info-private.h"

/* Per-stream information */
G_DEFINE_ABSTRACT_TYPE (GtkGstPlayerStreamInfo, gtk_gst_player_stream_info,
    G_TYPE_OBJECT);

static void
gtk_gst_player_stream_info_init (GtkGstPlayerStreamInfo * sinfo)
{
  sinfo->stream_index = -1;
}

static void
gtk_gst_player_stream_info_finalize (GObject * object)
{
  GtkGstPlayerStreamInfo *sinfo = GTK_GST_PLAYER_STREAM_INFO (object);

  g_clear_object (&sinfo->info);

  G_OBJECT_CLASS (gtk_gst_player_stream_info_parent_class)->finalize (object);
}

static void
gtk_gst_player_stream_info_class_init (GtkGstPlayerStreamInfoClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->finalize = gtk_gst_player_stream_info_finalize;
}

/**
 * gtk_gst_player_stream_info_get_index:
 * @info: a #GtkGstPlayerStreamInfo
 *
 * Function to get stream index from #GtkGstPlayerStreamInfo instance or -1 if
 * unknown.
 *
 * Returns: the stream index of this stream.
 */
gint
gtk_gst_player_stream_info_get_index (const GtkGstPlayerStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_STREAM_INFO (info), -1);

  return info->stream_index;
}

/**
 * gtk_gst_player_stream_info_get_stream_type:
 * @info: a #GtkGstPlayerStreamInfo
 *
 * Function to return human readable name for the stream type
 * of the given @info (ex: "audio", "video", "subtitle")
 *
 * Returns: a human readable name
 */
const gchar *
gtk_gst_player_stream_info_get_stream_type (const GtkGstPlayerStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_STREAM_INFO (info), NULL);

  return gtk_gst_play_stream_info_get_stream_type (info->info);
}

/**
 * gtk_gst_player_stream_info_get_tags:
 * @info: a #GtkGstPlayerStreamInfo
 *
 * Returns: (transfer none) (nullable): the tags contained in this stream.
 */
GstTagList *
gtk_gst_player_stream_info_get_tags (const GtkGstPlayerStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_STREAM_INFO (info), NULL);

  return gtk_gst_play_stream_info_get_tags (info->info);
}

/**
 * gtk_gst_player_stream_info_get_codec:
 * @info: a #GtkGstPlayerStreamInfo
 *
 * A string describing codec used in #GtkGstPlayerStreamInfo.
 *
 * Returns: (nullable): codec string or %NULL on unknown.
 */
const gchar *
gtk_gst_player_stream_info_get_codec (const GtkGstPlayerStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_STREAM_INFO (info), NULL);

  return gtk_gst_play_stream_info_get_codec (info->info);
}

/**
 * gtk_gst_player_stream_info_get_caps:
 * @info: a #GtkGstPlayerStreamInfo
 *
 * Returns: (transfer none) (nullable): the #GstCaps of the stream.
 */
GstCaps *
gtk_gst_player_stream_info_get_caps (const GtkGstPlayerStreamInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_STREAM_INFO (info), NULL);

  return gtk_gst_play_stream_info_get_caps (info->info);
}

/* Video information */
G_DEFINE_TYPE (GtkGstPlayerVideoInfo, gtk_gst_player_video_info,
    GST_TYPE_PLAYER_STREAM_INFO);

static void
gtk_gst_player_video_info_init (G_GNUC_UNUSED GtkGstPlayerVideoInfo * info)
{

}

static void
gtk_gst_player_video_info_finalize (GObject * object)
{
  GtkGstPlayerVideoInfo *info = GTK_GST_PLAYER_VIDEO_INFO (object);

  g_clear_object (&info->info);

  G_OBJECT_CLASS (gtk_gst_player_video_info_parent_class)->finalize (object);
}

static void
gtk_gst_player_video_info_class_init (G_GNUC_UNUSED GtkGstPlayerVideoInfoClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->finalize = gtk_gst_player_video_info_finalize;
}

/**
 * gtk_gst_player_video_info_get_width:
 * @info: a #GtkGstPlayerVideoInfo
 *
 * Returns: the width of video in #GtkGstPlayerVideoInfo or -1 if unknown.
 */
gint
gtk_gst_player_video_info_get_width (const GtkGstPlayerVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_VIDEO_INFO (info), -1);

  return gtk_gst_play_video_info_get_width (info->info);
}

/**
 * gtk_gst_player_video_info_get_height:
 * @info: a #GtkGstPlayerVideoInfo
 *
 * Returns: the height of video in #GtkGstPlayerVideoInfo or -1 if unknown.
 */
gint
gtk_gst_player_video_info_get_height (const GtkGstPlayerVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_VIDEO_INFO (info), -1);

  return gtk_gst_play_video_info_get_height (info->info);
}

/**
 * gtk_gst_player_video_info_get_framerate:
 * @info: a #GtkGstPlayerVideoInfo
 * @fps_n: (out): Numerator of frame rate
 * @fps_d: (out): Denominator of frame rate
 *
 */
void
gtk_gst_player_video_info_get_framerate (const GtkGstPlayerVideoInfo * info,
    gint * fps_n, gint * fps_d)
{
  g_return_if_fail (GST_IS_PLAYER_VIDEO_INFO (info));

  gtk_gst_play_video_info_get_framerate (info->info, fps_n, fps_d);
}

/**
 * gtk_gst_player_video_info_get_pixel_aspect_ratio:
 * @info: a #GtkGstPlayerVideoInfo
 * @par_n: (out): numerator
 * @par_d: (out): denominator
 *
 * Returns the pixel aspect ratio in @par_n and @par_d
 *
 */
void
gtk_gst_player_video_info_get_pixel_aspect_ratio (const GtkGstPlayerVideoInfo * info,
    guint * par_n, guint * par_d)
{
  g_return_if_fail (GST_IS_PLAYER_VIDEO_INFO (info));

  gtk_gst_play_video_info_get_pixel_aspect_ratio (info->info, par_n, par_d);
}

/**
 * gtk_gst_player_video_info_get_bitrate:
 * @info: a #GtkGstPlayerVideoInfo
 *
 * Returns: the current bitrate of video in #GtkGstPlayerVideoInfo or -1 if
 * unknown.
 */
gint
gtk_gst_player_video_info_get_bitrate (const GtkGstPlayerVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_VIDEO_INFO (info), -1);

  return gtk_gst_play_video_info_get_bitrate (info->info);
}

/**
 * gtk_gst_player_video_info_get_max_bitrate:
 * @info: a #GtkGstPlayerVideoInfo
 *
 * Returns: the maximum bitrate of video in #GtkGstPlayerVideoInfo or -1 if
 * unknown.
 */
gint
gtk_gst_player_video_info_get_max_bitrate (const GtkGstPlayerVideoInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_VIDEO_INFO (info), -1);

  return gtk_gst_play_video_info_get_max_bitrate (info->info);
}

/* Audio information */
G_DEFINE_TYPE (GtkGstPlayerAudioInfo, gtk_gst_player_audio_info,
    GST_TYPE_PLAYER_STREAM_INFO);

static void
gtk_gst_player_audio_info_init (G_GNUC_UNUSED GtkGstPlayerAudioInfo * info)
{

}

static void
gtk_gst_player_audio_info_finalize (GObject * object)
{
  GtkGstPlayerAudioInfo *info = GTK_GST_PLAYER_AUDIO_INFO (object);

  g_clear_object (&info->info);

  G_OBJECT_CLASS (gtk_gst_player_audio_info_parent_class)->finalize (object);
}

static void
gtk_gst_player_audio_info_class_init (GtkGstPlayerAudioInfoClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->finalize = gtk_gst_player_audio_info_finalize;
}

/**
 * gtk_gst_player_audio_info_get_language:
 * @info: a #GtkGstPlayerAudioInfo
 *
 * Returns: (nullable): the language of the stream, or NULL if unknown.
 */
const gchar *
gtk_gst_player_audio_info_get_language (const GtkGstPlayerAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_AUDIO_INFO (info), NULL);

  return gtk_gst_play_audio_info_get_language (info->info);
}

/**
 * gtk_gst_player_audio_info_get_channels:
 * @info: a #GtkGstPlayerAudioInfo
 *
 * Returns: the number of audio channels in #GtkGstPlayerAudioInfo or 0 if
 * unknown.
 */
gint
gtk_gst_player_audio_info_get_channels (const GtkGstPlayerAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_AUDIO_INFO (info), 0);

  return gtk_gst_play_audio_info_get_channels (info->info);
}

/**
 * gtk_gst_player_audio_info_get_sample_rate:
 * @info: a #GtkGstPlayerAudioInfo
 *
 * Returns: the audio sample rate in #GtkGstPlayerAudioInfo or 0 if unknown.
 */
gint
gtk_gst_player_audio_info_get_sample_rate (const GtkGstPlayerAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_AUDIO_INFO (info), 0);

  return gtk_gst_play_audio_info_get_sample_rate (info->info);
}

/**
 * gtk_gst_player_audio_info_get_bitrate:
 * @info: a #GtkGstPlayerAudioInfo
 *
 * Returns: the audio bitrate in #GtkGstPlayerAudioInfo or -1 if unknown.
 */
gint
gtk_gst_player_audio_info_get_bitrate (const GtkGstPlayerAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_AUDIO_INFO (info), -1);

  return gtk_gst_play_audio_info_get_bitrate (info->info);
}

/**
 * gtk_gst_player_audio_info_get_max_bitrate:
 * @info: a #GtkGstPlayerAudioInfo
 *
 * Returns: the audio maximum bitrate in #GtkGstPlayerAudioInfo or -1 if unknown.
 */
gint
gtk_gst_player_audio_info_get_max_bitrate (const GtkGstPlayerAudioInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_AUDIO_INFO (info), -1);

  return gtk_gst_play_audio_info_get_max_bitrate (info->info);
}

/* Subtitle information */
G_DEFINE_TYPE (GtkGstPlayerSubtitleInfo, gtk_gst_player_subtitle_info,
    GST_TYPE_PLAYER_STREAM_INFO);

static void
gtk_gst_player_subtitle_info_init (G_GNUC_UNUSED GtkGstPlayerSubtitleInfo * info)
{
  /* nothing to do */
}

static void
gtk_gst_player_subtitle_info_finalize (GObject * object)
{
  GtkGstPlayerSubtitleInfo *info = GTK_GST_PLAYER_SUBTITLE_INFO (object);

  g_clear_object (&info->info);

  G_OBJECT_CLASS (gtk_gst_player_subtitle_info_parent_class)->finalize (object);
}

static void
gtk_gst_player_subtitle_info_class_init (GtkGstPlayerSubtitleInfoClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  gobject_class->finalize = gtk_gst_player_subtitle_info_finalize;
}

/**
 * gtk_gst_player_subtitle_info_get_language:
 * @info: a #GtkGstPlayerSubtitleInfo
 *
 * Returns: (nullable): the language of the stream, or %NULL if unknown.
 */
const gchar *
gtk_gst_player_subtitle_info_get_language (const GtkGstPlayerSubtitleInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_SUBTITLE_INFO (info), NULL);

  return gtk_gst_play_subtitle_info_get_language (info->info);
}

/* Global media information */
G_DEFINE_TYPE (GtkGstPlayerMediaInfo, gtk_gst_player_media_info, G_TYPE_OBJECT);

static void
gtk_gst_player_media_info_init (G_GNUC_UNUSED GtkGstPlayerMediaInfo * info)
{

}

static void
gtk_gst_player_media_info_finalize (GObject * object)
{
  GtkGstPlayerMediaInfo *info = GTK_GST_PLAYER_MEDIA_INFO (object);

  if (info->audio_stream_list)
    g_list_free (info->audio_stream_list);

  if (info->video_stream_list)
    g_list_free (info->video_stream_list);

  if (info->subtitle_stream_list)
    g_list_free (info->subtitle_stream_list);

  if (info->stream_list)
    g_list_free_full (info->stream_list, g_object_unref);
  g_clear_object (&info->info);

  G_OBJECT_CLASS (gtk_gst_player_media_info_parent_class)->finalize (object);
}

static void
gtk_gst_player_media_info_class_init (GtkGstPlayerMediaInfoClass * klass)
{
  GObjectClass *oclass = (GObjectClass *) klass;

  oclass->finalize = gtk_gst_player_media_info_finalize;
}

static GtkGstPlayerVideoInfo *
gtk_gst_player_video_info_new (void)
{
  return g_object_new (GST_TYPE_PLAYER_VIDEO_INFO, NULL);
}

static GtkGstPlayerAudioInfo *
gtk_gst_player_audio_info_new (void)
{
  return g_object_new (GST_TYPE_PLAYER_AUDIO_INFO, NULL);
}

static GtkGstPlayerSubtitleInfo *
gtk_gst_player_subtitle_info_new (void)
{
  return g_object_new (GST_TYPE_PLAYER_SUBTITLE_INFO, NULL);
}

static GtkGstPlayerStreamInfo *
gtk_gst_player_video_info_copy (GtkGstPlayerVideoInfo * ref)
{
  GtkGstPlayerVideoInfo *ret;

  ret = gtk_gst_player_video_info_new ();
  ret->info = g_object_ref (ref->info);

  return (GtkGstPlayerStreamInfo *) ret;
}

static GtkGstPlayerStreamInfo *
gtk_gst_player_audio_info_copy (GtkGstPlayerAudioInfo * ref)
{
  GtkGstPlayerAudioInfo *ret;

  ret = gtk_gst_player_audio_info_new ();
  ret->info = g_object_ref (ref->info);

  return (GtkGstPlayerStreamInfo *) ret;
}

static GtkGstPlayerStreamInfo *
gtk_gst_player_subtitle_info_copy (GtkGstPlayerSubtitleInfo * ref)
{
  GtkGstPlayerSubtitleInfo *ret;

  ret = gtk_gst_player_subtitle_info_new ();
  ret->info = g_object_ref (ref->info);

  return (GtkGstPlayerStreamInfo *) ret;
}

GtkGstPlayerStreamInfo *
gtk_gst_player_stream_info_copy (GtkGstPlayerStreamInfo * ref)
{
  GtkGstPlayerStreamInfo *info = NULL;

  if (!ref)
    return NULL;

  if (GST_IS_PLAYER_VIDEO_INFO (ref))
    info = gtk_gst_player_video_info_copy ((GtkGstPlayerVideoInfo *) ref);
  else if (GST_IS_PLAYER_AUDIO_INFO (ref))
    info = gtk_gst_player_audio_info_copy ((GtkGstPlayerAudioInfo *) ref);
  else
    info = gtk_gst_player_subtitle_info_copy ((GtkGstPlayerSubtitleInfo *) ref);

  info->stream_index = ref->stream_index;

  return info;
}

GtkGstPlayerMediaInfo *
gtk_gst_player_media_info_copy (GtkGstPlayerMediaInfo * ref)
{
  GList *l;
  GtkGstPlayerMediaInfo *info;

  if (!ref)
    return NULL;

  info = gtk_gst_player_media_info_new ();

  for (l = gtk_gst_player_media_info_get_stream_list (ref); l != NULL; l = l->next) {
    GtkGstPlayerStreamInfo *s;

    s = gtk_gst_player_stream_info_copy ((GtkGstPlayerStreamInfo *) l->data);
    info->stream_list = g_list_append (info->stream_list, s);

    if (GST_IS_PLAYER_AUDIO_INFO (s))
      info->audio_stream_list = g_list_append (info->audio_stream_list, s);
    else if (GST_IS_PLAYER_VIDEO_INFO (s))
      info->video_stream_list = g_list_append (info->video_stream_list, s);
    else
      info->subtitle_stream_list =
          g_list_append (info->subtitle_stream_list, s);
  }

  info->info = g_object_ref (ref->info);

  return info;
}

GtkGstPlayerStreamInfo *
gtk_gst_player_stream_info_new (gint stream_index, GType type)
{
  GtkGstPlayerStreamInfo *info = NULL;

  if (type == GST_TYPE_PLAYER_AUDIO_INFO)
    info = (GtkGstPlayerStreamInfo *) gtk_gst_player_audio_info_new ();
  else if (type == GST_TYPE_PLAYER_VIDEO_INFO)
    info = (GtkGstPlayerStreamInfo *) gtk_gst_player_video_info_new ();
  else
    info = (GtkGstPlayerStreamInfo *) gtk_gst_player_subtitle_info_new ();

  info->stream_index = stream_index;

  return info;
}

GtkGstPlayerStreamInfo *
gtk_gst_player_stream_info_wrapped (GtkGstPlayStreamInfo * info)
{
  GtkGstPlayerStreamInfo *ret;
  GType type;

  if (GST_IS_PLAY_AUDIO_INFO (info)) {
    type = GST_TYPE_PLAYER_AUDIO_INFO;
  } else if (GST_IS_PLAY_VIDEO_INFO (info)) {
    type = GST_TYPE_PLAYER_VIDEO_INFO;
  } else {
    type = GST_TYPE_PLAYER_SUBTITLE_INFO;
  }

  ret =
      gtk_gst_player_stream_info_new (gtk_gst_play_stream_info_get_index (info), type);
  ret->info = g_object_ref (info);
  return ret;
}

GtkGstPlayerMediaInfo *
gtk_gst_player_media_info_new (void)
{
  return g_object_new (GST_TYPE_PLAYER_MEDIA_INFO, NULL);
}

GtkGstPlayerMediaInfo *
gtk_gst_player_media_info_wrapped (GtkGstPlayMediaInfo * info)
{
  GtkGstPlayerMediaInfo *ret;
  GList *l;

  ret = gtk_gst_player_media_info_new ();
  ret->info = g_object_ref (info);

  for (l = gtk_gst_play_media_info_get_stream_list (info); l != NULL; l = l->next) {
    GtkGstPlayerStreamInfo *s;

    s = gtk_gst_player_stream_info_wrapped ((GtkGstPlayStreamInfo *) l->data);
    ret->stream_list = g_list_append (ret->stream_list, s);

    if (GST_IS_PLAYER_AUDIO_INFO (s)) {
      GtkGstPlayerAudioInfo *i = GTK_GST_PLAYER_AUDIO_INFO (s);
      i->info = g_object_ref (GTL_GST_PLAY_AUDIO_INFO (l->data));
      ret->audio_stream_list = g_list_append (ret->audio_stream_list, i);
    } else if (GST_IS_PLAYER_VIDEO_INFO (s)) {
      GtkGstPlayerVideoInfo *i = GTK_GST_PLAYER_VIDEO_INFO (s);
      i->info = g_object_ref (GTL_GST_PLAY_VIDEO_INFO (l->data));
      ret->video_stream_list = g_list_append (ret->video_stream_list, i);
    } else {
      GtkGstPlayerSubtitleInfo *i = GTK_GST_PLAYER_SUBTITLE_INFO (s);
      i->info = g_object_ref (GTL_GST_PLAY_SUBTITLE_INFO (l->data));
      ret->subtitle_stream_list = g_list_append (ret->subtitle_stream_list, i);
    }
  }

  return ret;
}

GtkGstPlayerAudioInfo *
gtk_gst_player_audio_info_wrapped (GtkGstPlayAudioInfo * info)
{
  GtkGstPlayerStreamInfo *s;
  GtkGstPlayerAudioInfo *i;

  s = gtk_gst_player_stream_info_wrapped ((GtkGstPlayStreamInfo *) info);
  i = GTK_GST_PLAYER_AUDIO_INFO (s);
  i->info = g_object_ref (info);
  return i;
}

GtkGstPlayerVideoInfo *
gtk_gst_player_video_info_wrapped (GtkGstPlayVideoInfo * info)
{
  GtkGstPlayerStreamInfo *s;
  GtkGstPlayerVideoInfo *i;

  s = gtk_gst_player_stream_info_wrapped ((GtkGstPlayStreamInfo *) info);
  i = GTK_GST_PLAYER_VIDEO_INFO (s);
  i->info = g_object_ref (info);
  return i;
}

GtkGstPlayerSubtitleInfo *
gtk_gst_player_subtitle_info_wrapped (GtkGstPlaySubtitleInfo * info)
{
  GtkGstPlayerStreamInfo *s;
  GtkGstPlayerSubtitleInfo *i;

  s = gtk_gst_player_stream_info_wrapped ((GtkGstPlayStreamInfo *) info);
  i = GTK_GST_PLAYER_SUBTITLE_INFO (s);
  i->info = g_object_ref (info);
  return i;
}

/**
 * gtk_gst_player_media_info_get_uri:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: the URI associated with #GtkGstPlayerMediaInfo.
 */
const gchar *
gtk_gst_player_media_info_get_uri (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return gtk_gst_play_media_info_get_uri (info->info);
}

/**
 * gtk_gst_player_media_info_is_seekable:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: %TRUE if the media is seekable.
 */
gboolean
gtk_gst_player_media_info_is_seekable (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), FALSE);

  return gtk_gst_play_media_info_is_seekable (info->info);
}

/**
 * gtk_gst_player_media_info_is_live:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: %TRUE if the media is live.
 */
gboolean
gtk_gst_player_media_info_is_live (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), FALSE);

  return gtk_gst_play_media_info_is_live (info->info);
}

/**
 * gtk_gst_player_media_info_get_stream_list:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayerStreamInfo): A #GList of
 * matching #GtkGstPlayerStreamInfo.
 */
GList *
gtk_gst_player_media_info_get_stream_list (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return info->stream_list;
}

/**
 * gtk_gst_player_media_info_get_video_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayerVideoInfo): A #GList of
 * matching #GtkGstPlayerVideoInfo.
 */
GList *
gtk_gst_player_media_info_get_video_streams (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return info->video_stream_list;
}

/**
 * gtk_gst_player_media_info_get_subtitle_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayerSubtitleInfo): A #GList of
 * matching #GtkGstPlayerSubtitleInfo.
 */
GList *
gtk_gst_player_media_info_get_subtitle_streams (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return info->subtitle_stream_list;
}

/**
 * gtk_gst_player_media_info_get_audio_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayerAudioInfo): A #GList of
 * matching #GtkGstPlayerAudioInfo.
 */
GList *
gtk_gst_player_media_info_get_audio_streams (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return info->audio_stream_list;
}

/**
 * gtk_gst_player_media_info_get_duration:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: duration of the media or %GST_CLOCK_TIME_NONE if unknown.
 */
GstClockTime
gtk_gst_player_media_info_get_duration (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), -1);

  return gtk_gst_play_media_info_get_duration (info->info);
}

/**
 * gtk_gst_player_media_info_get_tags:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (nullable): the tags contained in media info.
 */
GstTagList *
gtk_gst_player_media_info_get_tags (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return gtk_gst_play_media_info_get_tags (info->info);
}

/**
 * gtk_gst_player_media_info_get_title:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (nullable): the media title or %NULL if unknown.
 */
const gchar *
gtk_gst_player_media_info_get_title (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return gtk_gst_play_media_info_get_title (info->info);
}

/**
 * gtk_gst_player_media_info_get_container_format:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (nullable): the container format or %NULL if unknown.
 */
const gchar *
gtk_gst_player_media_info_get_container_format (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return gtk_gst_play_media_info_get_container_format (info->info);
}

/**
 * gtk_gst_player_media_info_get_image_sample:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Function to get the image (or preview-image) stored in taglist.
 * Application can use `gst_sample_*_()` API's to get caps, buffer etc.
 *
 * Returns: (transfer none) (nullable): GstSample or %NULL.
 */
GstSample *
gtk_gst_player_media_info_get_image_sample (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), NULL);

  return gtk_gst_play_media_info_get_image_sample (info->info);
}

/**
 * gtk_gst_player_media_info_get_number_of_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: number of total streams or 0 if unknown.
 *
 * Since: 1.12
 */
guint
gtk_gst_player_media_info_get_number_of_streams (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), 0);

  return g_list_length (info->stream_list);
}

/**
 * gtk_gst_player_media_info_get_number_of_video_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: number of video streams or 0 if unknown.
 *
 * Since: 1.12
 */
guint
gtk_gst_player_media_info_get_number_of_video_streams (const GtkGstPlayerMediaInfo *
    info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), 0);

  return g_list_length (info->video_stream_list);
}

/**
 * gtk_gst_player_media_info_get_number_of_audio_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: number of audio streams or 0 if unknown.
 *
 * Since: 1.12
 */
guint
gtk_gst_player_media_info_get_number_of_audio_streams (const GtkGstPlayerMediaInfo *
    info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), 0);

  return g_list_length (info->audio_stream_list);
}

/**
 * gtk_gst_player_media_info_get_number_of_subtitle_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: number of subtitle streams or 0 if unknown.
 *
 * Since: 1.12
 */
guint gtk_gst_player_media_info_get_number_of_subtitle_streams
    (const GtkGstPlayerMediaInfo * info)
{
  g_return_val_if_fail (GST_IS_PLAYER_MEDIA_INFO (info), 0);

  return g_list_length (info->subtitle_stream_list);
}

/**
 * gtk_gst_player_get_video_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayerVideoInfo): A #GList of
 * matching #GtkGstPlayerVideoInfo.
 */
#ifndef GST_REMOVE_DEPRECATED
GList *
gtk_gst_player_get_video_streams (const GtkGstPlayerMediaInfo * info)
{
  return gtk_gst_player_media_info_get_video_streams (info);
}
#endif

/**
 * gtk_gst_player_get_audio_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayerAudioInfo): A #GList of
 * matching #GtkGstPlayerAudioInfo.
 */
#ifndef GST_REMOVE_DEPRECATED
GList *
gtk_gst_player_get_audio_streams (const GtkGstPlayerMediaInfo * info)
{
  return gtk_gst_player_media_info_get_audio_streams (info);
}
#endif

/**
 * gtk_gst_player_get_subtitle_streams:
 * @info: a #GtkGstPlayerMediaInfo
 *
 * Returns: (transfer none) (element-type GtkGstPlayerSubtitleInfo): A #GList of
 * matching #GtkGstPlayerSubtitleInfo.
 */
#ifndef GST_REMOVE_DEPRECATED
GList *
gtk_gst_player_get_subtitle_streams (const GtkGstPlayerMediaInfo * info)
{
  return gtk_gst_player_media_info_get_subtitle_streams (info);
}
#endif
