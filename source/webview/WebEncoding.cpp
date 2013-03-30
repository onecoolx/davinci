/*
** WebEncoding.cpp: WebEncoding implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "WebEncoding.h"
#include "WebGlobal.h"

namespace MaCross {

const char * Encodings[] = {
  "ISO8859-1",
  "ISO8859-2",
  "ISO8859-3",
  "ISO8859-4",
  "ISO8859-5",
  "ISO8859-6",
  "ISO8859-7",
  "ISO8859-8",
  "ISO8859-9",
  "ISO8859-10",
  "ISO8859-11",
  "ISO8859-13",
  "ISO8859-14",
  "ISO8859-15",
  "ISO8859-16",
  "GB2312-0",      
  "GBK",
  "BIG5",
  "EUC-KR",     
  "EUC-JP",
  "SHIFT-JIS",
  "UTF-8",
};

int EncodingNum = TABLE_SIZE(Encodings);

}
