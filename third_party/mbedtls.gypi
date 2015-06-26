# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'variables': {
    'lib_dir': 'mbedtls-1.3.11',
    'lib_name': 'mbedtls',
  },
  'target_name': '<(lib_name)',
  'type': 'shared_library',
  'dependencies': [
  ],
  'defines': [
    '_USRDLL',
    'MBEDTLS_EXPORTS',
  ],
  'include_dirs': [
    '<(lib_dir)',
  ],
  'sources': [
    '<(lib_dir)/library/aes.c',
    '<(lib_dir)/library/aesni.c',
    '<(lib_dir)/library/arc4.c',
    '<(lib_dir)/library/asn1parse.c',
    '<(lib_dir)/library/asn1write.c',
    '<(lib_dir)/library/base64.c',
    '<(lib_dir)/library/bignum.c',
    '<(lib_dir)/library/blowfish.c',
    '<(lib_dir)/library/camellia.c',
    '<(lib_dir)/library/ccm.c',
    '<(lib_dir)/library/certs.c',
    '<(lib_dir)/library/cipher.c',
    '<(lib_dir)/library/cipher_wrap.c',
    '<(lib_dir)/library/ctr_drbg.c',
    '<(lib_dir)/library/debug.c',
    '<(lib_dir)/library/des.c',
    '<(lib_dir)/library/dhm.c',
    '<(lib_dir)/library/ecp.c',
    '<(lib_dir)/library/ecp_curves.c',
    '<(lib_dir)/library/ecdh.c',
    '<(lib_dir)/library/ecdsa.c',
    '<(lib_dir)/library/entropy.c',
    '<(lib_dir)/library/entropy_poll.c',
    '<(lib_dir)/library/error.c',
    '<(lib_dir)/library/gcm.c',
    '<(lib_dir)/library/havege.c',
    '<(lib_dir)/library/hmac_drbg.c',
    '<(lib_dir)/library/md.c',
    '<(lib_dir)/library/md_wrap.c',
    '<(lib_dir)/library/md2.c',
    '<(lib_dir)/library/md4.c',
    '<(lib_dir)/library/md5.c',
    '<(lib_dir)/library/memory_buffer_alloc.c',
    '<(lib_dir)/library/net.c',
    '<(lib_dir)/library/oid.c',
    '<(lib_dir)/library/padlock.c',
    '<(lib_dir)/library/pbkdf2.c',
    '<(lib_dir)/library/pem.c',
    '<(lib_dir)/library/pkcs5.c',
    '<(lib_dir)/library/pkcs11.c',
    '<(lib_dir)/library/pkcs12.c',
    '<(lib_dir)/library/pk.c',
    '<(lib_dir)/library/pk_wrap.c',
    '<(lib_dir)/library/pkparse.c',
    '<(lib_dir)/library/pkwrite.c',
    '<(lib_dir)/library/platform.c',
    '<(lib_dir)/library/ripemd160.c',
    '<(lib_dir)/library/rsa.c',
    '<(lib_dir)/library/sha1.c',
    '<(lib_dir)/library/sha256.c',
    '<(lib_dir)/library/sha512.c',
    '<(lib_dir)/library/ssl_cache.c',
    '<(lib_dir)/library/ssl_ciphersuites.c',
    '<(lib_dir)/library/ssl_cli.c',
    '<(lib_dir)/library/ssl_srv.c',
    '<(lib_dir)/library/ssl_tls.c',
    '<(lib_dir)/library/threading.c',
    '<(lib_dir)/library/timing.c',
    '<(lib_dir)/library/version.c',
    '<(lib_dir)/library/version_features.c',
    '<(lib_dir)/library/x509.c',
    '<(lib_dir)/library/x509_crt.c',
    '<(lib_dir)/library/x509_crl.c',
    '<(lib_dir)/library/x509_csr.c',
    '<(lib_dir)/library/x509_create.c',
    '<(lib_dir)/library/x509write_crt.c',
    '<(lib_dir)/library/x509write_csr.c',
    '<(lib_dir)/library/xtea.c',
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
          '<(lib_dir)/include/polarssl', 
         ],
        'outputs': [
          '$(OutDir)/include/polarssl',
         ],
        'action': [
          'python',
          'tools/cp.py',
          '<(_inputs)',
          '$(OutDir)/include/polarssl',
        ],
        'msvs_cygwin_shell': 0,
       }],
    }],
    ['OS=="linux"', {
      'include_dirs': [
        '$(builddir)/include',
      ],
      'actions': [
       {
        'action_name': 'install_headers',
        'inputs': [
          '<(lib_dir)/include/polarssl', 
        ],
        'outputs': [
          '$(builddir)/include/polarssl', 
        ],
        'action': [
        'python',
        'tools/cp.py',
        '<(_inputs)',
        '$(builddir)/include/polarssl',
        ],
       }],
    }],
  ],
  'includes': [
    '../build/configs.gypi',
    '../build/defines.gypi',
  ],
}

