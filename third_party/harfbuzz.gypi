# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'harfbuzz-1.0.6',
    'lib_name': 'harfbuzz',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
    'freetype2',
  ],
  'defines': [
  ],
  'include_dirs': [
  ],
  'sources': [
	'<(lib_dir)/src/fcarch.h',
  ],
  'conditions': [
    ['OS=="win"', {
      'include_dirs': [
        '$(OutDir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_header',
        'inputs': [
          '<(lib_dir)/fontconfig',
         ],
        'outputs': [
          '$(OutDir)/include/fontconfig',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/fontconfig',
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
        'action_name': 'install_header',
        'inputs': [
          '<(lib_dir)/fontconfig',
        ],
        'outputs': [
          '$(builddir)/include/fontconfig',
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/fontconfig',
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

