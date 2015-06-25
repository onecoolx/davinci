
#ifndef _UnicodeTrie_h
#define _UnicodeTrie_h

#include  "UnicodeGlobal.h"

typedef int32_t UTrieGetFoldingOffset(uint32_t data);

typedef struct {
    const uint16_t *index;
    const uint32_t *data32; /* NULL if 16b data is used via index */
    UTrieGetFoldingOffset *getFoldingOffset;
    int32_t indexLength; 
    int32_t dataLength;
    uint32_t initialValue;
    int isLatin1Linear;
} UTrie;

enum {
    UTRIE_SHIFT=5,

    UTRIE_DATA_BLOCK_LENGTH=1<<UTRIE_SHIFT,

    UTRIE_MASK=UTRIE_DATA_BLOCK_LENGTH-1,

    UTRIE_LEAD_INDEX_DISP=0x2800>>UTRIE_SHIFT,

    UTRIE_INDEX_SHIFT=2,

    UTRIE_DATA_GRANULARITY=1<<UTRIE_INDEX_SHIFT,

    UTRIE_SURROGATE_BLOCK_BITS=10-UTRIE_SHIFT,

    UTRIE_SURROGATE_BLOCK_COUNT=(1<<UTRIE_SURROGATE_BLOCK_BITS),

    UTRIE_BMP_INDEX_LENGTH=0x10000>>UTRIE_SHIFT
};

#define UTF_FIRST_SURROGATE(supplementary) (UChar)(((supplementary)>>10)+0xd7c0)

#define UTF16_LEAD(supplementary) UTF_FIRST_SURROGATE(supplementary)


#define U16_APPEND(s, i, capacity, c, isError) { \
    if((uint32_t)(c)<=0xffff) { \
        (s)[(i)++]=(uint16_t)(c); \
    } else if((uint32_t)(c)<=0x10ffff && (i)+1<(capacity)) { \
        (s)[(i)++]=(uint16_t)(((c)>>10)+0xd7c0); \
        (s)[(i)++]=(uint16_t)(((c)&0x3ff)|0xdc00); \
    } else /* c>0x10ffff or not enough space */ { \
        (isError)=TRUE; \
    } \
}


#define _UTRIE_GET_RAW(trie, data, offset, c16) \
    (trie)->data[ \
        ((int32_t)((trie)->index[(offset)+((c16)>>UTRIE_SHIFT)])<<UTRIE_INDEX_SHIFT)+ \
        ((c16)&UTRIE_MASK) \
    ]

#define _UTRIE_GET_FROM_PAIR(trie, data, c, c2, result, resultType) { \
    int32_t __offset; \
\
    /* get data for lead surrogate */ \
    (result)=_UTRIE_GET_RAW((trie), data, 0, (c)); \
    __offset=(trie)->getFoldingOffset(result); \
\
    /* get the real data from the folded lead/trail units */ \
    if(__offset>0) { \
        (result)=_UTRIE_GET_RAW((trie), data, __offset, (c2)&0x3ff); \
    } else { \
        (result)=(resultType)((trie)->initialValue); \
    } \
}

#define _UTRIE_GET_FROM_BMP(trie, data, c16) \
    _UTRIE_GET_RAW(trie, data, 0xd800<=(c16) && (c16)<=0xdbff ? UTRIE_LEAD_INDEX_DISP : 0, c16);

#define _UTRIE_GET(trie, data, c32, result, resultType) \
    if((uint32_t)(c32)<=0xffff) { \
        /* BMP code points */ \
        (result)=_UTRIE_GET_FROM_BMP(trie, data, c32); \
    } else if((uint32_t)(c32)<=0x10ffff) { \
        /* supplementary code point */ \
        UChar __lead16=UTF16_LEAD(c32); \
        _UTRIE_GET_FROM_PAIR(trie, data, __lead16, c32, result, resultType); \
    } else { \
        /* out of range */ \
        (result)=(resultType)((trie)->initialValue); \
    }

#define UTRIE_GET16(trie, c32, result) _UTRIE_GET(trie, index, c32, result, uint16_t)

#define UTRIE_GET32(trie, c32, result) _UTRIE_GET(trie, data32, c32, result, uint32_t)

#define UTRIE_GET32_FROM_LEAD(trie, c16) _UTRIE_GET_RAW(trie, data32, 0, c16)

#define UTRIE_GET32_FROM_OFFSET_TRAIL(trie, offset, c2) _UTRIE_GET_RAW(trie, data32, offset, (c2)&0x3ff)


#define U16_GET(s, start, i, length, c) { \
    (c)=(s)[i]; \
    if(U16_IS_SURROGATE(c)) { \
        uint16_t __c2; \
        if(U16_IS_SURROGATE_LEAD(c)) { \
            if((i)+1<(length) && U16_IS_TRAIL(__c2=(s)[(i)+1])) { \
                (c)=U16_GET_SUPPLEMENTARY((c), __c2); \
            } \
        } else { \
            if((i)-1>=(start) && U16_IS_LEAD(__c2=(s)[(i)-1])) { \
                (c)=U16_GET_SUPPLEMENTARY(__c2, (c)); \
            } \
        } \
    } \
}


int32_t defaultGetFoldingOffset(uint32_t data);

#endif
