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

#ifndef __GTK_GST_PLAYER_H__
#define __GTK_GST_PLAYER_H__

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/player/player-prelude.h>
#include <gst/player/gstplayer-types.h>
#include <gst/player/gstplayer-signal-dispatcher.h>
#include <gst/player/gstplayer-video-renderer.h>
#include <gst/player/gstplayer-media-info.h>

G_BEGIN_DECLS

GTK_GST_PLAYER_API
GType        gtk_gst_player_state_get_type                (void);
#define      GST_TYPE_PLAYER_STATE                    (gtk_gst_player_state_get_type ())

/**
 * GtkGstPlayerState:
 * @GTK_GST_PLAYER_STATE_STOPPED: the player is stopped.
 * @GTK_GST_PLAYER_STATE_BUFFERING: the player is buffering.
 * @GTK_GST_PLAYER_STATE_PAUSED: the player is paused.
 * @GTK_GST_PLAYER_STATE_PLAYING: the player is currently playing a
 * stream.
 */
typedef enum
{
  GTK_GST_PLAYER_STATE_STOPPED,
  GTK_GST_PLAYER_STATE_BUFFERING,
  GTK_GST_PLAYER_STATE_PAUSED,
  GTK_GST_PLAYER_STATE_PLAYING
} GtkGstPlayerState;

GTK_GST_PLAYER_API
const gchar *gtk_gst_player_state_get_name                (GtkGstPlayerState state);

GTK_GST_PLAYER_API
GQuark       gtk_gst_player_error_quark                   (void);

GTK_GST_PLAYER_API
GType        gtk_gst_player_error_get_type                (void);
#define      GTK_GST_PLAYER_ERROR                         (gtk_gst_player_error_quark ())
#define      GST_TYPE_PLAYER_ERROR                    (gtk_gst_player_error_get_type ())

/**
 * GtkGstPlayerError:
 * @GTK_GST_PLAYER_ERROR_FAILED: generic error.
 */
typedef enum {
  GTK_GST_PLAYER_ERROR_FAILED = 0
} GtkGstPlayerError;

GTK_GST_PLAYER_API
const gchar *gtk_gst_player_error_get_name                (GtkGstPlayerError error);

GTK_GST_PLAYER_API
GType gtk_gst_player_color_balance_type_get_type          (void);
#define GST_TYPE_PLAYER_COLOR_BALANCE_TYPE            (gtk_gst_player_color_balance_type_get_type ())

/**
 * GtkGstPlayerColorBalanceType:
 * @GTK_GST_PLAYER_COLOR_BALANCE_BRIGHTNESS: brightness or black level.
 * @GTK_GST_PLAYER_COLOR_BALANCE_CONTRAST: contrast or luma gain.
 * @GTK_GST_PLAYER_COLOR_BALANCE_SATURATION: color saturation or chroma
 * gain.
 * @GTK_GST_PLAYER_COLOR_BALANCE_HUE: hue or color balance.
 */
typedef enum
{
  GTK_GST_PLAYER_COLOR_BALANCE_BRIGHTNESS,
  GTK_GST_PLAYER_COLOR_BALANCE_CONTRAST,
  GTK_GST_PLAYER_COLOR_BALANCE_SATURATION,
  GTK_GST_PLAYER_COLOR_BALANCE_HUE,
} GtkGstPlayerColorBalanceType;

GTK_GST_PLAYER_API
const gchar *gtk_gst_player_color_balance_type_get_name   (GtkGstPlayerColorBalanceType type);

#define GST_TYPE_PLAYER             (gtk_gst_player_get_type ())
#define GST_IS_PLAYER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_PLAYER))
#define GST_IS_PLAYER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_PLAYER))
#define GTK_GST_PLAYER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_PLAYER, GtkGstPlayerClass))
#define GST_PLAYER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_PLAYER, GtkGstPlayer))
#define GTK_GST_PLAYER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_PLAYER, GtkGstPlayerClass))
#define GTK_GST_PLAYER_CAST(obj)        ((GtkGstPlayer*)(obj))

#ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGstPlayer, gst_object_unref)
#endif

GTK_GST_PLAYER_API
GType        gtk_gst_player_get_type                      (void);

GTK_GST_PLAYER_API
GtkGstPlayer *  gtk_gst_player_new                           (GtkGstPlayerVideoRenderer * video_renderer, GtkGstPlayerSignalDispatcher * signal_dispatcher);

GTK_GST_PLAYER_API
void         gtk_gst_player_play                          (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_pause                         (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_stop                          (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_seek                          (GtkGstPlayer    * player,
                                                       GstClockTime   position);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_rate                      (GtkGstPlayer    * player,
                                                       gdouble        rate);

GTK_GST_PLAYER_API
gdouble      gtk_gst_player_get_rate                      (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
gchar *      gtk_gst_player_get_uri                       (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_uri                       (GtkGstPlayer    * player,
                                                       const gchar  * uri);

GTK_GST_PLAYER_API
gchar *      gtk_gst_player_get_subtitle_uri              (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_subtitle_uri              (GtkGstPlayer    * player,
                                                       const gchar *uri);

GTK_GST_PLAYER_API
GstClockTime gtk_gst_player_get_position                  (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
GstClockTime gtk_gst_player_get_duration                  (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
gdouble      gtk_gst_player_get_volume                    (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_volume                    (GtkGstPlayer    * player,
                                                       gdouble        val);

GTK_GST_PLAYER_API
gboolean     gtk_gst_player_get_mute                      (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_mute                      (GtkGstPlayer    * player,
                                                       gboolean       val);

GTK_GST_PLAYER_API
GstElement * gtk_gst_player_get_pipeline                  (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_video_track_enabled       (GtkGstPlayer    * player,
                                                       gboolean enabled);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_audio_track_enabled       (GtkGstPlayer    * player,
                                                       gboolean enabled);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_subtitle_track_enabled    (GtkGstPlayer    * player,
                                                       gboolean enabled);

GTK_GST_PLAYER_API
gboolean     gtk_gst_player_set_audio_track               (GtkGstPlayer    *player,
                                                       gint stream_index);

GTK_GST_PLAYER_API
gboolean     gtk_gst_player_set_video_track               (GtkGstPlayer    *player,
                                                       gint stream_index);

GTK_GST_PLAYER_API
gboolean     gtk_gst_player_set_subtitle_track            (GtkGstPlayer    *player,
                                                       gint stream_index);

GTK_GST_PLAYER_API
GtkGstPlayerMediaInfo *    gtk_gst_player_get_media_info     (GtkGstPlayer * player);

GTK_GST_PLAYER_API
GtkGstPlayerAudioInfo *    gtk_gst_player_get_current_audio_track (GtkGstPlayer * player);

GTK_GST_PLAYER_API
GtkGstPlayerVideoInfo *    gtk_gst_player_get_current_video_track (GtkGstPlayer * player);

GTK_GST_PLAYER_API
GtkGstPlayerSubtitleInfo * gtk_gst_player_get_current_subtitle_track (GtkGstPlayer * player);

GTK_GST_PLAYER_API
gboolean     gtk_gst_player_set_visualization             (GtkGstPlayer    * player,
                                                       const gchar *name);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_visualization_enabled     (GtkGstPlayer    * player,
                                                       gboolean enabled);

GTK_GST_PLAYER_API
gchar *      gtk_gst_player_get_current_visualization     (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
gboolean     gtk_gst_player_has_color_balance             (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_color_balance             (GtkGstPlayer    * player,
                                                       GtkGstPlayerColorBalanceType type,
                                                       gdouble value);

GTK_GST_PLAYER_API
gdouble      gtk_gst_player_get_color_balance             (GtkGstPlayer    * player,
                                                       GtkGstPlayerColorBalanceType type);


GTK_GST_PLAYER_API
GstVideoMultiviewFramePacking gtk_gst_player_get_multiview_mode (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void                     gtk_gst_player_set_multiview_mode (GtkGstPlayer    * player,
                                                        GstVideoMultiviewFramePacking mode);

GTK_GST_PLAYER_API
GstVideoMultiviewFlags  gtk_gst_player_get_multiview_flags  (GtkGstPlayer  * player);

GTK_GST_PLAYER_API
void                    gtk_gst_player_set_multiview_flags  (GtkGstPlayer  * player,
                                                         GstVideoMultiviewFlags flags);

GTK_GST_PLAYER_API
gint64       gtk_gst_player_get_audio_video_offset        (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_audio_video_offset        (GtkGstPlayer    * player,
                                                       gint64 offset);

GTK_GST_PLAYER_API
gint64       gtk_gst_player_get_subtitle_video_offset        (GtkGstPlayer    * player);

GTK_GST_PLAYER_API
void         gtk_gst_player_set_subtitle_video_offset        (GtkGstPlayer    * player,
                                                          gint64 offset);

GTK_GST_PLAYER_API
gboolean       gtk_gst_player_set_config                  (GtkGstPlayer * player,
                                                       GstStructure * config);

GTK_GST_PLAYER_API
GstStructure * gtk_gst_player_get_config                  (GtkGstPlayer * player);

/* helpers for configuring the config structure */

GTK_GST_PLAYER_API
void           gtk_gst_player_config_set_user_agent       (GstStructure * config,
                                                       const gchar * agent);

GTK_GST_PLAYER_API
gchar *        gtk_gst_player_config_get_user_agent       (const GstStructure * config);

GTK_GST_PLAYER_API
void           gtk_gst_player_config_set_position_update_interval  (GstStructure * config,
                                                                guint          interval);

GTK_GST_PLAYER_API
guint          gtk_gst_player_config_get_position_update_interval  (const GstStructure * config);

GTK_GST_PLAYER_API
void           gtk_gst_player_config_set_seek_accurate (GstStructure * config, gboolean accurate);

GTK_GST_PLAYER_API
gboolean       gtk_gst_player_config_get_seek_accurate (const GstStructure * config);

typedef enum
{
  GTK_GST_PLAYER_THUMBNAIL_RAW_NATIVE = 0,
  GTK_GST_PLAYER_THUMBNAIL_RAW_xRGB,
  GTK_GST_PLAYER_THUMBNAIL_RAW_BGRx,
  GTK_GST_PLAYER_THUMBNAIL_JPG,
  GTK_GST_PLAYER_THUMBNAIL_PNG
} GtkGstPlayerSnapshotFormat;

GTK_GST_PLAYER_API
GstSample * gtk_gst_player_get_video_snapshot (GtkGstPlayer * player,
    GtkGstPlayerSnapshotFormat format, const GstStructure * config);

G_END_DECLS

#endif /* __GTK_GST_PLAYER_H__ */
