/*
** TextBreakIteratorPS.cpp: TextBreakIterator implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include <string.h>

#include "config.h"
#include "TextBreakIterator.h"
#include "TextBoundary.h"
#include "Debug.h"

namespace WebCore {
class PlatformBreakData
{
public:
    PlatformBreakData()
    {
        memset(&lbkInfo, 0, sizeof(LINE_BREAK));
		memset(&wbkInfo, 0, sizeof(WORD_BREAK));
	    memset(&cbkInfo, 0, sizeof(CHARS_BREAK));
    }

    ~PlatformBreakData()
    {
    }

    void clear(void)
    {
        memset(&lbkInfo, 0, sizeof(LINE_BREAK));
        memset(&wbkInfo, 0, sizeof(WORD_BREAK));
	    memset(&cbkInfo, 0, sizeof(CHARS_BREAK));
    }

    LINE_BREAK lbkInfo;
	WORD_BREAK wbkInfo;
    CHARS_BREAK cbkInfo;
};

// text break iterator
TextBreakIterator::TextBreakIterator(BREAK_TYPE type)
    :btype(type), string(NULL), string_len(0)
{
    data = new PlatformBreakData;
}

TextBreakIterator::~TextBreakIterator()
{
    delete data;
}

void TextBreakIterator::clear(void)
{
    string = NULL;
    string_len = 0;
    data->clear();
}

int TextBreakIterator::break_first()
{
	switch (btype)
	{
		case BRK_LINE:
			return FirstLineBreak(string, string_len, &(data->lbkInfo));
		case BRK_CHAR:
            return FirstCharsBreak(string, string_len, &(data->cbkInfo));
		case BRK_WORD:
            return FirstWordBreak(string, string_len, &(data->wbkInfo));
		default:
			break;
	}
    return -1;
}

int TextBreakIterator::break_last()
{
	switch (btype)
	{
		case BRK_LINE:
            notImplemented();
			break;
		case BRK_CHAR:
            notImplemented();
			break;
		case BRK_WORD:
            notImplemented();
			break;
		default:
			break;
	}
	return -1;
}

int TextBreakIterator::break_next()
{
	switch (btype)
	{
		case BRK_LINE:
			return NextLineBreak(string, string_len, &(data->lbkInfo));
		case BRK_CHAR:
            return NextCharsBreak(string, string_len, &(data->cbkInfo));
		case BRK_WORD:
            return NextWordBreak(string, string_len, &(data->wbkInfo));
		default:
			break;
	}
	return -1;
}

int TextBreakIterator::break_prev()
{
	switch (btype)
	{
		case BRK_LINE:
			return PreviousLineBreak(string, string_len, &(data->lbkInfo));
		case BRK_CHAR:
            return PreviousCharsBreak(string, string_len, &(data->cbkInfo));
		case BRK_WORD:
            notImplemented();
			break;
		default:
			break;
	}
	return -1;
}

int TextBreakIterator::break_preceding(int pos)
{
	switch (btype)
	{
		case BRK_LINE:
			return PrecedingLineBreak(string, string_len, &(data->lbkInfo), pos);
		case BRK_CHAR:
            return PrecedingCharsBreak(string, string_len, &(data->cbkInfo), pos);
		case BRK_WORD:
    notImplemented();
			break;
		default:
			break;
	}
	return -1;
}

int TextBreakIterator::break_following(int pos)
{
	switch (btype)
	{
		case BRK_LINE:
			return FollowingLineBreak(string, string_len, &(data->lbkInfo), pos);
		case BRK_CHAR:
            return FollowingCharsBreak(string, string_len, &(data->cbkInfo), pos);
		case BRK_WORD:
    notImplemented();
			break;
		default:
			break;
	}

	return -1;     //error
}

int TextBreakIterator::break_current()
{
	switch (btype)
	{
		case BRK_LINE:
			return data->lbkInfo.pos;
		case BRK_CHAR:
            return data->cbkInfo.current; 
		case BRK_WORD:
            return data->wbkInfo.current; 
		default:
			break;
	}
   return -1;
}

bool TextBreakIterator::is_break(int pos)
{
	switch (btype)
	{
		case BRK_LINE:
            {
                int ret = IsLineBreak (string, string_len, pos);  
                if (ret < 0)
                    return false;
                return ret ? true : false;  
            }
            break;
		case BRK_CHAR:
		case BRK_WORD:
    notImplemented();
			break;
		default:
			break;
	}

	return false;     //error
}

// breaking functions

TextBreakIterator* characterBreakIterator(const UChar* string, int length)
{
	static TextBreakIterator TextBreak(BRK_CHAR);

	TextBreak.setText(string, length);

	return &TextBreak;
}

TextBreakIterator* wordBreakIterator(const UChar* string, int length)
{
	static TextBreakIterator TextBreak(BRK_WORD);

	TextBreak.setText(string, length);

	return &TextBreak;
}

TextBreakIterator* sentenceBreakIterator(const UChar*, int length)
{
    notImplemented();
    return 0;
}

TextBreakIterator* lineBreakIterator(const UChar* string, int length)
{
	static TextBreakIterator TextBreak(BRK_LINE);

	TextBreak.setText(string, length);

	return &TextBreak;
}

int textBreakFirst(TextBreakIterator* bi)
{
	if (!bi)
		return -1;     //error

   return bi->break_first();
}

int textBreakLast(TextBreakIterator* bi)
{
	if (!bi)
		return -1;     //error

   return bi->break_last();
}

int textBreakPrevious(TextBreakIterator* bi)
{
	if (!bi)
		return -1;     //error

    return bi->break_prev();
}

int textBreakNext(TextBreakIterator* bi)
{
	if (!bi)
		return -1;     //error

    return bi->break_next();
}

int textBreakPreceding(TextBreakIterator* bi, int pos)
{
	if (!bi)
		return -1;     //error

    return bi->break_preceding(pos);
}

int textBreakFollowing(TextBreakIterator* bi, int pos)
{
	if(!bi)
		return -1;    //error

    return bi->break_following(pos);
}

int textBreakCurrent(TextBreakIterator* bi)
{
	if(!bi)
		return -1;    //error

    return bi->break_current();
}

bool isTextBreak(TextBreakIterator* bi, int pos)
{
	if(!bi)
		return false;    //error

    return bi->is_break(pos);
}

}
