# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
      'lib_dir': 'zlib-1.2.8',
      'conditions': [
        ['OS=="win"', {
          'lib_name': 'zlib',
        }],
        ['OS=="linux"', {
          'lib_name': 'z',
        }],
      ],
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
  ],
  'defines': [
    'ZLIB_DLL',
  ],
  'include_dirs': [
    '<(lib_dir)',
  ],
  'sources': [
    '<(lib_dir)/adler32.c',
    '<(lib_dir)/compress.c',
    '<(lib_dir)/crc32.c',
    '<(lib_dir)/deflate.c',
    '<(lib_dir)/gzclose.c',
    '<(lib_dir)/gzlib.c',
    '<(lib_dir)/gzread.c',
    '<(lib_dir)/gzwrite.c',
    '<(lib_dir)/infback.c',
    '<(lib_dir)/inffast.c',
    '<(lib_dir)/inflate.c',
    '<(lib_dir)/inftrees.c',
    '<(lib_dir)/trees.c',
    '<(lib_dir)/uncompr.c',
    '<(lib_dir)/zutil.c',
  ],
  'conditions': [
    ['OS=="win"', {
      'sources': [
        '<(lib_dir)/win32/zlib.def',
        '<(lib_dir)/win32/zlib1.rc',
      ],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

