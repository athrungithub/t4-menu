project(
  't4-menu',
  'c',
  license: 'MIT',
  )

gtk = dependency('gtk+-3.0')
wlroots = dependency('wlroots', required: false)
wayland_client_dep = dependency('wayland-client', required: false)
wayland_protos = dependency('wayland-protocols', required: false)
wayland_scanner_dep = dependency('wayland-scanner', required: false, native: true)

src_files = [
  't4.c',
  'desktop.c',
  ]

r = run_command('git', 'describe', '--tags')
version = r.stdout().strip()
charver = '-DVERSION="'+version+'"'
add_global_arguments(charver, language: 'c')

r1 = run_command('date', '+%Y.%m.%d')
date = r1.stdout().strip()
charver = '-DBUILDDATE="'+date+'"'
add_global_arguments(charver, language: 'c')

executable(
  't4',
  files(src_files),
  dependencies: [
    gtk,
    wlroots,
    wayland_client_dep,
    wayland_protos,
    ],
  install: true,
  )
