
#include  "UnicodeTrie.h"
#include  "UnicodeProperty.h"
#include  "UnicodeChar.h"

#include  "uchar_props_data.cpp"

#define GET_PROPS(c, result) UTRIE_GET16(&propsTrie, c, result)

#define GET_CATEGORY(props) ((props)&0x1f)
#define CAT_MASK(props) U_MASK(GET_CATEGORY(props))

#define GET_NUMERIC_VALUE(props) (((props)>>UPROPS_NUMERIC_VALUE_SHIFT)&0xff)

UBool u_isdigit(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_DECIMAL_DIGIT_NUMBER);
}

int8_t u_charType(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);
    return (int8_t)GET_CATEGORY(props);
}


int32_t u_charDigitValue(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);

    if(GET_NUMERIC_TYPE(props)==1) {
        return GET_NUMERIC_VALUE(props);
    } else {
        return -1;
    }
}


UBool u_ispunct(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&U_GC_P_MASK)!=0);
}


UBool u_islower(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_LOWERCASE_LETTER);
}

uint32_t u_getUnicodeProperties(USChar32 c, int32_t column) 
{
    uint16_t vecIndex;

    if(column==-1) {
        uint32_t props;
        GET_PROPS(c, props);
        return props;
    } else if(
               column<0 || column>=propsVectorsColumns
    ) {
        return 0;
    } else {
        UTRIE_GET16(&propsVectorsTrie, c, vecIndex);
        return propsVectors[vecIndex+column];
    }
}

UBool u_isblank(USChar32 c) 
{
    if((uint32_t)c<=0x9f) {
        return c==9 || c==0x20; /* TAB or SPACE */
    } else {
        /* Zs */
        uint32_t props;
        GET_PROPS(c, props);
        return (UBool)(GET_CATEGORY(props)==U_SPACE_SEPARATOR);
    }
}

UBool u_isgraphPOSIX(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&
                    (U_GC_CC_MASK|U_GC_CS_MASK|U_GC_CN_MASK|U_GC_Z_MASK))
                   ==0);
}

UBool u_isprintPOSIX(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((GET_CATEGORY(props)==U_SPACE_SEPARATOR) || u_isgraphPOSIX(c));
}

UBool u_isxdigit(USChar32 c) 
{
    uint32_t props;
    if(
        (c<=0x66 && c>=0x41 && (c<=0x46 || c>=0x61)) ||
        (c>=0xff21 && c<=0xff46 && (c<=0xff26 || c>=0xff41))
    ) {
        return TRUE;
    }

    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_DECIMAL_DIGIT_NUMBER);
}

UBool u_isUAlphabetic(USChar32 c) 
{
    return (u_getUnicodeProperties(c, 1)&U_MASK(UPROPS_ALPHABETIC))!=0;
}

UBool u_isalnumPOSIX(USChar32 c) 
{
    return (UBool)(u_isUAlphabetic(c) || u_isdigit(c));
}

UBlockCode ublock_getCode(USChar32 c) 
{
    return (UBlockCode)((u_getUnicodeProperties(c, 0)&UPROPS_BLOCK_MASK)>>UPROPS_BLOCK_SHIFT);
}

UScriptCode uscript_getScript(USChar32 c, UErrorCode *pErrorCode) 
{
    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return USCRIPT_INVALID_CODE;
    }
    if((uint32_t)c>0x10ffff) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return USCRIPT_INVALID_CODE;
    }

    return (UScriptCode)(u_getUnicodeProperties(c, 0)&UPROPS_SCRIPT_MASK);
}

UHangulSyllableType uchar_getHST(USChar32 c) 
{
    if(c<JAMO_L_BASE) {
    } else if(c<=0x11ff) {
        if(c<=0x115f) {
            if(c==0x115f || c<=0x1159 || u_charType(c)==U_OTHER_LETTER) {
                return U_HST_LEADING_JAMO;
            }
        } else if(c<=0x11a7) {
            if(c<=0x11a2 || u_charType(c)==U_OTHER_LETTER) {
                return U_HST_VOWEL_JAMO;
            }
        } else {
            if(c<=0x11f9 || u_charType(c)==U_OTHER_LETTER) {
                return U_HST_TRAILING_JAMO;
            }
        }
    } else if((c-=HANGUL_BASE)<0) {
    } else if(c<HANGUL_COUNT) {
        return c%JAMO_T_COUNT==0 ? U_HST_LV_SYLLABLE : U_HST_LVT_SYLLABLE;
    }
    return U_HST_NOT_APPLICABLE;
}

UBool u_isprint(USChar32 c) 
{
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&U_GC_C_MASK)==0);
}


