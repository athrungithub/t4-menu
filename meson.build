project(
  't4-menu',
  'c',
  license: 'MIT',
  )

gtk = dependency('gtk+-3.0')

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
    ],
  install: true,
  )
