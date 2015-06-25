/*
 * Copyright (C) 2006 Lars Knoll <lars@trolltech.com>
 * Copyright (C) 2007 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef TextBreakIterator_h
#define TextBreakIterator_h

#include <wtf/unicode/Unicode.h>

namespace WebCore {

typedef enum {
    BRK_CHAR,
    BRK_WORD,
    BRK_LINE,
}BREAK_TYPE;

class PlatformBreakData;

class TextBreakIterator
{
public:
    TextBreakIterator(BREAK_TYPE type);
    ~TextBreakIterator();

    bool setText(const UChar * str, int len)
    {
        clear();

        if (!str || (len < 0))
            return false;
        
        string = str;
        string_len = len;
        return true;
    }
    
    const UChar * getText(void)
    {
        return string;
    }
    
    int getTextLen(void) 
    {
        return string_len;
    }
    
    BREAK_TYPE getType(void)
    {
        return btype;
    }
public:

    int break_first(void);
    int break_last(void);
    int break_next(void);
    int break_prev(void);
    int break_preceding(int pos);
    int break_following(int pos);
    int break_current(void);
    bool is_break(int pos);

private:
    BREAK_TYPE btype;
    const UChar * string;
    int string_len;
    PlatformBreakData * data;
    void clear(void);
private:
    TextBreakIterator(const TextBreakIterator &);
    TextBreakIterator &operator=(const TextBreakIterator &);
};

// Note: The returned iterator is good only until you get another iterator.
TextBreakIterator* characterBreakIterator(const UChar*, int length);
TextBreakIterator* wordBreakIterator(const UChar*, int length);
TextBreakIterator* lineBreakIterator(const UChar*, int length);
TextBreakIterator* sentenceBreakIterator(const UChar*, int length);

int textBreakFirst(TextBreakIterator*);
int textBreakLast(TextBreakIterator*);
int textBreakNext(TextBreakIterator*);
int textBreakPrevious(TextBreakIterator*);
int textBreakCurrent(TextBreakIterator*);
int textBreakPreceding(TextBreakIterator*, int);
int textBreakFollowing(TextBreakIterator*, int);
bool isTextBreak(TextBreakIterator*, int);

const int TextBreakDone = -1;

}

#endif
