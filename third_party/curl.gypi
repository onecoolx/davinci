# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'curl-8.8.0',
    'lib_name': 'curl',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
    'mbedtls',
    'zlib',
  ],
  'defines': [
    'BUILDING_LIBCURL',
  ],
  'include_dirs': [
    '<(lib_dir)/lib',
    '<(lib_dir)/lib/vtls',
    '<(lib_dir)/include',
  ],
  'sources': [
    '<(lib_dir)/lib/altsvc.c',
    '<(lib_dir)/lib/bufq.c',
    '<(lib_dir)/lib/bufref.c',
    '<(lib_dir)/lib/c-hyper.c',
    '<(lib_dir)/lib/cf-h1-proxy.c',
    '<(lib_dir)/lib/cf-h2-proxy.c',
    '<(lib_dir)/lib/cf-haproxy.c',
    '<(lib_dir)/lib/cf-https-connect.c',
    '<(lib_dir)/lib/cf-socket.c',
    '<(lib_dir)/lib/cfilters.c',
    '<(lib_dir)/lib/asyn-ares.c',
    '<(lib_dir)/lib/asyn-thread.c',
    '<(lib_dir)/lib/base64.c',
    '<(lib_dir)/lib/conncache.c',
    '<(lib_dir)/lib/connect.c',
    '<(lib_dir)/lib/content_encoding.c',
    '<(lib_dir)/lib/cookie.c',
    '<(lib_dir)/lib/curl_addrinfo.c',
    '<(lib_dir)/lib/curl_des.c',
    '<(lib_dir)/lib/curl_endian.c',
    '<(lib_dir)/lib/curl_fnmatch.c',
    '<(lib_dir)/lib/curl_get_line.c',
    '<(lib_dir)/lib/curl_gethostname.c',
    '<(lib_dir)/lib/curl_gssapi.c',
    '<(lib_dir)/lib/curl_memrchr.c',
    '<(lib_dir)/lib/curl_multibyte.c',
    '<(lib_dir)/lib/curl_ntlm_core.c',
    '<(lib_dir)/lib/curl_path.c',
    '<(lib_dir)/lib/curl_range.c',
    '<(lib_dir)/lib/curl_trc.c',
    '<(lib_dir)/lib/curl_rtmp.c',
    '<(lib_dir)/lib/curl_sasl.c',
    '<(lib_dir)/lib/curl_gssapi.c',
    '<(lib_dir)/lib/curl_sspi.c',
    '<(lib_dir)/lib/curl_threads.c',
    '<(lib_dir)/lib/curl_sha512_256.c',
    '<(lib_dir)/lib/dict.c',
    '<(lib_dir)/lib/cw-out.c',
    '<(lib_dir)/lib/doh.c',
    '<(lib_dir)/lib/dynbuf.c',
    '<(lib_dir)/lib/dynhds.c',
    '<(lib_dir)/lib/easy.c',
    '<(lib_dir)/lib/easygetopt.c',
    '<(lib_dir)/lib/easyoptions.c',
    '<(lib_dir)/lib/escape.c',
    '<(lib_dir)/lib/file.c',
    '<(lib_dir)/lib/fileinfo.c',
    '<(lib_dir)/lib/fopen.c',
    '<(lib_dir)/lib/formdata.c',
    '<(lib_dir)/lib/ftp.c',
    '<(lib_dir)/lib/ftplistparser.c',
    '<(lib_dir)/lib/getenv.c',
    '<(lib_dir)/lib/getinfo.c',
    '<(lib_dir)/lib/gopher.c',
    '<(lib_dir)/lib/hash.c',
    '<(lib_dir)/lib/headers.c',
    '<(lib_dir)/lib/hmac.c',
    '<(lib_dir)/lib/hsts.c',
    '<(lib_dir)/lib/hostasyn.c',
    '<(lib_dir)/lib/hostip.c',
    '<(lib_dir)/lib/hostip4.c',
    '<(lib_dir)/lib/hostip6.c',
    '<(lib_dir)/lib/hostsyn.c',
    '<(lib_dir)/lib/http.c',
    '<(lib_dir)/lib/http1.c',
    '<(lib_dir)/lib/http2.c',
    '<(lib_dir)/lib/http_aws_sigv4.c',
    '<(lib_dir)/lib/http_chunks.c',
    '<(lib_dir)/lib/http_digest.c',
    '<(lib_dir)/lib/http_negotiate.c',
    '<(lib_dir)/lib/http_ntlm.c',
    '<(lib_dir)/lib/http_proxy.c',
    '<(lib_dir)/lib/idn.c',
    '<(lib_dir)/lib/if2ip.c',
    '<(lib_dir)/lib/imap.c',
    '<(lib_dir)/lib/inet_ntop.c',
    '<(lib_dir)/lib/inet_pton.c',
    '<(lib_dir)/lib/krb5.c',
    '<(lib_dir)/lib/ldap.c',
    '<(lib_dir)/lib/llist.c',
    '<(lib_dir)/lib/md4.c',
    '<(lib_dir)/lib/md5.c',
    '<(lib_dir)/lib/memdebug.c',
    '<(lib_dir)/lib/mime.c',
    '<(lib_dir)/lib/mprintf.c',
    '<(lib_dir)/lib/mqtt.c',
    '<(lib_dir)/lib/multi.c',
    '<(lib_dir)/lib/netrc.c',
    '<(lib_dir)/lib/nonblock.c',
    '<(lib_dir)/lib/noproxy.c',
    '<(lib_dir)/lib/openldap.c',
    '<(lib_dir)/lib/parsedate.c',
    '<(lib_dir)/lib/pingpong.c',
    '<(lib_dir)/lib/pop3.c',
    '<(lib_dir)/lib/psl.c',
    '<(lib_dir)/lib/progress.c',
    '<(lib_dir)/lib/rand.c',
    '<(lib_dir)/lib/rename.c',
    '<(lib_dir)/lib/request.c',
    '<(lib_dir)/lib/rtsp.c',
    '<(lib_dir)/lib/sha256.c',
    '<(lib_dir)/lib/setopt.c',
    '<(lib_dir)/lib/select.c',
    '<(lib_dir)/lib/sendf.c',
    '<(lib_dir)/lib/share.c',
    '<(lib_dir)/lib/slist.c',
    '<(lib_dir)/lib/smb.c',
    '<(lib_dir)/lib/smtp.c',
    '<(lib_dir)/lib/socks.c',
    '<(lib_dir)/lib/socketpair.c',
    '<(lib_dir)/lib/socks_gssapi.c',
    '<(lib_dir)/lib/socks_sspi.c',
    '<(lib_dir)/lib/speedcheck.c',
    '<(lib_dir)/lib/splay.c',
    '<(lib_dir)/lib/strdup.c',
    '<(lib_dir)/lib/strcase.c',
    '<(lib_dir)/lib/strerror.c',
    '<(lib_dir)/lib/strtok.c',
    '<(lib_dir)/lib/strtoofft.c',
    '<(lib_dir)/lib/telnet.c',
    '<(lib_dir)/lib/tftp.c',
    '<(lib_dir)/lib/timeval.c',
    '<(lib_dir)/lib/timediff.c',
    '<(lib_dir)/lib/transfer.c',
    '<(lib_dir)/lib/url.c',
    '<(lib_dir)/lib/urlapi.c',
    '<(lib_dir)/lib/version.c',
    '<(lib_dir)/lib/warnless.c',
    '<(lib_dir)/lib/ws.c',
    '<(lib_dir)/lib/vtls/cipher_suite.c',
    '<(lib_dir)/lib/vtls/x509asn1.c',
    '<(lib_dir)/lib/vtls/hostcheck.c',
    '<(lib_dir)/lib/vtls/mbedtls.c',
    '<(lib_dir)/lib/vtls/mbedtls_threadlock.c',
    '<(lib_dir)/lib/vtls/vtls.c',
    '<(lib_dir)/lib/vauth/cleartext.c',
    '<(lib_dir)/lib/vauth/cram.c',
    '<(lib_dir)/lib/vauth/digest.c',
    '<(lib_dir)/lib/vauth/digest_sspi.c',
    '<(lib_dir)/lib/vauth/krb5_gssapi.c',
    '<(lib_dir)/lib/vauth/krb5_sspi.c',
    '<(lib_dir)/lib/vauth/gsasl.c',
    '<(lib_dir)/lib/vauth/ntlm.c',
    '<(lib_dir)/lib/vauth/ntlm_sspi.c',
    '<(lib_dir)/lib/vauth/oauth2.c',
    '<(lib_dir)/lib/vauth/vauth.c',
    '<(lib_dir)/lib/vquic/curl_msh3.c',
    '<(lib_dir)/lib/vquic/curl_ngtcp2.c',
    '<(lib_dir)/lib/vquic/curl_osslq.c',
    '<(lib_dir)/lib/vquic/curl_quiche.c',
    '<(lib_dir)/lib/vquic/vquic-tls.c',
    '<(lib_dir)/lib/vquic/vquic.c',
  ],
  'conditions': [
    ['OS=="win"', {
      'include_dirs': [
        '$(OutDir)/include',
      ],
      'defines': [
        'CURL_PULL_WS2TCPIP_H',
        'CURL_DISABLE_LDAPS',
        'CURL_DISABLE_LDAP',
        '__SIZEOF_LONG__=4',
      ],
      'sources': [
        '<(lib_dir)/lib/dllmain.c',
        '<(lib_dir)/lib/version_win32.c',
        '<(lib_dir)/lib/system_win32.c',
        '<(lib_dir)/lib/libcurl.rc',
      ],
      'libraries': [
        '-lws2_32',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include/curl', 
         ],
        'outputs': [
          '$(OutDir)/include/curl',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/curl',
        ],
        'msvs_cygwin_shell': 0,
       }],
    }],
    ['OS=="linux"', {
      'include_dirs': [
        '$(builddir)/include',
      ],
      'defines': [
        'CURL_PULL_SYS_SOCKET_H',
        'HAVE_CONFIG_H',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include/curl', 
        ],
        'outputs': [
          '$(builddir)/include/curl', 
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/curl',
        ],
       }],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

