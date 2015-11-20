# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'sqlite-3.9.1',
    'lib_name': 'sqlite',
  },
  'target_name': '<(lib_name)',
  'type': 'static_library',
  'dependencies': [
  ],
  'defines': [
    'SQLITE_THREADSAFE',
    'SQLITE_ENABLE_FTS3',
    'SQLITE_ENABLE_RTREE',
  ],
  'include_dirs': [
    '<(lib_dir)',
  ],
  'sources': [
    '<(lib_dir)/sqlite3.c',
  ],
  'conditions': [
    ['OS=="win"', {
      'include_dirs': [
        '$(OutDir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_header1',
        'inputs': [
          '<(lib_dir)/sqlite3.h',
         ],
        'outputs': [
          '$(OutDir)/include/sqlite3.h',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/sqlite3.h',
        ],
        'msvs_cygwin_shell': 0,
       },
       {
        'action_name': 'install_header2',
        'inputs': [
          '<(lib_dir)/sqlite3ext.h',
         ],
        'outputs': [
          '$(OutDir)/include/sqlite3ext.h',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/sqlite3ext.h',
        ],
        'msvs_cygwin_shell': 0,
       },
      ],
    }],
    ['OS=="linux"', {
      'include_dirs': [
        '$(builddir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_header1',
        'inputs': [
          '<(lib_dir)/sqlite3.h',
        ],
        'outputs': [
          '$(builddir)/include/sqlite3.h',
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/sqlite3.h',
        ],
       },
       {
        'action_name': 'install_header2',
        'inputs': [
          '<(lib_dir)/sqlite3ext.h',
        ],
        'outputs': [
          '$(builddir)/include/sqlite3ext.h',
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/sqlite3ext.h',
        ],
       },
      ],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

