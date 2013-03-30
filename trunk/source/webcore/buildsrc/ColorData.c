/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: gperf -CDEot -L ANSI-C -N findColor -D -s 2 /home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf  */
/* Computed positions: -k'3-4,6-8,12-13' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
struct NamedColor { const char *name; int RGBValue; };
/* maximum key range = 573, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578,   5,   5,  75,
       65,   0, 180,   0,   5,  35,  95, 115,  30, 155,
       45,   0,  15, 160,  10,  65,  15,  10,  75, 145,
       15, 235,  60, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578, 578, 578, 578,
      578, 578, 578, 578, 578, 578, 578
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      /*FALLTHROUGH*/
      case 11:
      case 10:
      case 9:
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]+1];
      /*FALLTHROUGH*/
      case 5:
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct NamedColor *
findColor (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 149,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 20,
      MIN_HASH_VALUE = 5,
      MAX_HASH_VALUE = 577
    };

  static const struct NamedColor wordlist[] =
    {
#line 58 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"green", 0x008000},
#line 147 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"wheat", 0xf5deb3},
#line 12 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"blue", 0x0000ff},
#line 64 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"ivory", 0xfffff0},
#line 90 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"maroon", 0x800000},
#line 5 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"aqua", 0x00ffff},
#line 19 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"coral", 0xff7f50},
#line 89 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"magenta", 0xff00ff},
#line 118 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"peru", 0xcd853f},
#line 7 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"azure", 0xf0ffff},
#line 75 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightgrey", 0xd3d3d3},
#line 76 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightgreen", 0x90ee90},
#line 74 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightgray", 0xd3d3d3},
#line 141 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"teal", 0x008080},
#line 8 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"beige", 0xf5f5dc},
#line 50 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"forestgreen", 0x228b22},
#line 136 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"slategrey", 0x708090},
#line 145 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"violet", 0xee82ee},
#line 140 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"tan", 0xd2b48c},
#line 135 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"slategray", 0x708090},
#line 88 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"linen", 0xfaf0e6},
#line 23 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"cyan", 0x00ffff},
#line 148 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"white", 0xffffff},
#line 131 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"sienna", 0xa0522d},
#line 146 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"violetred", 0xd02090},
#line 15 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"burlywood", 0xdeb887},
#line 78 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightsalmon", 0xffa07a},
#line 123 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"red", 0xff0000},
#line 73 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightgoldenrodyellow", 0xfafad2},
#line 138 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"springgreen", 0x00ff7f},
#line 6 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"aquamarine", 0x7fffd4},
#line 83 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightslategrey", 0x778899},
#line 150 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"yellow", 0xffff00},
#line 79 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightseagreen", 0x20b2aa},
#line 82 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightslategray", 0x778899},
#line 10 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"black", 0x000000},
#line 111 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"orchid", 0xda70d6},
#line 84 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightsteelblue", 0xb0c4de},
#line 71 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightcoral", 0xf08080},
#line 66 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lavender", 0xe6e6fa},
#line 151 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"yellowgreen", 0x9acd32},
#line 54 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"gold", 0xffd700},
#line 17 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"chartreuse", 0x7fff00},
#line 59 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"greenyellow", 0xadff2f},
#line 113 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"palegreen", 0x98fb98},
#line 85 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightyellow", 0xffffe0},
#line 81 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightslateblue", 0x8470ff},
#line 55 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"goldenrod", 0xdaa520},
#line 107 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"olive", 0x808000},
#line 62 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"indianred", 0xcd5c5c},
#line 63 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"indigo", 0x4b0082},
#line 139 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"steelblue", 0x4682b4},
#line 65 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"khaki", 0xf0e68c},
#line 70 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightblue", 0xadd8e6},
#line 53 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"ghostwhite", 0xf8f8ff},
#line 108 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"olivedrab", 0x6b8e23},
#line 101 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mintcream", 0xf5fffa},
#line 31 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkmagenta", 0x8b008b},
#line 134 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"slateblue", 0x6a5acd},
#line 13 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"blueviolet", 0x8a2be2},
#line 100 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"midnightblue", 0x191970},
#line 137 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"snow", 0xfffafa},
#line 14 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"brown", 0xa52a2a},
#line 61 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"hotpink", 0xff69b4},
#line 86 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lime", 0x00ff00},
#line 119 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"pink", 0xffc0cb},
#line 106 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"oldlace", 0xfdf5e6},
#line 67 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lavenderblush", 0xfff0f5},
#line 120 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"plum", 0xdda0dd},
#line 52 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"gainsboro", 0xdcdcdc},
#line 47 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"dodgerblue", 0x1e90ff},
#line 132 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"silver", 0xc0c0c0},
#line 143 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"tomato", 0xff6347},
#line 94 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumpurple", 0x9370d8},
#line 116 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"papayawhip", 0xffefd5},
#line 51 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"fuchsia", 0xff00ff},
#line 16 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"cadetblue", 0x5f9ea0},
#line 92 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumblue", 0x0000cd},
#line 127 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"salmon", 0xfa8072},
#line 48 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"firebrick", 0xb22222},
#line 60 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"honeydew", 0xf0fff0},
#line 29 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkgreen", 0x006400},
#line 128 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"sandybrown", 0xf4a460},
#line 11 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"blanchedalmond", 0xffebcd},
#line 122 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"purple", 0x800080},
#line 112 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"palegoldenrod", 0xeee8aa},
#line 102 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mistyrose", 0xffe4e1},
#line 98 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumturquoise", 0x48d1cc},
#line 95 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumseagreen", 0x3cb371},
#line 87 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"limegreen", 0x32cd32},
#line 149 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"whitesmoke", 0xf5f5f5},
#line 93 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumorchid", 0xba55d3},
#line 115 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"palevioletred", 0xd87093},
#line 3 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"aliceblue", 0xf0f8ff},
#line 109 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"orange", 0xffa500},
#line 129 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"seagreen", 0x2e8b57},
#line 57 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"grey", 0x808080},
#line 97 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumspringgreen", 0x00fa9a},
#line 25 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkcyan", 0x008b8b},
#line 56 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"gray", 0x808080},
#line 110 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"orangered", 0xff4500},
#line 33 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkorange", 0xff8c00},
#line 103 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"moccasin", 0xffe4b5},
#line 77 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightpink", 0xffb6c1},
#line 104 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"navajowhite", 0xffdead},
#line 22 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"crimson", 0xdc143c},
#line 18 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"chocolate", 0xd2691e},
#line 42 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkviolet", 0x9400d3},
#line 142 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"thistle", 0xd8bfd8},
#line 68 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lawngreen", 0x7cfc00},
#line 43 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"deeppink", 0xff1493},
#line 34 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkorchid", 0x9932cc},
#line 4 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"antiquewhite", 0xfaebd7},
#line 30 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkkhaki", 0xbdb76b},
#line 96 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumslateblue", 0x7b68ee},
#line 144 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"turquoise", 0x40e0d0},
#line 99 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumvioletred", 0xc71585},
#line 44 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"deepskyblue", 0x00bfff},
#line 24 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkblue", 0x00008b},
#line 21 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"cornsilk", 0xfff8dc},
#line 26 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkgoldenrod", 0xb8860b},
#line 105 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"navy", 0x000080},
#line 69 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lemonchiffon", 0xfffacd},
#line 130 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"seashell", 0xfff5ee},
#line 72 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightcyan", 0xe0ffff},
#line 121 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"powderblue", 0xb0e0e6},
#line 133 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"skyblue", 0x87ceeb},
#line 38 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkslateblue", 0x483d8b},
#line 36 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darksalmon", 0xe9967a},
#line 49 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"floralwhite", 0xfffaf0},
#line 126 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"saddlebrown", 0x8b4513},
#line 91 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"mediumaquamarine", 0x66cdaa},
#line 114 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"paleturquoise", 0xafeeee},
#line 125 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"royalblue", 0x4169e1},
#line 37 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkseagreen", 0x8fbc8f},
#line 35 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkred", 0x8b0000},
#line 80 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"lightskyblue", 0x87cefa},
#line 45 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"dimgray", 0x696969},
#line 32 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkolivegreen", 0x556b2f},
#line 20 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"cornflowerblue", 0x6495ed},
#line 9 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"bisque", 0xffe4c4},
#line 28 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkgrey", 0xa9a9a9},
#line 27 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkgray", 0xa9a9a9},
#line 117 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"peachpuff", 0xffdab9},
#line 41 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkturquoise", 0x00ced1},
#line 124 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"rosybrown", 0xbc8f8f},
#line 40 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkslategrey", 0x2f4f4f},
#line 39 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"darkslategray", 0x2f4f4f},
#line 46 "/home/jpzhang/mbrowser/source/webcore/platform/ColorData.gperf"
      {"dimgrey", 0x696969}
    };

  static const short lookup[] =
    {
       -1,  -1,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1,
        1,  -1,  -1,  -1,   2,   3,   4,  -1,  -1,   5,
        6,  -1,   7,  -1,   8,   9,  -1,  -1,  -1,  10,
       11,  -1,  -1,  -1,  12,  -1,  -1,  -1,  -1,  13,
       14,  15,  -1,  -1,  16,  -1,  17,  -1,  18,  19,
       20,  -1,  -1,  -1,  21,  22,  23,  -1,  -1,  24,
       -1,  -1,  -1,  -1,  25,  -1,  26,  -1,  27,  -1,
       28,  29,  -1,  -1,  -1,  30,  -1,  -1,  -1,  31,
       -1,  32,  -1,  33,  34,  35,  36,  -1,  -1,  37,
       38,  -1,  -1,  39,  -1,  -1,  40,  -1,  -1,  41,
       42,  43,  -1,  -1,  44,  -1,  45,  -1,  -1,  46,
       -1,  -1,  -1,  -1,  47,  48,  -1,  -1,  -1,  49,
       -1,  50,  -1,  -1,  51,  52,  -1,  -1,  -1,  53,
       54,  -1,  -1,  -1,  55,  -1,  -1,  -1,  -1,  56,
       -1,  57,  -1,  -1,  58,  59,  -1,  60,  -1,  61,
       62,  -1,  63,  -1,  -1,  -1,  -1,  -1,  -1,  64,
       -1,  -1,  -1,  -1,  65,  -1,  -1,  66,  67,  68,
       -1,  -1,  -1,  -1,  69,  70,  71,  -1,  -1,  -1,
       -1,  72,  73,  -1,  -1,  74,  -1,  75,  -1,  76,
       77,  78,  -1,  -1,  79,  -1,  -1,  -1,  80,  81,
       -1,  -1,  -1,  -1,  -1,  82,  -1,  -1,  -1,  83,
       -1,  84,  -1,  -1,  -1,  -1,  -1,  -1,  85,  86,
       87,  -1,  -1,  -1,  88,  -1,  -1,  -1,  -1,  89,
       90,  -1,  91,  92,  93,  -1,  94,  -1,  95,  96,
       -1,  -1,  97,  98,  99,  -1,  -1,  -1,  -1, 100,
      101,  -1,  -1, 102, 103,  -1, 104, 105,  -1, 106,
      107,  -1, 108,  -1, 109,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 110,  -1,
      111,  -1, 112,  -1,  -1,  -1,  -1,  -1,  -1, 113,
      114,  -1,  -1,  -1, 115, 116, 117,  -1, 118,  -1,
       -1,  -1,  -1, 119,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1, 120, 121,  -1,  -1, 122, 123, 124,
      125,  -1, 126, 127,  -1, 128, 129,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1, 130,  -1,  -1,  -1,
       -1, 131,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1, 132,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1, 133,  -1,  -1, 134,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1, 135,  -1,  -1,
       -1,  -1, 136,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1, 137,  -1, 138,  -1,  -1,  -1,  -1, 139,
       -1, 140,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1, 141,  -1,  -1,  -1,  -1, 142, 143,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 144,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 145,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 146,  -1,
       -1,  -1,  -1, 147,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1, 148
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
        }
    }
  return 0;
}
