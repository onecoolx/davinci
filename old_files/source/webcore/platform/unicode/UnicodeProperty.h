
#ifndef _UnicodePreperty_h_
#define _UnicodePreperty_h_

#include "Normalize.h"
#include "UnicodeCase.h"

#define UPROPS_LB_MASK          0x00FC0000
#define UPROPS_LB_SHIFT         18

#define UPROPS_EA_MASK          0x00038000
#define UPROPS_EA_SHIFT         15

#define UPROPS_BLOCK_MASK       0x00007f80
#define UPROPS_BLOCK_SHIFT      7
#define UPROPS_SCRIPT_MASK      0x0000007f

#define GET_NUMERIC_TYPE(props) (((props)>>UPROPS_NUMERIC_TYPE_SHIFT)&7)

#define UPROPS_SB_MASK          0x0007c000
#define UPROPS_SB_SHIFT         14

#define UPROPS_WB_MASK          0x00003c00
#define UPROPS_WB_SHIFT         10

#define UPROPS_GCB_MASK         0x000003e0
#define UPROPS_GCB_SHIFT        5

#define UPROPS_DT_MASK          0x0000001f


enum {
    UPROPS_V2_S_TERM=24,                        /* new in ICU 3.0 and Unicode 4.0.1 */
    UPROPS_V2_VARIATION_SELECTOR,
    UPROPS_V2_PATTERN_SYNTAX,                   /* new in ICU 3.4 and Unicode 4.1 */
    UPROPS_V2_PATTERN_WHITE_SPACE,
    UPROPS_V2_TOP                               /* must be <=32 */
};

enum {
    /* general category shift==0                                0 (5 bits) */
    UPROPS_NUMERIC_TYPE_SHIFT=5,                            /*  5 (3 bits) */
    UPROPS_NUMERIC_VALUE_SHIFT=8                            /*  8 (8 bits) */
};


enum {
    UPROPS_WHITE_SPACE,
    UPROPS_WAS_BIDI_CONTROL,                /* reserved, was used in format version 3 */
    UPROPS_WAS_JOIN_CONTROL,
    UPROPS_DASH,
    UPROPS_HYPHEN,
    UPROPS_QUOTATION_MARK,
    UPROPS_TERMINAL_PUNCTUATION,
    UPROPS_MATH,
    UPROPS_HEX_DIGIT,
    UPROPS_ASCII_HEX_DIGIT,
    UPROPS_ALPHABETIC,
    UPROPS_IDEOGRAPHIC,
    UPROPS_DIACRITIC,
    UPROPS_EXTENDER,
    UPROPS_WAS_LOWERCASE,                   /* reserved, was used in format version 3 */
    UPROPS_WAS_UPPERCASE,
    UPROPS_NONCHARACTER_CODE_POINT,
    UPROPS_GRAPHEME_EXTEND,
    UPROPS_GRAPHEME_LINK,
    UPROPS_IDS_BINARY_OPERATOR,
    UPROPS_IDS_TRINARY_OPERATOR,
    UPROPS_RADICAL,
    UPROPS_UNIFIED_IDEOGRAPH,
    UPROPS_DEFAULT_IGNORABLE_CODE_POINT,
    UPROPS_DEPRECATED,
        UPROPS_WAS_SOFT_DOTTED,                 /* reserved, was used in format version 3 */
    UPROPS_LOGICAL_ORDER_EXCEPTION,
    UPROPS_XID_START,
    UPROPS_XID_CONTINUE,
    UPROPS_ID_START,                            /* ICU 2.6, uprops format version 3.2 */
    UPROPS_ID_CONTINUE,
    UPROPS_GRAPHEME_BASE,
    UPROPS_BINARY_1_TOP                         /* ==32 - full! */
};

/* indexes[] entries */
enum {
    UPROPS_PROPS32_INDEX,
    UPROPS_EXCEPTIONS_INDEX,
    UPROPS_EXCEPTIONS_TOP_INDEX,

    UPROPS_ADDITIONAL_TRIE_INDEX,
    UPROPS_ADDITIONAL_VECTORS_INDEX,
    UPROPS_ADDITIONAL_VECTORS_COLUMNS_INDEX,

    UPROPS_RESERVED_INDEX, /* 6 */

    /* maximum values for code values in vector word 0 */
    UPROPS_MAX_VALUES_INDEX=10,
    /* maximum values for code values in vector word 2 */
    UPROPS_MAX_VALUES_2_INDEX,

    UPROPS_INDEX_COUNT=16
};

typedef enum {
    UPROPS_SRC_NONE,
    UPROPS_SRC_CHAR,
    UPROPS_SRC_PROPSVEC,
    UPROPS_SRC_HST,
    UPROPS_SRC_NAMES,
    UPROPS_SRC_NORM,
    UPROPS_SRC_CASE,
    UPROPS_SRC_BIDI,
    UPROPS_SRC_CHAR_AND_PROPSVEC,
    UPROPS_SRC_COUNT
}UPropertySource;


int32_t u_getIntPropertyValue(USChar32 c, UProperty which);

#endif

