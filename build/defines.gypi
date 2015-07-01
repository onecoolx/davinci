# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'conditions': [
    ['OS=="win"', {
      'defines': [
        'WIN32',
        '_WIN32',
        'DLL_EXPORT',
        '_USE_MATH_DEFINES',
        '_CRT_SECURE_NO_DEPRECATE',
        '_CRT_SECURE_NO_WARNINGS',
        '_CRT_NONSTDC_NO_WARNINGS',
        '_HAS_EXCEPTIONS=0',
      ],
    }],
  ],
}
