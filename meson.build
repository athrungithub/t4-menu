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

r = run_command('git', 'describe', '--tags', check: true)
version = r.stdout().strip()
charver = '-DVERSION="'+version+'"'
add_global_arguments(charver, language: 'c')

r1 = run_command('date', '+%Y.%m.%d', check: true)
date = r1.stdout().strip()
charver = '-DBUILDDATE="'+date+'"'
add_global_arguments(charver, language: 'c')



executable(
  't4',
  src_files,
  dependencies: [
    gtk,
    ],
  install: true,
  )
