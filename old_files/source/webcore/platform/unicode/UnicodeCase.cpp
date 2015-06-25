
#include  "UnicodeTrie.h"
#include  "UnicodeCase.h"

#define UCASE_SENSITIVE     4

#define _FOLD_CASE_OPTIONS_MASK 0xff

#define UCASE_EXC_CONDITIONAL_SPECIAL   0x4000

#define UCASE_EXC_CONDITIONAL_FOLD      0x8000

#define UCASE_FULL_LOWER    0xf
#define UCASE_FULL_FOLDING  0xf0
#define UCASE_FULL_UPPER    0xf00
#define UCASE_FULL_TITLE    0xf000

#define UCASE_CASE_IGNORABLE 0x40

#define UCASE_DOT_MASK      0x30
enum {
    UCASE_NO_DOT=0,         /* normal characters with cc=0 */
    UCASE_SOFT_DOTTED=0x10, /* soft-dotted characters with cc=0 */
    UCASE_ABOVE=0x20,       /* "above" accents with cc=230 */
    UCASE_OTHER_ACCENT=0x30 /* other accent character (0<cc!=230) */
};

enum {
    UCASE_EXC_LOWER,
    UCASE_EXC_FOLD,
    UCASE_EXC_UPPER,
    UCASE_EXC_TITLE,
    UCASE_EXC_4,            /* reserved */
    UCASE_EXC_5,            /* reserved */
    UCASE_EXC_CLOSURE,
    UCASE_EXC_FULL_MAPPINGS,
    UCASE_EXC_ALL_SLOTS     /* one past the last slot */
};

#define UCASE_EXC_DOT_SHIFT     8


enum {
    UCASE_IX_INDEX_TOP,
    UCASE_IX_LENGTH,
    UCASE_IX_TRIE_SIZE,
    UCASE_IX_EXC_LENGTH,
    UCASE_IX_UNFOLD_LENGTH,

    UCASE_IX_MAX_FULL_LENGTH=15,
    UCASE_IX_TOP=16
};

/* 2-bit constants for types of cased characters */
#define UCASE_TYPE_MASK     3
enum {
    UCASE_NONE,
    UCASE_LOWER,
    UCASE_UPPER,
    UCASE_TITLE
};


#define UCASE_GET_TYPE(props) ((props)&UCASE_TYPE_MASK)


#define UCASE_DELTA_SHIFT   6
#define UCASE_DELTA_MASK    0xffc0
#define UCASE_MAX_DELTA     0x1ff
#define UCASE_MIN_DELTA     (-UCASE_MAX_DELTA-1)
#define UCASE_EXCEPTION     8
#define UCASE_EXC_SHIFT     4

#define UCASE_EXC_DOUBLE_SLOTS      0x100

#define UCASE_GET_DELTA(props) ((int16_t)(props)>>UCASE_DELTA_SHIFT)


////////////////////////////////////////////////////////////////////
struct UCaseProps {
    const int32_t *indexes;
    const uint16_t *exceptions;
    const UChar *unfold;

    UTrie trie;
    uint8_t formatVersion[4];
};

#include  "ucase_props_data.cpp"

static UCaseProps *gCsp=NULL;

const UCaseProps* ucase_getSingleton(UErrorCode *pErrorCode)
{

    if(U_FAILURE(*pErrorCode)) {
        return NULL;
    }
    return &ucase_props_singleton;
}

static const UCaseProps *getCaseProps()
{
    const UCaseProps *csp;
    UErrorCode errorCode=U_ZERO_ERROR;

    csp=ucase_getSingleton(&errorCode);

    return csp;
}

#define GET_CASE_PROPS() (gCsp!=NULL ? gCsp : getCaseProps())

#define GET_PROPS(csp, c, result) UTRIE_GET16(&(csp)->trie, c, result);

#define GET_EXCEPTIONS(csp, props) ((csp)->exceptions+((props)>>UCASE_EXC_SHIFT))

#define PROPS_HAS_EXCEPTION(props) ((props)&UCASE_EXCEPTION)

/* number of bits in an 8-bit integer value */
static const uint8_t flagsOffset[256]={
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

#define HAS_SLOT(flags, index) ((flags)&(1<<(index)))
#define SLOT_OFFSET(flags, index) flagsOffset[(flags)&((1<<(index))-1)]

#define GET_SLOT_VALUE(excWord, index, pExc16, value) \
    if(((excWord)&UCASE_EXC_DOUBLE_SLOTS)==0) { \
        (pExc16)+=SLOT_OFFSET(excWord, index); \
        (value)=*pExc16; \
    } else { \
        (pExc16)+=2*SLOT_OFFSET(excWord, index); \
        (value)=*pExc16++; \
        (value)=((value)<<16)|*pExc16; \
    }


enum {
    LOC_UNKNOWN,
    LOC_ROOT,
    LOC_TURKISH,
    LOC_LITHUANIAN
};

#define is_a(c) ((c)=='a' || (c)=='A')
#define is_e(c) ((c)=='e' || (c)=='E')
#define is_i(c) ((c)=='i' || (c)=='I')
#define is_l(c) ((c)=='l' || (c)=='L')
#define is_r(c) ((c)=='r' || (c)=='R')
#define is_t(c) ((c)=='t' || (c)=='T')
#define is_u(c) ((c)=='u' || (c)=='U')
#define is_z(c) ((c)=='z' || (c)=='Z')

/* separator? */
#define is_sep(c) ((c)=='_' || (c)=='-' || (c)==0)

/**
 * Requires non-NULL locale ID but otherwise does the equivalent of
 * checking for language codes as if uloc_getLanguage() were called:
 * Accepts both 2- and 3-letter codes and accepts case variants.
 */
int32_t ucase_getCaseLocale(const char *locale, int32_t *locCache)
{
    int32_t result;
    char c;

    if(locCache!=NULL && (result=*locCache)!=LOC_UNKNOWN) {
        return result;
    }

    result=LOC_ROOT;
    c=*locale++;
    if(is_t(c)) {
        /* tr or tur? */
        c=*locale++;
        if(is_u(c)) {
            c=*locale++;
        }
        if(is_r(c)) {
            c=*locale;
            if(is_sep(c)) {
                result=LOC_TURKISH;
            }
        }
    } else if(is_a(c)) {
        /* az or aze? */
        c=*locale++;
        if(is_z(c)) {
            c=*locale++;
            if(is_e(c)) {
                c=*locale;
            }
            if(is_sep(c)) {
                result=LOC_TURKISH;
            }
        }
    } else if(is_l(c)) {
        /* lt or lit? */
        c=*locale++;
        if(is_i(c)) {
            c=*locale++;
        }
        if(is_t(c)) {
            c=*locale;
            if(is_sep(c)) {
                result=LOC_LITHUANIAN;
            }
        }
    }

    if(locCache!=NULL) {
        *locCache=result;
    }
    return result;
}


/** @return UCASE_NO_DOT, UCASE_SOFT_DOTTED, UCASE_ABOVE, UCASE_OTHER_ACCENT */
static int32_t getDotType(const UCaseProps *csp, USChar32 c)
{
    uint16_t props;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        return props&UCASE_DOT_MASK;
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        return (*pe>>UCASE_EXC_DOT_SHIFT)&UCASE_DOT_MASK;
    }
}

static UBool
isPrecededBySoftDotted(const UCaseProps *csp, UCaseContextIterator *iter, void *context)
{
    USChar32 c;
    int32_t dotType;
    int8_t dir;

    if(iter==NULL) {
        return FALSE;
    }

    for(dir=-1; (c=iter(context, dir))>=0; dir=0) {
        dotType=getDotType(csp, c);
        if(dotType==UCASE_SOFT_DOTTED) {
            return TRUE; /* preceded by TYPE_i */
        } else if(dotType!=UCASE_OTHER_ACCENT) {
            return FALSE; /* preceded by different base character (not TYPE_i), or intervening cc==230 */
        }
    }

    return FALSE; /* not preceded by TYPE_i */
}

/* Is followed by one or more cc==230 ? */
static UBool
isFollowedByMoreAbove(const UCaseProps *csp, UCaseContextIterator *iter, void *context)
{
    USChar32 c;
    int32_t dotType;
    int8_t dir;

    if(iter==NULL) {
        return FALSE;
    }

    for(dir=1; (c=iter(context, dir))>=0; dir=0) {
        dotType=getDotType(csp, c);
        if(dotType==UCASE_ABOVE) {
            return TRUE; /* at least one cc==230 following */
        } else if(dotType!=UCASE_OTHER_ACCENT) {
            return FALSE; /* next base character, no more cc==230 following */
        }
    }

    return FALSE; /* no more cc==230 following */
}


static UBool
isPrecededBy_I(const UCaseProps *csp, UCaseContextIterator *iter, void *context)
{
    USChar32 c;
    int32_t dotType;
    int8_t dir;

    if(iter==NULL) {
        return FALSE;
    }

    for(dir=-1; (c=iter(context, dir))>=0; dir=0) {
        if(c==0x49) {
            return TRUE; /* preceded by I */
        }
        dotType=getDotType(csp, c);
        if(dotType!=UCASE_OTHER_ACCENT) {
            return FALSE; /* preceded by different base character (not I), or intervening cc==230 */
        }
    }

    return FALSE; /* not preceded by I */
}


/* Is followed by a dot above (without cc==230 in between) ? */
static UBool
isFollowedByDotAbove(const UCaseProps *csp, UCaseContextIterator *iter, void *context)
{
    USChar32 c;
    int32_t dotType;
    int8_t dir;

    if(iter==NULL) {
        return FALSE;
    }

    for(dir=1; (c=iter(context, dir))>=0; dir=0) {
        if(c==0x307) {
            return TRUE;
        }
        dotType=getDotType(csp, c);
        if(dotType!=UCASE_OTHER_ACCENT) {
            return FALSE; /* next base character or cc==230 in between */
        }
    }

    return FALSE; /* no dot above following */
}


/* Is followed by {case-ignorable}* cased  ? (dir determines looking forward/backward) */
static UBool
isFollowedByCasedLetter(const UCaseProps *csp, UCaseContextIterator *iter, void *context, int8_t dir)
{
    USChar32 c;
    uint16_t props;

    if(iter==NULL) {
        return FALSE;
    }

    for(/* dir!=0 sets direction */; (c=iter(context, dir))>=0; dir=0) {
        GET_PROPS(csp, c, props);
        if(UCASE_GET_TYPE(props)!=UCASE_NONE) {
            return TRUE; /* followed by cased letter */
        } else if(c==0x307 || (props&(UCASE_EXCEPTION|UCASE_CASE_IGNORABLE))==UCASE_CASE_IGNORABLE) {
            /* case-ignorable, continue with the loop */
        } else {
            return FALSE; /* not ignorable */
        }
    }

    return FALSE; /* not followed by cased letter */
}


int32_t ucase_toFullLower(const UCaseProps *csp, USChar32 c,
                  UCaseContextIterator *iter, void *context,
                  const UChar **pString,
                  const char *locale, int32_t *locCache) 
{
    static const UChar
        iDot[2]=        { 0x69, 0x307 },
        jDot[2]=        { 0x6a, 0x307 },
        iOgonekDot[3]= { 0x12f, 0x307 },
        iDotGrave[3]=   { 0x69, 0x307, 0x300 },
        iDotAcute[3]=   { 0x69, 0x307, 0x301 },
        iDotTilde[3]=   { 0x69, 0x307, 0x303 };

    USChar32 result;
    uint16_t props;

    result=c;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)>=UCASE_UPPER) {
            result=c+UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props), *pe2;
        uint16_t excWord=*pe++;
        int32_t full;

        pe2=pe;

        if(excWord&UCASE_EXC_CONDITIONAL_SPECIAL) {
            /* use hardcoded conditions and mappings */
            int32_t loc=ucase_getCaseLocale(locale, locCache);
            if( loc==LOC_LITHUANIAN &&
                    /* base characters, find accents above */
                    (((c==0x49 || c==0x4a || c==0x12e) &&
                        isFollowedByMoreAbove(csp, iter, context)) ||
                    /* precomposed with accent above, no need to find one */
                    (c==0xcc || c==0xcd || c==0x128))
            ) {
                switch(c) {
                case 0x49:  /* LATIN CAPITAL LETTER I */
                    *pString=iDot;
                    return 2;
                case 0x4a:  /* LATIN CAPITAL LETTER J */
                    *pString=jDot;
                    return 2;
                case 0x12e: /* LATIN CAPITAL LETTER I WITH OGONEK */
                    *pString=iOgonekDot;
                    return 2;
                case 0xcc:  /* LATIN CAPITAL LETTER I WITH GRAVE */
                    *pString=iDotGrave;
                    return 3;
                case 0xcd:  /* LATIN CAPITAL LETTER I WITH ACUTE */
                    *pString=iDotAcute;
                    return 3;
                case 0x128: /* LATIN CAPITAL LETTER I WITH TILDE */
                    *pString=iDotTilde;
                    return 3;
                default:
                    return 0; /* will not occur */
                }
            /* # Turkish and Azeri */
            } else if(loc==LOC_TURKISH && c==0x130) {
                return 0x69;
            } else if(loc==LOC_TURKISH && c==0x307 && isPrecededBy_I(csp, iter, context)) {
                return 0; /* remove the dot (continue without output) */
            } else if(loc==LOC_TURKISH && c==0x49 && !isFollowedByDotAbove(csp, iter, context)) {
                return 0x131;
            } else if(c==0x130) {
                *pString=iDot;
                return 2;
            } else if(  c==0x3a3 &&
                        !isFollowedByCasedLetter(csp, iter, context, 1) &&
                        isFollowedByCasedLetter(csp, iter, context, -1) /* -1=preceded */
            ) {
                return 0x3c2; /* greek small final sigma */
            } else {
                /* no known conditional special case mapping, use a normal mapping */
            }
        } else if(HAS_SLOT(excWord, UCASE_EXC_FULL_MAPPINGS)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_FULL_MAPPINGS, pe, full);
            full&=UCASE_FULL_LOWER;
            if(full!=0) {
                /* set the output pointer to the lowercase mapping */
                *pString=pe+1;

                /* return the string length */
                return full;
            }
        }

        if(HAS_SLOT(excWord, UCASE_EXC_LOWER)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_LOWER, pe2, result);
        }
    }

    return (result==c) ? ~result : result;
}


int32_t
toUpperOrTitle(const UCaseProps *csp, USChar32 c,
               UCaseContextIterator *iter, void *context,
               const UChar **pString,
               const char *locale, int32_t *locCache,
               UBool upperNotTitle) 
{
    USChar32 result;
    uint16_t props;

    result=c;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)==UCASE_LOWER) {
            result=c+UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props), *pe2;
        uint16_t excWord=*pe++;
        int32_t full, index;

        pe2=pe;

        if(excWord&UCASE_EXC_CONDITIONAL_SPECIAL) {
            /* use hardcoded conditions and mappings */
            int32_t loc=ucase_getCaseLocale(locale, locCache);

            if(loc==LOC_TURKISH && c==0x69) {
                return 0x130;
            } else if(loc==LOC_LITHUANIAN && c==0x307 && isPrecededBySoftDotted(csp, iter, context)) {
                return 0; /* remove the dot (continue without output) */
            } else {
                /* no known conditional special case mapping, use a normal mapping */
            }
        } else if(HAS_SLOT(excWord, UCASE_EXC_FULL_MAPPINGS)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_FULL_MAPPINGS, pe, full);

            /* start of full case mapping strings */
            ++pe;

            /* skip the lowercase and case-folding result strings */
            pe+=full&UCASE_FULL_LOWER;
            full>>=4;
            pe+=full&0xf;
            full>>=4;

            if(upperNotTitle) {
                full&=0xf;
            } else {
                /* skip the uppercase result string */
                pe+=full&0xf;
                full=(full>>4)&0xf;
            }

            if(full!=0) {
                /* set the output pointer to the result string */
                *pString=pe;

                /* return the string length */
                return full;
            }
        }

        if(!upperNotTitle && HAS_SLOT(excWord, UCASE_EXC_TITLE)) {
            index=UCASE_EXC_TITLE;
        } else if(HAS_SLOT(excWord, UCASE_EXC_UPPER)) {
            /* here, titlecase is same as uppercase */
            index=UCASE_EXC_UPPER;
        } else {
            return ~c;
        }
        GET_SLOT_VALUE(excWord, index, pe2, result);
    }

    return (result==c) ? ~result : result;
}

int32_t ucase_toFullUpper(const UCaseProps *csp, USChar32 c,
                  UCaseContextIterator *iter, void *context,
                  const UChar **pString,
                  const char *locale, int32_t *locCache) 
{
    return toUpperOrTitle(csp, c, iter, context, pString, locale, locCache, TRUE);
}


int32_t ucase_toFullFolding(const UCaseProps *csp, USChar32 c,
                    const UChar **pString,
                    uint32_t options)
{
    static const UChar
        iDot[2]=        { 0x69, 0x307 };

    USChar32 result;
    uint16_t props;

    result=c;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)>=UCASE_UPPER) {
            result=c+UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props), *pe2;
        uint16_t excWord=*pe++;
        int32_t full, index;

        pe2=pe;

        if(excWord&UCASE_EXC_CONDITIONAL_FOLD) {
            /* use hardcoded conditions and mappings */
            if((options&_FOLD_CASE_OPTIONS_MASK)==U_FOLD_CASE_DEFAULT) {
                /* default mappings */
                if(c==0x49) {
                    /* 0049; C; 0069; # LATIN CAPITAL LETTER I */
                    return 0x69;
                } else if(c==0x130) {
                    /* 0130; F; 0069 0307; # LATIN CAPITAL LETTER I WITH DOT ABOVE */
                    *pString=iDot;
                    return 2;
                }
            } else {
                /* Turkic mappings */
                if(c==0x49) {
                    /* 0049; T; 0131; # LATIN CAPITAL LETTER I */
                    return 0x131;
                } else if(c==0x130) {
                    /* 0130; T; 0069; # LATIN CAPITAL LETTER I WITH DOT ABOVE */
                    return 0x69;
                }
            }
        } else if(HAS_SLOT(excWord, UCASE_EXC_FULL_MAPPINGS)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_FULL_MAPPINGS, pe, full);

            /* start of full case mapping strings */
            ++pe;

            /* skip the lowercase result string */
            pe+=full&UCASE_FULL_LOWER;
            full=(full>>4)&0xf;

            if(full!=0) {
                /* set the output pointer to the result string */
                *pString=pe;

                /* return the string length */
                return full;
            }
        }

        if(HAS_SLOT(excWord, UCASE_EXC_FOLD)) {
            index=UCASE_EXC_FOLD;
        } else if(HAS_SLOT(excWord, UCASE_EXC_LOWER)) {
            index=UCASE_EXC_LOWER;
        } else {
            return ~c;
        }
        GET_SLOT_VALUE(excWord, index, pe2, result);
    }

    return (result==c) ? ~result : result;
}


USChar32 ucase_tolower(const UCaseProps *csp, USChar32 c)
{
    uint16_t props;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)>=UCASE_UPPER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        if(HAS_SLOT(excWord, UCASE_EXC_LOWER)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_LOWER, pe, c);
        }
    }
    return c;
}


USChar32 u_tolower(USChar32 c) 
{
    return ucase_tolower(GET_CASE_PROPS(), c);
}

USChar32 ucase_toupper(const UCaseProps *csp, USChar32 c)
{
    uint16_t props;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)==UCASE_LOWER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        if(HAS_SLOT(excWord, UCASE_EXC_UPPER)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_UPPER, pe, c);
        }
    }
    return c;
}

USChar32 u_toupper(USChar32 c)
{
    return ucase_toupper(GET_CASE_PROPS(), c);
}


USChar32 ucase_totitle(const UCaseProps *csp, USChar32 c)
{
    uint16_t props;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)==UCASE_LOWER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        int32_t index;
        if(HAS_SLOT(excWord, UCASE_EXC_TITLE)) {
            index=UCASE_EXC_TITLE;
        } else if(HAS_SLOT(excWord, UCASE_EXC_UPPER)) {
            index=UCASE_EXC_UPPER;
        } else {
            return c;
        }
        GET_SLOT_VALUE(excWord, index, pe, c);
    }
    return c;
}


USChar32 u_totitle(USChar32 c)
{
    return ucase_totitle(GET_CASE_PROPS(), c);
}


USChar32 ucase_fold(const UCaseProps *csp, USChar32 c, uint32_t options)
{
    uint16_t props;
    GET_PROPS(csp, c, props);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)>=UCASE_UPPER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        int32_t index;
        if(excWord&UCASE_EXC_CONDITIONAL_FOLD) {
            /* special case folding mappings, hardcoded */
            if((options&_FOLD_CASE_OPTIONS_MASK)==U_FOLD_CASE_DEFAULT) {
                /* default mappings */
                if(c==0x49) {
                    /* 0049; C; 0069; # LATIN CAPITAL LETTER I */
                    return 0x69;
                } else if(c==0x130) {
                    /* no simple case folding for U+0130 */
                    return c;
                }
            } else {
                /* Turkic mappings */
                if(c==0x49) {
                    /* 0049; T; 0131; # LATIN CAPITAL LETTER I */
                    return 0x131;
                } else if(c==0x130) {
                    /* 0130; T; 0069; # LATIN CAPITAL LETTER I WITH DOT ABOVE */
                    return 0x69;
                }
            }
        }
        if(HAS_SLOT(excWord, UCASE_EXC_FOLD)) {
            index=UCASE_EXC_FOLD;
        } else if(HAS_SLOT(excWord, UCASE_EXC_LOWER)) {
            index=UCASE_EXC_LOWER;
        } else {
            return c;
        }
        GET_SLOT_VALUE(excWord, index, pe, c);
    }
    return c;
}

USChar32 u_foldCase(USChar32 c, uint32_t options)
{
    return ucase_fold(GET_CASE_PROPS(), c, options);
}

/** @return UCASE_NONE, UCASE_LOWER, UCASE_UPPER, UCASE_TITLE */
int32_t ucase_getType(const UCaseProps *csp, USChar32 c)
{
    uint16_t props;
    GET_PROPS(csp, c, props);
    return UCASE_GET_TYPE(props);
}


UBool u_isUUppercase(USChar32 c)
{
    return (UBool)(UCASE_UPPER==ucase_getType(GET_CASE_PROPS(), c));
}

UBool ucase_isSoftDotted(const UCaseProps *csp, USChar32 c)
{
    return (UBool)(getDotType(csp, c)==UCASE_SOFT_DOTTED);
}

UBool ucase_isCaseSensitive(const UCaseProps *csp, USChar32 c)
{
    uint16_t props;
    GET_PROPS(csp, c, props);
    return (UBool)((props&UCASE_SENSITIVE)!=0);
}

int32_t ucase_hasBinaryProperty(USChar32 c, UProperty which)
{
    /* case mapping properties */
    const UCaseProps *csp=GET_CASE_PROPS();
    if(csp==NULL) {
        return FALSE;
    }
    switch(which) {
    case UCHAR_LOWERCASE:
        return (UBool)(UCASE_LOWER==ucase_getType(csp, c));
    case UCHAR_UPPERCASE:
        return (UBool)(UCASE_UPPER==ucase_getType(csp, c));
    case UCHAR_SOFT_DOTTED:
        return ucase_isSoftDotted(csp, c);
    case UCHAR_CASE_SENSITIVE:
        return ucase_isCaseSensitive(csp, c);
    default:
        return FALSE;
    }
}





