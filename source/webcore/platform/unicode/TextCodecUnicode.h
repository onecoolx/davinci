
#ifndef UTEXTCODEC_H
#define UTEXTCODEC_H

#include "UChar.h"

class UTextCodec;

UTextCodec * CreateCodec(const char* name);
void DestoryCodec(UTextCodec* codec);
const char * GetCodecName(UTextCodec* codec);

int UTextDecode(UTextCodec* codec, UChar16* dest, int len, const unsigned char* str, int str_len, int* conved_str_len);
int UTextEncode(UTextCodec* codec, unsigned char* dest, int dblen, const UChar16 *wcs, int wcs_len, int* conved_wcs_len);
#endif
