
#ifndef _BidiPreoerty_h
#define _BidiPreoerty_h

#include  "UChar.h"
#include  "UnicodeGlobal.h"


#define UBIDI_JT_MASK           0x000000e0

typedef struct UBiDiProps UBiDiProps;

enum {
    UBIDI_IX_INDEX_TOP,
    UBIDI_IX_LENGTH,
    UBIDI_IX_TRIE_SIZE,
    UBIDI_IX_MIRROR_LENGTH,

    UBIDI_IX_JG_START,
    UBIDI_IX_JG_LIMIT,

    UBIDI_MAX_VALUES_INDEX=15,
    UBIDI_IX_TOP=16
};


enum {
    UBIDI_JT_SHIFT=5,
    UBIDI_JOIN_CONTROL_SHIFT=10,
    UBIDI_BIDI_CONTROL_SHIFT=11,

    UBIDI_IS_MIRRORED_SHIFT=12,
    UBIDI_MIRROR_DELTA_SHIFT=13,

    UBIDI_MAX_JG_SHIFT=16
};

#define UBIDI_CLASS_MASK        0x0000001f

#define UBIDI_GET_CLASS(props) ((props)&UBIDI_CLASS_MASK)

enum {
    UBIDI_ESC_MIRROR_DELTA=-4,
    UBIDI_MIN_MIRROR_DELTA=-3,
    UBIDI_MAX_MIRROR_DELTA=3
};


enum {
    UBIDI_MIRROR_INDEX_SHIFT=21,
    UBIDI_MAX_MIRROR_INDEX=0x7ff
};

#define UBIDI_GET_MIRROR_CODE_POINT(m) (USChar32)((m)&0x1fffff)

#define UBIDI_GET_MIRROR_INDEX(m) ((m)>>UBIDI_MIRROR_INDEX_SHIFT)

#define UBIDI_GET_FLAG(props, shift) (((props)>>(shift))&1)


UCharDirection u_charDirection(USChar32 c);
USChar32 u_charMirror(USChar32 c);
UBool ubidi_isMirrored(const UBiDiProps *bdp, USChar32 c);
UBool ubidi_isBidiControl(const UBiDiProps *bdp, USChar32 c);
UBool ubidi_isJoinControl(const UBiDiProps *bdp, USChar32 c);

UJoiningType ubidi_getJoiningType(const UBiDiProps *bdp, USChar32 c);
UJoiningGroup ubidi_getJoiningGroup(const UBiDiProps *bdp, USChar32 c);

const UBiDiProps * ubidi_getSingleton(UErrorCode *pErrorCode);

#endif
