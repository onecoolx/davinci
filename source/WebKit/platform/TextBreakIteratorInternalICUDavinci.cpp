/*
 * TextBreakIteratorInternalICUDavinci.cpp: TextBreakIteratorInternalICU implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */


#include "config.h"
#include "TextBreakIteratorInternalICU.h"

namespace WebCore {

const char* currentSearchLocaleID()
{
    // FIXME: Should use system locale.
    return "";
}

const char* currentTextBreakLocaleID()
{
    return "en_US_POSIX";
}

}
