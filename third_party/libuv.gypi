# HTML5 runtime
# 
# Copyright (C) 2016 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'libuv-v1.9.0',
    'lib_name': 'uv',
  },
  'target_name': '<(lib_name)',
  'type': 'static_library',
  'dependencies': [
  ],
  'defines': [
  ],
  'include_dirs': [
    '<(lib_dir)/include',
    '<(lib_dir)/src',
  ],
  'sources': [
    '<(lib_dir)/include/uv.h',
    '<(lib_dir)/include/tree.h',
    '<(lib_dir)/include/uv-errno.h',
    '<(lib_dir)/include/uv-threadpool.h',
    '<(lib_dir)/include/uv-version.h',
    '<(lib_dir)/src/fs-poll.c',
    '<(lib_dir)/src/heap-inl.h',
    '<(lib_dir)/src/inet.c',
    '<(lib_dir)/src/queue.h',
    '<(lib_dir)/src/threadpool.c',
    '<(lib_dir)/src/uv-common.c',
    '<(lib_dir)/src/uv-common.h',
    '<(lib_dir)/src/version.c'
  ],
  'conditions': [
    ['OS=="win"', {
      'defines': [
        '_WIN32_WINNT=0x0600',
        '_GNU_SOURCE',
      ],
      'sources': [
        '<(lib_dir)/include/uv-win.h',
        '<(lib_dir)/src/win/async.c',
        '<(lib_dir)/src/win/atomicops-inl.h',
        '<(lib_dir)/src/win/core.c',
        '<(lib_dir)/src/win/dl.c',
        '<(lib_dir)/src/win/error.c',
        '<(lib_dir)/src/win/fs.c',
        '<(lib_dir)/src/win/fs-event.c',
        '<(lib_dir)/src/win/getaddrinfo.c',
        '<(lib_dir)/src/win/getnameinfo.c',
        '<(lib_dir)/src/win/handle.c',
        '<(lib_dir)/src/win/handle-inl.h',
        '<(lib_dir)/src/win/internal.h',
        '<(lib_dir)/src/win/loop-watcher.c',
        '<(lib_dir)/src/win/pipe.c',
        '<(lib_dir)/src/win/thread.c',
        '<(lib_dir)/src/win/poll.c',
        '<(lib_dir)/src/win/process.c',
        '<(lib_dir)/src/win/process-stdio.c',
        '<(lib_dir)/src/win/req.c',
        '<(lib_dir)/src/win/req-inl.h',
        '<(lib_dir)/src/win/signal.c',
        '<(lib_dir)/src/win/snprintf.c',
        '<(lib_dir)/src/win/stream.c',
        '<(lib_dir)/src/win/stream-inl.h',
        '<(lib_dir)/src/win/tcp.c',
        '<(lib_dir)/src/win/tty.c',
        '<(lib_dir)/src/win/timer.c',
        '<(lib_dir)/src/win/udp.c',
        '<(lib_dir)/src/win/util.c',
        '<(lib_dir)/src/win/winapi.c',
        '<(lib_dir)/src/win/winapi.h',
        '<(lib_dir)/src/win/winsock.c',
        '<(lib_dir)/src/win/winsock.h',
      ],
      'link_settings': {
        'libraries': [
          '-ladvapi32',
          '-liphlpapi',
          '-lpsapi',
          '-lshell32',
          '-luserenv',
          '-lws2_32'
        ],
      },
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include', 
         ],
        'outputs': [
          '$(OutDir)/include/uv',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/uv',
        ],
        'msvs_cygwin_shell': 0,
       }],
    }],
    ['OS=="linux"', {
      'defines': [
        '_LARGEFILE_SOURCE',
        '_FILE_OFFSET_BITS=64',
        '_POSIX_C_SOURCE=200112',
        '_GNU_SOURCE',
      ],
      'sources': [ 
        '<(lib_dir)/include/uv-unix.h',
        '<(lib_dir)/include/uv-linux.h',
        '<(lib_dir)/include/uv-sunos.h',
        '<(lib_dir)/include/uv-darwin.h',
        '<(lib_dir)/include/uv-bsd.h',
        '<(lib_dir)/include/uv-aix.h',
        '<(lib_dir)/src/unix/async.c',
        '<(lib_dir)/src/unix/atomic-ops.h',
        '<(lib_dir)/src/unix/core.c',
        '<(lib_dir)/src/unix/dl.c',
        '<(lib_dir)/src/unix/fs.c',
        '<(lib_dir)/src/unix/getaddrinfo.c',
        '<(lib_dir)/src/unix/getnameinfo.c',
        '<(lib_dir)/src/unix/internal.h',
        '<(lib_dir)/src/unix/loop.c',
        '<(lib_dir)/src/unix/loop-watcher.c',
        '<(lib_dir)/src/unix/pipe.c',
        '<(lib_dir)/src/unix/poll.c',
        '<(lib_dir)/src/unix/process.c',
        '<(lib_dir)/src/unix/signal.c',
        '<(lib_dir)/src/unix/spinlock.h',
        '<(lib_dir)/src/unix/stream.c',
        '<(lib_dir)/src/unix/tcp.c',
        '<(lib_dir)/src/unix/thread.c',
        '<(lib_dir)/src/unix/timer.c',
        '<(lib_dir)/src/unix/tty.c',
        '<(lib_dir)/src/unix/udp.c',
        '<(lib_dir)/src/unix/proctitle.c',
        '<(lib_dir)/src/unix/linux-core.c',
        '<(lib_dir)/src/unix/linux-inotify.c',
        '<(lib_dir)/src/unix/linux-syscalls.c',
        '<(lib_dir)/src/unix/linux-syscalls.h',
      ],
      'cflags': [
        '-fstrict-aliasing',
        '-fomit-frame-pointer',
        '-fdata-sections',
        '-ffunction-sections',
        '--std=gnu89',
        '-pedantic',
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter',
      ],
      'link_settings': {
        'libraries': [
          '-lpthread',
          '-lm',
        ],
      },
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include', 
        ],
        'outputs': [
          '$(builddir)/include/uv', 
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/uv',
        ],
       }],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

