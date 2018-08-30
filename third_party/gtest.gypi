# HTML5 runtime
# 
# Copyright (C) 2018 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'gtest-1.8.0',
    'lib_name': 'gtest',
  },
  'target_name': '<(lib_name)',
  'type': 'static_library',
  'dependencies': [
  ],
  'defines': [
  ],
  'include_dirs': [
    '<(lib_dir)',
    '<(lib_dir)/include',
  ],
  'sources': [
    '<(lib_dir)/src/gtest-all.cc',
    '<(lib_dir)/src/gtest_main.cc',
  ],
  'conditions': [
    ['OS=="win"', {
      'include_dirs': [
        '<(lib_dir)/win32',
        '$(OutDir)/include',
      ],
      'libraries': [
        '-lws2_32',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include/gtest', 
         ],
        'outputs': [
          '$(OutDir)/include/gtest',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/gtest',
        ],
        'msvs_cygwin_shell': 0,
       }],
       'msvs_disabled_warnings': [4996,4244,4267],
    }],
    ['OS=="linux"', {
      'include_dirs': [
        '<(lib_dir)/linux',
        '$(builddir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include/gtest', 
        ],
        'outputs': [
          '$(builddir)/include/gtest', 
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/gtest',
        ],
       }],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

