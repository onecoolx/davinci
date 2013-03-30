
#include  "UChar.h"
#include  "UnicodeGlobal.h"
#include  "UnicodeSet.h"
#include  "UnicodeTrie.h"
#include  "Normalize.h"
#include  "StringCase.h"

#include <wtf/Assertions.h>
#include <wtf/FastMalloc.h>

#include  "unorm_props_data.cpp"

enum {
    _NORM_OPTIONS_NX_MASK=0x1f,
    _NORM_OPTIONS_UNICODE_MASK=0x60,
    _NORM_OPTIONS_SETS_MASK=0x7f,

    _NORM_OPTIONS_UNICODE_SHIFT=5,

    _NORM_OPTIONS_COMPAT=0x1000,
    _NORM_OPTIONS_COMPOSE_CONTIGUOUS=0x2000
};

typedef UBool cleanupFunc(void);

#define LENGTHOF(a) (sizeof(a)/sizeof(a[0]))

static inline UBool _haveData(UErrorCode &errorCode) 
{
    return U_SUCCESS(errorCode);
}

static inline const uint16_t *_getExtraData(uint32_t norm32) 
{
    return extraData+(norm32>>_NORM_EXTRA_SHIFT);
}

static inline uint32_t _getNorm32(UChar c) 
{
    return UTRIE_GET32_FROM_LEAD(&normTrie, c);
}

static UnicodeSet *nxCache[_NORM_OPTIONS_SETS_MASK+1]={ NULL };

static inline UBool isNorm32LeadSurrogate(uint32_t norm32) 
{
    return _NORM_MIN_SPECIAL<=norm32 && norm32<_NORM_SURROGATES_TOP;
}


static inline uint32_t _getNorm32FromSurrogatePair(uint32_t norm32, UChar c2) 
{
    norm32 = UTRIE_BMP_INDEX_LENGTH+
            ((norm32>>(_NORM_EXTRA_SHIFT-UTRIE_SURROGATE_BLOCK_BITS))&
             (0x3ff<<UTRIE_SURROGATE_BLOCK_BITS));
    return UTRIE_GET32_FROM_OFFSET_TRAIL(&normTrie, norm32, c2);
}


static inline uint32_t _getNorm32(const UChar *p, uint32_t mask) 
{
    uint32_t norm32=_getNorm32(*p);
    if((norm32&mask) && isNorm32LeadSurrogate(norm32)) {
        norm32=_getNorm32FromSurrogatePair(norm32, *(p+1));
    }
    return norm32;
}

UBool u_growBufferFromStatic(void *context,UChar **pBuffer, int32_t *pCapacity, int32_t reqCapacity, int32_t length) 
{
    UChar *newBuffer=(UChar *)fastMalloc(reqCapacity*U_SIZEOF_UCHAR);
    if(newBuffer!=NULL) {
        if(length>0) {
            memcpy(newBuffer, *pBuffer, length*U_SIZEOF_UCHAR);
        }
        *pCapacity=reqCapacity;
    } else {
        *pCapacity=0;
    }

    if(*pBuffer!=(UChar *)context) {
        fastFree(*pBuffer);
    }

    *pBuffer=newBuffer;
    return (UBool)(newBuffer!=NULL);
}


static inline UBool nx_contains(const UnicodeSet *nx, USChar32 c) 
{
    return nx!=NULL && nx->contains(c);
}

static inline UBool nx_contains(const UnicodeSet *nx, UChar c, UChar c2) 
{
    return nx!=NULL && nx->contains(c2==0 ? c : U16_GET_SUPPLEMENTARY(c, c2));
}

static inline UBool isNorm32Regular(uint32_t norm32) 
{
    return norm32<_NORM_MIN_SPECIAL;
}

static inline UBool isNorm32HangulOrJamo(uint32_t norm32) 
{
    return norm32>=_NORM_MIN_HANGUL;
}

static inline UBool isHangulWithoutJamoT(UChar c) 
{
    c-=HANGUL_BASE;
    return c<HANGUL_COUNT && c%JAMO_T_COUNT==0;
}


static inline uint32_t _getNextCombining(UChar *&p, const UChar *limit,
                  UChar &c, UChar &c2, uint16_t &combiningIndex, uint8_t &cc, const UnicodeSet *nx) 
{
    uint32_t norm32, combineFlags;

    c=*p++;
    norm32=_getNorm32(c);

    c2=0;
    combiningIndex=0;
    cc=0;

    if((norm32&(_NORM_CC_MASK|_NORM_COMBINES_ANY))==0) {
        return 0;
    } else {
        if(isNorm32Regular(norm32)) {
        } else if(isNorm32HangulOrJamo(norm32)) {
            combiningIndex=(uint16_t)(0xfff0|(norm32>>_NORM_EXTRA_SHIFT));
            return norm32&_NORM_COMBINES_ANY;
        } else {
            if(p!=limit && UTF_IS_SECOND_SURROGATE(c2=*p)) {
                ++p;
                norm32=_getNorm32FromSurrogatePair(norm32, c2);
            } else {
                c2=0;
                return 0;
            }
        }

        if(nx_contains(nx, c, c2)) {
            return 0;
        }

        cc=(uint8_t)(norm32>>_NORM_CC_SHIFT);

        combineFlags=norm32&_NORM_COMBINES_ANY;
        if(combineFlags!=0) {
            combiningIndex=*(_getExtraData(norm32)-1);
        }
        return combineFlags;
    }
}

static inline uint16_t _combine(const uint16_t *table, uint16_t combineBackIndex, uint16_t &value, uint16_t &value2) 
{
    uint16_t key;

    for(;;) {
        key=*table++;
        if(key>=combineBackIndex) {
            break;
        }
        table+= *table&0x8000 ? 2 : 1;
    }

    if((key&0x7fff)==combineBackIndex) {
        value=*table;

        key=(uint16_t)((value&0x2000)+1);

        if(value&0x8000) {
            if(value&0x4000) {
                value=(uint16_t)((value&0x3ff)|0xd800);
                value2=*(table+1);
            } else {
                value=*(table+1);
                value2=0;
            }
        } else {
            value&=0x1fff;
            value2=0;
        }

        return key;
    } else {
        return 0;
    }
}


static inline uint16_t _getCombiningIndexFromStarter(UChar c, UChar c2) 
{
    uint32_t norm32;

    norm32=_getNorm32(c);
    if(c2!=0) {
        norm32=_getNorm32FromSurrogatePair(norm32, c2);
    }
    return *(_getExtraData(norm32)-1);
}

static uint8_t _recompose(UChar *p, UChar *&limit, int32_t options, const UnicodeSet *nx) 
{
    UChar *starter, *pRemove, *q, *r;
    uint32_t combineFlags;
    UChar c, c2;
    uint16_t combineFwdIndex, combineBackIndex;
    uint16_t result, value, value2;
    uint8_t cc, prevCC;
    UBool starterIsSupplementary;

    starter=NULL;
    combineFwdIndex=0;
    combineBackIndex=0;
    value=value2=0;
    starterIsSupplementary=FALSE;
    prevCC=0;

    for(;;) {
        combineFlags=_getNextCombining(p, limit, c, c2, combineBackIndex, cc, nx);
        if((combineFlags&_NORM_COMBINES_BACK) && starter!=NULL) {
            if(combineBackIndex&0x8000) {
                if((options&UNORM_BEFORE_PRI_29) || prevCC==0) {
                    pRemove=NULL;
                    combineFlags=0;
                    c2=*starter;
                    if(combineBackIndex==0xfff2) {
                        c2=(UChar)(c2-JAMO_L_BASE);
                        if(c2<JAMO_L_COUNT) {
                            pRemove=p-1;
                            c=(UChar)(HANGUL_BASE+(c2*JAMO_V_COUNT+(c-JAMO_V_BASE))*JAMO_T_COUNT);
                            if(p!=limit && (c2=(UChar)(*p-JAMO_T_BASE))<JAMO_T_COUNT) {
                                ++p;
                                c+=c2;
                            } else {
                                combineFlags=_NORM_COMBINES_FWD;
                            }
                            if(!nx_contains(nx, c)) {
                                *starter=c;
                            } else {
                                if(!isHangulWithoutJamoT(c)) {
                                    --p; 
                                }
                                pRemove=NULL;
                            }
                        }

                    } else {
                        if(isHangulWithoutJamoT(c2)) {
                            c2+=(UChar)(c-JAMO_T_BASE);
                            if(!nx_contains(nx, c2)) {
                                pRemove=p-1;
                                *starter=c2;
                            }
                        }
                    }

                    if(pRemove!=NULL) {
                        q=pRemove;
                        r=p;
                        while(r<limit) {
                            *q++=*r++;
                        }
                        p=pRemove;
                        limit=q;
                    }

                    c2=0; /* c2 held *starter temporarily */

                    if(combineFlags!=0) {
                        if(p==limit) {
                            return prevCC;
                        }

                         combineFwdIndex=0xfff0;
                        continue;
                    }
                }

            } else if(
                !(combineFwdIndex&0x8000) &&
                ((options&UNORM_BEFORE_PRI_29) ?
                    (prevCC!=cc || prevCC==0) :
                    (prevCC<cc || prevCC==0)) &&
                0!=(result=_combine(combiningTable+combineFwdIndex, combineBackIndex, value, value2)) &&
                !nx_contains(nx, value, value2)
            ) {
                pRemove= c2==0 ? p-1 : p-2; /* pointer to the combining mark */

                 *starter=(UChar)value;
                if(starterIsSupplementary) {
                    if(value2!=0) {
                        *(starter+1)=(UChar)value2;
                    } else {
                        starterIsSupplementary=FALSE;
                        q=starter+1;
                        r=q+1;
                        while(r<pRemove) {
                            *q++=*r++;
                        }
                        --pRemove;
                    }
                } else if(value2!=0) {
                    starterIsSupplementary=TRUE;
                    ++starter; /* temporarily increment for the loop boundary */
                    q=pRemove;
                    r=++pRemove;
                    while(starter<q) {
                        *--r=*--q;
                    }
                    *starter=(UChar)value2;
                    --starter; /* undo the temporary increment */
                }

                if(pRemove<p) {
                    q=pRemove;
                    r=p;
                    while(r<limit) {
                        *q++=*r++;
                    }
                    p=pRemove;
                    limit=q;
                }

                if(p==limit) {
                    return prevCC;
                }

                if(result>1) {
                    combineFwdIndex=_getCombiningIndexFromStarter((UChar)value, (UChar)value2);
                } else {
                    starter=NULL;
                }

                continue;
            }
        }

        prevCC=cc;
        if(p==limit) {
            return prevCC;
        }

        if(cc==0) {
            if(combineFlags&_NORM_COMBINES_FWD) {
                if(c2==0) {
                    starterIsSupplementary=FALSE;
                    starter=p-1;
                } else {
                    starterIsSupplementary=TRUE;
                    starter=p-2;
                }
                combineFwdIndex=combineBackIndex;
            } else {
                starter=NULL;
            }
        } else if(options&_NORM_OPTIONS_COMPOSE_CONTIGUOUS) {
            starter=NULL;
        }
    }
}


static inline const UChar * _decompose(uint32_t norm32, uint32_t qcMask, 
                                            int32_t &length, uint8_t &cc, uint8_t &trailCC) 
{
    const UChar *p=(const UChar *)_getExtraData(norm32);
    length=*p++;

    if((norm32&qcMask&_NORM_QC_NFKD)!=0 && length>=0x100) {
        p+=((length>>7)&1)+(length&_NORM_DECOMP_LENGTH_MASK);
        length>>=8;
    }

    if(length&_NORM_DECOMP_FLAG_LENGTH_HAS_CC) {
        UChar bothCCs=*p++;
        cc=(uint8_t)(bothCCs>>8);
        trailCC=(uint8_t)bothCCs;
    } else {
        cc=trailCC=0;
    }

    length&=_NORM_DECOMP_LENGTH_MASK;
    return p;
}


static inline uint32_t _getPrevNorm32(const UChar *start, const UChar *&src,
                                            uint32_t minC, uint32_t mask, UChar &c, UChar &c2) 
{
    uint32_t norm32;

    c=*--src;
    c2=0;

    if(c<minC) {
        return 0;
    } else if(!UTF_IS_SURROGATE(c)) {
        return _getNorm32(c);
    } else if(UTF_IS_SURROGATE_FIRST(c)) {
        return 0;
    } else if(src!=start && UTF_IS_FIRST_SURROGATE(c2=*(src-1))) {
        --src;
        norm32=_getNorm32(c2);

        if((norm32&mask)==0) {
            return 0;
        } else {
            return _getNorm32FromSurrogatePair(norm32, c);
        }
    } else {
        c2=0;
        return 0;
    }
}


static inline uint8_t _getPrevCC(const UChar *start, const UChar *&p) 
{
    UChar c, c2;
    return (uint8_t)(_getPrevNorm32(start, p, _NORM_MIN_WITH_LEAD_CC, _NORM_CC_MASK, c, c2)>>_NORM_CC_SHIFT);
}

static uint8_t _insertOrdered(const UChar *start, UChar *current, UChar *p, UChar c, UChar c2, uint8_t cc) 
{
    const UChar *pBack, *pPreBack;
    UChar *r;
    uint8_t prevCC, trailCC=cc;

    if(start<current && cc!=0) {
        pPreBack=pBack=current;
        prevCC=_getPrevCC(start, pPreBack);
        if(cc<prevCC) {
            trailCC=prevCC;
            pBack=pPreBack;
            while(start<pPreBack) {
                prevCC=_getPrevCC(start, pPreBack);
                if(cc>=prevCC) {
                    break;
                }
                pBack=pPreBack;
            }
            r=p;
            do {
                *--r=*--current;
            } while(pBack!=current);
        }
    }

    *current=c;
    if(c2!=0) {
        *(current+1)=c2;
    }

    return trailCC;
}

static inline uint8_t _getNextCC(const UChar *&p, const UChar *limit, UChar &c, UChar &c2) 
{
    uint32_t norm32;

    c=*p++;
    norm32=_getNorm32(c);
    if((norm32&_NORM_CC_MASK)==0) {
        c2=0;
        return 0;
    } else {
        if(!isNorm32LeadSurrogate(norm32)) {
            c2=0;
        } else {
            /* c is a lead surrogate, get the real norm32 */
            if(p!=limit && UTF_IS_SECOND_SURROGATE(c2=*p)) {
                ++p;
                norm32=_getNorm32FromSurrogatePair(norm32, c2);
            } else {
                c2=0;
                return 0;
            }
        }

        return (uint8_t)(norm32>>_NORM_CC_SHIFT);
    }
}

static uint8_t _mergeOrdered(UChar *start, UChar *current,
              const UChar *next, const UChar *limit, UBool isOrdered=TRUE) 
{
    UChar *r;
    UChar c, c2;
    uint8_t cc, trailCC=0;
    UBool adjacent;

    adjacent= current==next;

    if(start!=current || !isOrdered) {
        while(next<limit) {
            cc=_getNextCC(next, limit, c, c2);
            if(cc==0) {
                /* does not bubble back */
                trailCC=0;
                if(adjacent) {
                    current=(UChar *)next;
                } else {
                    *current++=c;
                    if(c2!=0) {
                        *current++=c2;
                    }
                }
                if(isOrdered) {
                    break;
                } else {
                    start=current;
                }
            } else {
                r=current+(c2==0 ? 1 : 2);
                trailCC=_insertOrdered(start, current, r, c, c2, cc);
                current=r;
            }
        }
    }

    if(next==limit) {
        /* we know the cc of the last code point */
        return trailCC;
    } else {
        if(!adjacent) {
            /* copy the second string part */
            do {
                *current++=*next++;
            } while(next!=limit);
            limit=current;
        }
        return _getPrevCC(start, limit);
    }
}



static int32_t _decompose(UChar *dest, int32_t destCapacity,
           const UChar *src, int32_t srcLength, UBool compat, const UnicodeSet *nx, uint8_t &outTrailCC) 
{
    UChar buffer[3];
    const UChar *limit, *prevSrc, *p;
    uint32_t norm32, ccOrQCMask, qcMask;
    int32_t destIndex, reorderStartIndex, length;
    UChar c, c2, minNoMaybe;
    uint8_t cc, prevCC, trailCC;

    if(!compat) {
        minNoMaybe=(UChar)indexes[_NORM_INDEX_MIN_NFD_NO_MAYBE];
        qcMask=_NORM_QC_NFD;
    } else {
        minNoMaybe=(UChar)indexes[_NORM_INDEX_MIN_NFKD_NO_MAYBE];
        qcMask=_NORM_QC_NFKD;
    }

    /* initialize */
    ccOrQCMask=_NORM_CC_MASK|qcMask;
    destIndex=reorderStartIndex=0;
    prevCC=0;

    /* avoid compiler warnings */
    norm32=0;
    c=0;
    cc=0;
    trailCC=0;

    if(srcLength>=0) {
        /* string with length */
        limit=src+srcLength;
    } else /* srcLength==-1 */ {
        /* zero-terminated string */
        limit=NULL;
    }

    for(;;) {
        /* count code units below the minimum or with irrelevant data for the quick check */
        prevSrc=src;
        if(limit==NULL) {
            while((c=*src)<minNoMaybe ? c!=0 : ((norm32=_getNorm32(c))&ccOrQCMask)==0) {
                prevCC=0;
                ++src;
            }
        } else {
            while(src!=limit && ((c=*src)<minNoMaybe || ((norm32=_getNorm32(c))&ccOrQCMask)==0)) {
                prevCC=0;
                ++src;
            }
        }

        /* copy these code units all at once */
        if(src!=prevSrc) {
            length=(int32_t)(src-prevSrc);
            if((destIndex+length)<=destCapacity) {
                memcpy(dest+destIndex, prevSrc, length*U_SIZEOF_UCHAR);
            }
            destIndex+=length;
            reorderStartIndex=destIndex;
        }

        /* end of source reached? */
        if(limit==NULL ? c==0 : src==limit) {
            break;
        }

        ++src;

        if(isNorm32HangulOrJamo(norm32)) {
            if(nx_contains(nx, c)) {
                c2=0;
                p=NULL;
                length=1;
            } else {
                /* Hangul syllable: decompose algorithmically */
                p=buffer;
                cc=trailCC=0;

                c-=HANGUL_BASE;

                c2=(UChar)(c%JAMO_T_COUNT);
                c/=JAMO_T_COUNT;
                if(c2>0) {
                    buffer[2]=(UChar)(JAMO_T_BASE+c2);
                    length=3;
                } else {
                    length=2;
                }

                buffer[1]=(UChar)(JAMO_V_BASE+c%JAMO_V_COUNT);
                buffer[0]=(UChar)(JAMO_L_BASE+c/JAMO_V_COUNT);
            }
        } else {
            if(isNorm32Regular(norm32)) {
                c2=0;
                length=1;
            } else {
                /* c is a lead surrogate, get the real norm32 */
                if(src!=limit && UTF_IS_SECOND_SURROGATE(c2=*src)) {
                    ++src;
                    length=2;
                    norm32=_getNorm32FromSurrogatePair(norm32, c2);
                } else {
                    c2=0;
                    length=1;
                    norm32=0;
                }
            }

            /* get the decomposition and the lead and trail cc's */
            if(nx_contains(nx, c, c2)) {
                /* excluded: norm32==0 */
                cc=trailCC=0;
                p=NULL;
            } else if((norm32&qcMask)==0) {
                /* c does not decompose */
                cc=trailCC=(uint8_t)(norm32>>_NORM_CC_SHIFT);
                p=NULL;
            } else {
                /* c decomposes, get everything from the variable-length extra data */
                p=_decompose(norm32, qcMask, length, cc, trailCC);
                if(length==1) {
                    /* fastpath a single code unit from decomposition */
                    c=*p;
                    c2=0;
                    p=NULL;
                }
            }
        }

        /* append the decomposition to the destination buffer, assume length>0 */
        if((destIndex+length)<=destCapacity) {
            UChar *reorderSplit=dest+destIndex;
            if(p==NULL) {
                /* fastpath: single code point */
                if(cc!=0 && cc<prevCC) {
                    /* (c, c2) is out of order with respect to the preceding text */
                    destIndex+=length;
                    trailCC=_insertOrdered(dest+reorderStartIndex, reorderSplit, dest+destIndex, c, c2, cc);
                } else {
                    /* just append (c, c2) */
                    dest[destIndex++]=c;
                    if(c2!=0) {
                        dest[destIndex++]=c2;
                    }
                }
            } else {
                /* general: multiple code points (ordered by themselves) from decomposition */
                if(cc!=0 && cc<prevCC) {
                    /* the decomposition is out of order with respect to the preceding text */
                    destIndex+=length;
                    trailCC=_mergeOrdered(dest+reorderStartIndex, reorderSplit, p, p+length);
                } else {
                    /* just append the decomposition */
                    do {
                        dest[destIndex++]=*p++;
                    } while(--length>0);
                }
            }
        } else {
            /* buffer overflow */
            /* keep incrementing the destIndex for preflighting */
            destIndex+=length;
        }

        prevCC=trailCC;
        if(prevCC==0) {
            reorderStartIndex=destIndex;
        }
    }

    outTrailCC=prevCC;
    return destIndex;
}




/* decompose and recompose [prevStarter..src[ */
static const UChar * _composePart(UChar *stackBuffer, UChar *&buffer, int32_t &bufferCapacity, int32_t &length,
             const UChar *prevStarter, const UChar *src, uint8_t &prevCC, int32_t options, const UnicodeSet *nx,
             UErrorCode *pErrorCode) 
{
    UChar *recomposeLimit;
    uint8_t trailCC;
    UBool compat;

    compat=(UBool)((options&_NORM_OPTIONS_COMPAT)!=0);

    /* decompose [prevStarter..src[ */
    length=_decompose(buffer, bufferCapacity,
                      prevStarter, (int32_t)(src-prevStarter),
                      compat, nx,
                      trailCC);
    if(length>bufferCapacity) {
        if(!u_growBufferFromStatic(stackBuffer, &buffer, &bufferCapacity, 2*length, 0)) {
            *pErrorCode=U_MEMORY_ALLOCATION_ERROR;
            return NULL;
        }
        length=_decompose(buffer, bufferCapacity,
                          prevStarter, (int32_t)(src-prevStarter),
                          compat, nx,
                          trailCC);
    }

    /* recompose the decomposition */
    recomposeLimit=buffer+length;
    if(length>=2) {
        prevCC=_recompose(buffer, recomposeLimit, options, nx);
    }

    /* return with a pointer to the recomposition and its length */
    length=(int32_t)(recomposeLimit-buffer);
    return buffer;
}



static inline UBool _isTrueStarter(uint32_t norm32, uint32_t ccOrQCMask, uint32_t decompQCMask) 
{
    if((norm32&ccOrQCMask)==0) {
        return TRUE; /* this is a true starter (could be Hangul or Jamo L) */
    }

    if((norm32&decompQCMask)!=0) {
        const UChar *p;
        int32_t length;
        uint8_t cc, trailCC;

        p=_decompose(norm32, decompQCMask, length, cc, trailCC);
        if(cc==0) {
            uint32_t qcMask=ccOrQCMask&_NORM_QC_MASK;

            if((_getNorm32(p, qcMask)&qcMask)==0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

static const UChar * _findPreviousStarter(const UChar *start, const UChar *src,
                     uint32_t ccOrQCMask, uint32_t decompQCMask, UChar minNoMaybe) 
{
    uint32_t norm32;
    UChar c, c2;

    while(start<src) {
        norm32=_getPrevNorm32(start, src, minNoMaybe, ccOrQCMask|decompQCMask, c, c2);
        if(_isTrueStarter(norm32, ccOrQCMask, decompQCMask)) {
            break;
        }
    }
    return src;
}


static const UChar * _findNextStarter(const UChar *src, const UChar *limit,
                 uint32_t qcMask, uint32_t decompQCMask, UChar minNoMaybe) 
{
    const UChar *p;
    uint32_t norm32, ccOrQCMask;
    int32_t length;
    UChar c, c2;
    uint8_t cc, trailCC;

    ccOrQCMask=_NORM_CC_MASK|qcMask;

    for(;;) {
        if(src==limit) {
            break; /* end of string */
        }
        c=*src;
        if(c<minNoMaybe) {
            break; /* catches NUL terminater, too */
        }

        norm32=_getNorm32(c);
        if((norm32&ccOrQCMask)==0) {
            break; /* true starter */
        }

        if(isNorm32LeadSurrogate(norm32)) {
            if((src+1)==limit || !UTF_IS_SECOND_SURROGATE(c2=*(src+1))) {
                break; /* unmatched first surrogate: counts as a true starter */
            }
            norm32=_getNorm32FromSurrogatePair(norm32, c2);

            if((norm32&ccOrQCMask)==0) {
                break; /* true starter */
            }
        } else {
            c2=0;
        }

        if(norm32&decompQCMask) {
            p=_decompose(norm32, decompQCMask, length, cc, trailCC);

            if(cc==0 && (_getNorm32(p, qcMask)&qcMask)==0) {
                break; /* true starter */
            }
        }

        src+= c2==0 ? 1 : 2; /* not a true starter, continue */
    }

    return src;
}


int32_t getFoldingNormOffset(uint32_t norm32) 
{
    if(isNorm32LeadSurrogate(norm32)) {
        return
            UTRIE_BMP_INDEX_LENGTH+
                (((int32_t)norm32>>(_NORM_EXTRA_SHIFT-UTRIE_SURROGATE_BLOCK_BITS))&
                 (0x3ff<<UTRIE_SURROGATE_BLOCK_BITS));
    } else {
        return 0;
    }
}

int32_t getFoldingAuxOffset(uint32_t data) 
{
    return (int32_t)(data&_NORM_AUX_FNC_MASK)<<UTRIE_SURROGATE_BLOCK_BITS;
}


UBool unorm_internalIsFullCompositionExclusion(USChar32 c) 
{
    if(auxTrie.index!=NULL) {
        uint16_t aux;

        UTRIE_GET16(&auxTrie, c, aux);
        return (UBool)((aux&_NORM_AUX_COMP_EX_MASK)!=0);
    } else {
        return FALSE;
    }
}

UBool unorm_isCanonSafeStart(USChar32 c) 
{
    if(auxTrie.index!=NULL) {
        uint16_t aux;

        UTRIE_GET16(&auxTrie, c, aux);
        return (UBool)((aux&_NORM_AUX_UNSAFE_MASK)==0);
    } else {
        return FALSE;
    }
}

/* uchar.h */
uint8_t u_getCombiningClass(USChar32 c) 
{
        uint32_t norm32;

        UTRIE_GET32(&normTrie, c, norm32);
        return (uint8_t)(norm32>>_NORM_CC_SHIFT);
}

UBool unorm_isNFSkippable(USChar32 c, UNormalizationMode mode) 
{
    uint32_t norm32, mask;
    uint16_t aux, fcd;

    switch(mode) {
    case UNORM_NONE:
        return TRUE;
    case UNORM_NFD:
        mask=_NORM_CC_MASK|_NORM_QC_NFD;
        break;
    case UNORM_NFKD:
        mask=_NORM_CC_MASK|_NORM_QC_NFKD;
        break;
    case UNORM_NFC:
        mask=_NORM_CC_MASK|_NORM_COMBINES_ANY|(_NORM_QC_NFC&_NORM_QC_ANY_NO);
        break;
    case UNORM_NFKC:
        mask=_NORM_CC_MASK|_NORM_COMBINES_ANY|(_NORM_QC_NFKC&_NORM_QC_ANY_NO);
        break;
    case UNORM_FCD:
        if(fcdTrie.index!=NULL) {
            UTRIE_GET16(&fcdTrie, c, fcd);
            return fcd<=1;
        } else {
            return FALSE;
        }
    default:
        return FALSE;
    }

    UTRIE_GET32(&normTrie, c, norm32);
    if((norm32&mask)!=0) {
        return FALSE; /* fails (a)..(e), not skippable */
    }

    if(mode<UNORM_NFC) {
        return TRUE; /* NF*D, passed (a)..(c), is skippable */
    }

    if((norm32&_NORM_QC_NFD)==0) {
        return TRUE; /* no canonical decomposition, is skippable */
    }

    if(isNorm32HangulOrJamo(norm32)) {
        return !isHangulWithoutJamoT((UChar)c); /* LVT are skippable, LV are not */
    }

    if(auxTrie.index==NULL) {
        return FALSE; /* no (f) data, say not skippable to be safe */
    }

    UTRIE_GET16(&auxTrie, c, aux);
    return (aux&_NORM_AUX_NFC_SKIP_F_MASK)==0; /* TRUE=skippable if the (f) flag is not set */

}

UNormalizationCheckResult unorm_getQuickCheck(USChar32 c, UNormalizationMode mode) 
{
    static const uint32_t qcMask[UNORM_MODE_COUNT]={
        0, 0, _NORM_QC_NFD, _NORM_QC_NFKD, _NORM_QC_NFC, _NORM_QC_NFKC
    };

    uint32_t norm32;

    UTRIE_GET32(&normTrie, c, norm32);
    norm32&=qcMask[mode];

    if(norm32==0) {
        return UNORM_YES;
    } else if(norm32&_NORM_QC_ANY_NO) {
        return UNORM_NO;
    } else /* _NORM_QC_ANY_MAYBE */ {
        return UNORM_MAYBE;
    }
}


uint16_t unorm_getFCD16FromCodePoint(USChar32 c) 
{
    UErrorCode errorCode;
    uint16_t fcd;

    errorCode=U_ZERO_ERROR;
    if(
        fcdTrie.index==NULL
    ) {
        return 0;
    }

    UTRIE_GET16(&fcdTrie, c, fcd);
    return fcd;
}

int32_t uprv_strCompare(const UChar *s1, int32_t length1,
                const UChar *s2, int32_t length2,
                UBool strncmpStyle, UBool codePointOrder) 
{
    const UChar *start1, *start2, *limit1, *limit2;
    UChar c1, c2;

    start1=s1;
    start2=s2;

    if(length1<0 && length2<0) {
        if(s1==s2) {
            return 0;
        }

        for(;;) {
            c1=*s1;
            c2=*s2;
            if(c1!=c2) {
                break;
            }
            if(c1==0) {
                return 0;
            }
            ++s1;
            ++s2;
        }

        limit1=limit2=NULL;
    } else if(strncmpStyle) {
        if(s1==s2) {
            return 0;
        }

        limit1=start1+length1;

        for(;;) {
            if(s1==limit1) {
                return 0;
            }

            c1=*s1;
            c2=*s2;
            if(c1!=c2) {
                break;
            }
            if(c1==0) {
                return 0;
            }
            ++s1;
            ++s2;
        }

        limit2=start2+length1; /* use length1 here, too, to enforce assumption */
    } else {
        int32_t lengthResult;

        if(length1<0) {
            length1=u_strlen(s1);
        }
        if(length2<0) {
            length2=u_strlen(s2);
        }

        if(length1<length2) {
            lengthResult=-1;
            limit1=start1+length1;
        } else if(length1==length2) {
            lengthResult=0;
            limit1=start1+length1;
        } else /* length1>length2 */ {
            lengthResult=1;
            limit1=start1+length2;
        }

        if(s1==s2) {
            return lengthResult;
        }

        for(;;) {
            if(s1==limit1) {
                return lengthResult;
            }

            c1=*s1;
            c2=*s2;
            if(c1!=c2) {
                break;
            }
            ++s1;
            ++s2;
        }

        limit1=start1+length1;
        limit2=start2+length2;
    }

    if(c1>=0xd800 && c2>=0xd800 && codePointOrder) {
        if(
            (c1<=0xdbff && (s1+1)!=limit1 && UTF_IS_TRAIL(*(s1+1))) ||
            (UTF_IS_TRAIL(c1) && start1!=s1 && UTF_IS_LEAD(*(s1-1)))
        ) {
        } else {
            c1-=0x2800;
        }

        if(
            (c2<=0xdbff && (s2+1)!=limit2 && UTF_IS_TRAIL(*(s2+1))) ||
            (UTF_IS_TRAIL(c2) && start2!=s2 && UTF_IS_LEAD(*(s2-1)))
        ) {
        } else {
            c2-=0x2800;
        }
    }

    return (int32_t)c1-(int32_t)c2;
}

static UNormalizationCheckResult _quickCheck(const UChar *src, int32_t srcLength,
            UNormalizationMode mode,UBool allowMaybe,const UnicodeSet *nx,UErrorCode *pErrorCode) 
{
    UChar stackBuffer[_STACK_BUFFER_CAPACITY];
    UChar *buffer;
    int32_t bufferCapacity;

    const UChar *start, *limit;
    uint32_t norm32, qcNorm32, ccOrQCMask, qcMask;
    int32_t options;
    UChar c, c2, minNoMaybe;
    uint8_t cc, prevCC;
    UNormalizationCheckResult result;

    /* check arguments */
    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return UNORM_MAYBE;
    }

    if(src==NULL || srcLength<-1) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return UNORM_MAYBE;
    }

    if(!_haveData(*pErrorCode)) {
        return UNORM_MAYBE;
    }

    switch(mode) {
    case UNORM_NFC:
        minNoMaybe=(UChar)indexes[_NORM_INDEX_MIN_NFC_NO_MAYBE];
        qcMask=_NORM_QC_NFC;
        options=0;
        break;
    case UNORM_NFKC:
        minNoMaybe=(UChar)indexes[_NORM_INDEX_MIN_NFKC_NO_MAYBE];
        qcMask=_NORM_QC_NFKC;
        options=_NORM_OPTIONS_COMPAT;
        break;

    default:
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return UNORM_MAYBE;
    }

    /* initialize */
    buffer=stackBuffer;
    bufferCapacity=_STACK_BUFFER_CAPACITY;

    ccOrQCMask=_NORM_CC_MASK|qcMask;
    result=UNORM_YES;
    prevCC=0;

    start=src;
    if(srcLength>=0) {
        limit=src+srcLength;
    } else /* srcLength==-1 */ {
        limit=NULL;
    }

    //U_ALIGN_CODE(16);  //changed by malin 07-03-26

    for(;;) {
        if(limit==NULL) {
            for(;;) {
                c=*src++;
                if(c<minNoMaybe) {
                    if(c==0) {
                        goto endloop; /* break out of outer loop */
                    }
                } else if(((norm32=_getNorm32(c))&ccOrQCMask)!=0) {
                    break;
                }
                prevCC=0;
            }
        } else {
            for(;;) {
                if(src==limit) {
                    goto endloop; /* break out of outer loop */
                } else if((c=*src++)>=minNoMaybe && ((norm32=_getNorm32(c))&ccOrQCMask)!=0) {
                    break;
                }
                prevCC=0;
            }
        }

        if(isNorm32LeadSurrogate(norm32)) {
            if(src!=limit && UTF_IS_SECOND_SURROGATE(c2=*src)) {
                ++src;
                norm32=_getNorm32FromSurrogatePair(norm32, c2);
            } else {
                c2=0;
                norm32=0;
            }
        } else {
            c2=0;
        }

        if(nx_contains(nx, c, c2)) {
            norm32=0;
        }

        cc=(uint8_t)(norm32>>_NORM_CC_SHIFT);
        if(cc!=0 && cc<prevCC) {
            result=UNORM_NO;
            break;
        }
        prevCC=cc;

        qcNorm32=norm32&qcMask;
        if(qcNorm32&_NORM_QC_ANY_NO) {
            result=UNORM_NO;
            break;
        } else if(qcNorm32!=0) {
            if(allowMaybe) {
                result=UNORM_MAYBE;
            } else {
                const UChar *prevStarter;
                uint32_t decompQCMask;
                int32_t length;

                decompQCMask=(qcMask<<2)&0xf; /* decomposition quick check mask */

                prevStarter=src-1; /* set prevStarter to the beginning of the current character */
                if(UTF_IS_TRAIL(*prevStarter)) {
                    --prevStarter; /* safe because unpaired surrogates do not result in "maybe" */
                }
                prevStarter=_findPreviousStarter(start, prevStarter, ccOrQCMask, decompQCMask, minNoMaybe);

                src=_findNextStarter(src, limit, qcMask, decompQCMask, minNoMaybe);

                _composePart(stackBuffer, buffer, bufferCapacity,
                             length,
                             prevStarter,
                             src,
                             prevCC,
                             options, nx, pErrorCode);
                if(U_FAILURE(*pErrorCode)) {
                    result=UNORM_MAYBE; /* error (out of memory) */
                    break;
                }

                if(0!=uprv_strCompare(prevStarter, (int32_t)(src-prevStarter), buffer, length, FALSE, FALSE)) {
                    result=UNORM_NO; /* normalization differs */
                    break;
                }

            }
        }
    }
endloop:

    if(buffer!=stackBuffer) {
        fastFree(buffer);
    }

    return result;
}


UNormalizationCheckResult unorm_quickCheck(const UChar *src, int32_t srcLength, 
                                                        UNormalizationMode mode,UErrorCode *pErrorCode) 
{
    return _quickCheck(src, srcLength, mode, TRUE, NULL, pErrorCode);
}

#define UMTX_CHECK(pMutex, expression, result) (result)=(expression);

static cleanupFunc *gCommonCleanupFunctions[UCLN_COMMON_COUNT];

void ucln_common_registerCleanup(ECleanupCommonType type,
                            cleanupFunc *func)
{
    ASSERT(UCLN_COMMON_START < type && type < UCLN_COMMON_COUNT);
    if (UCLN_COMMON_START < type && type < UCLN_COMMON_COUNT)
    {
        gCommonCleanupFunctions[type] = func;
    }
}

static UBool unorm_cleanup(void) 
{
    int32_t i;

    for(i=0; i<(int32_t)LENGTHOF(nxCache); ++i) {
        if (nxCache[i]) {
            delete nxCache[i];
            nxCache[i] = 0;
        }
    }

    return TRUE;
}

UBool NormalizeCleanup(void) 
{
    int commonFunc = UCLN_COMMON_START;

    for (commonFunc++; commonFunc<UCLN_COMMON_COUNT; commonFunc++) {
        if (gCommonCleanupFunctions[commonFunc])
        {
            gCommonCleanupFunctions[commonFunc]();
            gCommonCleanupFunctions[commonFunc] = NULL;
        }
    }
    return TRUE;
}


static const UnicodeSet *
internalGetNXHangul(UErrorCode &errorCode) 
{
    UBool isCached;

    UMTX_CHECK(NULL, (UBool)(nxCache[UNORM_NX_HANGUL]!=NULL), isCached);

    if(!isCached) {
        UnicodeSet *set=new UnicodeSet(0xac00, 0xd7a3);
        if(set==NULL) {
            errorCode=U_MEMORY_ALLOCATION_ERROR;
            return NULL;
        }

        if(nxCache[UNORM_NX_HANGUL]==NULL) {
            nxCache[UNORM_NX_HANGUL]=set;
            set=NULL;
            ucln_common_registerCleanup(UCLN_COMMON_UNORM, unorm_cleanup);
        }

        delete set;
    }

    return nxCache[UNORM_NX_HANGUL];
}



UBool uset_getSerializedSet(USerializedSet* fillSet, const uint16_t* src, int32_t srcLength) 
{
    int32_t length;

    if(fillSet==NULL) {
        return FALSE;
    }
    if(src==NULL || srcLength<=0) {
        fillSet->length=fillSet->bmpLength=0;
        return FALSE;
    }

    length=*src++;
    if(length&0x8000) {
        /* there are supplementary values */
        length&=0x7fff;
        if(srcLength<(2+length)) {
            fillSet->length=fillSet->bmpLength=0;
            return FALSE;
        }
        fillSet->bmpLength=*src++;
    } else {
        /* only BMP values */
        if(srcLength<(1+length)) {
            fillSet->length=fillSet->bmpLength=0;
            return FALSE;
        }
        fillSet->bmpLength=length;
    }
    fillSet->array=src;
    fillSet->length=length;
    return TRUE;
}


UBool uset_getSerializedRange(const USerializedSet* set, int32_t rangeIndex,
                        USChar32* pStart, USChar32* pEnd) 
{
    const uint16_t* array;
    int32_t bmpLength, length;

    if(set==NULL || rangeIndex<0 || pStart==NULL || pEnd==NULL) {
        return FALSE;
    }

    array=set->array;
    length=set->length;
    bmpLength=set->bmpLength;

    rangeIndex*=2; /* address start/limit pairs */
    if(rangeIndex<bmpLength) {
        *pStart=array[rangeIndex++];
        if(rangeIndex<bmpLength) {
            *pEnd=array[rangeIndex];
        } else if(rangeIndex<length) {
            *pEnd=(((int32_t)array[rangeIndex])<<16)|array[rangeIndex+1];
        } else {
            *pEnd=0x110000;
        }
        --*pEnd;
        return TRUE;
    } else {
        rangeIndex-=bmpLength;
        rangeIndex*=2; /* address pairs of pairs of units */
        length-=bmpLength;
        if(rangeIndex<length) {
            array+=bmpLength;
            *pStart=(((int32_t)array[rangeIndex])<<16)|array[rangeIndex+1];
            rangeIndex+=2;
            if(rangeIndex<length) {
                *pEnd=(((int32_t)array[rangeIndex])<<16)|array[rangeIndex+1];
            } else {
                *pEnd=0x110000;
            }
            --*pEnd;
            return TRUE;
        } else {
            return FALSE;
        }
    }
}


static const UnicodeSet * internalGetSerializedNX(int32_t options, int32_t nxIndex, UErrorCode &errorCode) 
{
    UBool isCached;

    UMTX_CHECK(NULL, (UBool)(nxCache[options]!=NULL), isCached);

    if( !isCached &&
        canonStartSets!=NULL &&
        canonStartSets[nxIndex]!=0 && canonStartSets[nxIndex+1]>canonStartSets[nxIndex]
    ) {
        USerializedSet sset;
        UnicodeSet *set;
        USChar32 start, end;
        int32_t i;

        if( !uset_getSerializedSet(
                    &sset,
                    canonStartSets+canonStartSets[nxIndex],
                    canonStartSets[nxIndex+1]-canonStartSets[nxIndex])
        ) {
            errorCode=U_INVALID_FORMAT_ERROR;
            return NULL;
        }

        set=new UnicodeSet();
        if(set==NULL) {
            errorCode=U_MEMORY_ALLOCATION_ERROR;
            return NULL;
        }
        for(i=0; uset_getSerializedRange(&sset, i, &start, &end); ++i) {
            set->add(start, end);
        }

        if(nxCache[options]==NULL) {
            nxCache[options]=set;
            set=NULL;
            ucln_common_registerCleanup(UCLN_COMMON_UNORM, unorm_cleanup);
        }

        delete set;
    }

    return nxCache[options];
}


static const UnicodeSet * internalGetNXCJKCompat(UErrorCode &errorCode) 
{
    return internalGetSerializedNX(UNORM_NX_CJK_COMPAT,
                _NORM_SET_INDEX_NX_CJK_COMPAT_OFFSET,errorCode);
}


static const UnicodeSet * internalGetNXUnicode(uint32_t options, UErrorCode &errorCode) 
{
    int32_t nxIndex;

    options&=_NORM_OPTIONS_UNICODE_MASK;
    switch(options) {
    case 0:
        return NULL;
    case 0x20:
        nxIndex=_NORM_SET_INDEX_NX_UNICODE32_OFFSET;
        break;
    default:
        errorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return NULL;
    }

    return internalGetSerializedNX(options, nxIndex, errorCode);
}

static const UnicodeSet * internalGetNX(int32_t options, UErrorCode &errorCode) 
{
    options&=_NORM_OPTIONS_SETS_MASK;

    UBool isCached;
    UMTX_CHECK(NULL, (UBool)(nxCache[options]!=NULL), isCached);
    if(!isCached) {
        if(options==UNORM_NX_HANGUL) {
            return internalGetNXHangul(errorCode);
        }
        if(options==UNORM_NX_CJK_COMPAT) {
            return internalGetNXCJKCompat(errorCode);
        }
        if((options&_NORM_OPTIONS_UNICODE_MASK)!=0 && (options&_NORM_OPTIONS_NX_MASK)==0) {
            return internalGetNXUnicode(options, errorCode);
        }

        UnicodeSet *set;
        const UnicodeSet *other;
        set=new UnicodeSet();
        if(set==NULL) {
            errorCode=U_MEMORY_ALLOCATION_ERROR;
            return NULL;
        }

        if((options&UNORM_NX_HANGUL)!=0 && NULL!=(other=internalGetNXHangul(errorCode))) {
            set->addAll(*other);
        }
        if((options&UNORM_NX_CJK_COMPAT)!=0 && NULL!=(other=internalGetNXCJKCompat(errorCode))) {
            set->addAll(*other);
        }
        if((options&_NORM_OPTIONS_UNICODE_MASK)!=0 && NULL!=(other=internalGetNXUnicode(options, errorCode))) {
            set->addAll(*other);
        }

        if(U_FAILURE(errorCode)) {
            delete set;
            return NULL;
        }

        if(nxCache[options]==NULL) {
            nxCache[options]=set;
            set=NULL;
            ucln_common_registerCleanup(UCLN_COMMON_UNORM, unorm_cleanup);
        }

        delete set;
    }

    return nxCache[options];
}


static inline const UnicodeSet * getNX(int32_t options, UErrorCode &errorCode) 
{
    if(U_FAILURE(errorCode) || (options&=_NORM_OPTIONS_SETS_MASK)==0) {
        return NULL;
    } else {
        return internalGetNX(options, errorCode);
    }
}

static inline UBool isJamoVTNorm32JamoV(uint32_t norm32) 
{
    return norm32<_NORM_JAMO_V_TOP;
}


static inline UBool _composeHangul(UChar prev, UChar c, uint32_t norm32, const UChar *&src, const UChar *limit,
               UBool compat, UChar *dest, const UnicodeSet *nx) 
{
    if(isJamoVTNorm32JamoV(norm32)) {
        prev=(UChar)(prev-JAMO_L_BASE);
        if(prev<JAMO_L_COUNT) {
            c=(UChar)(HANGUL_BASE+(prev*JAMO_V_COUNT+(c-JAMO_V_BASE))*JAMO_T_COUNT);

            if(src!=limit) {
                UChar next, t;

                next=*src;
                if((t=(UChar)(next-JAMO_T_BASE))<JAMO_T_COUNT) {
                    ++src;
                    c+=t;
                } else if(compat) {
                    norm32=_getNorm32(next);
                    if(isNorm32Regular(norm32) && (norm32&_NORM_QC_NFKD)) {
                        const UChar *p;
                        int32_t length;
                        uint8_t cc, trailCC;

                        p=_decompose(norm32, _NORM_QC_NFKD, length, cc, trailCC);
                        if(length==1 && (t=(UChar)(*p-JAMO_T_BASE))<JAMO_T_COUNT) {
                            /* compatibility Jamo T */
                            ++src;
                            c+=t;
                        }
                    }
                }
            }
            if(nx_contains(nx, c)) {
                if(!isHangulWithoutJamoT(c)) {
                    --src; /* undo ++src from reading the Jamo T */
                }
                return FALSE;
            }
            if(dest!=0) {
                *dest=c;
            }
            return TRUE;
        }
    } else if(isHangulWithoutJamoT(prev)) {
        c=(UChar)(prev+(c-JAMO_T_BASE));
        if(nx_contains(nx, c)) {
            return FALSE;
        }
        if(dest!=0) {
            *dest=c;
        }
        return TRUE;
    }
    return FALSE;
}


static int32_t _compose(UChar *dest, int32_t destCapacity,const UChar *src, int32_t srcLength,
                                int32_t options, const UnicodeSet *nx,UErrorCode *pErrorCode) 
{
    UChar stackBuffer[_STACK_BUFFER_CAPACITY];
    UChar *buffer;
    int32_t bufferCapacity;

    const UChar *limit, *prevSrc, *prevStarter;
    uint32_t norm32, ccOrQCMask, qcMask;
    int32_t destIndex, reorderStartIndex, length;
    UChar c, c2, minNoMaybe;
    uint8_t cc, prevCC;

    if(options&_NORM_OPTIONS_COMPAT) {
        minNoMaybe=(UChar)indexes[_NORM_INDEX_MIN_NFKC_NO_MAYBE];
        qcMask=_NORM_QC_NFKC;
    } else {
        minNoMaybe=(UChar)indexes[_NORM_INDEX_MIN_NFC_NO_MAYBE];
        qcMask=_NORM_QC_NFC;
    }

    /* initialize */
    buffer=stackBuffer;
    bufferCapacity=_STACK_BUFFER_CAPACITY;

    prevStarter=src;

    ccOrQCMask=_NORM_CC_MASK|qcMask;
    destIndex=reorderStartIndex=0;
    prevCC=0;

    norm32=0;
    c=0;

    if(srcLength>=0) {
        limit=src+srcLength;
    } else /* srcLength==-1 */ {
        limit=NULL;
    }

    for(;;) {
        prevSrc=src;
        if(limit==NULL) {
            while((c=*src)<minNoMaybe ? c!=0 : ((norm32=_getNorm32(c))&ccOrQCMask)==0) {
                prevCC=0;
                ++src;
            }
        } else {
            while(src!=limit && ((c=*src)<minNoMaybe || ((norm32=_getNorm32(c))&ccOrQCMask)==0)) {
                prevCC=0;
                ++src;
            }
        }

        if(src!=prevSrc) {
            length=(int32_t)(src-prevSrc);
            if((destIndex+length)<=destCapacity) {
                memcpy(dest+destIndex, prevSrc, length*U_SIZEOF_UCHAR);
            }
            destIndex+=length;
            reorderStartIndex=destIndex;

            prevStarter=src-1;
            if(UTF_IS_SECOND_SURROGATE(*prevStarter) && prevSrc<prevStarter && UTF_IS_FIRST_SURROGATE(*(prevStarter-1)))            {
                --prevStarter;
            }

            prevSrc=src;
        }

        if(limit==NULL ? c==0 : src==limit) {
            break;
        }

        ++src;
        if(isNorm32HangulOrJamo(norm32)) {
            prevCC=cc=0;
            reorderStartIndex=destIndex;

            if(
                destIndex>0 &&
                _composeHangul(
                    *(prevSrc-1), c, norm32, src, limit, (UBool)((options&_NORM_OPTIONS_COMPAT)!=0),
                    destIndex<=destCapacity ? dest+(destIndex-1) : 0,
                    nx)
            ) {
                prevStarter=src;
                continue;
            }

            c2=0;
            length=1;
            prevStarter=prevSrc;
        } else {
            if(isNorm32Regular(norm32)) {
                c2=0;
                length=1;
            } else {
                if(src!=limit && UTF_IS_SECOND_SURROGATE(c2=*src)) {
                    ++src;
                    length=2;
                    norm32=_getNorm32FromSurrogatePair(norm32, c2);
                } else {
                    c2=0;
                    length=1;
                    norm32=0;
                }
            }

            if(nx_contains(nx, c, c2)) {
                cc=0;
            } else if((norm32&qcMask)==0) {
                cc=(uint8_t)(norm32>>_NORM_CC_SHIFT);
            } else {
                const UChar *p;
                uint32_t decompQCMask;

                decompQCMask=(qcMask<<2)&0xf; /* decomposition quick check mask */

                if(_isTrueStarter(norm32, ccOrQCMask, decompQCMask)) {
                    prevStarter=prevSrc;
                } else {
                    destIndex-=(int32_t)(prevSrc-prevStarter);
                }

                src=_findNextStarter(src, limit, qcMask, decompQCMask, minNoMaybe);

                p=_composePart(stackBuffer, buffer, bufferCapacity,
                               length,          /* output */
                               prevStarter, src,
                               prevCC,          /* output */
                               options, nx,
                               pErrorCode);

                if(p==NULL) {
                    destIndex=0;   /* an error occurred (out of memory) */
                    break;
                }

                if((destIndex+length)<=destCapacity) {
                    while(length>0) {
                        dest[destIndex++]=*p++;
                        --length;
                    }
                } else {
                    destIndex+=length;
                }

                /* set the next starter */
                prevStarter=src;

                continue;
            }
        }

        if((destIndex+length)<=destCapacity) {
            if(cc!=0 && cc<prevCC) {
                UChar *reorderSplit=dest+destIndex;
                destIndex+=length;
                prevCC=_insertOrdered(dest+reorderStartIndex, reorderSplit, dest+destIndex, c, c2, cc);
            } else {
                /* just append (c, c2) */
                dest[destIndex++]=c;
                if(c2!=0) {
                    dest[destIndex++]=c2;
                }
                prevCC=cc;
            }
        } else {
            destIndex+=length;
            prevCC=cc;
        }
    }

    /* cleanup */
    if(buffer!=stackBuffer) {
        fastFree(buffer);
    }

    return destIndex;
}

int32_t unorm_internalNormalizeWithNX(UChar *dest, int32_t destCapacity,const UChar *src, int32_t srcLength,
                              UNormalizationMode mode, int32_t options, const UnicodeSet *nx, UErrorCode *pErrorCode) 
{
    int32_t destLength;

    switch(mode) {
    case UNORM_NFC:
        destLength=_compose(dest, destCapacity,
                            src, srcLength,
                            options, nx, pErrorCode);
        break;
    case UNORM_NFKC:
        destLength=_compose(dest, destCapacity,
                            src, srcLength,
                            options|_NORM_OPTIONS_COMPAT, nx, pErrorCode);
        break;
    case UNORM_NONE:
        if(srcLength==-1) {
            srcLength=u_strlen(src);
        }
        if(srcLength>0 && srcLength<=destCapacity) {
            memcpy(dest, src, srcLength*U_SIZEOF_UCHAR);
        }
        destLength=srcLength;
        break;
    default:
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    return u_terminateUChars(dest, destCapacity, destLength, pErrorCode);
}

int32_t unorm_internalNormalize(UChar *dest, int32_t destCapacity,const UChar *src, int32_t srcLength,
                        UNormalizationMode mode, int32_t options, UErrorCode *pErrorCode) 
{
    const UnicodeSet *nx;

    if(!_haveData(*pErrorCode)) {
        return 0;
    }

    nx=getNX(options, *pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }

    options&=~(_NORM_OPTIONS_SETS_MASK|_NORM_OPTIONS_COMPAT|_NORM_OPTIONS_COMPOSE_CONTIGUOUS);

    return unorm_internalNormalizeWithNX(dest, destCapacity,
                                         src, srcLength,
                                         mode, options, nx,
                                         pErrorCode);
}



int32_t unorm_normalize(const UChar *src, int32_t srcLength, UNormalizationMode mode, int32_t options,
                                                    UChar *dest, int32_t destCapacity, UErrorCode *pErrorCode) 
{
    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return 0;
    }

    if( destCapacity<0 || (dest==NULL && destCapacity>0) ||
        src==NULL || srcLength<-1
    ) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    if( dest!=NULL &&
        ((src>=dest && src<(dest+destCapacity)) ||
         (srcLength>0 && dest>=src && dest<(src+srcLength)))
    ) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    return unorm_internalNormalize(dest, destCapacity,
                                   src, srcLength,
                                   mode, options,
                                   pErrorCode);
}


