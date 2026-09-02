/* gdkvulkancontext-wayland.h
 *
 * gdkvulkancontext-wayland.h: Wayland specific Vulkan wrappers
 *
 * Copyright (C) 2017 Georges Basile Stavracas Neto <georges.stavracas@gmail.com>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "gdkconfig.h"

#ifdef GDK_RENDERING_VULKAN

#define VK_USE_PLATFORM_WAYLAND_KHR

#include "gdkvulkancontextprivate.h"

G_BEGIN_DECLS

#define GDK_TYPE_WAYLAND_VULKAN_CONTEXT		(gdk_wayland_vulkan_context_get_type ())
GDK_DECLARE_INTERNAL_TYPE (GdkWaylandVulkanContext, gdk_wayland_vulkan_context, GDK, WAYLAND_VULKAN_CONTEXT, GdkVulkanContext)

struct _GdkWaylandVulkanContext
{
  GdkVulkanContext parent_instance;
};

struct _GdkWaylandVulkanContextClass
{
  GdkVulkanContextClass parent_class;
};

G_END_DECLS

#endif /* !GDK_RENDERING_VULKAN */
