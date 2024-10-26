# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'libxslt-1.1.28',
    'lib_name': 'xslt',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
    'xml2',
  ],
  'defines': [
  ],
  'include_dirs': [
    '<(lib_dir)',
    '<(lib_dir)/libxslt',
  ],
  'sources': [
    '<(lib_dir)/libxslt/attrvt.c',
	'<(lib_dir)/libxslt/xslt.c',
	'<(lib_dir)/libxslt/xsltlocale.c',
	'<(lib_dir)/libxslt/xsltutils.c',
	'<(lib_dir)/libxslt/pattern.c',
	'<(lib_dir)/libxslt/templates.c',
	'<(lib_dir)/libxslt/variables.c',
	'<(lib_dir)/libxslt/keys.c',
	'<(lib_dir)/libxslt/numbers.c',
	'<(lib_dir)/libxslt/extensions.c',
	'<(lib_dir)/libxslt/extra.c',
	'<(lib_dir)/libxslt/functions.c',
	'<(lib_dir)/libxslt/namespaces.c',
	'<(lib_dir)/libxslt/imports.c',
	'<(lib_dir)/libxslt/attributes.c',
	'<(lib_dir)/libxslt/documents.c',
	'<(lib_dir)/libxslt/preproc.c',
	'<(lib_dir)/libxslt/transform.c',
	'<(lib_dir)/libxslt/security.c',
  ],
  'conditions': [
    ['OS=="win"', {
      'include_dirs': [
        '$(OutDir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/libxslt', 
         ],
        'outputs': [
          '$(OutDir)/include/libxslt',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/libxslt',
        ],
        'msvs_cygwin_shell': 0,
       }],
       'msvs_disabled_warnings': [4996,4244,4267],
    }],
    ['OS=="linux"', {
      'include_dirs': [
        '$(builddir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/libxslt', 
        ],
        'outputs': [
          '$(builddir)/include/libxslt', 
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/libxslt',
        ],
       }],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

