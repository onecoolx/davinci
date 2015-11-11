# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'targets': [
  {
    'target_name': 'test',
    'type': 'executable',
    'dependencies': [
      'WTF',
      'JavaScriptCore',
      'WebCore',
    ],
    'include_dirs': [
    ],
    'sources': [
      'test.cpp',
    ],
    'conditions': [
      ['OS=="win"', {
        'sources': [
        ],
      }],
      ['OS=="linux"', {
        'sources': [
        ],
        'cflags': [
        ],
        'cflags_cc': [
        ],
        'libraries': [
          '-lpthread',
        ],
      }],
    ],
    'includes':[
      '../build/configs.gypi',
      '../build/defines.gypi',
    ],
  },
  ],
}

