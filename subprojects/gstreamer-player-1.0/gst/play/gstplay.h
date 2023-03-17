/* GStreamer
 *
 * Copyright (C) 2014-2015 Sebastian Dröge <sebastian@centricular.com>
 * Copyright (C) 2019-2020 Stephan Hesse <stephan@emliri.com>
 * Copyright (C) 2020 Philippe Normand <philn@igalia.com>
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

#ifndef __GTL_GST_PLAY_H__
#define __GTL_GST_PLAY_H__

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/play/play-prelude.h>
#include <gst/play/gstplay-types.h>
#include <gst/play/gstplay-video-renderer.h>
#include <gst/play/gstplay-media-info.h>

G_BEGIN_DECLS

GTL_GST_PLAY_API
GType        gtk_gst_play_state_get_type                (void);

/**
 * GST_TYPE_PLAY_STATE:
 * Since: 1.20
 */
#define      GST_TYPE_PLAY_STATE                    (gtk_gst_play_state_get_type ())

GTL_GST_PLAY_API
GType        gtk_gst_play_message_get_type              (void);

/**
 * GST_TYPE_PLAY_MESSAGE:
 * Since: 1.20
 */
#define      GST_TYPE_PLAY_MESSAGE                  (gtk_gst_play_message_get_type ())

/**
 * GtkGstPlayState:
 * @GTL_GST_PLAY_STATE_STOPPED: the play is stopped.
 * @GTL_GST_PLAY_STATE_BUFFERING: the play is buffering.
 * @GTL_GST_PLAY_STATE_PAUSED: the play is paused.
 * @GTL_GST_PLAY_STATE_PLAYING: the play is currently playing a
 * stream.
 *
 * Since: 1.20
 */
typedef enum
{
  GTL_GST_PLAY_STATE_STOPPED,
  GTL_GST_PLAY_STATE_BUFFERING,
  GTL_GST_PLAY_STATE_PAUSED,
  GTL_GST_PLAY_STATE_PLAYING
} GtkGstPlayState;

/**
 * GtkGstPlayMessage:
 * @GTL_GST_PLAY_MESSAGE_URI_LOADED: Source element was initalized for set URI
 * @GTL_GST_PLAY_MESSAGE_POSITION_UPDATED: Sink position changed
 * @GTL_GST_PLAY_MESSAGE_DURATION_CHANGED: Duration of stream changed
 * @GTL_GST_PLAY_MESSAGE_STATE_CHANGED: State changed, see #GtkGstPlayState
 * @GTL_GST_PLAY_MESSAGE_BUFFERING: Pipeline is in buffering state, message contains the percentage value of the decoding buffer
 * @GTL_GST_PLAY_MESSAGE_END_OF_STREAM: Sink has received EOS
 * @GTL_GST_PLAY_MESSAGE_ERROR: Message contains an error
 * @GTL_GST_PLAY_MESSAGE_WARNING: Message contains an error
 * @GTL_GST_PLAY_MESSAGE_VIDEO_DIMENSIONS_CHANGED: Video sink received format in different dimensions than before
 * @GTL_GST_PLAY_MESSAGE_MEDIA_INFO_UPDATED: A media-info property has changed, message contains current #GtkGstPlayMediaInfo
 * @GTL_GST_PLAY_MESSAGE_VOLUME_CHANGED: The volume of the audio ouput has changed
 * @GTL_GST_PLAY_MESSAGE_MUTE_CHANGED: Audio muting flag has been toggled
 * @GTL_GST_PLAY_MESSAGE_SEEK_DONE: Any pending seeking operation has been completed
 *
 * Since: 1.20
 *
 * Types of messages that will be posted on the play API bus.
 *
 * See also #gtk_gst_play_get_message_bus()
 *
 */
typedef enum
{
  GTL_GST_PLAY_MESSAGE_URI_LOADED,
  GTL_GST_PLAY_MESSAGE_POSITION_UPDATED,
  GTL_GST_PLAY_MESSAGE_DURATION_CHANGED,
  GTL_GST_PLAY_MESSAGE_STATE_CHANGED,
  GTL_GST_PLAY_MESSAGE_BUFFERING,
  GTL_GST_PLAY_MESSAGE_END_OF_STREAM,
  GTL_GST_PLAY_MESSAGE_ERROR,
  GTL_GST_PLAY_MESSAGE_WARNING,
  GTL_GST_PLAY_MESSAGE_VIDEO_DIMENSIONS_CHANGED,
  GTL_GST_PLAY_MESSAGE_MEDIA_INFO_UPDATED,
  GTL_GST_PLAY_MESSAGE_VOLUME_CHANGED,
  GTL_GST_PLAY_MESSAGE_MUTE_CHANGED,
  GTL_GST_PLAY_MESSAGE_SEEK_DONE
} GtkGstPlayMessage;

GTL_GST_PLAY_API
const gchar *gtk_gst_play_state_get_name                (GtkGstPlayState state);

GTL_GST_PLAY_API
const gchar *gtk_gst_play_message_get_name              (GtkGstPlayMessage message_type);

GTL_GST_PLAY_API
GQuark       gtk_gst_play_error_quark                   (void);

GTL_GST_PLAY_API
GType        gtk_gst_play_error_get_type                (void);

/**
 * GTL_GST_PLAY_ERROR:
 *
 * Since: 1.20
 */
#define      GTL_GST_PLAY_ERROR                         (gtk_gst_play_error_quark ())

/**
 * GST_TYPE_PLAY_ERROR:
 *
 * Since: 1.20
 */
#define      GST_TYPE_PLAY_ERROR                    (gtk_gst_play_error_get_type ())

/**
 * GtkGstPlayError:
 * @GTL_GST_PLAY_ERROR_FAILED: generic error.
 *
 * Since: 1.20
 */
typedef enum {
  GTL_GST_PLAY_ERROR_FAILED = 0
} GtkGstPlayError;

GTL_GST_PLAY_API
const gchar *gtk_gst_play_error_get_name                (GtkGstPlayError error);

GTL_GST_PLAY_API
GType gtk_gst_play_color_balance_type_get_type          (void);

/**
 * GST_TYPE_PLAY_COLOR_BALANCE_TYPE:
 *
 * Since: 1.20
 */
#define GST_TYPE_PLAY_COLOR_BALANCE_TYPE            (gtk_gst_play_color_balance_type_get_type ())

/**
 * GtkGstPlayColorBalanceType:
 * @GTL_GST_PLAY_COLOR_BALANCE_BRIGHTNESS: brightness or black level.
 * @GTL_GST_PLAY_COLOR_BALANCE_CONTRAST: contrast or luma gain.
 * @GTL_GST_PLAY_COLOR_BALANCE_SATURATION: color saturation or chroma
 * gain.
 * @GTL_GST_PLAY_COLOR_BALANCE_HUE: hue or color balance.
 *
 * Since: 1.20
 */
typedef enum
{
  GTL_GST_PLAY_COLOR_BALANCE_BRIGHTNESS,
  GTL_GST_PLAY_COLOR_BALANCE_CONTRAST,
  GTL_GST_PLAY_COLOR_BALANCE_SATURATION,
  GTL_GST_PLAY_COLOR_BALANCE_HUE,
} GtkGstPlayColorBalanceType;

GTL_GST_PLAY_API
const gchar *gtk_gst_play_color_balance_type_get_name   (GtkGstPlayColorBalanceType type);

#define GST_TYPE_PLAY             (gtk_gst_play_get_type ())
#define GST_IS_PLAY(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_PLAY))
#define GST_IS_PLAY_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_PLAY))
#define GTL_GST_PLAY_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_PLAY, GtkGstPlayClass))
#define GST_PLAY(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_PLAY, GtkGstPlay))
#define GTL_GST_PLAY_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_PLAY, GtkGstPlayClass))

/**
 * GTL_GST_PLAY_CAST:
 * Since: 1.20
 */
#define GTL_GST_PLAY_CAST(obj)        ((GtkGstPlay*)(obj))

#ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGstPlay, gst_object_unref)
#endif

GTL_GST_PLAY_API
GType        gtk_gst_play_get_type                      (void);

GTL_GST_PLAY_API
GtkGstPlay *    gtk_gst_play_new                           (GtkGstPlayVideoRenderer * video_renderer);

GTL_GST_PLAY_API
GstBus *     gtk_gst_play_get_message_bus               (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_play                          (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_pause                         (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_stop                          (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_seek                          (GtkGstPlay    * play,
                                                     GstClockTime   position);

GTL_GST_PLAY_API
void         gtk_gst_play_set_rate                      (GtkGstPlay    * play,
                                                     gdouble        rate);

GTL_GST_PLAY_API
gdouble      gtk_gst_play_get_rate                      (GtkGstPlay    * play);

GTL_GST_PLAY_API
gchar *      gtk_gst_play_get_uri                       (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_uri                       (GtkGstPlay    * play,
                                                     const gchar  * uri);

GTL_GST_PLAY_API
gchar *      gtk_gst_play_get_subtitle_uri              (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_subtitle_uri              (GtkGstPlay    * play,
                                                     const gchar *uri);

GTL_GST_PLAY_API
GstClockTime gtk_gst_play_get_position                  (GtkGstPlay    * play);

GTL_GST_PLAY_API
GstClockTime gtk_gst_play_get_duration                  (GtkGstPlay    * play);

GTL_GST_PLAY_API
gdouble      gtk_gst_play_get_volume                    (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_volume                    (GtkGstPlay    * play,
                                                     gdouble        val);

GTL_GST_PLAY_API
gboolean     gtk_gst_play_get_mute                      (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_mute                      (GtkGstPlay    * play,
                                                     gboolean       val);

GTL_GST_PLAY_API
GstElement * gtk_gst_play_get_pipeline                  (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_video_track_enabled       (GtkGstPlay    * play,
                                                     gboolean enabled);

GTL_GST_PLAY_API
void         gtk_gst_play_set_audio_track_enabled       (GtkGstPlay    * play,
                                                     gboolean enabled);

GTL_GST_PLAY_API
void         gtk_gst_play_set_subtitle_track_enabled    (GtkGstPlay    * play,
                                                     gboolean enabled);

GTL_GST_PLAY_API
gboolean     gtk_gst_play_set_audio_track               (GtkGstPlay    *play,
                                                     gint stream_index);

GTL_GST_PLAY_API
gboolean     gtk_gst_play_set_video_track               (GtkGstPlay    *play,
                                                     gint stream_index);

GTL_GST_PLAY_API
gboolean     gtk_gst_play_set_subtitle_track            (GtkGstPlay    *play,
                                                     gint stream_index);

GTL_GST_PLAY_API
GtkGstPlayMediaInfo *    gtk_gst_play_get_media_info     (GtkGstPlay * play);

GTL_GST_PLAY_API
GtkGstPlayAudioInfo *    gtk_gst_play_get_current_audio_track (GtkGstPlay * play);

GTL_GST_PLAY_API
GtkGstPlayVideoInfo *    gtk_gst_play_get_current_video_track (GtkGstPlay * play);

GTL_GST_PLAY_API
GtkGstPlaySubtitleInfo * gtk_gst_play_get_current_subtitle_track (GtkGstPlay * play);

GTL_GST_PLAY_API
gboolean     gtk_gst_play_set_visualization             (GtkGstPlay    * play,
                                                     const gchar *name);

GTL_GST_PLAY_API
void         gtk_gst_play_set_visualization_enabled     (GtkGstPlay    * play,
                                                     gboolean enabled);

GTL_GST_PLAY_API
gchar *      gtk_gst_play_get_current_visualization     (GtkGstPlay    * play);

GTL_GST_PLAY_API
gboolean     gtk_gst_play_has_color_balance             (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_color_balance             (GtkGstPlay    * play,
                                                     GtkGstPlayColorBalanceType type,
                                                     gdouble value);

GTL_GST_PLAY_API
gdouble      gtk_gst_play_get_color_balance             (GtkGstPlay    * play,
                                                     GtkGstPlayColorBalanceType type);


GTL_GST_PLAY_API
GstVideoMultiviewFramePacking gtk_gst_play_get_multiview_mode (GtkGstPlay    * play);

GTL_GST_PLAY_API
void                     gtk_gst_play_set_multiview_mode (GtkGstPlay    * play,
                                                      GstVideoMultiviewFramePacking mode);

GTL_GST_PLAY_API
GstVideoMultiviewFlags  gtk_gst_play_get_multiview_flags  (GtkGstPlay  * play);

GTL_GST_PLAY_API
void                    gtk_gst_play_set_multiview_flags  (GtkGstPlay  * play,
                                                       GstVideoMultiviewFlags flags);

GTL_GST_PLAY_API
gint64       gtk_gst_play_get_audio_video_offset        (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_audio_video_offset        (GtkGstPlay    * play,
                                                     gint64 offset);

GTL_GST_PLAY_API
gint64       gtk_gst_play_get_subtitle_video_offset        (GtkGstPlay    * play);

GTL_GST_PLAY_API
void         gtk_gst_play_set_subtitle_video_offset        (GtkGstPlay    * play,
                                                        gint64 offset);

GTL_GST_PLAY_API
gboolean       gtk_gst_play_set_config                  (GtkGstPlay * play,
                                                     GstStructure * config);

GTL_GST_PLAY_API
GstStructure * gtk_gst_play_get_config                  (GtkGstPlay * play);

/* helpers for configuring the config structure */

GTL_GST_PLAY_API
void           gtk_gst_play_config_set_user_agent       (GstStructure * config,
                                                     const gchar * agent);

GTL_GST_PLAY_API
gchar *        gtk_gst_play_config_get_user_agent       (const GstStructure * config);

GTL_GST_PLAY_API
void           gtk_gst_play_config_set_position_update_interval  (GstStructure * config,
                                                              guint          interval);

GTL_GST_PLAY_API
guint          gtk_gst_play_config_get_position_update_interval  (const GstStructure * config);

GTL_GST_PLAY_API
void           gtk_gst_play_config_set_seek_accurate (GstStructure * config, gboolean accurate);

GTL_GST_PLAY_API
gboolean       gtk_gst_play_config_get_seek_accurate (const GstStructure * config);

/**
 * GtkGstPlaySnapshotFormat:
 * @GTL_GST_PLAY_THUMBNAIL_RAW_NATIVE: raw native format.
 * @GTL_GST_PLAY_THUMBNAIL_RAW_xRGB: raw xRGB format.
 * @GTL_GST_PLAY_THUMBNAIL_RAW_BGRx: raw BGRx format.
 * @GTL_GST_PLAY_THUMBNAIL_JPG: jpeg format.
 * @GTL_GST_PLAY_THUMBNAIL_PNG: png format.
 *
 * Since: 1.20
 */
typedef enum
{
  GTL_GST_PLAY_THUMBNAIL_RAW_NATIVE = 0,
  GTL_GST_PLAY_THUMBNAIL_RAW_xRGB,
  GTL_GST_PLAY_THUMBNAIL_RAW_BGRx,
  GTL_GST_PLAY_THUMBNAIL_JPG,
  GTL_GST_PLAY_THUMBNAIL_PNG
} GtkGstPlaySnapshotFormat;

GTL_GST_PLAY_API
GstSample * gtk_gst_play_get_video_snapshot (GtkGstPlay * play,
    GtkGstPlaySnapshotFormat format, const GstStructure * config);

GTL_GST_PLAY_API
gboolean       gtk_gst_play_is_play_message                        (GstMessage *msg);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_type                       (GstMessage *msg, GtkGstPlayMessage *type);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_duration_updated           (GstMessage *msg, GstClockTime *duration);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_position_updated           (GstMessage *msg, GstClockTime *position);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_state_changed              (GstMessage *msg, GtkGstPlayState *state);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_buffering_percent          (GstMessage *msg, guint *percent);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_error                      (GstMessage *msg, GError **error, GstStructure **details);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_warning                    (GstMessage *msg, GError **error, GstStructure **details);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_video_dimensions_changed   (GstMessage *msg, guint *width, guint *height);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_media_info_updated         (GstMessage *msg, GtkGstPlayMediaInfo **info);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_volume_changed             (GstMessage *msg, gdouble *volume);

GTL_GST_PLAY_API
void           gtk_gst_play_message_parse_muted_changed              (GstMessage *msg, gboolean *muted);

G_END_DECLS

#endif /* __GTL_GST_PLAY_H__ */
