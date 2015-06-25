#ifndef  _TEXT_BOUNDARYMG_H
#define  _TEXT_BOUNDARYMG_H

#include  "UChar.h"

typedef enum {
	// input types
	OP = 0,	// open
	CL,	// close
	QU,	// quotation
	GL,	// glue
	NS,	// no-start
	EX,	// exclamation/interrogation
	SY,	// Syntax (slash)
	IS,	// infix (numeric) separator
	PR,	// prefix
	PO,	// postfix
	NU,	// numeric
	AL,	// alphabetic
	ID,	// ideograph (atomic)
	IN,	// inseparable
	HY,	// hyphen
	BA,	// break after
	BB,	// break before
	B2,	// break both
	ZW,	// ZW space
	CM,	// combining mark
	WJ, // word joiner

	// used for Korean Syllable Block pair table
	H2, // Hamgul 2 Jamo Syllable
	H3, // Hangul 3 Jamo Syllable
	JL, // Jamo leading consonant
	JV, // Jamo vowel
	JT, // Jamo trailing consonant

	// these are not handled in the pair tables
	SA, // South (East) Asian
	SP,	// space
	PS,	// paragraph and line separators
	BK,	// hard break (newline)
	L_CR, // carriage return
	L_LF, // line feed
	NL, // next line
	CB, // contingent break opportunity
	SG, // surrogate
	AI, // ambiguous
	FXX, // unknown
}BREAKCLASS;

typedef  struct {
    BREAKCLASS   mlbkClass;
    int          pos;
    int          length;
}LINE_BREAK;


int FirstLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo);
int NextLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo);
int PreviousLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo);
int PrecedingLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo, int Precedingpos);
int FollowingLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo, int Followingpos);
int IsLineBreak(const UChar* text, int textlength,int pos);

typedef enum {
    w_ERROR_TYPE=-1,
    FORMAT=1,
    KATAKANA,
    ALETTER,
    MIDLETTER,
    MIDNUM,
    NUMERIC,
    EXTENDNUMLET,
    w_TYPE_ANY
}WORD_TYPE;

typedef struct {
    WORD_TYPE word_type;
    int current;
}WORD_BREAK;

int FirstWordBreak(const UChar* text, int textlength, WORD_BREAK* pWBKinfo);
int NextWordBreak(const UChar* text, int textlength, WORD_BREAK* pWBKinfo);

typedef enum {
    c_ERROR_TYPE=-1,
    CR=1,
    LF,
    CONTROL,
    EXTEND,
    L,
    V,
    T,
    LV,
    LVT,
    c_TYPE_ANY
}CHARS_TYPE;

typedef struct {
    CHARS_TYPE  char_type;
    int current;
}CHARS_BREAK;

int FirstCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo);
int NextCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo);
int PreviousCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo);
int FollowingCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo, int Followingpos);
int PrecedingCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo, int Precedingpos);

#endif




