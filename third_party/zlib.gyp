# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
      'zlib_dir': 'zlib-1.2.8',
      'conditions': [
        ['OS=="win"', {
          'lib_name': 'zlib',
        }],
        ['OS=="linux"', {
          'lib_name': 'z',
        }],
      ],
  },
  'targets': [
    {
      'target_name': '<(lib_name)',
      'type': 'shared_library',
      'dependencies': [
      ],
      'defines':[
        'ZLIB_DLL',
      ],
      'include_dirs': [
        '<(zlib_dir)',
      ],
      'sources': [
        '<(zlib_dir)/adler32.c',
        '<(zlib_dir)/compress.c',
        '<(zlib_dir)/crc32.c',
        '<(zlib_dir)/deflate.c',
        '<(zlib_dir)/gzclose.c',
        '<(zlib_dir)/gzlib.c',
        '<(zlib_dir)/gzread.c',
        '<(zlib_dir)/gzwrite.c',
        '<(zlib_dir)/infback.c',
        '<(zlib_dir)/inffast.c',
        '<(zlib_dir)/inflate.c',
        '<(zlib_dir)/inftrees.c',
        '<(zlib_dir)/trees.c',
        '<(zlib_dir)/uncompr.c',
        '<(zlib_dir)/zutil.c',
      ],
      'conditions': [
        ['OS=="win"', {
          'sources': [
            '<(zlib_dir)/win32/zlib.def',
            '<(zlib_dir)/win32/zlib1.rc',
          ],
        }],
      ],
      'includes':[
        '../build/configs.gypi',
        '../build/defines.gypi',
      ],
    },
  ]
}

