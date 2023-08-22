testexecdir = join_paths(installed_test_bindir, 'gdk')
testdatadir = join_paths(installed_test_datadir, 'gdk')

clipboard_client = executable('clipboard-client',
  sources: ['clipboard-client.c'],
  include_directories: [confinc],
  c_args: common_cflags,
  dependencies: [ libgtk_dep ],
  install: get_option('install-tests'),
  install_dir: testexecdir
)

tests = [
  { 'name': 'array' },
  { 'name': 'cairo' },
  { 'name': 'clipboard', 'parallel': false, 'suites': 'flaky' },
  { 'name': 'colorstate' },
  { 'name': 'contentformats' },
  { 'name': 'contentserializer' },
  { 'name': 'cursor' },
  { 'name': 'displaymanager' },
  { 'name': 'glcontext' },
  { 'name': 'keysyms' },
  { 'name': 'memorytexture', 'sources': [ 'gdktestutils.c' ] },
  { 'name': 'rectangle' },
  { 'name': 'rgba' },
  { 'name': 'seat' },
  { 'name': 'texture-threads' },
  { 'name': 'toplevellayout' },
  { 'name': 'popuplayout' },
]

if x11_enabled
  tests += [
    { 'name': 'display' },
    { 'name': 'encoding' },
  ]
endif

if os_linux
  tests += [
    { 'name': 'dmabuf-support',
      'sources': [ 'udmabuf.c' ],
      # This needs to pass on upstream Gitlab-CI, but cannot be guaranteed
      # to work on developer machines or downstream build environments
      'suites': [ 'needs-udmabuf' ],
    },
  ]
endif

foreach t : tests
  test_name = t.get('name')
  test_exe = executable(test_name,
    sources: [ '@0@.c'.format(test_name) ] + t.get('sources', []),
    c_args: common_cflags,
    dependencies: libgtk_dep,
    install: get_option('install-tests'),
    install_dir: testexecdir,
  )

  suites = ['gdk'] + t.get('suites', [])

  test(test_name, test_exe,
    args: [ '--tap', '-k' ],
    protocol: 'tap',
    is_parallel: t.get('parallel', false),
    env: [
      'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
      'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir()),
      'DBUS_SESSION_BUS_ADDRESS=',
    ],
    suite: suites,
  )
endforeach

internal_tests = [
  { 'name': 'colorstate-internal' },
  { 'name': 'dihedral' },
  { 'name': 'image' },
  { 'name': 'texture' },
  { 'name': 'gltexture' },
  { 'name': 'subsurface' },
  { 'name': 'memoryformat' },
]

if os_linux
  internal_tests += { 'name': 'dmabufformats' }
  internal_tests += { 'name': 'dmabuftexture', 'suites': 'failing' }
endif


foreach t : internal_tests
  test_name = t.get('name')
  test_exe = executable(test_name,
    sources: '@0@.c'.format(test_name),
    c_args: common_cflags + ['-DGTK_COMPILATION'],
    dependencies: libgtk_static_dep,
    install: get_option('install-tests'),
    install_dir: testexecdir,
  )

  suites = ['gdk'] + t.get('suites', [])

  if host_machine.endian() == 'big' and t.get('name') == 'gltexture'
    suites += 'failing'
  endif

  test(test_name, test_exe,
    args: [ '--tap', '-k' ],
    protocol: 'tap',
    env: [
      'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
      'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir()),
      'DBUS_SESSION_BUS_ADDRESS=',
    ],
    suite: suites,
  )
endforeach


if get_option('install-tests')
  foreach t : tests
    test_name = t.get('name')
    suites = t.get('suites', [])

    if suites.contains('flaky') or suites.contains('failing')
      continue
    endif

    test_cdata = configuration_data()
    test_cdata.set('testexecdir', testexecdir)
    test_cdata.set('test', test_name)
    configure_file(input: 'gdk.test.in',
      output: '@0@.test'.format(test_name),
      configuration: test_cdata,
      install: true,
      install_dir: testdatadir,
    )
  endforeach

  install_subdir('clipboard-data', install_dir: testexecdir)
  install_subdir('image-data', install_dir: testexecdir)
endif
