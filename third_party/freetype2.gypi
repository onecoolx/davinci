# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'freetype-2.6.1',
    'lib_name': 'freetype2',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
    'png',
    'zlib',
  ],
  'defines': [
    'FT2_BUILD_LIBRARY',
  ],
  'include_dirs': [
    '<(lib_dir)/include',
  ],
  'sources': [
    '<(lib_dir)/src/autofit/afangles.h',
    '<(lib_dir)/src/autofit/afblue.h',
    '<(lib_dir)/src/autofit/afcjk.h',
    '<(lib_dir)/src/autofit/afcover.h',
    '<(lib_dir)/src/autofit/afdummy.h',
    '<(lib_dir)/src/autofit/aferrors.h',
    '<(lib_dir)/src/autofit/afglobal.h',
    '<(lib_dir)/src/autofit/afhints.h',
    '<(lib_dir)/src/autofit/afindic.h',
    '<(lib_dir)/src/autofit/aflatin.h',
    '<(lib_dir)/src/autofit/aflatin2.h',
    '<(lib_dir)/src/autofit/afloader.h',
    '<(lib_dir)/src/autofit/afmodule.h',
    '<(lib_dir)/src/autofit/afpic.h',
    '<(lib_dir)/src/autofit/afranges.h',
    '<(lib_dir)/src/autofit/afscript.h',
    '<(lib_dir)/src/autofit/afstyles.h',
    '<(lib_dir)/src/autofit/aftypes.h',
    '<(lib_dir)/src/autofit/afwarp.h',
    '<(lib_dir)/src/autofit/afwrtsys.h',
    '<(lib_dir)/src/autofit/hbshim.h',
    '<(lib_dir)/src/autofit/autofit.c',
    '<(lib_dir)/src/base/basepic.h',
    '<(lib_dir)/src/base/md5.h',
    '<(lib_dir)/src/base/ftbase.h',
    '<(lib_dir)/src/base/ftbase.c',
    '<(lib_dir)/src/bdf/bdf.h',
    '<(lib_dir)/src/bdf/bdfdrivr.h',
    '<(lib_dir)/src/bdf/bdferror.h',
    '<(lib_dir)/src/bdf/bdf.c',
  ],
  'conditions': [
    ['OS=="win"', {
      'sources': [
        '<(lib_dir)/winfonts/winfnt.c',
        '<(lib_dir)/winfonts/winfnt.h',
        '<(lib_dir)/winfonts/fnterrs.h',
      ],
      'include_dirs': [
        '$(OutDir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_header1',
        'inputs': [
          '<(lib_dir)/include/freetype',
         ],
        'outputs': [
          '$(OutDir)/include/freetype',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/freetype',
        ],
        'msvs_cygwin_shell': 0,
       },
       {
        'action_name': 'install_header2',
        'inputs': [
          '<(lib_dir)/include/ft2build.h',
         ],
        'outputs': [
          '$(OutDir)/include/ft2build.h',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/ft2build.h',
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
          '<(lib_dir)/include/freetype',
        ],
        'outputs': [
          '$(builddir)/include/freetype',
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/freetype',
        ],
       },
       {
        'action_name': 'install_header2',
        'inputs': [
          '<(lib_dir)/include/ft2build.h',
        ],
        'outputs': [
          '$(builddir)/include/ft2build.h',
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/ft2build.h',
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

