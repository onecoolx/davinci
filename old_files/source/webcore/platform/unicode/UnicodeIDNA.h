
#ifndef  _UNICODE_IDNA_H
#define  _UNICODE_IDNA_H

#include  "UChar.h"
#include  "UnicodeGlobal.h"

typedef  struct tagUIDNADB{
        unsigned int   startcode;
        unsigned int   endcode;
}UIDNADB;


typedef  struct tagOneMapOne{
        unsigned int  origincode;
        unsigned int  mapcode;
}ONEMAPONE;


typedef  struct tagOneMapTwo{
        unsigned int  origincode;
        unsigned int  mapcode1;
        unsigned int  mapcode2;
}ONEMAPTWO;


typedef  struct tagOneMapThree{
        unsigned int  origincode;
        unsigned int  mapcode1;
        unsigned int  mapcode2;
        unsigned int  mapcode3;
}ONEMAPTHREE;


typedef  struct tagOneMapFour{
        unsigned int  origincode;
        unsigned int  mapcode1;
        unsigned int  mapcode2;
        unsigned int  mapcode3;
        unsigned int  mapcode4;
}ONEMAPFOUR;

#define USPREP_ALLOW_UNASSIGNED 0x0001
#define UIDNA_ALLOW_UNASSIGNED 0x0001
#define UIDNA_USE_STD3_RULES   0x0002

#   define U_IDNA_ZERO_LENGTH_LABEL_ERROR U_IDNA_ERROR_LIMIT


#define UTF_SURROGATE_OFFSET ((0xd800<<10UL)+0xdc00-0x10000)
#define U_IS_SURROGATE(c) (((c)&0xfffff800)==0xd800)
#define U16_IS_SINGLE(c) !U_IS_SURROGATE(c)
#define UTF_IS_SINGLE(uchar) U16_IS_SINGLE(uchar)

#define UTF16_GET_PAIR_VALUE(first, second) \
    (((first)<<10UL)+(second)-UTF_SURROGATE_OFFSET)


int uidna_IDNToASCII(  const UChar *src, int srcLength,
                   UChar* dest, int destCapacity,
                   int options,
                   UErrorCode *status);

#endif   /*end of head file*/


