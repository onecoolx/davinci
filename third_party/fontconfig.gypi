# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'fontconfig-2.11.94',
    'lib_name': 'fontconfig',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
    'freetype2',
  ],
  'defines': [
    'HAVE_CONFIG_H',
  ],
  'include_dirs': [
    '<(lib_dir)/',
  ],
  'sources': [
	'<(lib_dir)/src/fcarch.h',
	'<(lib_dir)/src/fcatomic.c',
	'<(lib_dir)/src/fcatomic.h',
	'<(lib_dir)/src/fcblanks.c',
	'<(lib_dir)/src/fccache.c',
	'<(lib_dir)/src/fccfg.c',
	'<(lib_dir)/src/fccharset.c',
	'<(lib_dir)/src/fccompat.c',
	'<(lib_dir)/src/fcdbg.c',
	'<(lib_dir)/src/fcdefault.c',
	'<(lib_dir)/src/fcdir.c',
	'<(lib_dir)/src/fcformat.c',
	'<(lib_dir)/src/fcfreetype.c',
	'<(lib_dir)/src/fcfs.c',
	'<(lib_dir)/src/fcinit.c',
	'<(lib_dir)/src/fclang.c',
	'<(lib_dir)/src/fclist.c',
	'<(lib_dir)/src/fcmatch.c',
	'<(lib_dir)/src/fcmatrix.c',
	'<(lib_dir)/src/fcmutex.h',
	'<(lib_dir)/src/fcname.c',
	'<(lib_dir)/src/fcobjs.c',
	'<(lib_dir)/src/fcobjs.h',
	'<(lib_dir)/src/fcobjshash.h',
	'<(lib_dir)/src/fcpat.c',
	'<(lib_dir)/src/fcrange.c',
	'<(lib_dir)/src/fcserialize.c',
	'<(lib_dir)/src/fcstat.c',
	'<(lib_dir)/src/fcstr.c',
	'<(lib_dir)/src/fcweight.c',
	'<(lib_dir)/src/fcwindows.h',
	'<(lib_dir)/src/fcxml.c',
	'<(lib_dir)/src/ftglue.h',
	'<(lib_dir)/src/ftglue.c',
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

