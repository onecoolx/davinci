
#include "config.h"

#include <string.h>
#include "charset.h"
#include <wtf/HashMap.h>

#include "gbk_map.h"
#include "gb2312_map.h"
#include "big5_map.h"
#include "eucjp_map.h"
#include "euckr_map.h"
#include "shiftjis_map.h"

namespace WTF {

    template<typename T> struct StrHash;

	const unsigned PHI = 0x9e3779b9U;

    template<> struct StrHash<const char*> {
		static unsigned hash(const char* key)
		{
			// This hash is designed to work on 16-bit chunks at a time. But since the normal case
			// (above) is to hash UTF-16 characters, we just treat the 8-bit chars as if they
			// were 16-bit chunks, which should give matching results

			unsigned m_length = strlen(key);
			uint32_t hash = PHI;
			uint32_t tmp;

			int rem = m_length & 1;
			m_length >>= 1;

			// Main loop
			for (; m_length > 0; m_length--) {
					hash += (unsigned char)key[0];
					tmp = ((unsigned char)key[1] << 11) ^ hash;
					hash = (hash << 16) ^ tmp;
					key += 2;
					hash += hash >> 11;
			}

			// Handle end case
			if (rem) {
					hash += (unsigned char)key[0];
					hash ^= hash << 11;
					hash += hash >> 17;
			}

			// Force "avalanching" of final 127 bits
			hash ^= hash << 3;
			hash += hash >> 5;
			hash ^= hash << 2;
			hash += hash >> 15;
			hash ^= hash << 10;

			// this avoids ever returning a hash code of 0, since that is used to
			// signal "hash not computed yet", using a value that is likely to be
			// effectively the same as 0 when the low bits are masked
			if (hash == 0)
					hash = 0x80000000;

			return hash;
		}
		static bool equal(const char* a, const char* b)
		{
            if (a == b)
                return true;
            if (!a || !b)
                return false;

			return strcmp(a, b) == 0 ? true : false;
		}
	};

    template<typename T> struct DefaultHash;
    template<> struct DefaultHash<const char*> {
		typedef StrHash<const char*> Hash;		
	};
};

typedef HashMap<const char*, charset_ops*> CharSetMap;

static CharSetMap* g_charset_map = 0; 

static void init_charset_map(void);


struct charset_ops* create_charset_ops(const char* name)
{
	init_charset_map();

	return g_charset_map->get(name);
}

void destory_charset_ops(struct charset_ops* ops)
{
	// do nothing
}

//------------------------- BIG5
#if ENABLE(BIG5_SUPPORT)
static int big5_len_first_char (const unsigned char* mstr, int len)
{
    unsigned char ch1;
    unsigned char ch2;

    if (len < 2) return 0;

    ch1 = mstr [0];
    if (ch1 == '\0')
        return 0;

    ch2 = mstr [1];
    if (ch1 >= 0xA1 && ch1 <= 0xFE && 
            ((ch2 >=0x40 && ch2 <= 0x7E) || (ch2 >= 0xA1 && ch2 <= 0xFE)))
        return 2;

    return 0;
}

static unsigned short big5_conv_to_uchar (const unsigned char* mchar, int len)
{
	int index = 0;
    if (mchar [1] & 0x80)
        index = (mchar [0] - 0xA1) * 94 + mchar [1] - 0xA1;
    else
        index = 94 * 94 + (mchar [0] - 0xa1) * 63 + (mchar [1] - 0x40);

	return (unsigned short)big5_map[index];
}

static int big5_conv_from_uchar (unsigned short wc, unsigned char* mchar)
{
    const unsigned char* got;

    if (wc > 0xFFFF)
        return 0;

    got = map_uc16_to_big5 ((unsigned short)wc);

    if (got) {
        mchar [0] = got [0];
        mchar [1] = got [1];
        return 2;
    }

    return 0;
}

struct charset_ops charset_big5= {
	"BIG5",
	big5_len_first_char,
	big5_conv_to_uchar,
	big5_conv_from_uchar,
};
#endif
//------------------------- GB2312
#if ENABLE(GB2312_SUPPORT)
static int gb2312_len_first_char (const unsigned char* mstr, int len)
{
    unsigned char ch1;
    unsigned char ch2;

    if (len < 2) return 0;

    ch1 = mstr [0];
    if (ch1 == '\0')
        return 0;

    ch2 = mstr [1];
	if (((ch1 >= 0xA1 && ch1 <= 0xA9) || (ch1 >= 0xB0 && ch1 <= 0xF7)) && ch2 >= 0xA1 && ch2 <= 0xFE)
		return 2;

    return 0;
}

static unsigned short gb2312_conv_to_uchar (const unsigned char* mchar, int len)
{
	int index = 0;
    int area = mchar [0] - 0xA1;

    if (area < 9) 
        index = (area * 94 + mchar [1] - 0xA1);
    else if (area >= 15)
        index = ((area - 6)* 94 + mchar [1] - 0xA1);

    return (unsigned short)gb2312_map[index];
}

static int gb2312_conv_from_uchar (unsigned short wc, unsigned char* mchar)
{
    const unsigned char* got;

    if (wc > 0xFFFF)
        return 0;

    got = map_uc16_to_gb2312((unsigned short)wc);

    if (got) {
        mchar [0] = got [0];
        mchar [1] = got [1];
        return 2;
    }

    return 0;
}

struct charset_ops charset_gb2312= {
	"GB2312-0",
	gb2312_len_first_char,
	gb2312_conv_to_uchar,
	gb2312_conv_from_uchar,
};
#endif
//------------------------- GBK
#if ENABLE(GBK_SUPPORT)
static int gbk_len_first_char (const unsigned char* mstr, int len)
{
    unsigned char ch1;
    unsigned char ch2;

    if (len < 2) return 0;

    ch1 = mstr [0];
    if (ch1 == '\0')
        return 0;

    ch2 = mstr [1];
    if (ch1 >= 0x81 && ch1 <= 0xFE && ch2 >= 0x40 && ch2 <= 0xFE && ch2 != 0x7F)
        return 2;

    return 0;
}

static unsigned short gbk_conv_to_uchar (const unsigned char* mchar, int len)
{
    if (mchar[1] > 0x7F)
        return (unsigned short)gbk_map[(mchar[0] - 0x81)*190 + mchar[1] - 0x41];
    else
        return (unsigned short)gbk_map[(mchar[0] - 0x81)*190 + mchar[1] - 0x40];
}

static int gbk_conv_from_uchar (unsigned short wc, unsigned char* mchar)
{
    const unsigned char* got;

    if (wc > 0xFFFF)
        return 0;

    got = map_uc16_to_gbk ((unsigned short)wc);

    if (got) {
        mchar [0] = got [0];
        mchar [1] = got [1];
        return 2;
    }

    return 0;
}

struct charset_ops charset_gbk= {
	"GBK",
	gbk_len_first_char,
	gbk_conv_to_uchar,
	gbk_conv_from_uchar,
};
#endif

#if ENABLE(EUCJP_SUPPORT)
static int eucjp_len_first_char (const unsigned char* mstr, int len)
{
    unsigned char ch1;
    unsigned char ch2;

    if (len < 2) return 0;

    ch1 = mstr [0];
    if (ch1 == '\0')
        return 0;

    ch2 = mstr [1];
    if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
        return 2;

    return 0;
}

static unsigned short jisx0208_mbtowc(const unsigned char* s)
{
    unsigned char c1 = s[0];
    if ((c1 >= 0x21 && c1 <= 0x28) || (c1 >= 0x30 && c1 <= 0x74)) {
        unsigned char c2 = s[1];
        if (c2 >= 0x21 && c2 < 0x7f) {
            unsigned int i = 94 * (c1 - 0x21) + (c2 - 0x21);
            wchar_t wc = 0xfffd;
            if (i < 1410) {
                if (i < 690)
                    wc = jisx0208_2uni_page21[i];
            } else {
                if (i < 7808)
                    wc = jisx0208_2uni_page30[i-1410];
            }
            if (wc != 0xfffd) {
                return wc;
            }
        }
        return 0;
    }
    return 0;
}

static unsigned short jisx0212_mbtowc(const unsigned char* s)
{
    unsigned char c1 = s[0];
    if ((c1 == 0x22) || (c1 >= 0x26 && c1 <= 0x27) || (c1 >= 0x29 && c1 <= 0x2b) || (c1 >= 0x30 && c1 <= 0x6d)) {
        unsigned char c2 = s[1];
        if (c2 >= 0x21 && c2 < 0x7f) {
            unsigned int i = 94 * (c1 - 0x21) + (c2 - 0x21);
            wchar_t wc = 0xfffd;
            if (i < 470) {
                if (i < 175)
                    wc = jisx0212_2uni_page22[i-94];
            } else if (i < 752) {
                if (i < 658)
                    wc = jisx0212_2uni_page26[i-470];
            } else if (i < 1410) {
                if (i < 1027)
                    wc = jisx0212_2uni_page29[i-752];
            } else {
                if (i < 7211)
                    wc = jisx0212_2uni_page30[i-1410];
            }
            if (wc != 0xfffd) {
                return wc;
            }
        }
        return 0;
    }
    return 0;
}

static unsigned short eucjp_conv_to_uchar (const unsigned char* s, int n)
{
    unsigned char c = *s;
    /* Code set 0 (ASCII or JIS X 0201-1976 Roman) */
    if (c < 0x80) {
        return *s;
    }
    /* Code set 1 (JIS X 0208) */
    if (c >= 0xa1 && c < 0xff) {
        if (n < 2)
            return 0;
        if (c < 0xf5) {
            unsigned char c2 = s[1];
            if (c2 >= 0xa1 && c2 < 0xff) {
                unsigned char buf[2];
                buf[0] = c-0x80;
                buf[1] = c2-0x80;
                return jisx0208_mbtowc(buf);
            } else
                return 0;
        } else {
            /* User-defined range. See
            * Ken Lunde's "CJKV Information Processing", table 4-66, p. 206. */
            unsigned char c2 = s[1];
            if (c2 >= 0xa1 && c2 < 0xff) {
                return 0xe000 + 94*(c-0xf5) + (c2-0xa1);
            } else
                return 0;
        }
    }
    /* Code set 2 (half-width katakana) */
    if (c == 0x8e) {
        if (n < 2)
            return 0;
        {
            unsigned char c2 = s[1];
            if (c2 >= 0xa1 && c2 < 0xe0) {
                return c2 + 0xfec0;
            } else
                return 0;
        }
    }
    /* Code set 3 (JIS X 0212-1990) */
    if (c == 0x8f) {
        if (n < 2)
            return 0;
        {
            unsigned char c2 = s[1];
            if (c2 >= 0xa1 && c2 < 0xff) {
                if (n < 3)
                    return 0;
                if (c2 < 0xf5) {
                    unsigned char c3 = s[2];
                    if (c3 >= 0xa1 && c3 < 0xff) {
                        unsigned char buf[2];
                        buf[0] = c2-0x80;
                        buf[1] = c3-0x80;
                        return jisx0212_mbtowc(buf);
                    } else
                        return 0;
                } else {
                    /* User-defined range. See
                    * Ken Lunde's "CJKV Information Processing", table 4-66, p. 206. */
                    unsigned char c3 = s[2];
                    if (c3 >= 0xa1 && c3 < 0xff) {
                        return 0xe3ac + 94*(c2-0xf5) + (c3-0xa1);
                    } else
                        return 0;
                }
            } else
                return 0;
        }
    }
    return 0;
}

static int eucjp_conv_from_uchar (unsigned short wc, unsigned char* mchar)
{
	//FIXME: not implement yet, replace with my own unicode library feature.
	return 0;
}

struct charset_ops charset_eucjp= {
	"EUC-JP",
	eucjp_len_first_char,
	eucjp_conv_to_uchar,
	eucjp_conv_from_uchar,
};
#endif

#if ENABLE(SHIFTJIS_SUPPORT)
static int shiftjis_len_first_char (const unsigned char* mstr, int len)
{
    unsigned char ch1;
    unsigned char ch2;

    if (len < 2) return 0;

    ch1 = mstr [0];
    if (ch1 == '\0')
        return 0;

    ch2 = mstr [1];
    if (((ch1 >= 0x81 && ch1 <= 0x9F) || (ch1 >= 0xE0 && ch1 <= 0xEF)) && 
            ((ch2 >= 0x40 && ch2 <= 0x7E) || (ch2 >= 0x80 && ch2 <= 0xFC)))
        return 2;

    return 0;
}

static unsigned short shiftjis_conv_to_uchar (const unsigned char* mchar, int len)
{
    unsigned char ch1 = mchar [0];
    unsigned char ch2 = mchar [1];
    int adjust = ch2 < 159;
    int rowOffset = ch1 < 160 ? 112 : 176;
    int cellOffset = adjust ? (ch2 > 127 ? 32 : 31) : 126;

    ch1 = ((ch1 - rowOffset) << 1) - adjust;
    ch2 -= cellOffset;

    ch1 += 128;
    ch2 += 128;
	return (unsigned short)shiftjis_map[(ch1 - 0xA1) * 94 + ch2 - 0xA1];
}

static int shiftjis_conv_from_uchar (unsigned short wc, unsigned char* mchar)
{
	//FIXME: not implement yet, replace with my own unicode library feature.
	return 0;
}

struct charset_ops charset_shiftjis= {
	"SHIFT-JIS",
	shiftjis_len_first_char,
	shiftjis_conv_to_uchar,
	shiftjis_conv_from_uchar,
};
#endif

#if ENABLE(EUCKR_SUPPORT)
static int euckr_len_first_char (const unsigned char* mstr, int len)
{
    unsigned char ch1;
    unsigned char ch2;

    if (len < 2) return 0;

    ch1 = mstr [0];
    if (ch1 == '\0')
        return 0;

    ch2 = mstr [1];
    if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
        return 2;

    return 0;
}

static unsigned short euckr_conv_to_uchar (const unsigned char* mchar, int len)
{
	return (unsigned short)euckr_map[(mchar [0] - 0xA1) * 94 + mchar [1] - 0xA1];
}

static int euckr_conv_from_uchar (unsigned short wc, unsigned char* mchar)
{
	//FIXME: not implement yet, replace with my own unicode library feature.
	return 0;
}

struct charset_ops charset_euckr= {
	"EUC-KR",
	euckr_len_first_char,
	euckr_conv_to_uchar,
	euckr_conv_from_uchar,
};
#endif
//------------------------- UTF-8

static int utf8_len_first_char (const unsigned char* mstr, int len)
{
    int t, c = *((unsigned char *)(mstr++));
    int n = 1, ch_len = 0;

    /*for ascii character*/
    if (c < 0x80) {
        return 1;
    }

    if (c & 0x80) {
        while (c & (0x80 >> n))
            n++;

        if (n > len)
            return 0;

        ch_len = n;
        while (--n > 0) {
            t = *((unsigned char *)(mstr++));

            if ((!(t & 0x80)) || (t & 0x40))
                return 0;
        }
    }

    return ch_len;
}

static unsigned short utf8_conv_to_uchar (const unsigned char* mchar, int len)
{
    unsigned int wc = *((unsigned char *)(mchar++));
    int n, t;

    if (wc & 0x80) {
        n = 1;
        while (wc & (0x80 >> n))
            n++;

        wc &= (1 << (8-n)) - 1;
        while (--n > 0) {
            t = *((unsigned char *)(mchar++));

            wc = (wc << 6) | (t & 0x3F);
        }
    }

    return wc;
}

static int utf8_conv_from_uchar (unsigned short wc, unsigned char* mchar)
{
    int first, len;

    if (wc < 0x80) {
        first = 0;
        len = 1;
    }
    else if (wc < 0x800) {
        first = 0xC0;
        len = 2;
    }
    else if (wc < 0x10000) {
        first = 0xE0;
        len = 3;
    }
    else if (wc < 0x200000) {
        first = 0xF0;
        len = 4;
    }
    else if (wc < 0x400000) {
        first = 0xF8;
        len = 5;
    }
    else {
        first = 0xFC;
        len = 6;
    }

    switch (len) {
        case 6:
            mchar [5] = (wc & 0x3f) | 0x80; wc >>= 6; /* Fall through */
        case 5:
            mchar [4] = (wc & 0x3f) | 0x80; wc >>= 6; /* Fall through */
        case 4:
            mchar [3] = (wc & 0x3f) | 0x80; wc >>= 6; /* Fall through */
        case 3:
            mchar [2] = (wc & 0x3f) | 0x80; wc >>= 6; /* Fall through */
        case 2:
            mchar [1] = (wc & 0x3f) | 0x80; wc >>= 6; /* Fall through */
        case 1:
            mchar [0] = wc | first;
    }

    return len;
}

struct charset_ops charset_utf8= {
	"UTF-8",
	utf8_len_first_char,
	utf8_conv_to_uchar,
	utf8_conv_from_uchar,
};

//---------------------------------------
static void init_charset_map(void)
{
	if (!g_charset_map) {
		g_charset_map = new CharSetMap;
		//init map functions
		g_charset_map->add("UTF-8", &charset_utf8);
#if ENABLE(GBK_SUPPORT)
		g_charset_map->add("GBK", &charset_gbk);
#endif
#if ENABLE(GB2312_SUPPORT)
		g_charset_map->add("GB2312-0", &charset_gb2312);
#endif
#if ENABLE(BIG5_SUPPORT)
		g_charset_map->add("BIG5", &charset_big5);
#endif
#if ENABLE(EUCJP_SUPPORT)
		g_charset_map->add("EUC-JP", &charset_eucjp);
#endif
#if ENABLE(SHIFTJIS_SUPPORT)
		g_charset_map->add("SHIFT-JIS", &charset_shiftjis);
#endif
#if ENABLE(EUCKR_SUPPORT)
		g_charset_map->add("EUC-KR", &charset_euckr);
#endif
	}
}
