# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_name': 'WebCore',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
  ],
  'defines': [
  ],
  'include_dirs': [
  ],
  'sources': [ 
  #  '<(lib_dir)/source/common/appendable.cpp',
  ],
  'conditions': [
    ['OS=="win"', {
      'include_dirs': [
        '$(OutDir)/include',
      ],
      'defines': [
      ],
      'sources': [ 
      ],
#      'msvs_disabled_warnings': [4251, 4244],
    }],
    ['OS=="linux"', {
      'include_dirs': [
        '$(builddir)/include',
      ],
      'defines': [
      ],
      'sources': [ 
      ],
    }],
  ],
  'libraries': [
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

