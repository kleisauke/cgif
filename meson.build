project(
  'libcgif',
  'c',
  license : 'MIT',
  default_options : ['c_std=c99'],
)

lib = library(
  'cgif',
  'cgif.c',
  install : true,
)

install_headers('cgif.h')

import('pkgconfig').generate(
  lib,
  name : 'cgif',
  description : 'A fast and lightweight GIF encoder',
)

if get_option('tests') and not meson.is_cross_build()
  libcgif_dep = declare_dependency(link_with : lib)
  subdir('tests')
endif
