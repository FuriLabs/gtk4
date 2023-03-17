/* GStreamer
 *
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/play/gstplay-video-renderer.h>

#include "gstplayer-wrapped-video-renderer-private.h"
#include "gstplayer.h"
#include "gstplayer-video-renderer-private.h"

/*
 * This object is an internal wrapper created by the GtkGstPlayer, implementing the
 * new GtkGstPlayVideoRenderer interface and acting as a bridge from the legacy
 * GtkGstPlayerVideoRenderer interface.
 */

struct _GtkGstPlayerWrappedVideoRenderer
{
  GObject parent;

  GtkGstPlayerVideoRenderer *renderer;
  GtkGstPlayer *player;
};

struct _GtkGstPlayerWrappedVideoRendererClass
{
  GObjectClass parent_class;
};

static void
    gtk_gst_player_wrapped_video_renderer_interface_init
    (GtkGstPlayVideoRendererInterface * iface);

G_DEFINE_TYPE_WITH_CODE (GtkGstPlayerWrappedVideoRenderer,
    gtk_gst_player_wrapped_video_renderer, G_TYPE_OBJECT,
    G_IMPLEMENT_INTERFACE (GST_TYPE_PLAY_VIDEO_RENDERER,
        gtk_gst_player_wrapped_video_renderer_interface_init));

static void
gtk_gst_player_wrapped_video_renderer_finalize (GObject * object)
{
  GtkGstPlayerWrappedVideoRenderer *self =
      GTK_GST_PLAYER_WRAPPED_VIDEO_RENDERER (object);

  g_clear_object (&self->renderer);

  G_OBJECT_CLASS
      (gtk_gst_player_wrapped_video_renderer_parent_class)->finalize (object);
}

static void
gtk_gst_player_wrapped_video_renderer_class_init (GtkGstPlayerWrappedVideoRendererClass
    * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = gtk_gst_player_wrapped_video_renderer_finalize;
}

static void
gtk_gst_player_wrapped_video_renderer_init (GtkGstPlayerWrappedVideoRenderer * self)
{
}

static GstElement *
gtk_gst_player_wrapped_video_renderer_create_video_sink (GtkGstPlayVideoRenderer *
    iface, GtkGstPlay * player)
{
  GtkGstPlayerWrappedVideoRenderer *self =
      GTK_GST_PLAYER_WRAPPED_VIDEO_RENDERER (iface);

  return gtk_gst_player_video_renderer_create_video_sink (self->renderer,
      self->player);
}

static void
gtk_gst_player_wrapped_video_renderer_interface_init (GtkGstPlayVideoRendererInterface
    * iface)
{
  iface->create_video_sink =
      gtk_gst_player_wrapped_video_renderer_create_video_sink;
}

GtkGstPlayerVideoRenderer *
gtk_gst_player_wrapped_video_renderer_new (GtkGstPlayerVideoRenderer * renderer,
    GtkGstPlayer * player)
{
  GtkGstPlayerWrappedVideoRenderer *self =
      g_object_new (GST_TYPE_PLAYER_WRAPPED_VIDEO_RENDERER,
      NULL);
  self->renderer = g_object_ref (renderer);
  self->player = player;
  return (GtkGstPlayerVideoRenderer *) self;
}
