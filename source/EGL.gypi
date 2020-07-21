# HTML5 runtime
#
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'webkit-2.2.8/Source/ThirdParty/ANGLE',
  },
  'target_name': 'EGL',
  'type': 'shared_library',
  'dependencies': [
    'GLESv2',
  ],
  'defines': [
    'NOMINMAX',
  ],
  'include_dirs': [
    '<(lib_dir)/include',
    '<(lib_dir)/src',
    '<(lib_dir)/src/libEGL',
    '<(lib_dir)/src/libGLESv2',
    '$(DXSDK_DIR)/include',
  ],
  'sources': [
    '<(lib_dir)/src/common/angleutils.h',
    '<(lib_dir)/src/common/debug.cpp',
    '<(lib_dir)/src/common/debug.h',
    '<(lib_dir)/src/common/RefCountObject.cpp',
    '<(lib_dir)/src/common/RefCountObject.h',
    '<(lib_dir)/src/common/version.h',
    '<(lib_dir)/src/libEGL/Config.cpp',
    '<(lib_dir)/src/libEGL/Config.h',
    '<(lib_dir)/src/libEGL/Display.cpp',
    '<(lib_dir)/src/libEGL/Display.h',
    '<(lib_dir)/src/libEGL/libEGL.cpp',
    '<(lib_dir)/src/libEGL/libEGL.def',
    '<(lib_dir)/src/libEGL/libEGL.rc',
    '<(lib_dir)/src/libEGL/main.cpp',
    '<(lib_dir)/src/libEGL/main.h',
    '<(lib_dir)/src/libEGL/Surface.cpp',
    '<(lib_dir)/src/libEGL/Surface.h',
  ],
  'libraries': [
    '-ld3d11',
    '-ld3d9',
  ],
  'msvs_disabled_warnings': [ 4267, 4996 ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}
