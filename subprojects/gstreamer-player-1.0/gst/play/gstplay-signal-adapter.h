/* GStreamer
 *
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

#ifndef __GTL_GST_PLAY_SIGNAL_ADAPTER_H__
#define __GTL_GST_PLAY_SIGNAL_ADAPTER_H__

#include <gst/play/gstplay-types.h>

G_BEGIN_DECLS

#define GST_TYPE_PLAY_SIGNAL_ADAPTER             (gtk_gst_play_signal_adapter_get_type ())
#define GST_IS_PLAY_SIGNAL_ADAPTER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_PLAY_SIGNAL_ADAPTER))
#define GST_IS_PLAY_SIGNAL_ADAPTER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_PLAY_SIGNAL_ADAPTER))
#define GTL_GST_PLAY_SIGNAL_ADAPTER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_PLAY_SIGNAL_ADAPTER, GtkGstPlaySignalAdapterClass))
#define GTL_GST_PLAY_SIGNAL_ADAPTER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_PLAY_SIGNAL_ADAPTER, GtkGstPlaySignalAdapter))
#define GTL_GST_PLAY_SIGNAL_ADAPTER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_PLAY_SIGNAL_ADAPTER, GtkGstPlaySignalAdapterClass))

/**
 * GTL_GST_PLAY_SIGNAL_ADAPTER_CAST:
 * Since: 1.20
 */
#define GTL_GST_PLAY_SIGNAL_ADAPTER_CAST(obj)        ((GtkGstPlaySignalAdapter*)(obj))

#ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGstPlaySignalAdapter, g_object_unref)
#endif

GTL_GST_PLAY_API
GType                  gtk_gst_play_signal_adapter_get_type               (void);

GTL_GST_PLAY_API
GtkGstPlaySignalAdapter * gtk_gst_play_signal_adapter_new                    (GtkGstPlay * play);

GTL_GST_PLAY_API
GtkGstPlaySignalAdapter * gtk_gst_play_signal_adapter_new_with_main_context  (GtkGstPlay * play, GMainContext * context);

GTL_GST_PLAY_API
GtkGstPlaySignalAdapter * gtk_gst_play_signal_adapter_new_sync_emit          (GtkGstPlay * play);

GTL_GST_PLAY_API
GtkGstPlay              * gtk_gst_play_signal_adapter_get_play               (GtkGstPlaySignalAdapter * adapter);

G_END_DECLS

#endif /* __GTL_GST_PLAY_SIGNAL_ADAPTER_H__ */
