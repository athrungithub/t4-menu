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

if (wlroots.found() and wayland_client_dep.found() and wayland_protos.found() and wayland_scanner_dep.found())
  add_project_arguments('-DLAYER', language: 'c')

  src_files += ['layer.c', 'layer.h']

  wl_protocol_dir = wayland_protos.get_pkgconfig_variable('pkgdatadir')

  wayland_scanner = find_program(
  wayland_scanner_dep.get_pkgconfig_variable('wayland_scanner'),
  native: true,
  )

  protocols = [
    [wl_protocol_dir, 'stable/xdg-shell/xdg-shell.xml'],
    'wlr-layer-shell-unstable-v1.xml',
    ]

  wl_protos_src = []
  wl_protos_headers = []

  foreach p : protocols
          xml = join_paths(p)
          wl_protos_src += custom_target(
                  xml.underscorify() + '_server_c',
                  input: xml,
                  output: '@BASENAME@-protocol.c',
                  command: [wayland_scanner, 'private-code', '@INPUT@', '@OUTPUT@'],
          )
          wl_protos_headers += custom_target(
                  xml.underscorify() + '_client_h',
                  input: xml,
                  output: '@BASENAME@-protocol.h',
                  command: [wayland_scanner, 'client-header', '@INPUT@', '@OUTPUT@'],
          )
  endforeach

  lib_client_protos = static_library(
          'protocols',
          wl_protos_src + wl_protos_headers,
          dependencies: wayland_client_dep.partial_dependency(compile_args: true),
  )

  client_protos = declare_dependency(
          link_with: lib_client_protos,
          sources: wl_protos_headers,
  )
endif


executable(
  't4',
  files(src_files),
  dependencies: [
    gtk,
    wlroots,
    wayland_client_dep,
    wayland_protos,
    ],
  link_with: lib_client_protos,
  install: true,
  )
