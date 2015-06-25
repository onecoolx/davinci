
#ifndef _UnicodeGlobal_h
#define _UnicodeGlobal_h

#include "config.h"

typedef int8_t UBool;

#ifndef TRUE
#   define TRUE  1
#endif
#ifndef FALSE
#   define FALSE 0
#endif

typedef enum {
    /** An output string could not be NUL-terminated because output length==destCapacity. */
    U_STRING_NOT_TERMINATED_WARNING = -124,
    U_ZERO_ERROR              =  0,  /**< No error, no warning. */
    U_ILLEGAL_ARGUMENT_ERROR  =  1,  /**< Start of codes indicating failure */
    U_INVALID_FORMAT_ERROR    =  3,  /**< Data format is not what is expected */
    U_INTERNAL_PROGRAM_ERROR  =  5,  /**< Indicates a bug in the library code */

    U_MEMORY_ALLOCATION_ERROR =  7,  /**< Memory allocation error */
    U_INDEX_OUTOFBOUNDS_ERROR =  8,  /**< Trying to access the index that is out of bounds */
    /** Character conversion: Unmappable input sequence. In other APIs: Invalid character. */
    U_INVALID_CHAR_FOUND      = 10, 

    U_BUFFER_OVERFLOW_ERROR   = 15,  /**< A result would not fit in the supplied buffer */

    /*
     * The error code in the range 0x10400-0x104ff are reserved for IDNA related error codes
     */
    U_IDNA_ERROR_START=0x10400,
    U_IDNA_PROHIBITED_ERROR,
    U_IDNA_UNASSIGNED_ERROR,
    U_IDNA_CHECK_BIDI_ERROR,
    U_IDNA_STD3_ASCII_RULES_ERROR,
    U_IDNA_ACE_PREFIX_ERROR,
    U_IDNA_VERIFICATION_ERROR,
    U_IDNA_LABEL_TOO_LONG_ERROR,
    U_IDNA_ERROR_LIMIT,
    /*
     * Aliases for StringPrep
     */
    U_STRINGPREP_PROHIBITED_ERROR = U_IDNA_PROHIBITED_ERROR,
    U_STRINGPREP_UNASSIGNED_ERROR = U_IDNA_UNASSIGNED_ERROR,
    U_STRINGPREP_CHECK_BIDI_ERROR = U_IDNA_CHECK_BIDI_ERROR
} UErrorCode;


#define U_SUCCESS(x) ((x)<=U_ZERO_ERROR)
#define U_FAILURE(x) ((x)>U_ZERO_ERROR)

#endif


