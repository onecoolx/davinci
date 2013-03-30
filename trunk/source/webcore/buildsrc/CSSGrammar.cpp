/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse cssyyparse
#define yylex   cssyylex
#define yyerror cssyyerror
#define yylval  cssyylval
#define yychar  cssyychar
#define yydebug cssyydebug
#define yynerrs cssyynerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UNIMPORTANT_TOK = 258,
     WHITESPACE = 259,
     SGML_CD = 260,
     INCLUDES = 261,
     DASHMATCH = 262,
     BEGINSWITH = 263,
     ENDSWITH = 264,
     CONTAINS = 265,
     STRING = 266,
     IDENT = 267,
     HEX = 268,
     IDSEL = 269,
     IMPORT_SYM = 270,
     PAGE_SYM = 271,
     MEDIA_SYM = 272,
     FONT_FACE_SYM = 273,
     CHARSET_SYM = 274,
     NAMESPACE_SYM = 275,
     WEBKIT_RULE_SYM = 276,
     WEBKIT_DECLS_SYM = 277,
     WEBKIT_VALUE_SYM = 278,
     WEBKIT_MEDIAQUERY_SYM = 279,
     IMPORTANT_SYM = 280,
     MEDIA_ONLY = 281,
     MEDIA_NOT = 282,
     MEDIA_AND = 283,
     QEMS = 284,
     EMS = 285,
     EXS = 286,
     PXS = 287,
     CMS = 288,
     MMS = 289,
     INS = 290,
     PTS = 291,
     PCS = 292,
     DEGS = 293,
     RADS = 294,
     GRADS = 295,
     MSECS = 296,
     SECS = 297,
     HERZ = 298,
     KHERZ = 299,
     DIMEN = 300,
     PERCENTAGE = 301,
     FLOATTOKEN = 302,
     INTEGER = 303,
     URI = 304,
     FUNCTION = 305,
     NOTFUNCTION = 306,
     UNICODERANGE = 307
   };
#endif
/* Tokens.  */
#define UNIMPORTANT_TOK 258
#define WHITESPACE 259
#define SGML_CD 260
#define INCLUDES 261
#define DASHMATCH 262
#define BEGINSWITH 263
#define ENDSWITH 264
#define CONTAINS 265
#define STRING 266
#define IDENT 267
#define HEX 268
#define IDSEL 269
#define IMPORT_SYM 270
#define PAGE_SYM 271
#define MEDIA_SYM 272
#define FONT_FACE_SYM 273
#define CHARSET_SYM 274
#define NAMESPACE_SYM 275
#define WEBKIT_RULE_SYM 276
#define WEBKIT_DECLS_SYM 277
#define WEBKIT_VALUE_SYM 278
#define WEBKIT_MEDIAQUERY_SYM 279
#define IMPORTANT_SYM 280
#define MEDIA_ONLY 281
#define MEDIA_NOT 282
#define MEDIA_AND 283
#define QEMS 284
#define EMS 285
#define EXS 286
#define PXS 287
#define CMS 288
#define MMS 289
#define INS 290
#define PTS 291
#define PCS 292
#define DEGS 293
#define RADS 294
#define GRADS 295
#define MSECS 296
#define SECS 297
#define HERZ 298
#define KHERZ 299
#define DIMEN 300
#define PERCENTAGE 301
#define FLOATTOKEN 302
#define INTEGER 303
#define URI 304
#define FUNCTION 305
#define NOTFUNCTION 306
#define UNICODERANGE 307




/* Copy the first part of user declarations.  */
#line 1 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"


/*
 *  This file is part of the KDE libraries
 *  Copyright (C) 2002-2003 Lars Knoll (knoll@kde.org)
 *  Copyright (C) 2004, 2005, 2006, 2007 Apple Inc.
 *  Copyright (C) 2006 Alexey Proskuryakov (ap@nypop.com)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "config.h"

#include "CSSMediaRule.h"
#include "CSSParser.h"
#include "CSSPrimitiveValue.h"
#include "CSSRule.h"
#include "CSSRuleList.h"
#include "CSSSelector.h"
#include "CSSStyleSheet.h"
#include "Document.h"
#include "HTMLNames.h"
#include "MediaList.h"
#include "MediaQuery.h"
#include "MediaQueryExp.h"
#include "PlatformString.h"
#include <stdlib.h>
#include <string.h>

using namespace WebCore;
using namespace HTMLNames;

#define YYMALLOC fastMalloc
#define YYFREE fastFree
// The following file defines the function
//     const struct props *findProp(const char *word, int len)
//
// with 'props->id' a CSS property in the range from CSS_PROP_MIN to
// (and including) CSS_PROP_TOTAL-1

#include "CSSPropertyNames.c"
#include "CSSValueKeywords.c"

namespace WebCore {

int getPropertyID(const char* tagStr, int len)
{
    DeprecatedString prop;

    if (len && tagStr[0] == '-') {
        prop = DeprecatedString(tagStr, len);
        if (prop.startsWith("-apple-")) {
            prop = "-webkit-" + prop.mid(7);
            tagStr = prop.ascii();
            len++;
        } else if (prop.startsWith("-khtml-")) {
            prop = "-webkit-" + prop.mid(7);
            len++;
            tagStr = prop.ascii();
        }

        // Honor the use of old-style opacity (for Safari 1.1).
        if (prop == "-webkit-opacity") {
            const char * const opacity = "opacity";
            tagStr = opacity;
            len = strlen(opacity);
        }
    }

    const struct props* propsPtr = findProp(tagStr, len);
    if (!propsPtr)
        return 0;

    return propsPtr->id;
}

} // namespace WebCore

static inline int getValueID(const char* tagStr, int len)
{
    DeprecatedString prop;
    if (len && tagStr[0] == '-') {
        prop = DeprecatedString(tagStr, len);
        if (prop.startsWith("-apple-")) {
            prop = "-webkit-" + prop.mid(7);
            tagStr = prop.ascii();
            len++;
        } else if (prop.startsWith("-khtml-")) {
            prop = "-webkit-" + prop.mid(7);
            len++;
            tagStr = prop.ascii();
        }
    }

    const struct css_value* val = findValue(tagStr, len);
    if (!val)
        return 0;

    return val->id;
}

#define YYENABLE_NLS 0
#define YYLTYPE_IS_TRIVIAL 1
#define YYMAXDEPTH 10000
#define YYDEBUG 0
#define YYPARSE_PARAM parser



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 125 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
{
    CSSRule* rule;
    CSSSelector* selector;
    bool ok;
    MediaList *mediaList;
    CSSMediaRule* mediaRule;
    CSSRuleList* ruleList;
    ParseString string;
    float val;
    int prop_id;
    int attribute;
    CSSSelector::Relation relation;
    bool b;
    int i;
    char tok;
    Value value;
    ValueList* valueList;

    MediaQuery* mediaQuery;
    MediaQueryExp* mediaQueryExp;
    Vector<MediaQueryExp*>* mediaQueryExpList;
    MediaQuery::Restrictor mediaQueryRestrictor;
}
/* Line 187 of yacc.c.  */
#line 354 "CSSGrammar.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 149 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"


static inline int cssyyerror(const char*) { return 1; }
static int cssyylex(YYSTYPE* yylval) { return CSSParser::current()->lex(yylval); }



/* Line 216 of yacc.c.  */
#line 373 "CSSGrammar.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   922

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  192
/* YYNRULES -- Number of states.  */
#define YYNSTATES  369

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    71,     2,    72,     2,     2,
      61,    62,    18,    64,    63,    67,    16,    70,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    15,    60,
       2,    69,    66,     2,    73,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    17,     2,    68,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,    19,    59,    65,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    12,    15,    18,    21,    23,    25,
      32,    38,    44,    50,    51,    54,    55,    58,    61,    62,
      64,    70,    74,    78,    79,    83,    84,    88,    89,    93,
      95,    97,    99,   101,   103,   105,   107,   114,   118,   122,
     129,   133,   137,   138,   141,   143,   145,   148,   149,   154,
     164,   166,   169,   170,   172,   173,   175,   177,   182,   183,
     185,   187,   192,   195,   203,   210,   211,   215,   218,   222,
     226,   234,   238,   242,   245,   248,   251,   252,   254,   256,
     262,   264,   269,   272,   274,   278,   281,   283,   286,   289,
     292,   296,   299,   303,   308,   312,   314,   316,   318,   321,
     324,   326,   328,   330,   332,   334,   337,   340,   345,   354,
     360,   370,   372,   374,   376,   378,   380,   382,   384,   386,
     389,   393,   398,   404,   406,   409,   411,   415,   417,   420,
     424,   429,   433,   439,   444,   449,   456,   462,   465,   472,
     475,   479,   482,   485,   486,   488,   492,   495,   498,   501,
     502,   504,   507,   510,   513,   516,   520,   523,   526,   528,
     531,   533,   536,   539,   542,   545,   548,   551,   554,   557,
     560,   563,   566,   569,   572,   575,   578,   581,   584,   587,
     590,   593,   599,   603,   606,   609,   613,   617,   619,   622,
     628,   632,   634
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    83,    82,    85,    86,    87,    -1,    77,
      81,    -1,    78,    81,    -1,    79,    81,    -1,    80,    81,
      -1,   109,    -1,    89,    -1,    26,    58,    81,    76,    81,
      59,    -1,    27,    58,    81,   123,    59,    -1,    28,    58,
      81,   128,    59,    -1,    29,     4,    81,    99,    59,    -1,
      -1,    81,     4,    -1,    -1,    82,     5,    -1,    82,     4,
      -1,    -1,    84,    -1,    24,    81,    11,    81,    60,    -1,
      24,     1,   137,    -1,    24,     1,    60,    -1,    -1,    85,
      89,    82,    -1,    -1,    86,    90,    82,    -1,    -1,    87,
      88,    82,    -1,   109,    -1,   102,    -1,   105,    -1,   106,
      -1,   136,    -1,   134,    -1,   135,    -1,    20,    81,    92,
      81,   100,    60,    -1,    20,     1,   137,    -1,    20,     1,
      60,    -1,    25,    81,    91,    92,    81,    60,    -1,    25,
       1,   137,    -1,    25,     1,    60,    -1,    -1,    12,     4,
      -1,    11,    -1,    54,    -1,    12,    81,    -1,    -1,    15,
      81,   128,    81,    -1,    33,    81,    61,    81,    93,    81,
      94,    62,    81,    -1,    95,    -1,    96,    95,    -1,    -1,
      96,    -1,    -1,    31,    -1,    32,    -1,    98,    81,   104,
      97,    -1,    -1,   101,    -1,    99,    -1,   101,    63,    81,
      99,    -1,   101,     1,    -1,    22,    81,   101,    58,    81,
     103,    59,    -1,    22,    81,    58,    81,   103,    59,    -1,
      -1,   103,   109,    81,    -1,    12,    81,    -1,    21,     1,
     137,    -1,    21,     1,    60,    -1,    23,    81,    58,    81,
     123,    59,    81,    -1,    23,     1,   137,    -1,    23,     1,
      60,    -1,    64,    81,    -1,    65,    81,    -1,    66,    81,
      -1,    -1,    67,    -1,    64,    -1,   110,    58,    81,   123,
      59,    -1,   111,    -1,   110,    63,    81,   111,    -1,   110,
       1,    -1,   113,    -1,   111,   107,   113,    -1,   111,     1,
      -1,    19,    -1,    18,    19,    -1,    12,    19,    -1,   114,
      81,    -1,   114,   115,    81,    -1,   115,    81,    -1,   112,
     114,    81,    -1,   112,   114,   115,    81,    -1,   112,   115,
      81,    -1,    12,    -1,    18,    -1,   116,    -1,   115,   116,
      -1,   115,     1,    -1,    14,    -1,    13,    -1,   117,    -1,
     119,    -1,   122,    -1,    16,    12,    -1,    12,    81,    -1,
      17,    81,   118,    68,    -1,    17,    81,   118,   120,    81,
     121,    81,    68,    -1,    17,    81,   112,   118,    68,    -1,
      17,    81,   112,   118,   120,    81,   121,    81,    68,    -1,
      69,    -1,     6,    -1,     7,    -1,     8,    -1,     9,    -1,
      10,    -1,    12,    -1,    11,    -1,    15,    12,    -1,    15,
      15,    12,    -1,    15,    55,    12,    62,    -1,    15,    56,
      81,   113,    62,    -1,   125,    -1,   124,   125,    -1,   124,
      -1,     1,   138,     1,    -1,     1,    -1,   124,     1,    -1,
     125,    60,    81,    -1,   125,   138,    60,    81,    -1,     1,
      60,    81,    -1,     1,   138,     1,    60,    81,    -1,   124,
     125,    60,    81,    -1,   124,     1,    60,    81,    -1,   124,
       1,   138,     1,    60,    81,    -1,   126,    15,    81,   128,
     127,    -1,   126,     1,    -1,   126,    15,    81,     1,   128,
     127,    -1,    30,    81,    -1,   126,    15,    81,    -1,    12,
      81,    -1,    30,    81,    -1,    -1,   130,    -1,   128,   129,
     130,    -1,   128,     1,    -1,    70,    81,    -1,    63,    81,
      -1,    -1,   131,    -1,   108,   131,    -1,    11,    81,    -1,
      12,    81,    -1,    50,    81,    -1,   108,    50,    81,    -1,
      54,    81,    -1,    57,    81,    -1,   133,    -1,    71,    81,
      -1,   132,    -1,    72,    81,    -1,    53,    81,    -1,    52,
      81,    -1,    51,    81,    -1,    37,    81,    -1,    38,    81,
      -1,    39,    81,    -1,    40,    81,    -1,    41,    81,    -1,
      42,    81,    -1,    43,    81,    -1,    44,    81,    -1,    45,
      81,    -1,    46,    81,    -1,    47,    81,    -1,    48,    81,
      -1,    49,    81,    -1,    35,    81,    -1,    34,    81,    -1,
      36,    81,    -1,    55,    81,   128,    62,    81,    -1,    55,
      81,     1,    -1,    13,    81,    -1,    14,    81,    -1,    73,
       1,   137,    -1,    73,     1,    60,    -1,    89,    -1,     1,
     137,    -1,    58,     1,   138,     1,    59,    -1,    58,     1,
      59,    -1,   137,    -1,   138,     1,   137,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   291,   291,   292,   293,   294,   295,   299,   300,   304,
     310,   316,   330,   337,   338,   341,   343,   344,   347,   349,
     354,   360,   362,   366,   368,   375,   377,   380,   382,   390,
     391,   392,   393,   394,   395,   396,   400,   403,   406,   412,
     417,   418,   422,   423,   427,   428,   432,   438,   441,   447,
     454,   459,   466,   469,   473,   476,   479,   485,   493,   496,
     500,   505,   510,   516,   519,   525,   526,   537,   554,   557,
     563,   567,   570,   576,   577,   578,   579,   583,   584,   588,
     594,   597,   605,   611,   614,   634,   640,   641,   642,   646,
     651,   658,   664,   675,   688,   702,   710,   718,   721,   734,
     740,   749,   762,   763,   764,   768,   780,   791,   796,   802,
     811,   824,   827,   830,   833,   836,   839,   845,   846,   850,
     870,   885,   895,   910,   913,   918,   921,   924,   927,   933,
     936,   939,   942,   945,   950,   953,   959,   973,   977,   984,
     989,   996,  1006,  1007,  1011,  1016,  1030,  1036,  1039,  1042,
    1048,  1049,  1050,  1051,  1058,  1059,  1060,  1061,  1062,  1063,
    1065,  1068,  1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,
    1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,
    1090,  1095,  1104,  1120,  1121,  1128,  1131,  1137,  1143,  1160,
    1161,  1165,  1166
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "UNIMPORTANT_TOK", "WHITESPACE",
  "SGML_CD", "INCLUDES", "DASHMATCH", "BEGINSWITH", "ENDSWITH", "CONTAINS",
  "STRING", "IDENT", "HEX", "IDSEL", "':'", "'.'", "'['", "'*'", "'|'",
  "IMPORT_SYM", "PAGE_SYM", "MEDIA_SYM", "FONT_FACE_SYM", "CHARSET_SYM",
  "NAMESPACE_SYM", "WEBKIT_RULE_SYM", "WEBKIT_DECLS_SYM",
  "WEBKIT_VALUE_SYM", "WEBKIT_MEDIAQUERY_SYM", "IMPORTANT_SYM",
  "MEDIA_ONLY", "MEDIA_NOT", "MEDIA_AND", "QEMS", "EMS", "EXS", "PXS",
  "CMS", "MMS", "INS", "PTS", "PCS", "DEGS", "RADS", "GRADS", "MSECS",
  "SECS", "HERZ", "KHERZ", "DIMEN", "PERCENTAGE", "FLOATTOKEN", "INTEGER",
  "URI", "FUNCTION", "NOTFUNCTION", "UNICODERANGE", "'{'", "'}'", "';'",
  "'('", "')'", "','", "'+'", "'~'", "'>'", "'-'", "']'", "'='", "'/'",
  "'#'", "'%'", "'@'", "$accept", "stylesheet", "ruleset_or_import",
  "webkit_rule", "webkit_decls", "webkit_value", "webkit_mediaquery",
  "maybe_space", "maybe_sgml", "maybe_charset", "charset", "import_list",
  "namespace_list", "rule_list", "rule", "import", "namespace",
  "maybe_ns_prefix", "string_or_uri", "media_feature", "maybe_media_value",
  "media_query_exp", "media_query_exp_list", "maybe_media_query_exp_list",
  "maybe_media_restrictor", "media_query", "maybe_media_list",
  "media_list", "media", "ruleset_list", "medium", "page", "font_face",
  "combinator", "unary_operator", "ruleset", "selector_list", "selector",
  "namespace_selector", "simple_selector", "element_name",
  "specifier_list", "specifier", "class", "attr_name", "attrib", "match",
  "ident_or_string", "pseudo", "declaration_list", "decl_list",
  "declaration", "property", "prio", "expr", "operator", "term",
  "unary_term", "function", "hexcolor", "invalid_at", "invalid_import",
  "invalid_rule", "invalid_block", "invalid_block_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    58,    46,    91,    42,   124,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   123,   125,
      59,    40,    41,    44,    43,   126,    62,    45,    93,    61,
      47,    35,    37,    64
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    75,    75,    75,    76,    76,    77,
      78,    79,    80,    81,    81,    82,    82,    82,    83,    83,
      84,    84,    84,    85,    85,    86,    86,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    89,    89,    89,    90,
      90,    90,    91,    91,    92,    92,    93,    94,    94,    95,
      96,    96,    97,    97,    98,    98,    98,    99,   100,   100,
     101,   101,   101,   102,   102,   103,   103,   104,   105,   105,
     106,   106,   106,   107,   107,   107,   107,   108,   108,   109,
     110,   110,   110,   111,   111,   111,   112,   112,   112,   113,
     113,   113,   113,   113,   113,   114,   114,   115,   115,   115,
     116,   116,   116,   116,   116,   117,   118,   119,   119,   119,
     119,   120,   120,   120,   120,   120,   120,   121,   121,   122,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   124,
     124,   124,   124,   124,   124,   124,   125,   125,   125,   125,
     125,   126,   127,   127,   128,   128,   128,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   132,   132,   133,   133,   134,   134,   135,   136,   137,
     137,   138,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     2,     2,     2,     2,     1,     1,     6,
       5,     5,     5,     0,     2,     0,     2,     2,     0,     1,
       5,     3,     3,     0,     3,     0,     3,     0,     3,     1,
       1,     1,     1,     1,     1,     1,     6,     3,     3,     6,
       3,     3,     0,     2,     1,     1,     2,     0,     4,     9,
       1,     2,     0,     1,     0,     1,     1,     4,     0,     1,
       1,     4,     2,     7,     6,     0,     3,     2,     3,     3,
       7,     3,     3,     2,     2,     2,     0,     1,     1,     5,
       1,     4,     2,     1,     3,     2,     1,     2,     2,     2,
       3,     2,     3,     4,     3,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     2,     2,     4,     8,     5,
       9,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     4,     5,     1,     2,     1,     3,     1,     2,     3,
       4,     3,     5,     4,     4,     6,     5,     2,     6,     2,
       3,     2,     2,     0,     1,     3,     2,     2,     2,     0,
       1,     2,     2,     2,     2,     3,     2,     2,     1,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     5,     3,     2,     2,     3,     3,     1,     2,     5,
       3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      18,     0,     0,     0,     0,     0,     0,    13,    13,    13,
      13,    15,    19,     0,     0,    13,    13,    13,    13,     1,
       3,     4,     5,     6,    23,     0,    22,    21,    14,    13,
       0,     0,     0,    54,    17,    16,    25,     0,     0,    95,
     101,   100,     0,     0,    13,    96,    86,     0,    13,     8,
       7,     0,     0,     0,    83,    13,     0,    97,   102,   103,
     104,   127,    13,    13,     0,     0,   123,     0,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    78,    77,    13,    13,     0,
       0,   144,   150,   160,   158,    55,    56,    13,     0,    27,
      15,   190,   191,     0,    20,    88,   119,     0,     0,    13,
     105,     0,    87,     0,     0,     0,    82,    13,    13,    85,
      13,    13,    13,     0,    95,    96,    13,     0,    89,     0,
      99,    91,    98,    13,     0,   141,   139,    10,   128,   124,
      13,     0,   137,    13,   152,   153,   183,   184,   179,   178,
     180,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   154,   164,   163,   162,   156,     0,
     157,   159,   161,    13,   151,   146,    11,    13,    13,     0,
       0,    12,     0,     0,    15,    24,     0,   120,     0,     0,
      13,     0,     0,     0,    38,    37,    44,    45,    13,     9,
       0,     0,    73,    74,    75,    84,    92,     0,    94,    90,
     131,   126,    13,     0,    13,   129,     0,    13,     0,   182,
       0,   155,   148,   147,   145,    13,    52,     0,    42,     0,
       0,    13,     0,     0,    15,   187,    30,    31,    32,    29,
      34,    35,    33,    26,   189,   192,   121,     0,   106,    13,
       0,   112,   113,   114,   115,   116,   107,   111,    13,    54,
       0,     0,    93,    13,   134,     0,   133,   130,     0,     0,
      13,    67,    13,    50,    53,    57,    41,    40,     0,     0,
     188,     0,    54,     0,     0,     0,    28,   122,   109,    13,
       0,    60,     0,     0,    79,   132,    13,     0,    13,   136,
     181,     0,    51,    43,    13,    69,    68,    13,     0,    72,
      71,    13,   186,   185,     0,   118,   117,    13,    36,    62,
      13,   135,   138,   142,    13,     0,    65,    13,     0,    13,
       0,    54,     0,    39,     0,    65,     0,     0,   108,    61,
      13,    13,    64,    13,     0,    13,   110,    46,    47,    66,
      63,    70,    13,     0,     0,    13,     0,    49,    48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,    48,     7,     8,     9,    10,   258,    24,    11,
      12,    36,   109,   193,   244,    49,   194,   289,   208,   351,
     363,   283,   284,   285,   107,   301,   302,   303,   246,   344,
     236,   247,   248,   133,    99,   353,    51,    52,    53,    54,
      55,    56,    57,    58,   203,    59,   268,   327,    60,    64,
      65,    66,    67,   309,   100,   189,   101,   102,   103,   104,
     250,   251,   252,   112,   113
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -207
static const yytype_int16 yypact[] =
{
     268,   232,   -39,   -35,   -20,   118,    53,  -207,  -207,  -207,
    -207,  -207,  -207,    81,    38,  -207,  -207,  -207,  -207,  -207,
     121,   121,   121,   121,   180,   127,  -207,  -207,  -207,  -207,
     462,    29,   713,   119,  -207,  -207,   125,   256,    44,   139,
    -207,  -207,   183,   168,  -207,   174,  -207,   142,  -207,  -207,
    -207,    50,   774,   270,  -207,   261,   196,  -207,  -207,  -207,
    -207,    99,  -207,  -207,   147,   104,   123,    20,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,   869,
     523,  -207,  -207,  -207,  -207,  -207,  -207,  -207,   169,   228,
    -207,  -207,  -207,   255,  -207,  -207,  -207,   253,   258,  -207,
    -207,   213,  -207,   160,   188,    52,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,   471,  -207,  -207,   261,   196,   121,   196,
    -207,   121,  -207,  -207,   279,   121,   121,  -207,   186,   230,
    -207,    43,  -207,  -207,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   651,
     121,   121,   121,  -207,  -207,  -207,  -207,  -207,  -207,   830,
      22,  -207,   136,   154,  -207,   180,   259,  -207,   238,   528,
     139,   174,   291,   195,  -207,  -207,  -207,  -207,  -207,  -207,
      29,   528,   121,   121,   121,  -207,   121,   196,   121,   121,
     121,   187,  -207,   305,  -207,   121,   250,  -207,   397,  -207,
     587,   121,   121,   121,  -207,  -207,   286,   197,    33,   250,
     311,  -207,    59,   320,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,   180,  -207,  -207,  -207,   260,   121,  -207,
     242,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,   129,
     264,   793,   121,  -207,   121,   208,   121,   121,   830,   333,
    -207,   121,  -207,  -207,   286,  -207,  -207,  -207,   321,    11,
    -207,   211,     8,   241,   120,   244,   180,  -207,  -207,  -207,
     218,  -207,   267,    49,  -207,   121,  -207,   333,  -207,  -207,
     121,    54,  -207,  -207,  -207,  -207,  -207,  -207,    56,  -207,
    -207,  -207,  -207,  -207,   218,  -207,  -207,  -207,  -207,  -207,
    -207,   121,  -207,   121,  -207,    60,   121,  -207,    29,  -207,
      27,   119,   152,  -207,   400,   121,   265,    32,  -207,  -207,
    -207,  -207,  -207,  -207,   408,  -207,  -207,   121,     9,   121,
    -207,   121,  -207,   266,   713,  -207,   459,   121,   121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -207,  -207,  -207,  -207,  -207,  -207,  -207,    -1,  -100,  -207,
    -207,  -207,  -207,  -207,  -207,   -31,  -207,  -207,    41,  -207,
    -207,    47,  -207,  -207,  -207,   -32,  -207,    40,  -207,   -10,
    -207,  -207,  -207,  -207,  -207,   -28,  -207,   126,   219,  -101,
     288,   -26,   -38,  -207,   137,  -207,    82,    19,  -207,  -206,
    -207,   283,  -207,    46,  -176,  -207,   162,   257,  -207,  -207,
    -207,  -207,  -207,    -2,   -41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -150
static const yytype_int16 yytable[] =
{
      14,   108,    50,   230,   270,   110,    20,    21,    22,    23,
     195,    27,    28,    28,    30,    31,    32,    33,   142,    15,
     144,   152,   206,    16,   362,   151,    28,   137,    38,   139,
      61,    28,   215,    28,   235,   153,    28,    28,    17,   105,
     106,    62,    28,   121,   226,   288,   124,   125,    28,    29,
     329,   126,   279,    19,   138,   141,    28,   329,    28,    63,
     293,   145,   146,   -13,    28,   207,   317,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   253,   348,   181,   182,   257,   142,
     356,   142,   307,   227,   114,   148,   190,   223,   127,   -59,
     217,   209,   330,   128,   337,   334,    62,   -13,   199,   330,
     343,   205,    18,    28,    28,    28,   210,   211,    37,   212,
     213,   214,   346,    28,    63,   216,   218,   237,   219,    25,
     -13,    26,   220,   123,   296,    47,   -13,   -13,   -13,   225,
     105,   106,   228,   -13,    -2,   239,    28,    25,   115,   143,
     105,   106,   245,  -125,   350,   249,    39,    40,    41,    42,
      43,    44,    45,    46,    47,   240,   241,   242,   321,   142,
     120,    25,   231,   150,    34,    35,   232,   233,   366,   -58,
     -13,   238,    28,   122,   255,   116,   -13,   140,   117,   206,
     -13,   261,   262,   263,   264,   265,   147,   269,   -13,    40,
      41,    42,    43,    44,   -13,   -13,   272,    28,    25,   255,
     204,   274,    28,   276,   255,   200,   277,   243,   191,   325,
     326,   201,    46,    13,   281,   287,   -13,   290,   118,   119,
     292,   294,   207,   -13,    25,    25,   222,   273,   261,   262,
     263,   264,   265,   192,   -13,    25,   196,   286,   -13,   -13,
     -13,   -13,   -13,   266,   267,   197,    25,   300,   306,    25,
     198,   315,   305,   255,    40,    41,    42,    43,    44,   310,
     221,   311,   134,    40,    41,    42,    43,    44,   135,   316,
     224,   320,     1,   323,     2,     3,     4,     5,   324,    25,
     256,   319,    25,   259,   322,   331,   275,   333,    25,   349,
     298,   267,   291,   335,    25,   111,   336,    25,   254,   282,
     338,   295,   297,   304,   355,   313,   340,   328,   365,   341,
     314,   312,   318,   342,   185,   354,   345,   271,   347,   260,
     202,   136,   299,   339,  -149,  -149,  -149,  -149,   149,   357,
     358,   234,   359,   332,   361,     0,   184,     0,     0,     0,
       0,   364,     0,   308,   367,   368,     0,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,     0,
    -149,  -143,  -143,  -143,     0,     0,   187,  -149,   278,     0,
    -149,    28,     0,   188,  -149,  -149,     0,     0,    68,    69,
      70,    71,    39,    40,    41,    42,    43,    44,    45,    46,
      39,    40,    41,    42,    43,    44,    45,    46,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,     0,    94,  -140,  -140,  -140,     0,   352,
     185,    95,     0,   -13,    96,     0,    28,   360,    97,    98,
    -149,  -149,  -149,  -149,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    39,    40,    41,    42,    43,    44,    45,
      46,     0,     0,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,     0,  -149,     0,     0,     0,
       0,   -13,   187,  -149,   185,     0,  -149,     0,     0,   188,
    -149,  -149,    28,     0,  -149,  -149,  -149,  -149,     0,     0,
      39,    40,    41,    42,    43,    44,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,     0,
    -149,     0,   186,     0,     0,     0,   187,  -149,   185,     0,
    -149,     0,     0,   188,  -149,  -149,     0,     0,  -149,  -149,
    -149,  -149,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,     0,  -149,     0,     0,     0,     0,   280,
     187,  -149,   229,     0,  -149,    28,     0,   188,  -149,  -149,
       0,     0,    68,    69,    70,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,     0,    94,     0,
       0,     0,     0,     0,     0,    95,     0,    28,    96,     0,
       0,     0,    97,    98,    68,    69,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,     0,
      94,     0,     0,     0,     0,   129,     0,    95,     0,     0,
      96,     0,     0,     0,    97,    98,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -80,     0,     0,     0,     0,   -80,   130,   131,
     132,    68,    69,    70,    71,     0,     0,     0,     0,     0,
       0,   -81,     0,     0,     0,     0,   -81,   130,   131,   132,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,     0,    94,     0,     0,
       0,     0,     0,     0,    95,     0,     0,    96,     0,     0,
       0,    97,    98,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   183,
      89,    90,    91
};

static const yytype_int16 yycheck[] =
{
       1,    33,    30,   179,   210,    36,     7,     8,     9,    10,
     110,    13,     4,     4,    15,    16,    17,    18,    56,    58,
      61,     1,    11,    58,    15,    66,     4,    53,    29,    55,
       1,     4,   133,     4,    12,    15,     4,     4,    58,    31,
      32,    12,     4,    44,     1,    12,    47,    48,     4,    11,
       1,     1,   228,     0,    55,    56,     4,     1,     4,    30,
       1,    62,    63,     4,     4,    54,    58,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,   194,    68,    97,    98,   199,   137,
      68,   139,   278,    60,    60,     1,   107,   148,    58,    60,
     136,    59,    63,    63,    58,    61,    12,    58,   119,    63,
      60,   123,     4,     4,     4,     4,   127,   128,     1,   130,
     131,   132,   338,     4,    30,   136,   137,     1,   139,    58,
       4,    60,   143,     1,   244,    20,     4,    11,    12,   150,
      31,    32,   153,    11,     0,     1,     4,    58,    19,    60,
      31,    32,   193,    59,    12,   193,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    58,   217,
      12,    58,   183,    60,     4,     5,   187,   188,   364,    60,
      54,   192,     4,    19,   196,    12,    54,     1,    15,    11,
       4,     6,     7,     8,     9,    10,    59,   208,    12,    13,
      14,    15,    16,    17,    18,    19,   217,     4,    58,   221,
      60,   222,     4,   224,   226,    12,   227,    73,    59,    11,
      12,    18,    19,     1,   235,   237,     4,   239,    55,    56,
     241,   242,    54,    11,    58,    58,    60,    60,     6,     7,
       8,     9,    10,    25,    58,    58,     1,    60,    62,    63,
      64,    65,    66,    68,    69,    12,    58,   268,    60,    58,
      12,    60,   273,   275,    13,    14,    15,    16,    17,   280,
       1,   282,    12,    13,    14,    15,    16,    17,    18,   291,
      60,   293,    24,   295,    26,    27,    28,    29,   299,    58,
      62,    60,    58,    12,    60,   306,     1,   308,    58,   341,
      68,    69,     1,   314,    58,    59,   317,    58,    59,    33,
     321,     1,    62,    59,    59,     4,   327,    60,    62,   330,
     289,   284,   292,   334,     1,   345,   337,   211,   339,   202,
     121,    53,   260,   324,    11,    12,    13,    14,    65,   350,
     351,   189,   353,   307,   355,    -1,    99,    -1,    -1,    -1,
      -1,   362,    -1,    30,   365,   366,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      57,    58,    59,    60,    -1,    -1,    63,    64,     1,    -1,
      67,     4,    -1,    70,    71,    72,    -1,    -1,    11,    12,
      13,    14,    12,    13,    14,    15,    16,    17,    18,    19,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    57,    58,    59,    60,    -1,    59,
       1,    64,    -1,     4,    67,    -1,     4,    59,    71,    72,
      11,    12,    13,    14,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    64,     1,    -1,    67,    -1,    -1,    70,
      71,    72,     4,    -1,    11,    12,    13,    14,    -1,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      57,    -1,    59,    -1,    -1,    -1,    63,    64,     1,    -1,
      67,    -1,    -1,    70,    71,    72,    -1,    -1,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    64,     1,    -1,    67,     4,    -1,    70,    71,    72,
      -1,    -1,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    -1,     4,    67,    -1,
      -1,    -1,    71,    72,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      57,    -1,    -1,    -1,    -1,     1,    -1,    64,    -1,    -1,
      67,    -1,    -1,    -1,    71,    72,    12,    13,    14,    15,
      16,    17,    18,    19,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    67,    -1,    -1,
      -1,    71,    72,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    26,    27,    28,    29,    75,    77,    78,    79,
      80,    83,    84,     1,    81,    58,    58,    58,     4,     0,
      81,    81,    81,    81,    82,    58,    60,   137,     4,    11,
      81,    81,    81,    81,     4,     5,    85,     1,    81,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    76,    89,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   119,
     122,     1,    12,    30,   123,   124,   125,   126,    11,    12,
      13,    14,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    57,    64,    67,    71,    72,   108,
     128,   130,   131,   132,   133,    31,    32,    98,    99,    86,
      89,    59,   137,   138,    60,    19,    12,    15,    55,    56,
      12,    81,    19,     1,    81,    81,     1,    58,    63,     1,
      64,    65,    66,   107,    12,    18,   114,   115,    81,   115,
       1,    81,   116,    60,   138,    81,    81,    59,     1,   125,
      60,   138,     1,    15,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    50,   131,     1,    59,    63,    70,   129,
      81,    59,    25,    87,    90,    82,     1,    12,    12,    81,
      12,    18,   112,   118,    60,   137,    11,    54,    92,    59,
      81,    81,    81,    81,    81,   113,    81,   115,    81,    81,
      81,     1,    60,   138,    60,    81,     1,    60,    81,     1,
     128,    81,    81,    81,   130,    12,   104,     1,    81,     1,
      21,    22,    23,    73,    88,    89,   102,   105,   106,   109,
     134,   135,   136,    82,    59,   137,    62,   113,    81,    12,
     118,     6,     7,     8,     9,    10,    68,    69,   120,    81,
     123,   111,    81,    60,    81,     1,    81,    81,     1,   128,
      62,    81,    33,    95,    96,    97,    60,   137,    12,    91,
     137,     1,    81,     1,    81,     1,    82,    62,    68,   120,
      81,    99,   100,   101,    59,    81,    60,   128,    30,   127,
      81,    81,    95,     4,    92,    60,   137,    58,   101,    60,
     137,    58,    60,   137,    81,    11,    12,   121,    60,     1,
      63,    81,   127,    81,    61,    81,    81,    58,    81,   121,
      81,    81,    81,    60,   103,    81,   123,    81,    68,    99,
      12,    93,    59,   109,   103,    59,    68,    81,    81,    81,
      59,    81,    15,    94,    81,    62,   128,    81,    81
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:
#line 304 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        static_cast<CSSParser*>(parser)->rule = (yyvsp[(4) - (6)].rule);
    ;}
    break;

  case 10:
#line 310 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        /* can be empty */
    ;}
    break;

  case 11:
#line 316 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        if ((yyvsp[(4) - (5)].valueList)) {
            p->valueList = p->sinkFloatingValueList((yyvsp[(4) - (5)].valueList));
            int oldParsedProperties = p->numParsedProperties;
            if (!p->parseValue(p->id, p->important))
                p->rollbackLastProperties(p->numParsedProperties - oldParsedProperties);
            delete p->valueList;
            p->valueList = 0;
        }
    ;}
    break;

  case 12:
#line 330 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
         CSSParser* p = static_cast<CSSParser*>(parser);
         p->mediaQuery = p->sinkFloatingMediaQuery((yyvsp[(4) - (5)].mediaQuery));
     ;}
    break;

  case 19:
#line 349 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
  ;}
    break;

  case 20:
#line 354 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
     CSSParser* p = static_cast<CSSParser*>(parser);
     (yyval.rule) = static_cast<CSSParser*>(parser)->createCharsetRule((yyvsp[(3) - (5)].string));
     if ((yyval.rule) && p->styleElement && p->styleElement->isCSSStyleSheet())
         p->styleElement->append((yyval.rule));
  ;}
    break;

  case 21:
#line 360 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
  ;}
    break;

  case 22:
#line 362 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
  ;}
    break;

  case 24:
#line 368 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
     CSSParser* p = static_cast<CSSParser*>(parser);
     if ((yyvsp[(2) - (3)].rule) && p->styleElement && p->styleElement->isCSSStyleSheet())
         p->styleElement->append((yyvsp[(2) - (3)].rule));
 ;}
    break;

  case 28:
#line 382 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
     CSSParser* p = static_cast<CSSParser*>(parser);
     if ((yyvsp[(2) - (3)].rule) && p->styleElement && p->styleElement->isCSSStyleSheet())
         p->styleElement->append((yyvsp[(2) - (3)].rule));
 ;}
    break;

  case 36:
#line 400 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createImportRule((yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].mediaList));
    ;}
    break;

  case 37:
#line 403 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 38:
#line 406 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 39:
#line 412 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
    CSSParser* p = static_cast<CSSParser*>(parser);
    if (p->styleElement && p->styleElement->isCSSStyleSheet())
        static_cast<CSSStyleSheet*>(p->styleElement)->addNamespace(p, atomicString((yyvsp[(3) - (6)].string)), atomicString((yyvsp[(4) - (6)].string)));
;}
    break;

  case 42:
#line 422 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.string).characters = 0; ;}
    break;

  case 43:
#line 423 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 46:
#line 432 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.string) = (yyvsp[(1) - (2)].string);
    ;}
    break;

  case 47:
#line 438 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    ;}
    break;

  case 48:
#line 441 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.valueList) = (yyvsp[(3) - (4)].valueList);
    ;}
    break;

  case 49:
#line 447 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyvsp[(5) - (9)].string).lower();
        (yyval.mediaQueryExp) = static_cast<CSSParser*>(parser)->createFloatingMediaQueryExp(atomicString((yyvsp[(5) - (9)].string)), (yyvsp[(7) - (9)].valueList));
    ;}
    break;

  case 50:
#line 454 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      CSSParser* p = static_cast<CSSParser*>(parser);
      (yyval.mediaQueryExpList) = p->createFloatingMediaQueryExpList();
      (yyval.mediaQueryExpList)->append(p->sinkFloatingMediaQueryExp((yyvsp[(1) - (1)].mediaQueryExp)));
    ;}
    break;

  case 51:
#line 459 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      (yyval.mediaQueryExpList) = (yyvsp[(1) - (2)].mediaQueryExpList);
      (yyval.mediaQueryExpList)->append(static_cast<CSSParser*>(parser)->sinkFloatingMediaQueryExp((yyvsp[(2) - (2)].mediaQueryExp)));
    ;}
    break;

  case 52:
#line 466 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = static_cast<CSSParser*>(parser)->createFloatingMediaQueryExpList();
    ;}
    break;

  case 54:
#line 473 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::None;
    ;}
    break;

  case 55:
#line 476 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::Only;
    ;}
    break;

  case 56:
#line 479 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::Not;
    ;}
    break;

  case 57:
#line 485 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyvsp[(3) - (4)].string).lower();
        (yyval.mediaQuery) = p->createFloatingMediaQuery((yyvsp[(1) - (4)].mediaQueryRestrictor), domString((yyvsp[(3) - (4)].string)), p->sinkFloatingMediaQueryExpList((yyvsp[(4) - (4)].mediaQueryExpList)));
    ;}
    break;

  case 58:
#line 493 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = static_cast<CSSParser*>(parser)->createMediaList();
     ;}
    break;

  case 60:
#line 500 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.mediaList) = p->createMediaList();
        (yyval.mediaList)->appendMediaQuery(p->sinkFloatingMediaQuery((yyvsp[(1) - (1)].mediaQuery)));
    ;}
    break;

  case 61:
#line 505 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = (yyvsp[(1) - (4)].mediaList);
        if ((yyval.mediaList))
            (yyval.mediaList)->appendMediaQuery(static_cast<CSSParser*>(parser)->sinkFloatingMediaQuery((yyvsp[(4) - (4)].mediaQuery)));
    ;}
    break;

  case 62:
#line 510 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.mediaList) = 0;
    ;}
    break;

  case 63:
#line 516 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createMediaRule((yyvsp[(3) - (7)].mediaList), (yyvsp[(6) - (7)].ruleList));
    ;}
    break;

  case 64:
#line 519 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createMediaRule(0, (yyvsp[(5) - (6)].ruleList));
    ;}
    break;

  case 65:
#line 525 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.ruleList) = 0; ;}
    break;

  case 66:
#line 526 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ruleList) = (yyvsp[(1) - (3)].ruleList);
        if ((yyvsp[(2) - (3)].rule)) {
            if (!(yyval.ruleList))
                (yyval.ruleList) = static_cast<CSSParser*>(parser)->createRuleList();
            (yyval.ruleList)->append((yyvsp[(2) - (3)].rule));
        }
    ;}
    break;

  case 67:
#line 537 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      (yyval.string) = (yyvsp[(1) - (2)].string);
  ;}
    break;

  case 68:
#line 554 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 69:
#line 557 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 70:
#line 564 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createFontFaceRule();
    ;}
    break;

  case 71:
#line 567 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 72:
#line 570 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      (yyval.rule) = 0;
    ;}
    break;

  case 73:
#line 576 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.relation) = CSSSelector::DirectAdjacent; ;}
    break;

  case 74:
#line 577 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.relation) = CSSSelector::IndirectAdjacent; ;}
    break;

  case 75:
#line 578 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.relation) = CSSSelector::Child; ;}
    break;

  case 76:
#line 579 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.relation) = CSSSelector::Descendant; ;}
    break;

  case 77:
#line 583 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.i) = -1; ;}
    break;

  case 78:
#line 584 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.i) = 1; ;}
    break;

  case 79:
#line 588 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = static_cast<CSSParser*>(parser)->createStyleRule((yyvsp[(1) - (5)].selector));
    ;}
    break;

  case 80:
#line 594 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    ;}
    break;

  case 81:
#line 597 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        if ((yyvsp[(1) - (4)].selector) && (yyvsp[(4) - (4)].selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selector) = (yyvsp[(1) - (4)].selector);
            (yyval.selector)->append(p->sinkFloatingSelector((yyvsp[(4) - (4)].selector)));
        } else
            (yyval.selector) = 0;
    ;}
    break;

  case 82:
#line 605 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = 0;
    ;}
    break;

  case 83:
#line 611 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    ;}
    break;

  case 84:
#line 614 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(3) - (3)].selector);
        if (!(yyvsp[(1) - (3)].selector))
            (yyval.selector) = 0;
        else if ((yyval.selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            CSSSelector* end = (yyval.selector);
            while (end->m_tagHistory)
                end = end->m_tagHistory;
            end->m_relation = (yyvsp[(2) - (3)].relation);
            end->m_tagHistory = p->sinkFloatingSelector((yyvsp[(1) - (3)].selector));
            if ((yyvsp[(2) - (3)].relation) == CSSSelector::Descendant || (yyvsp[(2) - (3)].relation) == CSSSelector::Child) {
                if (Document* doc = p->document())
                    doc->setUsesDescendantRules(true);
            } else if ((yyvsp[(2) - (3)].relation) == CSSSelector::DirectAdjacent || (yyvsp[(2) - (3)].relation) == CSSSelector::IndirectAdjacent) {
                if (Document* doc = p->document())
                    doc->setUsesSiblingRules(true);
            }
        }
    ;}
    break;

  case 85:
#line 634 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = 0;
    ;}
    break;

  case 86:
#line 640 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.string).characters = 0; (yyval.string).length = 0; ;}
    break;

  case 87:
#line 641 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { static UChar star = '*'; (yyval.string).characters = &star; (yyval.string).length = 1; ;}
    break;

  case 88:
#line 642 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 89:
#line 646 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_tag = QualifiedName(nullAtom, atomicString((yyvsp[(1) - (2)].string)), p->defaultNamespace);
    ;}
    break;

  case 90:
#line 651 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (3)].selector);
        if ((yyval.selector)) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selector)->m_tag = QualifiedName(nullAtom, atomicString((yyvsp[(1) - (3)].string)), p->defaultNamespace);
        }
    ;}
    break;

  case 91:
#line 658 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (2)].selector);
        CSSParser* p = static_cast<CSSParser*>(parser);
        if ((yyval.selector) && p->defaultNamespace != starAtom)
            (yyval.selector)->m_tag = QualifiedName(nullAtom, starAtom, p->defaultNamespace);
    ;}
    break;

  case 92:
#line 664 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        AtomicString namespacePrefix = atomicString((yyvsp[(1) - (3)].string));
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        if (p->styleElement && p->styleElement->isCSSStyleSheet())
            (yyval.selector)->m_tag = QualifiedName(namespacePrefix,
                                    atomicString((yyvsp[(2) - (3)].string)),
                                    static_cast<CSSStyleSheet*>(p->styleElement)->determineNamespace(namespacePrefix));
        else // FIXME: Shouldn't this case be an error?
            (yyval.selector)->m_tag = QualifiedName(nullAtom, atomicString((yyvsp[(2) - (3)].string)), p->defaultNamespace);
    ;}
    break;

  case 93:
#line 675 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(3) - (4)].selector);
        if ((yyval.selector)) {
            AtomicString namespacePrefix = atomicString((yyvsp[(1) - (4)].string));
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (p->styleElement && p->styleElement->isCSSStyleSheet())
                (yyval.selector)->m_tag = QualifiedName(namespacePrefix,
                                          atomicString((yyvsp[(2) - (4)].string)),
                                          static_cast<CSSStyleSheet*>(p->styleElement)->determineNamespace(namespacePrefix));
            else // FIXME: Shouldn't this case be an error?
                (yyval.selector)->m_tag = QualifiedName(nullAtom, atomicString((yyvsp[(2) - (4)].string)), p->defaultNamespace);
        }
    ;}
    break;

  case 94:
#line 688 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (3)].selector);
        if ((yyval.selector)) {
            AtomicString namespacePrefix = atomicString((yyvsp[(1) - (3)].string));
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (p->styleElement && p->styleElement->isCSSStyleSheet())
                (yyval.selector)->m_tag = QualifiedName(namespacePrefix,
                                          starAtom,
                                          static_cast<CSSStyleSheet*>(p->styleElement)->determineNamespace(namespacePrefix));
        }
    ;}
    break;

  case 95:
#line 702 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        ParseString& str = (yyvsp[(1) - (1)].string);
        CSSParser* p = static_cast<CSSParser*>(parser);
        Document* doc = p->document();
        if (doc && doc->isHTMLDocument())
            str.lower();
        (yyval.string) = str;
    ;}
    break;

  case 96:
#line 710 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        static UChar star = '*';
        (yyval.string).characters = &star;
        (yyval.string).length = 1;
    ;}
    break;

  case 97:
#line 718 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    ;}
    break;

  case 98:
#line 721 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        if (!(yyvsp[(2) - (2)].selector))
            (yyval.selector) = 0;
        else if ((yyvsp[(1) - (2)].selector)) {
            (yyval.selector) = (yyvsp[(1) - (2)].selector);
            CSSParser* p = static_cast<CSSParser*>(parser);
            CSSSelector* end = (yyvsp[(1) - (2)].selector);
            while (end->m_tagHistory)
                end = end->m_tagHistory;
            end->m_relation = CSSSelector::SubSelector;
            end->m_tagHistory = p->sinkFloatingSelector((yyvsp[(2) - (2)].selector));
        }
    ;}
    break;

  case 99:
#line 734 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = 0;
    ;}
    break;

  case 100:
#line 740 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::Id;
        if (!p->strict)
            (yyvsp[(1) - (1)].string).lower();
        (yyval.selector)->m_attr = idAttr;
        (yyval.selector)->m_value = atomicString((yyvsp[(1) - (1)].string));
    ;}
    break;

  case 101:
#line 749 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        if ((yyvsp[(1) - (1)].string).characters[0] >= '0' && (yyvsp[(1) - (1)].string).characters[0] <= '9') {
            (yyval.selector) = 0;
        } else {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selector) = p->createFloatingSelector();
            (yyval.selector)->m_match = CSSSelector::Id;
            if (!p->strict)
                (yyvsp[(1) - (1)].string).lower();
            (yyval.selector)->m_attr = idAttr;
            (yyval.selector)->m_value = atomicString((yyvsp[(1) - (1)].string));
        }
    ;}
    break;

  case 105:
#line 768 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::Class;
        if (!p->strict)
            (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->m_attr = classAttr;
        (yyval.selector)->m_value = atomicString((yyvsp[(2) - (2)].string));
    ;}
    break;

  case 106:
#line 780 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        ParseString& str = (yyvsp[(1) - (2)].string);
        CSSParser* p = static_cast<CSSParser*>(parser);
        Document* doc = p->document();
        if (doc && doc->isHTMLDocument())
            str.lower();
        (yyval.string) = str;
    ;}
    break;

  case 107:
#line 791 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_attr = QualifiedName(nullAtom, atomicString((yyvsp[(3) - (4)].string)), nullAtom);
        (yyval.selector)->m_match = CSSSelector::Set;
    ;}
    break;

  case 108:
#line 796 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_attr = QualifiedName(nullAtom, atomicString((yyvsp[(3) - (8)].string)), nullAtom);
        (yyval.selector)->m_match = (CSSSelector::Match)(yyvsp[(4) - (8)].i);
        (yyval.selector)->m_value = atomicString((yyvsp[(6) - (8)].string));
    ;}
    break;

  case 109:
#line 802 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        AtomicString namespacePrefix = atomicString((yyvsp[(3) - (5)].string));
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_attr = QualifiedName(namespacePrefix,
                                   atomicString((yyvsp[(4) - (5)].string)),
                                   static_cast<CSSStyleSheet*>(p->styleElement)->determineNamespace(namespacePrefix));
        (yyval.selector)->m_match = CSSSelector::Set;
    ;}
    break;

  case 110:
#line 811 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        AtomicString namespacePrefix = atomicString((yyvsp[(3) - (9)].string));
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.selector) = p->createFloatingSelector();
        (yyval.selector)->m_attr = QualifiedName(namespacePrefix,
                                   atomicString((yyvsp[(4) - (9)].string)),
                                   static_cast<CSSStyleSheet*>(p->styleElement)->determineNamespace(namespacePrefix));
        (yyval.selector)->m_match = (CSSSelector::Match)(yyvsp[(5) - (9)].i);
        (yyval.selector)->m_value = atomicString((yyvsp[(7) - (9)].string));
    ;}
    break;

  case 111:
#line 824 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.i) = CSSSelector::Exact;
    ;}
    break;

  case 112:
#line 827 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.i) = CSSSelector::List;
    ;}
    break;

  case 113:
#line 830 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.i) = CSSSelector::Hyphen;
    ;}
    break;

  case 114:
#line 833 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.i) = CSSSelector::Begin;
    ;}
    break;

  case 115:
#line 836 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.i) = CSSSelector::End;
    ;}
    break;

  case 116:
#line 839 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.i) = CSSSelector::Contain;
    ;}
    break;

  case 119:
#line 850 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoClass;
        (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->m_value = atomicString((yyvsp[(2) - (2)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoEmpty ||
                 type == CSSSelector::PseudoFirstChild) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            Document* doc = p->document();
            if (doc)
                doc->setUsesSiblingRules(true);
        } else if (type == CSSSelector::PseudoFirstLine) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (Document* doc = p->document())
                doc->setUsesFirstLineRules(true);
        }
    ;}
    break;

  case 120:
#line 870 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoElement;
        (yyvsp[(3) - (3)].string).lower();
        (yyval.selector)->m_value = atomicString((yyvsp[(3) - (3)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoFirstLine) {
            CSSParser* p = static_cast<CSSParser*>(parser);
            if (Document* doc = p->document())
                doc->setUsesFirstLineRules(true);
        }
    ;}
    break;

  case 121:
#line 885 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.selector) = static_cast<CSSParser*>(parser)->createFloatingSelector();
        (yyval.selector)->m_match = CSSSelector::PseudoClass;
        (yyval.selector)->m_argument = atomicString((yyvsp[(3) - (4)].string));
        (yyvsp[(2) - (4)].string).lower();
        (yyval.selector)->m_value = atomicString((yyvsp[(2) - (4)].string));
        if ((yyval.selector)->pseudoType() == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
    ;}
    break;

  case 122:
#line 895 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        if (!(yyvsp[(4) - (5)].selector))
            (yyval.selector) = 0;
        else {
            CSSParser* p = static_cast<CSSParser*>(parser);
            (yyval.selector) = p->createFloatingSelector();
            (yyval.selector)->m_match = CSSSelector::PseudoClass;
            (yyval.selector)->m_simpleSelector = p->sinkFloatingSelector((yyvsp[(4) - (5)].selector));
            (yyvsp[(2) - (5)].string).lower();
            (yyval.selector)->m_value = atomicString((yyvsp[(2) - (5)].string));
        }
    ;}
    break;

  case 123:
#line 910 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (1)].ok);
    ;}
    break;

  case 124:
#line 913 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (2)].ok);
        if ( (yyvsp[(2) - (2)].ok) )
            (yyval.ok) = (yyvsp[(2) - (2)].ok);
    ;}
    break;

  case 125:
#line 918 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (1)].ok);
    ;}
    break;

  case 126:
#line 921 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = false;
    ;}
    break;

  case 127:
#line 924 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = false;
    ;}
    break;

  case 128:
#line 927 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (2)].ok);
    ;}
    break;

  case 129:
#line 933 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (3)].ok);
    ;}
    break;

  case 130:
#line 936 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = false;
    ;}
    break;

  case 131:
#line 939 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = false;
    ;}
    break;

  case 132:
#line 942 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = false;
    ;}
    break;

  case 133:
#line 945 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (4)].ok);
        if ((yyvsp[(2) - (4)].ok))
            (yyval.ok) = (yyvsp[(2) - (4)].ok);
    ;}
    break;

  case 134:
#line 950 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (4)].ok);
    ;}
    break;

  case 135:
#line 953 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = (yyvsp[(1) - (6)].ok);
    ;}
    break;

  case 136:
#line 959 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = false;
        CSSParser* p = static_cast<CSSParser*>(parser);
        if ((yyvsp[(1) - (5)].prop_id) && (yyvsp[(4) - (5)].valueList)) {
            p->valueList = p->sinkFloatingValueList((yyvsp[(4) - (5)].valueList));
            int oldParsedProperties = p->numParsedProperties;
            (yyval.ok) = p->parseValue((yyvsp[(1) - (5)].prop_id), (yyvsp[(5) - (5)].b));
            if (!(yyval.ok))
                p->rollbackLastProperties(p->numParsedProperties - oldParsedProperties);
            delete p->valueList;
            p->valueList = 0;
        }
    ;}
    break;

  case 137:
#line 973 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.ok) = false;
    ;}
    break;

  case 138:
#line 977 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        /* The default movable type template has letter-spacing: .none;  Handle this by looking for
        error tokens at the start of an expr, recover the expr and then treat as an error, cleaning
        up and deleting the shifted expr.  */
        (yyval.ok) = false;
    ;}
    break;

  case 139:
#line 984 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        /* Handle this case: div { text-align: center; !important } Just reduce away the stray !important. */
        (yyval.ok) = false;
    ;}
    break;

  case 140:
#line 989 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        /* div { font-family: } Just reduce away this property with no value. */
        (yyval.ok) = false;
    ;}
    break;

  case 141:
#line 996 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyvsp[(1) - (2)].string).lower();
        DeprecatedString str = deprecatedString((yyvsp[(1) - (2)].string));
        const char* s = str.ascii();
        int l = str.length();
        (yyval.prop_id) = getPropertyID(s, l);
    ;}
    break;

  case 142:
#line 1006 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.b) = true; ;}
    break;

  case 143:
#line 1007 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.b) = false; ;}
    break;

  case 144:
#line 1011 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.valueList) = p->createFloatingValueList();
        (yyval.valueList)->addValue(p->sinkFloatingValue((yyvsp[(1) - (1)].value)));
    ;}
    break;

  case 145:
#line 1016 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        (yyval.valueList) = (yyvsp[(1) - (3)].valueList);
        if ((yyval.valueList)) {
            if ((yyvsp[(2) - (3)].tok)) {
                Value v;
                v.id = 0;
                v.unit = Value::Operator;
                v.iValue = (yyvsp[(2) - (3)].tok);
                (yyval.valueList)->addValue(v);
            }
            (yyval.valueList)->addValue(p->sinkFloatingValue((yyvsp[(3) - (3)].value)));
        }
    ;}
    break;

  case 146:
#line 1030 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    ;}
    break;

  case 147:
#line 1036 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.tok) = '/';
    ;}
    break;

  case 148:
#line 1039 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.tok) = ',';
    ;}
    break;

  case 149:
#line 1042 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.tok) = 0;
  ;}
    break;

  case 150:
#line 1048 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value) = (yyvsp[(1) - (1)].value); ;}
    break;

  case 151:
#line 1049 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value) = (yyvsp[(2) - (2)].value); (yyval.value).fValue *= (yyvsp[(1) - (2)].i); ;}
    break;

  case 152:
#line 1050 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_STRING; ;}
    break;

  case 153:
#line 1051 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      DeprecatedString str = deprecatedString((yyvsp[(1) - (2)].string));
      (yyval.value).id = getValueID(str.lower().latin1(), str.length());
      (yyval.value).unit = CSSPrimitiveValue::CSS_IDENT;
      (yyval.value).string = (yyvsp[(1) - (2)].string);
  ;}
    break;

  case 154:
#line 1058 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_DIMENSION ;}
    break;

  case 155:
#line 1059 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(2) - (3)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_DIMENSION ;}
    break;

  case 156:
#line 1060 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_URI; ;}
    break;

  case 157:
#line 1061 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).iValue = 0; (yyval.value).unit = CSSPrimitiveValue::CSS_UNKNOWN;/* ### */ ;}
    break;

  case 158:
#line 1062 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (1)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_RGBCOLOR; ;}
    break;

  case 159:
#line 1063 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = ParseString(); (yyval.value).unit = CSSPrimitiveValue::CSS_RGBCOLOR; ;}
    break;

  case 160:
#line 1065 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
      (yyval.value) = (yyvsp[(1) - (1)].value);
  ;}
    break;

  case 161:
#line 1068 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {;}
    break;

  case 162:
#line 1072 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = true; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; ;}
    break;

  case 163:
#line 1073 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = false; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; ;}
    break;

  case 164:
#line 1074 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_PERCENTAGE; ;}
    break;

  case 165:
#line 1075 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_PX; ;}
    break;

  case 166:
#line 1076 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_CM; ;}
    break;

  case 167:
#line 1077 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_MM; ;}
    break;

  case 168:
#line 1078 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_IN; ;}
    break;

  case 169:
#line 1079 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_PT; ;}
    break;

  case 170:
#line 1080 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_PC; ;}
    break;

  case 171:
#line 1081 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_DEG; ;}
    break;

  case 172:
#line 1082 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_RAD; ;}
    break;

  case 173:
#line 1083 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_GRAD; ;}
    break;

  case 174:
#line 1084 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_MS; ;}
    break;

  case 175:
#line 1085 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_S; ;}
    break;

  case 176:
#line 1086 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_HZ; ;}
    break;

  case 177:
#line 1087 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_KHZ; ;}
    break;

  case 178:
#line 1088 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_EMS; ;}
    break;

  case 179:
#line 1089 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = Value::Q_EMS; ;}
    break;

  case 180:
#line 1090 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (2)].val); (yyval.value).unit = CSSPrimitiveValue::CSS_EXS; ;}
    break;

  case 181:
#line 1095 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        Function* f = p->createFloatingFunction();
        f->name = (yyvsp[(1) - (5)].string);
        f->args = p->sinkFloatingValueList((yyvsp[(3) - (5)].valueList));
        (yyval.value).id = 0;
        (yyval.value).unit = Value::Function;
        (yyval.value).function = f;
    ;}
    break;

  case 182:
#line 1104 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        CSSParser* p = static_cast<CSSParser*>(parser);
        Function* f = p->createFloatingFunction();
        f->name = (yyvsp[(1) - (3)].string);
        f->args = 0;
        (yyval.value).id = 0;
        (yyval.value).unit = Value::Function;
        (yyval.value).function = f;
  ;}
    break;

  case 183:
#line 1120 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 184:
#line 1121 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); ;}
    break;

  case 185:
#line 1128 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 186:
#line 1131 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 187:
#line 1137 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;

  case 188:
#line 1143 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"
    {
        (yyval.rule) = 0;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3248 "CSSGrammar.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1169 "/home/jpzhang/mbrowser/source/webcore/css/CSSGrammar.y"


