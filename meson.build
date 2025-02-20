project('OpenVeTr', ['cpp', 'c'],
          version: '0.1.0',
    meson_version: '>= 1.0.0',
  default_options: [ 'warning_level=2', 'werror=false', 'cpp_std=gnu++2a', 'c_std=c2x' ],
)
project_description = 'A libary for easy vector with simd'

project_headers = [
  'include/internal/OVTplatform.h',
  'include/internal/OVTsimd.h',
  'include/OVT.h',
  'include/OVTUtils.h',
  'include/OVTfasttype.h'
]

project_source_files = [
  'src/OVT.c',
  'src/OVTUtils.c',
  'src/OVTfasttype.c'
]


build_args = [
  '-mavx'
]

# ===================================================================

# ======
# Target
# ======

public_headers = include_directories('include')

build_args += [
  '-DPROJECT_NAME=' + meson.project_name(),
  '-DPROJECT_VERSION=' + meson.project_version(),
  '-mavx',
]

project_target = shared_library(
  meson.project_name(),
  project_source_files,
  install : true,
  c_args : build_args,
  gnu_symbol_visibility : 'hidden',
  include_directories : public_headers,
)


# =======
# Project
# =======

# Make this library usable as a Meson subproject.
project_dep = declare_dependency(
  include_directories: public_headers,
  link_with : project_target
)
set_variable(meson.project_name() + '_dep', project_dep)

# Make this library usable from the system's
# package manager.
install_headers(project_headers, subdir : 'OpenVT')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : meson.project_name(),
  filebase : meson.project_name(),
  description : project_description,
  subdirs : meson.project_name(),
  libraries : project_target,
)
