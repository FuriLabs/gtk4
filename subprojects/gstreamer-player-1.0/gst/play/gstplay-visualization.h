/* GStreamer
 *
 * Copyright (C) 2014-2015 Sebastian Dröge <sebastian@centricular.com>
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

#ifndef __GTL_GST_PLAY_VISUALIZATION_H__
#define __GTL_GST_PLAY_VISUALIZATION_H__

#include <gst/gst.h>
#include <gst/play/play-prelude.h>

G_BEGIN_DECLS

typedef struct _GstPlayVisualization GtkGstPlayVisualization;
/**
 * GtkGstPlayVisualization:
 * @name: name of the visualization.
 * @description: description of the visualization.
 *
 * A #GtkGstPlayVisualization descriptor.
 * Since: 1.20
 */
struct _GstPlayVisualization {
  gchar *name;
  gchar *description;
};

GTL_GST_PLAY_API
GType                     gtk_gst_play_visualization_get_type (void);

GTL_GST_PLAY_API
GtkGstPlayVisualization *  gtk_gst_play_visualization_copy  (const GtkGstPlayVisualization *vis);

GTL_GST_PLAY_API
void                      gtk_gst_play_visualization_free  (GtkGstPlayVisualization *vis);

GTL_GST_PLAY_API
GtkGstPlayVisualization ** gtk_gst_play_visualizations_get  (void);

GTL_GST_PLAY_API
void                      gtk_gst_play_visualizations_free (GtkGstPlayVisualization **viss);

#ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGstPlayVisualization, gtk_gst_play_visualization_free)
#endif

G_END_DECLS

#endif /* __GTL_GST_PLAY_VISUALIZATION_H__ */
