#include  "UnicodeTrie.h"
#include  "BidiProperty.h"

struct UBiDiProps {
    const int32_t *indexes;
    const uint32_t *mirrors;
    const uint8_t *jgArray;

    UTrie trie;
    uint8_t formatVersion[4];
};

#include  "ubidi_props_data.cpp"

/* UTRIE_GET16() itself validates c */
#define GET_PROPS(bdp, c, result) \
    UTRIE_GET16(&(bdp)->trie, c, result);


USChar32 ubidi_getMirror(const UBiDiProps *bdp, USChar32 c) 
{
    uint32_t props;
    int32_t delta;

    GET_PROPS(bdp, c, props);
    delta=((int16_t)props)>>UBIDI_MIRROR_DELTA_SHIFT;
    if(delta!=UBIDI_ESC_MIRROR_DELTA) {
        return c+delta;
    } else {
        /* look for mirror code point in the mirrors[] table */
        const uint32_t *mirrors;
        uint32_t m;
        int32_t i, length;
        USChar32 c2;

        mirrors=bdp->mirrors;
        length=bdp->indexes[UBIDI_IX_MIRROR_LENGTH];

        /* linear search */
        for(i=0; i<length; ++i) {
            m=mirrors[i];
            c2=UBIDI_GET_MIRROR_CODE_POINT(m);
            if(c==c2) {
                /* found c, return its mirror code point using the index in m */
                return UBIDI_GET_MIRROR_CODE_POINT(mirrors[UBIDI_GET_MIRROR_INDEX(m)]);
            } else if(c<c2) {
                break;
            }
        }

        /* c not found, return it itself */
        return c;
    }
}

UCharDirection ubidi_getClass(const UBiDiProps *bdp, USChar32 c) 
{
    uint32_t props;
    GET_PROPS(bdp, c, props);
    return (UCharDirection)UBIDI_GET_CLASS(props);
}


const UBiDiProps * ubidi_getSingleton(UErrorCode *pErrorCode) 
{
    if(U_FAILURE(*pErrorCode)) {
        return NULL;
    }
    return &ubidi_props_singleton;
}


UCharDirection u_charDirection(USChar32 c) 
{
    UErrorCode errorCode=U_ZERO_ERROR;
    const UBiDiProps *bdp=ubidi_getSingleton(&errorCode);
    if(bdp!=NULL) {
        return ubidi_getClass(bdp, c);
    } else {
        return U_LEFT_TO_RIGHT;
    }
}


USChar32 u_charMirror(USChar32 c) 
{
    UErrorCode errorCode=U_ZERO_ERROR;
    const UBiDiProps *bdp=ubidi_getSingleton(&errorCode);
    if(bdp!=NULL) {
        return ubidi_getMirror(bdp, c);
    } else {
        return c;
    }
}

UBool ubidi_isMirrored(const UBiDiProps *bdp, USChar32 c) 
{
    uint32_t props;
    GET_PROPS(bdp, c, props);
    return (UBool)UBIDI_GET_FLAG(props, UBIDI_IS_MIRRORED_SHIFT);
}

UBool ubidi_isBidiControl(const UBiDiProps *bdp, USChar32 c) 
{
    uint32_t props;
    GET_PROPS(bdp, c, props);
    return (UBool)UBIDI_GET_FLAG(props, UBIDI_BIDI_CONTROL_SHIFT);
}

UBool ubidi_isJoinControl(const UBiDiProps *bdp, USChar32 c) 
{
    uint32_t props;
    GET_PROPS(bdp, c, props);
    return (UBool)UBIDI_GET_FLAG(props, UBIDI_JOIN_CONTROL_SHIFT);
}


UJoiningType ubidi_getJoiningType(const UBiDiProps *bdp, USChar32 c) 
{
    uint32_t props;
    GET_PROPS(bdp, c, props);
    return (UJoiningType)((props&UBIDI_JT_MASK)>>UBIDI_JT_SHIFT);
}


UJoiningGroup ubidi_getJoiningGroup(const UBiDiProps *bdp, USChar32 c)
{
    USChar32 start, limit;

    start=bdp->indexes[UBIDI_IX_JG_START];
    limit=bdp->indexes[UBIDI_IX_JG_LIMIT];
    if(start<=c && c<limit) {
        return (UJoiningGroup)bdp->jgArray[c-start];
    } else {
        return U_JG_NO_JOINING_GROUP;
    }
}

