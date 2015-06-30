# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'libxml2-2.9.2',
    'lib_name': 'xml2',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
    'zlib',
  ],
  'defines': [
  ],
  'include_dirs': [
    '<(lib_dir)',
    '<(lib_dir)/include',
  ],
  'sources': [
    '<(lib_dir)/SAX.c',
    '<(lib_dir)/entities.c',
    '<(lib_dir)/encoding.c',
    '<(lib_dir)/error.c',
    '<(lib_dir)/parserInternals.c',
    '<(lib_dir)/parser.c',
    '<(lib_dir)/tree.c',
    '<(lib_dir)/hash.c',
    '<(lib_dir)/list.c',
    '<(lib_dir)/xmlIO.c',
    '<(lib_dir)/xmlmemory.c',
    '<(lib_dir)/uri.c',
    '<(lib_dir)/valid.c',
    '<(lib_dir)/xlink.c',
    '<(lib_dir)/HTMLparser.c',
    '<(lib_dir)/HTMLtree.c',
    '<(lib_dir)/debugXML.c',
    '<(lib_dir)/xpath.c',
    '<(lib_dir)/xpointer.c',
    '<(lib_dir)/xinclude.c',
    '<(lib_dir)/nanohttp.c',
    '<(lib_dir)/nanoftp.c',
    '<(lib_dir)/DOCBparser.c',
    '<(lib_dir)/catalog.c',
    '<(lib_dir)/globals.c',
    '<(lib_dir)/threads.c',
    '<(lib_dir)/c14n.c',
    '<(lib_dir)/xmlstring.c',
    '<(lib_dir)/buf.c',
    '<(lib_dir)/xmlregexp.c',
    '<(lib_dir)/xmlschemas.c',
    '<(lib_dir)/xmlschemastypes.c',
    '<(lib_dir)/xmlunicode.c',
    '<(lib_dir)/xmlreader.c',
    '<(lib_dir)/relaxng.c',
    '<(lib_dir)/dict.c',
    '<(lib_dir)/SAX2.c',
    '<(lib_dir)/xmlwriter.c',
    '<(lib_dir)/legacy.c',
    '<(lib_dir)/chvalid.c',
    '<(lib_dir)/pattern.c',
    '<(lib_dir)/xmlsave.c',
    '<(lib_dir)/xmlmodule.c',
    '<(lib_dir)/schematron.c',
    '<(lib_dir)/xzlib.c',
  ],
  'conditions': [
    ['OS=="win"', {
      'msvs_settings': {
        'VCLinkerTool': {
          'AdditionalDependencies': [
            'ws2_32.lib',
          ],
        },
      },
      'include_dirs': [
        '<(lib_dir)/win32',
        '$(OutDir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include/libxml', 
         ],
        'outputs': [
          '$(OutDir)/include/libxml',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/libxml',
        ],
        'msvs_cygwin_shell': 0,
       }],
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
          '<(lib_dir)/include/libxml', 
        ],
        'outputs': [
          '$(builddir)/include/libxml', 
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/libxml',
        ],
       }],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

