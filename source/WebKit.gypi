# HTML5 runtime
# 
# Copyright (C) 2015 Zhang Ji Peng
# Contact: onecoolx@gmail.com

{
  'targets': [
       {
          'includes': [
           './ANGLE.gypi'
           ],
       },
       {
          'includes': [
           './WTF.gypi'
           ],
       },
       {
          'includes': [
           './JavaScriptCore.gypi'
           ],
       },
       {
          'includes': [
            './WebCore.gypi'
          ],
       },
   ],
   'conditions': [
     ['OS=="win"', {
       'targets': [
       {
          'includes': [
            './GLESv2.gypi'
          ],
       },
       {
          'includes': [
            './EGL.gypi'
          ],
       }],
     }],
   ],
}

