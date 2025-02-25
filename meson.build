project('pVctr', ['c'],
          version: '0.0.5',
    meson_version: '>= 1.3',
    license: 'MIT',
  default_options: [ 'warning_level=2', 'werror=false', 'c_std=c23' ],
)
version = meson.project_version().split('-')[0]
version_major = version.split('.')[0]
version_minor = version.split('.')[1]
version_patch = version.split('.')[2]
versioned_name = '@0@-1.0_@1@.@2@.@3@'.format(meson.project_name(), version_major, version_minor, version_patch)

project_description = 'A libary for easy vector with simd'

cc = meson.get_compiler('c')
add_project_arguments(cc.get_supported_arguments([
	'-msse',
  '-msse2',
  '-msse3',
  '-msse4',
  '-mavx',
  '-mfpmath=avx',
  '-Wimplicit-fallthrough',
  # gcc
  '-Wno-missing-field-initializers',
  '-Wno-unused-parameter',
  '-Wno-misleading-indentation',
  '-Wno-cast-function-type', # Needed for GetProcAddress.
  # clang
  '-Wno-unused-private-field',
  '-Wno-microsoft-exception-spec',
  '-Wno-extern-c-compat',
  '-Wno-unused-const-variable',
  '-Wno-missing-braces',
]), language: 'c')


project_headers = [
  'include/PVCTRplatform.h',
  'include/PVCTRTsimd.h',
  'include/PVCTR.h',
  'include/PVCTRfasttype.h',
]

project_source_files = [
  'src/pvctr_base.c',
  'src/pvctr_utils.c',
  'src/pvctr_fasttype.c',
  'src/pvctr_techniq.c',
  'src/pvctr_context.c',
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
  '-DPVCTR_PROTOTYPES=1',
]

project_target = shared_library(
  meson.project_name(),
  project_source_files,
  install : true,
  c_args : build_args,
  gnu_symbol_visibility : 'hidden',
  include_directories : [public_headers],
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
install_headers(project_headers, subdir : 'pvctr',  preserve_path : false)


pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : versioned_name,
  filebase : meson.project_name(),
  description : project_description,
  subdirs : meson.project_name(),
  libraries : project_target,
)
