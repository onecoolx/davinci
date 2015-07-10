# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_root_dir': 'webkit-2.2.8/Source',
    'lib_dir': 'webkit-2.2.8/Source/JavaScriptCore',
    'lib_name': 'JavaScriptCore',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
    'WTF',
  ],
  'defines': [
  ],
  'include_dirs': [
    '<(lib_root_dir)',
    '<(lib_root_dir)/WTF',
    '<(lib_dir)',
	'<(lib_dir)/API',
	'<(lib_dir)/ForwardingHeaders',
	'<(lib_dir)/assembler',
	'<(lib_dir)/bytecode',
	'<(lib_dir)/bytecompiler',
	'<(lib_dir)/debugger',
	'<(lib_dir)/dfg',
	'<(lib_dir)/disassembler',
	'<(lib_dir)/ftl',
	'<(lib_dir)/heap',
	'<(lib_dir)/interpreter',
	'<(lib_dir)/jit',
	'<(lib_dir)/llint',
	'<(lib_dir)/parser',
	'<(lib_dir)/profiler',
	'<(lib_dir)/runtime',
	'<(lib_dir)/tools',
	'<(lib_dir)/yarr',
  ],
  'sources': [ 
    '<(lib_dir)/AllInOneFile.cpp',
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
      'cflags': [
        '-fstrict-aliasing',
      ],
      'cflags_cc': [
        '-fno-rtti',
      ],
      'sources': [ 
      ],
      'libraries': [
        '-lpthread',
      ],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

