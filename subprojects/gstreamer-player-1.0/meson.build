project('gstreamer-player-1.0', 'c',
  version : '1.25.0.1',
  meson_version : '>= 0.62',
  default_options : [ 'warning_level=1',
                      'buildtype=debugoptimized',
                      'default_library=static' ])

gst_version = meson.project_version()
version_arr = gst_version.split('.')
gst_version_major = version_arr[0].to_int()
gst_version_minor = version_arr[1].to_int()
gst_version_micro = version_arr[2].to_int()

api_version = '1.0'
soversion = 0
# maintaining compatibility with the previous libtool versioning
# current = minor * 100 + micro
curversion = gst_version_minor * 100 + gst_version_micro
libversion = '@0@.@1@.0'.format(soversion, curversion)
osxversion = curversion + 1

build_gir = false
gst_libraries = []
configinc = include_directories('.')
libsinc = include_directories('.')

gst_plugins_bad_args = ['-DGST_API_EXPORT=__attribute__((visibility("default")))']

gst_dep = dependency('gstreamer-1.0')
gstaudio_dep = dependency('gstreamer-audio-1.0')
gstbase_dep = dependency('gstreamer-base-1.0')
gstpbutils_dep = dependency('gstreamer-pbutils-1.0')
gsttag_dep = dependency('gstreamer-tag-1.0')
gstvideo_dep = dependency('gstreamer-video-1.0')

pkgconfig = import('pkgconfig')
pkgconfig_subdirs = ['gstreamer-1.0']
pkgconfig_variables = ['exec_prefix=${prefix}',
    'toolsdir=${exec_prefix}/bin',
    'pluginsdir=${libdir}/gstreamer-1.0',
    'datarootdir=${prefix}/share',
    'girdir=${datadir}/gir-1.0',
    'typelibdir=${libdir}/girepository-1.0']

subdir('gst/play')
subdir('gst/player')
