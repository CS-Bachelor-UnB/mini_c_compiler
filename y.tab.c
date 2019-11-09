/* A Bison parser, made by GNU Bison 3.4.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 9 "parser.yacc"

#include "utilities.h"
#include "symbolTable.h"
#include "syntaxTree.h"
#include "code.h"
#include "functionCall.h"

#define DEBUG_SYNTAX
#define DEBUG_SYMBOLS

typedef struct TempVariable {
	Symbol *symbol;
	struct TempVariable *next;
} TempVariable;

typedef struct StringLiteral {
	Symbol 	*symbol;
	struct StringLiteral *next;
} StringLiteral;

/************************
 *						*
 * 		prototypes		*
 *						*
 ************************/

void 	typeError(char *errorMessage),
		generateNewTempID(),
		generateNewLabelID(),
		declareGlobalVariables(SyntaxTree *tree),
		writeCode(Code *code),
		insertStringLiteral(Symbol *stringLiteral),
		popStringLiterals(StringLiteral *stringLiteral),
		insertTempVariable(Symbol *tempVariable),
		popTempVariables(TempVariable *tempVariable),
		writeExpressionCode(char *mnemonic, char *operator, Code *code);
char	isStringLiteral(Symbol *target);
int		allocateStackSpace(SyntaxTree *declaration, int offset);
Symbol	*recallStringLiteral(char *string);
Code	*constructCode(SyntaxTree *tree);

/************************
 *						*
 *	global variables	*
 *						*
 ************************/

extern int yylineno;
extern char *yytext;
extern FunctionCall	*_callStack;
char	*_currID = NULL,
		*_currFID = NULL,
		_returnedValue = FALSE,
		_generateCode = TRUE,
		_errorMessage[255],
		_tempID[15],				// up to 10 billion temps > unsigned int max
		_labelID[16];				// up to 10 billion labels > unsigned int max
unsigned int	_tempNum = 0,
				_labelNum = 0,
				_offset = 0,
				_stackSize = 0;
Type	_currType = UNKNOWN,
		_currPType = UNKNOWN;
FunctionType _currFType = F_UNKNOWN;
Parameter *_currParam = NULL;
StringLiteral *_stringLiterals = NULL;
TempVariable *_tempVariables = NULL;

#line 139 "y.tab.c"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTCON = 259,
    CHARCON = 260,
    STRCON = 261,
    CHAR = 262,
    INT = 263,
    VOID = 264,
    IF = 265,
    ELSE = 266,
    WHILE = 267,
    FOR = 268,
    RETURN = 269,
    EXTERN = 270,
    UMINUS = 271,
    DBLEQ = 272,
    NOTEQ = 273,
    LTEQ = 274,
    GTEQ = 275,
    LOGICAND = 276,
    LOGICOR = 277,
    OTHER = 278
  };
#endif
/* Tokens.  */
#define ID 258
#define INTCON 259
#define CHARCON 260
#define STRCON 261
#define CHAR 262
#define INT 263
#define VOID 264
#define IF 265
#define ELSE 266
#define WHILE 267
#define FOR 268
#define RETURN 269
#define EXTERN 270
#define UMINUS 271
#define DBLEQ 272
#define NOTEQ 273
#define LTEQ 274
#define GTEQ 275
#define LOGICAND 276
#define LOGICOR 277
#define OTHER 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 78 "parser.yacc"

	char character;
	int integer;
	char *string;
	SyntaxTree *tree;
	struct exprReturn {
		Type type;
		SyntaxTree *tree;
	} exprReturn;

#line 239 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   320

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  193

#define YYUNDEFTOK  2
#define YYMAXUTOK   278

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,     2,     2,     2,     2,     2,
      32,    33,    28,    26,    34,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
      24,    39,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   112,   112,   113,   116,   117,   119,   122,   130,   132,
     133,   135,   138,   143,   149,   154,   159,   177,   178,   181,
     182,   185,   200,   228,   232,   238,   246,   261,   283,   287,
     293,   326,   367,   368,   371,   401,   514,   621,   640,   642,
     645,   652,   660,   667,   676,   700,   719,   720,   751,   750,
     795,   796,   799,   802,   808,   811,   812,   815,   843,   878,
     879,   882,   893,   904,   916,   928,   940,   952,   964,   976,
     988,  1000,  1012,  1024,  1035,  1047,  1046,  1062,  1063,  1072,
    1081,  1105,  1132,  1131,  1183,  1182,  1224,  1242,  1271,  1272
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTCON", "CHARCON", "STRCON",
  "CHAR", "INT", "VOID", "IF", "ELSE", "WHILE", "FOR", "RETURN", "EXTERN",
  "UMINUS", "DBLEQ", "NOTEQ", "LTEQ", "GTEQ", "LOGICAND", "LOGICOR",
  "OTHER", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'!'", "';'", "'('",
  "')'", "','", "'['", "']'", "'{'", "'}'", "'='", "$accept", "program",
  "declaration", "storeFID", "storeID", "storeExtern", "storeVoid",
  "makeProt", "multiProtDcl", "multiVarDcl", "varDcl", "type", "initParam",
  "paramTypes", "storePType", "arrayTypeOpt", "multiParam", "insertFunc",
  "function", "multiTypeDcl", "statement", "$@1", "statementOpt",
  "exprOpt", "assignment", "assgOpt", "expr", "$@2", "multiFuncOpt", "$@3",
  "$@4", "args", "multiExprOpt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    60,    62,    43,    45,    42,    47,
      33,    59,    40,    41,    44,    91,    93,   123,   125,    61
};
# endif

#define YYPACT_NINF -161

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-161)))

#define YYTABLE_NINF -13

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     237,   -12,    73,  -161,  -161,  -161,  -161,  -161,  -161,     8,
      46,    35,    62,  -161,  -161,  -161,    35,    35,  -161,    40,
      64,    47,  -161,    51,    53,  -161,    63,  -161,    55,  -161,
    -161,  -161,    66,  -161,    97,  -161,  -161,   135,    77,  -161,
      84,    95,  -161,   105,   124,  -161,  -161,  -161,   116,  -161,
     119,   125,  -161,  -161,   178,   136,  -161,   186,  -161,   186,
     186,   186,   185,    24,   138,  -161,  -161,   138,  -161,  -161,
    -161,  -161,  -161,    60,    56,    35,    94,   191,  -161,   199,
    -161,   209,   210,   211,   123,  -161,  -161,  -161,    -2,  -161,
     208,   215,  -161,  -161,    67,  -161,   131,   131,   245,  -161,
    -161,  -161,  -161,   131,   131,  -161,   131,   236,   102,   216,
     131,   131,  -161,  -161,  -161,   173,   190,    25,  -161,   219,
      86,  -161,  -161,   207,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,  -161,  -161,   220,   131,
     147,   251,  -161,   110,   110,   131,   226,  -161,  -161,  -161,
     288,   288,    49,    49,   277,   264,    49,    49,   120,   120,
    -161,  -161,  -161,   251,  -161,   227,   241,   275,  -161,   256,
     251,  -161,   131,   131,   118,   131,  -161,   110,   245,  -161,
     160,   267,   131,   251,  -161,   266,   126,  -161,  -161,  -161,
     110,  -161,  -161
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     5,     1,    23,    24,    15,    14,     0,
       0,     0,     0,     3,     4,     2,     0,     0,    12,     0,
      21,     0,    20,     0,     0,    34,     0,    34,     7,    34,
      34,    25,     0,    25,     0,    25,    25,     0,     0,    22,
       0,    21,    19,     0,     0,    28,    29,    26,     0,    33,
      18,    18,    18,    18,    30,    27,    39,    16,    39,    16,
      16,    16,     0,     0,    54,    16,    11,    54,     9,    10,
       8,    31,    32,     0,     0,     0,     0,     0,    20,     0,
      13,     0,     0,     0,     0,    51,    54,    36,     0,    53,
       0,     0,    35,    38,     0,    52,     0,     0,    60,    75,
      78,    79,    80,     0,     0,    45,     0,     0,     0,    48,
       0,     0,    46,    34,    37,     0,     0,     0,    59,     0,
      86,    61,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,    50,     0,     0,
       0,    57,    25,     0,     0,    56,    82,    84,    76,    77,
      67,    68,    69,    71,    73,    74,    70,    72,    63,    64,
      65,    66,    47,    87,    89,     0,     0,    40,    42,     0,
      55,    81,     0,     0,     0,     0,    17,     0,    60,    89,
       0,     0,     0,    58,    41,     0,     0,    85,    49,    88,
       0,    83,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -161,  -161,  -161,    -1,   -94,  -161,   290,   -25,   152,   231,
     -17,    16,  -161,   -33,  -161,   247,  -161,   -22,  -161,   253,
    -119,  -161,   -57,  -161,   -92,   140,   -83,  -161,  -161,  -161,
    -161,  -160,   141
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     9,    19,    88,    10,    11,    66,    57,    28,
      22,    73,    37,    38,    48,    49,    55,    31,    13,    64,
      89,   139,    74,   169,    90,   119,   163,   120,   148,   172,
     173,   164,   174
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,   107,    43,    44,   117,    33,   118,    35,    36,    14,
      76,    21,   179,   115,   116,    23,    24,    42,    12,     3,
     121,   122,   189,   123,   167,   168,    17,   140,   141,   108,
     109,    45,    46,   110,    68,    69,    70,   111,    18,    15,
      75,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,     5,     6,     7,    78,    79,   184,    80,
     110,    77,   170,    41,   111,    20,    81,    32,    82,    83,
      84,   192,    25,     4,    91,   132,   133,   134,   135,    27,
       5,     6,     7,    29,   117,    30,   118,    85,     8,    34,
     180,   142,   183,    86,    87,    79,   -12,    80,   114,    26,
      41,    34,    39,    79,    81,    80,    82,    83,    84,   166,
      50,    79,    81,    80,    82,    83,    84,    51,   146,    54,
      81,   147,    82,    83,    84,    85,    99,   100,   101,   102,
      26,    86,    92,    85,    99,   100,   101,   102,    52,    86,
     137,    85,    45,    46,    47,     5,     6,    86,   134,   135,
     103,   181,   182,   104,   105,   106,    56,    53,   103,   191,
     182,   104,    58,   106,   124,   125,   126,   127,   128,   129,
      63,   130,   131,   132,   133,   134,   135,   124,   125,   126,
     127,   128,   129,   165,   130,   131,   132,   133,   134,   135,
     124,   125,   126,   127,   128,   129,   187,   130,   131,   132,
     133,   134,   135,    59,    60,    61,   143,   124,   125,   126,
     127,   128,   129,    62,   130,   131,   132,   133,   134,   135,
      65,    71,    93,   144,   124,   125,   126,   127,   128,   129,
      95,   130,   131,   132,   133,   134,   135,    -6,     1,   112,
     149,    96,    97,    98,    -6,    -6,    -6,   113,    80,   138,
     145,   162,    -6,   124,   125,   126,   127,   128,   129,   171,
     130,   131,   132,   133,   134,   135,   175,   136,   124,   125,
     126,   127,   128,   129,   176,   130,   131,   132,   133,   134,
     135,   124,   125,   126,   127,   128,   177,   178,   130,   131,
     132,   133,   134,   135,   124,   125,   126,   127,   188,   190,
      16,   130,   131,   132,   133,   134,   135,   126,   127,    94,
      72,    67,   130,   131,   132,   133,   134,   135,   185,     0,
     186
};

static const yytype_int16 yycheck[] =
{
      33,    84,    35,    36,    98,    27,    98,    29,    30,     1,
      67,    12,   172,    96,    97,    16,    17,    34,     2,    31,
     103,   104,   182,   106,   143,   144,    10,   110,   111,    86,
      32,     7,     8,    35,    59,    60,    61,    39,     3,    31,
      65,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,     7,     8,     9,    73,     1,   177,     3,
      35,     1,   145,     3,    39,     3,    10,     4,    12,    13,
      14,   190,    32,     0,    75,    26,    27,    28,    29,    32,
       7,     8,     9,    32,   178,    32,   178,    31,    15,    34,
     173,   113,   175,    37,    38,     1,    32,     3,    31,    35,
       3,    34,    36,     1,    10,     3,    12,    13,    14,   142,
      33,     1,    10,     3,    12,    13,    14,    33,    32,     3,
      10,    35,    12,    13,    14,    31,     3,     4,     5,     6,
      35,    37,    38,    31,     3,     4,     5,     6,    33,    37,
      38,    31,     7,     8,     9,     7,     8,    37,    28,    29,
      27,    33,    34,    30,    31,    32,    37,    33,    27,    33,
      34,    30,    37,    32,    17,    18,    19,    20,    21,    22,
      34,    24,    25,    26,    27,    28,    29,    17,    18,    19,
      20,    21,    22,    36,    24,    25,    26,    27,    28,    29,
      17,    18,    19,    20,    21,    22,    36,    24,    25,    26,
      27,    28,    29,    51,    52,    53,    33,    17,    18,    19,
      20,    21,    22,    35,    24,    25,    26,    27,    28,    29,
      34,    36,    31,    33,    17,    18,    19,    20,    21,    22,
      31,    24,    25,    26,    27,    28,    29,     0,     1,    31,
      33,    32,    32,    32,     7,     8,     9,    32,     3,    33,
      31,    31,    15,    17,    18,    19,    20,    21,    22,    33,
      24,    25,    26,    27,    28,    29,    39,    31,    17,    18,
      19,    20,    21,    22,    33,    24,    25,    26,    27,    28,
      29,    17,    18,    19,    20,    21,    11,    31,    24,    25,
      26,    27,    28,    29,    17,    18,    19,    20,    31,    33,
      10,    24,    25,    26,    27,    28,    29,    19,    20,    78,
      63,    58,    24,    25,    26,    27,    28,    29,   178,    -1,
     179
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    41,    31,     0,     7,     8,     9,    15,    42,
      45,    46,    51,    58,     1,    31,    46,    51,     3,    43,
       3,    43,    50,    43,    43,    32,    35,    32,    49,    32,
      32,    57,     4,    57,    34,    57,    57,    52,    53,    36,
      53,     3,    50,    53,    53,     7,     8,     9,    54,    55,
      33,    33,    33,    33,     3,    56,    37,    48,    37,    48,
      48,    48,    35,    34,    59,    34,    47,    59,    47,    47,
      47,    36,    55,    51,    62,    47,    62,     1,    50,     1,
       3,    10,    12,    13,    14,    31,    37,    38,    44,    60,
      64,    43,    38,    31,    49,    31,    32,    32,    32,     3,
       4,     5,     6,    27,    30,    31,    32,    66,    62,    32,
      35,    39,    31,    32,    31,    66,    66,    44,    64,    65,
      67,    66,    66,    66,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    27,    28,    29,    31,    38,    33,    61,
      66,    66,    57,    33,    33,    31,    32,    35,    68,    33,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    31,    66,    71,    36,    53,    60,    60,    63,
      66,    33,    69,    70,    72,    39,    33,    11,    31,    71,
      66,    33,    34,    66,    60,    65,    72,    36,    31,    71,
      33,    33,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    41,    41,    41,    42,    42,    42,
      42,    42,    43,    44,    45,    46,    47,    48,    48,    49,
      49,    50,    50,    51,    51,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    58,    58,    59,    59,    59,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    60,
      60,    60,    60,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    66,    66,    66,    66,
      66,    68,    69,    68,    70,    68,    68,    71,    72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     3,     2,     0,     3,     9,     8,
       9,     8,     1,     1,     1,     1,     0,     8,     0,     3,
       0,     1,     4,     1,     1,     0,     2,     3,     1,     1,
       2,     4,     3,     0,     0,    10,    10,     5,     4,     0,
       5,     7,     5,     9,     3,     2,     2,     4,     0,     7,
       3,     1,     2,     2,     0,     1,     0,     3,     6,     1,
       0,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     3,     3,     1,     1,
       1,     2,     0,     5,     0,     4,     0,     1,     3,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4:
#line 116 "parser.yacc"
    { yyerrok; }
#line 1487 "y.tab.c"
    break;

  case 5:
#line 117 "parser.yacc"
    { yyerrok; }
#line 1493 "y.tab.c"
    break;

  case 7:
#line 123 "parser.yacc"
    {
			  printf(".data\n\n");
			  SyntaxTree *declarations = createTree(DECLARATION, NULL, (yyvsp[-1].tree), (yyvsp[0].tree));
			  declareGlobalVariables(declarations);
			  printf("\n");
			  destroyTree(declarations);
			}
#line 1505 "y.tab.c"
    break;

  case 8:
#line 131 "parser.yacc"
    { _currFType = F_UNKNOWN; }
#line 1511 "y.tab.c"
    break;

  case 9:
#line 132 "parser.yacc"
    { _currFType = F_UNKNOWN; }
#line 1517 "y.tab.c"
    break;

  case 10:
#line 134 "parser.yacc"
    { _currFType = F_UNKNOWN; }
#line 1523 "y.tab.c"
    break;

  case 11:
#line 135 "parser.yacc"
    { _currFType = F_UNKNOWN; }
#line 1529 "y.tab.c"
    break;

  case 12:
#line 139 "parser.yacc"
    {
			  _currFID = (yyvsp[0].string);
			}
#line 1537 "y.tab.c"
    break;

  case 13:
#line 144 "parser.yacc"
    {
			  _currID = (yyvsp[0].string);
			  (yyval.string) = (yyvsp[0].string);
			}
#line 1546 "y.tab.c"
    break;

  case 14:
#line 150 "parser.yacc"
    {
			  _currFType = EXTERN_TYPE;
			}
#line 1554 "y.tab.c"
    break;

  case 15:
#line 155 "parser.yacc"
    {
			  _currType = VOID_TYPE;
			}
#line 1562 "y.tab.c"
    break;

  case 16:
#line 159 "parser.yacc"
    {
			  Symbol *prevDcl = recallGlobal(_currFID);
	
			  if (prevDcl->functionType == PROTOTYPE || prevDcl->functionType == EXTERN_TYPE) {
				  sprintf(_errorMessage, "prototype %s previously declared",
					  _currFID);
			      typeError(_errorMessage);
			  } else {
				  if (_currFType == EXTERN_TYPE)
					  prevDcl->functionType = EXTERN_TYPE;
				  else
				      prevDcl->functionType = PROTOTYPE;
			  }
			
			  popSymbolTable();
			}
#line 1583 "y.tab.c"
    break;

  case 19:
#line 181 "parser.yacc"
    { (yyvsp[0].tree)->left = (yyvsp[-2].tree); (yyval.tree) = (yyvsp[0].tree); }
#line 1589 "y.tab.c"
    break;

  case 20:
#line 182 "parser.yacc"
    { (yyval.tree) = NULL; }
#line 1595 "y.tab.c"
    break;

  case 21:
#line 186 "parser.yacc"
    {
			  _currID = (yyvsp[0].string);
			
			  if (recallLocal(_currID)) {
				  sprintf(_errorMessage, "%s previously declared in this function",
					  _currID);
			      typeError(_errorMessage);
				  (yyval.tree) = NULL;
			  } else {
			  	  Symbol *currSymbol = insert(_currID, _currType);
				  currSymbol->functionType = NON_FUNCTION;
				  (yyval.tree) = createTree(DECLARATION, currSymbol, NULL, NULL);
			  }
			}
#line 1614 "y.tab.c"
    break;

  case 22:
#line 201 "parser.yacc"
    {
			  _currID = (yyvsp[-3].string);
			
			  if (_currType == CHAR_TYPE)
				  _currType = CHAR_ARRAY;
			  else
			      _currType = INT_ARRAY;
			
			  if (recallLocal(_currID)) {
				  sprintf(_errorMessage, "%s previously declared in this function",
					  _currID);
			      typeError(_errorMessage);
				  (yyval.tree) = NULL;
			  } else {
			  	  Symbol *currSymbol = insert(_currID, _currType);
			      currSymbol->functionType = NON_FUNCTION;
				  currSymbol->value.intVal = (yyvsp[-1].integer);
				  (yyval.tree) = createTree(DECLARATION, currSymbol, NULL, NULL);
			  }
			
			  if (_currType == CHAR_ARRAY)
				  _currType = CHAR_TYPE;
			  else
			      _currType = INT_TYPE;
			}
#line 1644 "y.tab.c"
    break;

  case 23:
#line 229 "parser.yacc"
    {
			  _currType = CHAR_TYPE;
			}
#line 1652 "y.tab.c"
    break;

  case 24:
#line 233 "parser.yacc"
    {
			  _currType = INT_TYPE;
			}
#line 1660 "y.tab.c"
    break;

  case 25:
#line 238 "parser.yacc"
    { 
			  Symbol *currSymbol = recallGlobal(_currFID);
			  
			  if (currSymbol)
				  _currParam = currSymbol->parameterListHead;
				
			}
#line 1672 "y.tab.c"
    break;

  case 26:
#line 247 "parser.yacc"
    {
			  Symbol *currentFunction = recallGlobal(_currFID);
			
		      if (_currParam) {
		 		  if (_currParam->type != VOID_TYPE)
				  	  typeError("Type mismatch: non-VOID parameter(s) expected");
			  } else {
				  addParameter(NULL, VOID_TYPE, currentFunction);
			  }

			  _currParam = NULL;
			  
			  (yyval.tree) = NULL;
			}
#line 1691 "y.tab.c"
    break;

  case 27:
#line 262 "parser.yacc"
    {
			  if (_currParam)
				  typeError("Type mismatch: missing previously declared types");
			  
			  _currParam = NULL;
			
			
			  SyntaxTree *tree = (yyvsp[0].tree);
			
			  if (tree) {
				  while (tree->left)
					  tree = tree->left;
			  
			  	  tree->left = (yyvsp[-1].tree);
			      (yyval.tree) = (yyvsp[0].tree);
			  } else {
				  (yyval.tree) = (yyvsp[-1].tree);
			  }
			  
			}
#line 1716 "y.tab.c"
    break;

  case 28:
#line 284 "parser.yacc"
    {
				_currPType = CHAR_TYPE;
			}
#line 1724 "y.tab.c"
    break;

  case 29:
#line 288 "parser.yacc"
    {
				_currPType = INT_TYPE;
			}
#line 1732 "y.tab.c"
    break;

  case 30:
#line 294 "parser.yacc"
    {
			  _currID = (yyvsp[0].string);
			
			  Symbol *currentFunction = recallGlobal(_currFID);
			
			    if (recallLocal(_currID)) {
				  sprintf(_errorMessage, "%s previously declared in this function",
					  _currID);
			      typeError(_errorMessage);
				  (yyval.tree) = NULL;
			    } else {
			  	  	if (_currParam) {
					  	if (_currParam->type != _currPType) {
							sprintf(_errorMessage, "%s does not match previous declaration",
								typeAsString(_currPType));
							typeError(_errorMessage);
							(yyval.tree) = NULL;
						} else {
							Symbol *currSymbol = insert(_currID, _currPType);
						    currSymbol->functionType = NON_FUNCTION;
							(yyval.tree) = createTree(FORMAL, currSymbol, NULL, NULL);
						}
			  	 	} else {
				  		Symbol *currSymbol = addParameter(_currID, _currPType, currentFunction);
					    currSymbol->functionType = NON_FUNCTION;
						(yyval.tree) = createTree(FORMAL, currSymbol, NULL, NULL);
			  		}
				}
				
			  if (_currParam)
			  	  _currParam = _currParam->next;
			}
#line 1769 "y.tab.c"
    break;

  case 31:
#line 327 "parser.yacc"
    {
			  _currID = (yyvsp[-2].string);
			  Symbol *currentFunction = recallGlobal(_currFID);
			
			  if (_currPType == CHAR_TYPE)
				  _currPType = CHAR_ARRAY;
			  else
			      _currPType = INT_ARRAY;
			
			  if (recallLocal(_currID)) {
				  sprintf(_errorMessage, "%s previously declared in this function",
					  _currID);
			      typeError(_errorMessage);
				  (yyval.tree) = NULL;
			  } else {
			  	  if (_currParam) {
					  if (_currParam->type != _currPType) {
						  if (_currPType == CHAR_ARRAY)
							  typeError("CHAR_ARRAY does not match previous declaration");
						  else
							  typeError("INT_ARRAY does not match previous declaration");
						  
						  (yyval.tree) = NULL;
					  } else {
						  Symbol *currSymbol = insert(_currID, _currPType);
						  currSymbol->functionType = NON_FUNCTION;
						  (yyval.tree) = createTree(FORMAL, currSymbol, NULL, NULL);
					  }
			  	  } else {
				  	  Symbol *currSymbol = addParameter(_currID, _currPType, currentFunction);
					  currSymbol->functionType = NON_FUNCTION;
					  (yyval.tree) = createTree(FORMAL, currSymbol, NULL, NULL);
			  	  }
			  }
			
			 if (_currParam)
			   _currParam = _currParam->next;
			}
#line 1812 "y.tab.c"
    break;

  case 32:
#line 367 "parser.yacc"
    { (yyvsp[0].tree)->left = (yyvsp[-2].tree); (yyval.tree) = (yyvsp[0].tree); }
#line 1818 "y.tab.c"
    break;

  case 33:
#line 368 "parser.yacc"
    { (yyval.tree) = NULL; }
#line 1824 "y.tab.c"
    break;

  case 34:
#line 371 "parser.yacc"
    {
			  Symbol *prevDcl = recallGlobal(_currFID);

			  if (prevDcl) {
			      if (prevDcl->functionType == DEFINITION) {
				      sprintf(_errorMessage, "function %s previously defined",
						  prevDcl->identifier);
			          typeError(_errorMessage);
			      } else if (prevDcl->functionType == EXTERN_TYPE) {
					  sprintf(_errorMessage, "function %s previously declared as extern",
						  prevDcl->identifier);
			          typeError(_errorMessage);
				  } else if (prevDcl->functionType == NON_FUNCTION) {
					  sprintf(_errorMessage, "function %s previously declared",
						  prevDcl->identifier);
					  typeError(_errorMessage);
				  } else if (prevDcl->type != _currType) {
					  sprintf(_errorMessage, "return type of function %s doesn't match previous declaration",
						  prevDcl->identifier);
				      typeError(_errorMessage);
				  }
			  } else {
				      Symbol *currFunction = insert(_currFID, _currType);
					  currFunction->functionType = DEFINITION;
			  }
			
			  pushSymbolTable();
			}
#line 1857 "y.tab.c"
    break;

  case 35:
#line 403 "parser.yacc"
    { 
			  if (!_returnedValue) {
				  sprintf(_errorMessage, "function %s must have at least one return statement",
					  _currFID);
				  typeError(_errorMessage);
			  } else {
				  _returnedValue = FALSE;
			  }
			  
			  Symbol *currFunction = recallGlobal(_currFID);

			  SyntaxTree *declarations = (yyvsp[-2].tree);

			  if (declarations) {
				  while (declarations->left)
					  declarations = declarations->left;

				  declarations->left = (yyvsp[-5].tree);
			  } else {
				  (yyvsp[-2].tree) = (yyvsp[-5].tree);
			  }

			  SyntaxTree *function = createTree(FUNCTION_ROOT, currFunction, (yyvsp[-2].tree), (yyvsp[-1].tree));

			  printf("\n.text\n\n");

			  #if defined(DEBUG_SYNTAX) || defined(DEBUG_ALL)
			  	  printf("\nSYNTAX TREE:\n\n");
			  	  printSyntaxTree(function, 0);
			  #endif

			  #if defined(DEBUG_SYMBOLS) || defined(DEBUG_ALL)
			  	  printSymbolTable();
			  #endif

			  if (strcmp("main", _currFID) == 0)
				  printf("main:\n");
			  else
				  printf("_%s:\n", _currFID);

			  _stackSize = 8;
			  _stackSize += allocateStackSpace(function, 0);

			  printf("\tsubu\t$sp, $sp, %d\n", _stackSize);
			  printf("\tsw\t\t$ra, %d($sp)\n", _stackSize - 4);
			  printf("\tsw\t\t$fp, %d($sp)\n", _stackSize - 8);
			  printf("\taddu\t$fp, $sp, %d\n", _stackSize);

			  SyntaxTree *parameter = (yyvsp[-5].tree);
			  SyntaxTree *parameterName = (yyvsp[-5].tree);
			  int i, j, k, l;
			  i = j = k = l = 0;
			  for(i = 12, j = 0; parameter; i += 4, j += 4) {

					// this 'if' is just to get the parameter names in order
					l = 0;
					parameterName = (yyvsp[-5].tree);
				    if (k == 0 && parameterName == parameter) {
						while (parameterName->left) {
							parameterName = parameterName->left;
							k++;
						}
						k--;
					} else {
						while (l < k) {
							parameterName = parameterName->left;
							l++;
						}
						k--;
					}

					if (parameter->symbol->type == CHAR_TYPE) {
						printf("\tlb\t\t$t0, %d($fp)\t\t# storing parameter %s\n", j, parameterName->symbol->identifier);
						printf("\tsb\t\t$t0, %d($sp)\n", _stackSize - i);
					} else {
						printf("\tlw\t\t$t0, %d($fp)\t\t# storing parameter %s\n", j, parameterName->symbol->identifier);
						printf("\tsw\t\t$t0, %d($sp)\n", _stackSize - i);
					}
					
					if (parameter->symbol->type == CHAR_ARRAY || parameter->symbol->type == INT_ARRAY)
						parameter->symbol->reference = TRUE;

					parameter = parameter->left;
			  }

			  if (i <= _stackSize) {
			  	  printf("\t# initializing local variables\n");

				  for( ; i <= _stackSize; i += 4)
					  printf("\tsw\t\t$0, %d($sp)\n", _stackSize - i);
			  }

			  Code *code = constructCode(function);

			  writeCode(code);

			  #if defined(DEBUG_CODE) || defined(DEBUG_ALL)
			      printf("\nTHREE ADDRESS CODE:\n\n");
			      printCode(code);
			  #endif

			  printf("\n__%sReturn:\n", _currFID);
			  printf("\tlw\t\t$fp, %d($sp)\n", _stackSize - 8);
			  printf("\tlw\t\t$ra, %d($sp)\n", _stackSize - 4);
			  printf("\taddu\t$sp, $sp, %d\n", _stackSize);
			  printf("\tjr\t\t$ra\n");

			  destroyTree(function);
			  destroyCode(code);
			  popSymbolTable();
			}
#line 1973 "y.tab.c"
    break;

  case 36:
#line 516 "parser.yacc"
    { 
			  Symbol *currFunction = recallGlobal(_currFID);
							
			  SyntaxTree *declarations = (yyvsp[-2].tree);
			
			  if (declarations) {
				  while (declarations->left)
					  declarations = declarations->left;
					
				  declarations->left = (yyvsp[-5].tree);
			  } else {
				  (yyvsp[-2].tree) = (yyvsp[-5].tree);
			  }
			
			  SyntaxTree *function = createTree(FUNCTION_ROOT, currFunction, (yyvsp[-2].tree), (yyvsp[-1].tree));
			
			  printf("\n.text\n\n");
			
			  #if defined(DEBUG_SYNTAX) || defined(DEBUG_ALL)
			  	  printf("\nSYNTAX TREE:\n\n");
			  	  printSyntaxTree(function, 0);
			  #endif

			  #if defined(DEBUG_SYMBOLS) || defined(DEBUG_ALL)
			  	  printSymbolTable();
			  #endif
			
			  if (strcmp("main", _currFID) == 0)
				  printf("main:\n");
			  else
				  printf("_%s:\n", _currFID);
			
			  _stackSize = 8;
			  _stackSize += allocateStackSpace(function, 0);

			  printf("\tsubu\t$sp, $sp, %d\n", _stackSize);
			  printf("\tsw\t\t$ra, %d($sp)\n", _stackSize - 4);
			  printf("\tsw\t\t$fp, %d($sp)\n", _stackSize - 8);
			  printf("\taddu\t$fp, $sp, %d\n", _stackSize);
			  
			  SyntaxTree *parameter = (yyvsp[-5].tree);
			  SyntaxTree *parameterName = (yyvsp[-5].tree);
			  int i, j, k, l;
			  i = j = k = l = 0;
			  for(i = 12, j = 0; parameter; i += 4, j += 4) {
					
					// this 'if' is just to get the parameter names in order
					l = 0;
					parameterName = (yyvsp[-5].tree);
				    if (k == 0 && parameterName == parameter) {
						while (parameterName->left) {
							parameterName = parameterName->left;
							k++;
						}
						k--;
					} else {
						while (l < k) {
							parameterName = parameterName->left;
							l++;
						}
						k--;
					}
				
					if (parameter->symbol->type == CHAR_TYPE) {
						printf("\tlb\t\t$t0, %d($fp)\t\t# storing parameter %s\n", j, parameterName->symbol->identifier);
						printf("\tsb\t\t$t0, %d($sp)\n", _stackSize - i);
					} else {
						printf("\tlw\t\t$t0, %d($fp)\t\t# storing parameter %s\n", j, parameterName->symbol->identifier);
						printf("\tsw\t\t$t0, %d($sp)\n", _stackSize - i);
					}
					
					if (parameter->symbol->type == CHAR_ARRAY || parameter->symbol->type == INT_ARRAY)
						parameter->symbol->reference = TRUE;
						
					parameter = parameter->left;
			  }
			  
			  if (i <= _stackSize) {
			  	  printf("\t# initializing local variables\n");
			
				  for( ; i <= _stackSize; i += 4)
					  printf("\tsw\t\t$0, %d($sp)\n", _stackSize - i);
			  }

			  Code *code = constructCode(function);
			
			  writeCode(code);
			  
			  #if defined(DEBUG_CODE) || defined(DEBUG_ALL)
			      printf("\nTHREE ADDRESS CODE:\n\n");
			      printCode(code);
			  #endif
			
			  printf("\n__%sReturn:\n", _currFID);
			  printf("\tlw\t\t$fp, %d($sp)\n", _stackSize - 8);
			  printf("\tlw\t\t$ra, %d($sp)\n", _stackSize - 4);
			  printf("\taddu\t$sp, $sp, %d\n", _stackSize);
			  printf("\tjr\t\t$ra\n");

			  destroyTree(function);
			  destroyCode(code);
			  popSymbolTable();
			}
#line 2081 "y.tab.c"
    break;

  case 37:
#line 622 "parser.yacc"
    {
				SyntaxTree *tree = (yyvsp[-1].tree);
				
				if (tree) {
					
					while (tree->left)
						tree = tree->left;
					
					tree->left = (yyvsp[-2].tree);
					(yyvsp[-2].tree)->left = (yyvsp[-4].tree);
					(yyval.tree) = (yyvsp[-1].tree);
				} else {
					(yyvsp[-2].tree)->left = (yyvsp[-4].tree);
					(yyval.tree) = (yyvsp[-2].tree);
				}
			}
#line 2102 "y.tab.c"
    break;

  case 38:
#line 640 "parser.yacc"
    { yyerrok; (yyval.tree) = NULL; }
#line 2108 "y.tab.c"
    break;

  case 39:
#line 642 "parser.yacc"
    { (yyval.tree) = NULL; }
#line 2114 "y.tab.c"
    break;

  case 40:
#line 646 "parser.yacc"
    {
			  if ((yyvsp[-2].exprReturn).type != BOOLEAN)
				  typeError("conditional in if statement must be a boolean");
			  
			  (yyval.tree) = createTree(IF_TREE, NULL, (yyvsp[-2].exprReturn).tree, (yyvsp[0].tree));
			}
#line 2125 "y.tab.c"
    break;

  case 41:
#line 653 "parser.yacc"
    {
			  if ((yyvsp[-4].exprReturn).type != BOOLEAN)
				  typeError("conditional in if statement must be a boolean");
				
				(yyval.tree) = createTree(IF_TREE, NULL, (yyvsp[-4].exprReturn).tree, (yyvsp[-2].tree));
				(yyval.tree)->opt = (yyvsp[0].tree);
			}
#line 2137 "y.tab.c"
    break;

  case 42:
#line 661 "parser.yacc"
    {
			  if ((yyvsp[-2].exprReturn).type != BOOLEAN)
				  typeError("conditional in while loop must be a boolean");
				
			  (yyval.tree) = createTree(WHILE_TREE, NULL, (yyvsp[-2].exprReturn).tree, (yyvsp[0].tree));
			}
#line 2148 "y.tab.c"
    break;

  case 43:
#line 668 "parser.yacc"
    {
			  if ((yyvsp[-4].exprReturn).type != BOOLEAN)
				  typeError("conditional in for loop must be a boolean");
				
			SyntaxTree *tree = createTree(WHILE_TREE, NULL, (yyvsp[-4].exprReturn).tree, (yyvsp[0].tree));
			tree->opt = (yyvsp[-2].tree);
			(yyval.tree) = createTree(STATEMENT, NULL, tree, (yyvsp[-6].tree));
			}
#line 2161 "y.tab.c"
    break;

  case 44:
#line 677 "parser.yacc"
    {
			  Symbol *currSymbol = recallGlobal(_currFID);
			
			  if (!currSymbol) {
				  typeError("unexpected return statement");
				  (yyval.tree) = NULL;
			  } else {
				  if (currSymbol->type != (yyvsp[-1].exprReturn).type) {
				      if ((currSymbol->type != INT_TYPE && currSymbol->type != CHAR_TYPE)
						  || ((yyvsp[-1].exprReturn).type != INT_TYPE && (yyvsp[-1].exprReturn).type != CHAR_TYPE)) {
						  	sprintf(_errorMessage, "return type for function %s does not match declared type",
								_currFID);
						  typeError(_errorMessage);
					  } else {
						_returnedValue = TRUE;
					  }
			  	  } else {
					  _returnedValue = TRUE;
				  }
				
				  (yyval.tree) = createTree(RETURN_TREE, currSymbol, (yyvsp[-1].exprReturn).tree, NULL);
			  }
			}
#line 2189 "y.tab.c"
    break;

  case 45:
#line 701 "parser.yacc"
    {
			  Symbol *currSymbol = recallGlobal(_currFID);
			
			  if (!currSymbol) {
				  typeError("unexpected return statement");
				  (yyval.tree) = NULL;
			  } else {
				  if (currSymbol->type != VOID_TYPE) {
					  sprintf(_errorMessage, "return type for function %s does not match declared type",
						  _currFID);
					  typeError(_errorMessage);
				  }
				
				  (yyval.tree) = createTree(RETURN_TREE, currSymbol, NULL, NULL);
			  }
			
			  
			}
#line 2212 "y.tab.c"
    break;

  case 46:
#line 719 "parser.yacc"
    { (yyval.tree) = (yyvsp[-1].tree); }
#line 2218 "y.tab.c"
    break;

  case 47:
#line 721 "parser.yacc"
    {
			  Symbol *currSymbol = recallGlobal(_currID);
			  
			  if (currSymbol) {
			      if (!currSymbol->parameterListHead) {
					  sprintf(_errorMessage, "%s is not a function", _currID);
				      typeError(_errorMessage);
				  }
			
			      else if (currSymbol->parameterListHead->type != VOID_TYPE) {
			          sprintf(_errorMessage, "function %s takes non-VOID arguments",
						  _currID);
			   	      typeError(_errorMessage);
				  }
				  
				  if (currSymbol->type != VOID_TYPE) {
					  sprintf(_errorMessage, "function %s must return VOID to be used as a statement",
						  _currID);
				      typeError(_errorMessage);
				  }
				  
				  (yyval.tree) = createTree(FUNCTION_CALL, currSymbol, NULL, NULL);
			  } else {
				  sprintf(_errorMessage, "%s undefined", _currID);
			      typeError(_errorMessage);
				  (yyval.tree) = NULL;
			  }
			
			}
#line 2252 "y.tab.c"
    break;

  case 48:
#line 751 "parser.yacc"
    {
			  Symbol *currSymbol = recallGlobal(_currID);

			  if (!currSymbol) {
				  	sprintf(_errorMessage, "%s undefined", _currID);
			        typeError(_errorMessage);
			  } else {
				  if (currSymbol->functionType == NON_FUNCTION) {
					  sprintf(_errorMessage, "%s is not a function", _currID);
			          typeError(_errorMessage);
				  } else {
					  if (currSymbol->type != VOID_TYPE) {
						  sprintf(_errorMessage, "function %s must return VOID to be used as a statement",
							  _currID);
					      typeError(_errorMessage);
					  }
					  pushFunctionCall(currSymbol);
				  }
			  }
			}
#line 2277 "y.tab.c"
    break;

  case 49:
#line 772 "parser.yacc"
    {
			  if (_callStack) {
			  	  if (_callStack->currParam) {
				  	  sprintf(_errorMessage, "more arguments expected for function %s",
					  	  _callStack->identifier);
				  	  typeError(_errorMessage);
			  	  }
				
				  SyntaxTree *tree = (yyvsp[-2].tree);

				  if (tree) {
					  while (tree->left)
						  tree = tree->left;

				  	  tree->left = (yyvsp[-3].tree);
				      (yyval.tree) = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), (yyvsp[-2].tree), NULL);
				  } else {
					  (yyval.tree) = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), (yyvsp[-3].tree), NULL);
				  }

		      	  popFunctionCall();
		      }
			}
#line 2305 "y.tab.c"
    break;

  case 50:
#line 795 "parser.yacc"
    { (yyval.tree) = (yyvsp[-1].tree); }
#line 2311 "y.tab.c"
    break;

  case 51:
#line 796 "parser.yacc"
    { (yyval.tree) = NULL; }
#line 2317 "y.tab.c"
    break;

  case 52:
#line 799 "parser.yacc"
    { yyerrok; }
#line 2323 "y.tab.c"
    break;

  case 53:
#line 803 "parser.yacc"
    {
			  if ((yyvsp[0].tree)) {
			  	  (yyval.tree) = createTree(STATEMENT, NULL, (yyvsp[0].tree), (yyvsp[-1].tree));
			  }
			}
#line 2333 "y.tab.c"
    break;

  case 54:
#line 808 "parser.yacc"
    { (yyval.tree) = NULL; }
#line 2339 "y.tab.c"
    break;

  case 55:
#line 811 "parser.yacc"
    { (yyval.exprReturn).type = (yyvsp[0].exprReturn).type; (yyval.exprReturn).tree = (yyvsp[0].exprReturn).tree; }
#line 2345 "y.tab.c"
    break;

  case 56:
#line 812 "parser.yacc"
    { (yyval.exprReturn).type = BOOLEAN; (yyval.exprReturn).tree = NULL; }
#line 2351 "y.tab.c"
    break;

  case 57:
#line 816 "parser.yacc"
    {
			  _currID = (yyvsp[-2].string);
			  Symbol *currSymbol = recall(_currID);

			  if (!currSymbol) {
				  sprintf(_errorMessage, "%s undefined", _currID);
				  typeError(_errorMessage);
		  	  } else {
				  if (currSymbol->type != INT_TYPE && currSymbol->type != CHAR_TYPE
						|| currSymbol->functionType != NON_FUNCTION) {
					sprintf(_errorMessage, "%s has incompatible type for assignment",
						_currID);
					typeError(_errorMessage);
				}
				  if (currSymbol->type != (yyvsp[0].exprReturn).type) {
					  if ((currSymbol->type != INT_TYPE && currSymbol->type != CHAR_TYPE)
						  && ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE)) {
						sprintf(_errorMessage, "incompatible types for assignment of %s",
							_currID);
						typeError(_errorMessage);
					  }
				  }
			  }
			
			  SyntaxTree *leftHandSide = createTree(SYMBOL, currSymbol, NULL, NULL);
			  (yyval.tree) = createTree(ASSIGNMENT, NULL, leftHandSide, (yyvsp[0].exprReturn).tree);
			}
#line 2383 "y.tab.c"
    break;

  case 58:
#line 844 "parser.yacc"
    {
			  _currID = (yyvsp[-5].string);
			  Symbol *currSymbol = recall(_currID);
			
			  if (!currSymbol) {
				  sprintf(_errorMessage, "%s undefined", _currID);
				  typeError(_errorMessage);
		  	  } else {
				  if (currSymbol->type != INT_ARRAY && currSymbol->type != CHAR_ARRAY) {
					  sprintf(_errorMessage, "%s must be an ARRAY to be indexed", _currID);
					  typeError(_errorMessage);
				  }
				  
				  if ((yyvsp[-3].exprReturn).type != INT_TYPE && (yyvsp[-3].exprReturn).type != CHAR_TYPE) {
					  sprintf(_errorMessage, "ARRAY index for %s must be INT or CHAR",
						  _currID);
					  typeError(_errorMessage);
				  }
				  
				  if ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE)  {
					    sprintf(_errorMessage, "incompatible types for assignment of %s",
							_currID);
						typeError(_errorMessage);
				  }
				
				SyntaxTree *symbolTree = createTree(SYMBOL, currSymbol, NULL, NULL);
				generateNewTempID();
				Symbol *newSymbol = insert(_tempID, currSymbol->type);
				SyntaxTree *array = createTree(ARRAY, newSymbol, symbolTree, (yyvsp[-3].exprReturn).tree);
				(yyval.tree) = createTree(ASSIGNMENT, NULL, array, (yyvsp[0].exprReturn).tree);
			  }
			}
#line 2420 "y.tab.c"
    break;

  case 59:
#line 878 "parser.yacc"
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2426 "y.tab.c"
    break;

  case 60:
#line 879 "parser.yacc"
    { (yyval.tree) = NULL; }
#line 2432 "y.tab.c"
    break;

  case 61:
#line 883 "parser.yacc"
    {
			  if ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE)
				  typeError("incompatible expression for operator '-'");
			
			  (yyval.exprReturn).type = (yyvsp[0].exprReturn).type;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, INT_TYPE);
			  (yyval.exprReturn).tree = createTree(NEG, newSymbol, (yyvsp[0].exprReturn).tree, NULL);
			}
#line 2447 "y.tab.c"
    break;

  case 62:
#line 894 "parser.yacc"
    {
			  if ((yyvsp[0].exprReturn).type != BOOLEAN)
				  typeError("incompatible expression for operator '!'");
			
			  (yyval.exprReturn).type = (yyvsp[0].exprReturn).type;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(NOT, newSymbol, (yyvsp[0].exprReturn).tree, NULL);
			}
#line 2462 "y.tab.c"
    break;

  case 63:
#line 905 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE)
				  || ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '+'");
			
			  (yyval.exprReturn).type = (yyvsp[-2].exprReturn).type;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, INT_TYPE);
			  (yyval.exprReturn).tree = createTree(ADD, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2478 "y.tab.c"
    break;

  case 64:
#line 917 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE)
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '-'");
			
			  (yyval.exprReturn).type = (yyvsp[-2].exprReturn).type;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, INT_TYPE);
			  (yyval.exprReturn).tree = createTree(SUB, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2494 "y.tab.c"
    break;

  case 65:
#line 929 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '*'");
			
			  (yyval.exprReturn).type = (yyvsp[-2].exprReturn).type;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, INT_TYPE);
			  (yyval.exprReturn).tree = createTree(MULT, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2510 "y.tab.c"
    break;

  case 66:
#line 941 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '/'");
			
			  (yyval.exprReturn).type = (yyvsp[-2].exprReturn).type;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, INT_TYPE);
			  (yyval.exprReturn).tree = createTree(DIV, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2526 "y.tab.c"
    break;

  case 67:
#line 953 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '=='");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(EQUAL, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2542 "y.tab.c"
    break;

  case 68:
#line 965 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '!='");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(NOT_EQUAL, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2558 "y.tab.c"
    break;

  case 69:
#line 977 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '<='");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(LESS_EQUAL, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2574 "y.tab.c"
    break;

  case 70:
#line 989 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '<'");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(LESS_THAN, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2590 "y.tab.c"
    break;

  case 71:
#line 1001 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '>='");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(GREATER_EQUAL, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2606 "y.tab.c"
    break;

  case 72:
#line 1013 "parser.yacc"
    {
			  if (((yyvsp[-2].exprReturn).type != INT_TYPE && (yyvsp[-2].exprReturn).type != CHAR_TYPE) 
					|| ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE))
				  typeError("incompatible expression for operator '>'");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(GREATER_THAN, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2622 "y.tab.c"
    break;

  case 73:
#line 1025 "parser.yacc"
    {
			  if ((yyvsp[-2].exprReturn).type != BOOLEAN || (yyvsp[0].exprReturn).type != BOOLEAN)
				  typeError("incompatible expression for operator '&&'");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(AND, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2637 "y.tab.c"
    break;

  case 74:
#line 1036 "parser.yacc"
    {
			  if ((yyvsp[-2].exprReturn).type != BOOLEAN || (yyvsp[0].exprReturn).type != BOOLEAN)
				  typeError("incompatible expression for operator '||'");
			
			  (yyval.exprReturn).type = BOOLEAN;
			
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, BOOLEAN);
			  (yyval.exprReturn).tree = createTree(OR, newSymbol, (yyvsp[0].exprReturn).tree, (yyvsp[-2].exprReturn).tree);
			}
#line 2652 "y.tab.c"
    break;

  case 75:
#line 1047 "parser.yacc"
    {
			  _currID = (yyvsp[0].string);
			  Symbol *currSymbol = recall(_currID);
			  
			  if (!currSymbol) {
				  sprintf(_errorMessage, "%s undefined", _currID);
				  typeError(_errorMessage);
			  }
				
			}
#line 2667 "y.tab.c"
    break;

  case 76:
#line 1058 "parser.yacc"
    {
				(yyval.exprReturn).type = (yyvsp[0].exprReturn).type;
				(yyval.exprReturn).tree = (yyvsp[0].exprReturn).tree;
			}
#line 2676 "y.tab.c"
    break;

  case 77:
#line 1062 "parser.yacc"
    { (yyval.exprReturn).type = (yyvsp[-1].exprReturn).type; (yyval.exprReturn).tree = (yyvsp[-1].exprReturn).tree; }
#line 2682 "y.tab.c"
    break;

  case 78:
#line 1064 "parser.yacc"
    {
			  (yyval.exprReturn).type = INT_TYPE;
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, INT_TYPE);
			  newSymbol->value.intVal = (yyvsp[0].integer);
			  newSymbol->functionType = NON_FUNCTION;
			  (yyval.exprReturn).tree = createTree(LITERAL, newSymbol, NULL, NULL);
			}
#line 2695 "y.tab.c"
    break;

  case 79:
#line 1073 "parser.yacc"
    {
			  (yyval.exprReturn).type = CHAR_TYPE;
			  generateNewTempID();
			  Symbol *newSymbol = insert(_tempID, CHAR_TYPE);
			  newSymbol->value.charVal = (yyvsp[0].character);
			  newSymbol->functionType = NON_FUNCTION;
			  (yyval.exprReturn).tree = createTree(LITERAL, newSymbol, NULL, NULL);
			}
#line 2708 "y.tab.c"
    break;

  case 80:
#line 1082 "parser.yacc"
    {
			  (yyval.exprReturn).type = CHAR_ARRAY;
			  
			  Symbol *currSymbol = recallStringLiteral((yyvsp[0].string));
			  
			  if (!currSymbol) {
			      generateNewTempID();
				  currSymbol = insertGlobal(_tempID, CHAR_ARRAY);
				  currSymbol->value.strVal = (yyvsp[0].string);
				  currSymbol->functionType = NON_FUNCTION;

				  if (!(currSymbol->location = malloc(strlen(currSymbol->identifier) + 2)))
					  ERROR(NULL, __LINE__, TRUE);				//out of memory


				  sprintf(currSymbol->location, "_%s", currSymbol->identifier);
				  insertStringLiteral(currSymbol);
			  }
			  
			  (yyval.exprReturn).tree = createTree(LITERAL, currSymbol, NULL, NULL);
			}
#line 2734 "y.tab.c"
    break;

  case 81:
#line 1106 "parser.yacc"
    {
			  Symbol *currSymbol = recallGlobal(_currID);
			  
			  if (currSymbol) {
			      if (!currSymbol->parameterListHead) {
					  sprintf(_errorMessage, "%s is not a function", _currID);
				      typeError(_errorMessage);
			      } else if (currSymbol->type == VOID_TYPE) {
					  sprintf(_errorMessage, "void function %s in expression", _currID);
					  typeError(_errorMessage);
				  }	else if (currSymbol->parameterListHead->type != VOID_TYPE) {
					  sprintf(_errorMessage, "function %s takes non-VOID arguments",
						  _currID);
			          typeError(_errorMessage);
			      }
				  (yyval.exprReturn).type = currSymbol->type;
				  generateNewTempID();
				  Symbol *newSymbol = insert(_tempID, currSymbol->type);
				  SyntaxTree *tree = createTree(FUNCTION_CALL, currSymbol, NULL, NULL);
				  (yyval.exprReturn).tree = createTree(RETRIEVE, newSymbol, tree, NULL);
			  } else {
				  (yyval.exprReturn).type = UNKNOWN;
				  (yyval.exprReturn).tree = NULL;
			  }
			}
#line 2764 "y.tab.c"
    break;

  case 82:
#line 1132 "parser.yacc"
    {
			  Symbol *currSymbol = recallGlobal(_currID);

			  if (currSymbol) {
			      if (currSymbol->functionType == NON_FUNCTION) {
				      sprintf(_errorMessage, "%s is not a function", _currID);
			          typeError(_errorMessage);
				  } else if (currSymbol->type == VOID_TYPE) {
				  	  sprintf(_errorMessage, "void function %s in expression", _currID);
					  typeError(_errorMessage);
				  }
				  pushFunctionCall(currSymbol);
			  }
			}
#line 2783 "y.tab.c"
    break;

  case 83:
#line 1147 "parser.yacc"
    { 
			  if (_callStack) {
			  	  if (_callStack->currParam) {
				  	  sprintf(_errorMessage, "more arguments expected for function %s",
					  	  _callStack->identifier);
				  	  typeError(_errorMessage);
			  	  }
			  	  (yyval.exprReturn).type = (recallGlobal(_callStack->identifier))->type;
				
				  SyntaxTree *tree = (yyvsp[-1].tree);

				  if (tree) {
					  while (tree->left)
						  tree = tree->left;

				  	  tree->left = (yyvsp[-2].tree);
					  
					  generateNewTempID();
					  Symbol *newSymbol = insert(_tempID, (yyval.exprReturn).type);
					  SyntaxTree *tree = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), (yyvsp[-1].tree), NULL);
					  (yyval.exprReturn).tree = createTree(RETRIEVE, newSymbol, tree, NULL);
				  } else {
					  generateNewTempID();
					  Symbol *newSymbol = insert(_tempID, (yyval.exprReturn).type);
					  SyntaxTree *tree = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), (yyvsp[-2].tree), NULL);
					  (yyval.exprReturn).tree = createTree(RETRIEVE, newSymbol, tree, NULL);
				  }
				
			      popFunctionCall();
			  } else {
			      (yyval.exprReturn).type = UNKNOWN;
				  (yyval.exprReturn).tree = NULL;
			  }
			  
			}
#line 2823 "y.tab.c"
    break;

  case 84:
#line 1183 "parser.yacc"
    {
			  Symbol *currSymbol = recall(_currID);

			  if (currSymbol) {
				  if (currSymbol->type != CHAR_ARRAY && currSymbol->type != INT_ARRAY) {
					  sprintf(_errorMessage, "%s must be an ARRAY to be indexed",
						  _currID);
					  typeError(_errorMessage);
				  }
				  
				  pushFunctionCall(currSymbol);
			  }
			}
#line 2841 "y.tab.c"
    break;

  case 85:
#line 1197 "parser.yacc"
    {
			  if ((yyvsp[-1].exprReturn).type != INT_TYPE && (yyvsp[-1].exprReturn).type != CHAR_TYPE) {
				  sprintf(_errorMessage, "array index for %s must be INT or CHAR",
					  _currID);
			  	  typeError(_errorMessage);
			  }
			
			  if (!_callStack) {
				  (yyval.exprReturn).type = UNKNOWN;
				  (yyval.exprReturn).tree = NULL;
			  } else {
				  (yyval.exprReturn).type = (recall(_callStack->identifier))->type;
				
				  generateNewTempID();
				  Symbol *newSymbol = insert(_tempID, (yyval.exprReturn).type);
				  SyntaxTree *tree = createTree(SYMBOL, recall(_callStack->identifier), NULL, NULL);
				  (yyval.exprReturn).tree = createTree(ARRAY, newSymbol, tree, (yyvsp[-1].exprReturn).tree);
				
				  if ((yyval.exprReturn).type == CHAR_ARRAY)
					  (yyval.exprReturn).type = CHAR_TYPE;
				  else
					  (yyval.exprReturn).type = INT_TYPE;
				
				  popFunctionCall();
			  }
			}
#line 2872 "y.tab.c"
    break;

  case 86:
#line 1224 "parser.yacc"
    {
			  Symbol *currSymbol = recall(_currID);
				
			  if (currSymbol) {
				  if (currSymbol->functionType != NON_FUNCTION) {
					  sprintf(_errorMessage, "expected arguments for function %s",
						  _currID);
					  typeError(_errorMessage);
				  }
				  (yyval.exprReturn).type = currSymbol->type;
				  (yyval.exprReturn).tree = createTree(SYMBOL, currSymbol, NULL, NULL);
			  } else {
				  (yyval.exprReturn).type = UNKNOWN;
				  (yyval.exprReturn).tree = NULL;
			  }
			}
#line 2893 "y.tab.c"
    break;

  case 87:
#line 1243 "parser.yacc"
    {
			  if (_callStack) {
		  	  	  if (!_callStack->currParam) {
					  sprintf(_errorMessage, "extra arguments passed to function %s",
						  _callStack->identifier);
				      typeError(_errorMessage);
					  (yyval.tree) = NULL;
				  } else if (_callStack->currParam->type != (yyvsp[0].exprReturn).type) {
					  if ((_callStack->currParam->type != INT_TYPE
					          && _callStack->currParam->type != CHAR_TYPE)
						      || ((yyvsp[0].exprReturn).type != INT_TYPE && (yyvsp[0].exprReturn).type != CHAR_TYPE)) {
			  	          typeError("type mismatch in arguments to function");
						  (yyval.tree) = NULL;
					  } else {
						  (yyval.tree) = createTree(PARAMETER, NULL, NULL, (yyvsp[0].exprReturn).tree);
					  }
				  } else {
					  (yyval.tree) = createTree(PARAMETER, NULL, NULL, (yyvsp[0].exprReturn).tree);
				  }
			  } else {
				  (yyval.tree) = NULL;
			  }
		  	  
		      if (_callStack->currParam)
			      _callStack->currParam = _callStack->currParam->next;
			}
#line 2924 "y.tab.c"
    break;

  case 88:
#line 1271 "parser.yacc"
    { (yyvsp[0].tree)->left = (yyvsp[-2].tree); (yyval.tree) = (yyvsp[0].tree); }
#line 2930 "y.tab.c"
    break;

  case 89:
#line 1272 "parser.yacc"
    { (yyval.tree) = NULL; }
#line 2936 "y.tab.c"
    break;


#line 2940 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1275 "parser.yacc"


/* Function: main
 * Parameters: none
 * Description: Program execution begins here.
 * Returns: 0 for success, 1 if errors were found (syntactic or semantic).
 * Preconditions: none
 */
main() {
	pushSymbolTable();				// initialize global symbol table

	yyparse();
	
	printf("\n.data\n");
	popTempVariables(_tempVariables);
	popStringLiterals(_stringLiterals);
	
	popSymbolTable();				// free global symbol table
	
	printf("\n.text\n\n");
	printf("_print_int:\n");
	printf("\tli\t\t$v0, 1\n");
	printf("\tlw\t\t$a0, 0($sp)\n");
	printf("\tsyscall\n");
	printf("\tjr\t\t$ra\n");
	
	printf("\n_print_string:\n");
	printf("\tli\t\t$v0, 4\n");
	printf("\tlw\t\t$a0, 0($sp)\n");
	printf("\tsyscall\n");
	printf("\tjr\t\t$ra\n");
	
	printf("\n_read_int:\n");
	printf("\tli\t\t$v0, 5\n");
	printf("\tsyscall\n");
	printf("\tjr\t\t$ra\n");
	
	printf("\n_read_string:\n");
	printf("\tli\t\t$v0, 8\n");
	printf("\tsyscall\n");
	printf("\tlw\t\t$t0, 0($sp)\n");
	printf("__read_string_copy:\n");
	printf("\tlb\t\t$t1, 0($a0)\n");
	printf("\tsb\t\t$t1, 0($t0)\n");
	printf("\taddi\t$t0, $t0, 1\n");
	printf("\taddi\t$a0, $a0, 1\n");
	printf("\tbgtz\t$t1, __read_string_copy\n");
	printf("\tjr\t\t$ra\n");
	
	if (_generateCode)
		return 0;					// success
	return 1;						// failure
}

/* Function: insertTempVariable
 * Parameters: Symbol *tempVariable
 * Description: Adds the given temp variable to the list of temp variables.
 * Returns: none
 * Preconditions: none
 */
void insertTempVariable(Symbol *tempVariable) {
	if (!tempVariable)
		return;
	
	TempVariable *newTemp = NULL;
	
	if (!(newTemp = malloc(sizeof(TempVariable))))
		ERROR(NULL, __LINE__, TRUE);					// out of memory
		
	newTemp->symbol = tempVariable;
	
	newTemp->next = _tempVariables;
	_tempVariables = newTemp;
}

/* Function: popTempVariables
 * Parameters: TempVariable *tempVariable
 * Description: Writes all global temps into mips global data and frees temp
 *					variables list.
 * Returns: none
 * Preconditions: none
 */
void popTempVariables(TempVariable *tempVariable) {
	if (!tempVariable)
		return;
	
	printf("\n");
	printf("_%s:\n", tempVariable->symbol->identifier);

	if (tempVariable->symbol->type == CHAR_TYPE)
		printf("\t.byte 0\n");
	else
		printf("\t.word 0\n");
	
	
	popTempVariables(tempVariable->next);
	free(tempVariable);
}

/* Function: insertStringLiteral
 * Parameters: Symbol *stringLiteral
 * Description: Adds the given string literal to the list of string literals.
 * Returns: none
 * Preconditions: none
 */
void insertStringLiteral(Symbol *stringLiteral) {
	if (!stringLiteral)
		return;
	
	StringLiteral *newStringLiteral = NULL;
	
	if (!(newStringLiteral = malloc(sizeof(StringLiteral))))
		ERROR(NULL, __LINE__, TRUE);						// out of memory
	
	newStringLiteral->symbol = stringLiteral;
	
	newStringLiteral->next = _stringLiterals;
	_stringLiterals = newStringLiteral;
}

/* Function: recallStringLiteral
 * Parameters: char *targetString
 * Description: Searches string literals list for target string. If found
 *					returns a reference to its symbol table entry.
 * Returns: A reference to the symbol table entry storing the specified string
 *				if found, NULL otherwise.
 * Preconditions: none
 */
Symbol	*recallStringLiteral(char *targetString) {
	if (!targetString)
		return NULL;
	
	StringLiteral *currString = _stringLiterals;
	
	while (currString) {
		if (strcmp(currString->symbol->value.strVal, targetString) == 0)
			return currString->symbol;
		
		currString = currString->next;
	}
	
	return NULL;
}

/* Function: popStringLiterals
 * Parameters: Symbol *stringLiteral
 * Description: Writes all global strings into mips global data and frees string
 *					literals list.
 * Returns: none
 * Preconditions: none
 */
void popStringLiterals(StringLiteral *stringLiteral) {
	if (!stringLiteral)
		return;
	
	printf("\n");
	printf("_%s:\n", stringLiteral->symbol->identifier);
	printf("\t.asciiz\t%s\n", stringLiteral->symbol->value.strVal);
	
	popStringLiterals(stringLiteral->next);
	free(stringLiteral->symbol->value.strVal);
	free(stringLiteral);
}

/* Function: yyerror
 * Parameters: char *errorMessage
 * Description: Called when syntax errors are found. Prints error message and
 *					turns code generation off.
 * Returns: void
 * Preconditions: none
 */
yyerror(char* errorMessage) {
	fprintf(stderr, "SYNTAX ERROR: line %d: Near token (%s)\n", yylineno, yytext);
	_generateCode = FALSE;
}

yywrap() {
	return 1;
}

/* Function: declareGlobalVariables
 * Parameters: SyntaxTree *tree
 * Description: Converts global declarations to assembly code.
 * Returns: none
 * Preconditions: none
 */
void declareGlobalVariables(SyntaxTree *tree) {
	if (!tree)
		return;

	Symbol *currSymbol = tree->symbol;
	
	if (!currSymbol) {
		declareGlobalVariables(tree->left);
		declareGlobalVariables(tree->right);
		return;
	}

	if (!(currSymbol->location = malloc(strlen(currSymbol->identifier) + 2)))
		ERROR(NULL, __LINE__, TRUE);				//out of memory
		
	sprintf(currSymbol->location, "_%s", currSymbol->identifier);
	printf("%s:\n", currSymbol->location);
	
	switch (currSymbol->type) {
		case CHAR_TYPE:
			printf("\t.byte 0\n");
			break;
		case INT_TYPE:
			printf("\t.word 0\n");
			break;
		case CHAR_ARRAY:
			printf("\t.space %d\n", currSymbol->value.intVal);
			break;
		case INT_ARRAY:
			printf("\t.space %d\n", (4 * currSymbol->value.intVal));
			break;
		default:
			break;
	}
	
	declareGlobalVariables(tree->left);
	declareGlobalVariables(tree->right);
}

/* Function: allocateStackSpace
 * Parameters: SyntaxTree *declaration, int offset
 * Description: Sets the stack offset for each declaration.
 * Returns: none
 * Preconditions: On the first call to this function the offset is 0.
 */
int allocateStackSpace(SyntaxTree *declaration, int offset) {
	if (!declaration)
		return offset;
	
	if (!declaration->symbol
			|| declaration->operation == LITERAL
			|| (declaration->operation != DECLARATION
			&& declaration->operation != FORMAL
			&& strncmp(declaration->symbol->identifier, "_temp", 5) != 0)) {
		offset = allocateStackSpace(declaration->right, offset);
		offset = allocateStackSpace(declaration->left, offset);
		offset = allocateStackSpace(declaration->opt, offset);
	} else {
		if (!(declaration->symbol->location = malloc(10 * sizeof(char))))
			ERROR(NULL, __LINE__, TRUE);							//out of memory
	
		sprintf(declaration->symbol->location, "%d($sp)", offset);
	
		//printf("Declaration %s has location %s\n", declaration->symbol->identifier, declaration->symbol->location);
	
		if (declaration->operation == DECLARATION) {
		
			if (declaration->symbol->type == CHAR_ARRAY) {
				offset += declaration->symbol->value.intVal;
				if (offset % 4 != 0)
					offset += 4 - (offset % 4);
				offset = allocateStackSpace(declaration->left, offset);
			} else	if (declaration->symbol->type == INT_ARRAY) {
				offset += 4 * declaration->symbol->value.intVal;
				offset = allocateStackSpace(declaration->left, offset);				
			} else {
				offset = allocateStackSpace(declaration->left, offset + 4);
			}

		} else {
			offset = allocateStackSpace(declaration->right, offset + 4);
			offset = allocateStackSpace(declaration->left, offset);
			offset = allocateStackSpace(declaration->opt, offset);
		}
	}
	return offset;
}

/* Function: constructCode
 * Parameters: SyntaxTree *tree
 * Description: Converts the given syntax tree into a three address code list.
 * Returns: The head of a code list.
 * Preconditions: none
 */
Code *constructCode(SyntaxTree *tree) {
	if (!tree || !_generateCode)
		return NULL;
	
	constructCode(tree->left);
	constructCode(tree->right);
	constructCode(tree->opt);
	
	Code *code = NULL;
	
	switch (tree->operation) {
		case ADD:
		
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(ADD_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(ADD_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(ADD_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}
			
			break;
	 	case SUB:
	
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(SUB_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(SUB_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(SUB_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}
			
			break;
		case MULT:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(MULT_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(MULT_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(MULT_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}
			
			break;
		case DIV:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(DIV_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(DIV_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(DIV_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}
			
			break;
		case NEG:
			
			if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(NEG_OP, tree->left->symbol, NULL, tree->symbol);
			} else {
				tree->code = createCode(NEG_OP, tree->left->symbol, NULL, tree->symbol);
			}
			
			break;
		case NOT:
			
			if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(NOT_OP, tree->left->symbol, NULL, tree->symbol);
			} else {
				tree->code = createCode(NOT_OP, tree->left->symbol, NULL, tree->symbol);
			}

			break;
		case EQUAL:
		
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}

			break;
		case NOT_EQUAL:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(NOT_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(NOT_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(NOT_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}

			break;
		case GREATER_THAN:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(GREATER_THAN_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(GREATER_THAN_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(GREATER_THAN_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}

			break;
		case GREATER_EQUAL:
		
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(GREATER_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(GREATER_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(GREATER_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}

			break;
		case LESS_THAN:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(LESS_THAN_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(LESS_THAN_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(LESS_THAN_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}

			break;
		case LESS_EQUAL:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(LESS_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(LESS_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(LESS_EQUAL_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}

			break;
		case AND:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = createCode(NOT_OP, tree->right->symbol, NULL, tree->right->symbol);
				code = code->next;
				generateNewLabelID();
				Symbol *shortSymbol = insertGlobal(_labelID, UNKNOWN);
				code->next = createCode(BRANCH, tree->right->symbol, NULL, shortSymbol);
				code = code->next;
				code->next = createCode(NOT_OP, tree->right->symbol, NULL, tree->right->symbol);
				code = code->next;
				
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(AND_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = code->next; 
				code->next = createCode(LABEL, shortSymbol, NULL, NULL);
			} else if (tree->left->code) {
				tree->code = createCode(NOT_OP, tree->right->symbol, NULL, tree->right->symbol);
				code = tree->code;
				generateNewLabelID();
				Symbol *shortSymbol = insertGlobal(_labelID, UNKNOWN);
				code->next = createCode(BRANCH, tree->right->symbol, NULL, shortSymbol);
				code = code->next;
				code->next = createCode(NOT_OP, tree->right->symbol, NULL, tree->right->symbol);
				code = code->next;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(AND_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = code->next;
				code->next = createCode(LABEL, shortSymbol, NULL, NULL);
			} else {
				tree->code = createCode(NOT_OP, tree->right->symbol, NULL, tree->right->symbol);
				code = tree->code;
				generateNewLabelID();
				Symbol *shortSymbol = insertGlobal(_labelID, UNKNOWN);
				code->next = createCode(BRANCH, tree->right->symbol, NULL, shortSymbol);
				code = code->next;
				code->next = createCode(NOT_OP, tree->right->symbol, NULL, tree->right->symbol);
				code = code->next;
				code->next = createCode(AND_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = code->next; 
				code->next = createCode(LABEL, shortSymbol, NULL, NULL);
			}

			break;
		case OR:
		
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = createCode(OR_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = code->next;
				generateNewLabelID();
				Symbol *shortSymbol = insertGlobal(_labelID, UNKNOWN);
				code->next = createCode(BRANCH, tree->right->symbol, NULL, shortSymbol);
				code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(OR_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = code->next; 
				code->next = createCode(LABEL, shortSymbol, NULL, NULL);
			} else if (tree->left->code) {
				tree->code = createCode(OR_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = tree->code;
				generateNewLabelID();
				Symbol *shortSymbol = insertGlobal(_labelID, UNKNOWN);
				code->next = createCode(BRANCH, tree->right->symbol, NULL, shortSymbol);
				code = code->next;
				
				code->next = tree->left->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(OR_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = code->next;
				code->next = createCode(LABEL, shortSymbol, NULL, NULL);
			} else {
				tree->code = createCode(OR_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = tree->code;
				generateNewLabelID();
				Symbol *shortSymbol = insertGlobal(_labelID, UNKNOWN);
				code->next = createCode(BRANCH, tree->right->symbol, NULL, shortSymbol);
				code = code->next;
				code->next = createCode(OR_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
				code = code->next;
				code->next = createCode(LABEL, shortSymbol, NULL, NULL);
			}

			break;
		case ARRAY:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
				
				code->next = createCode(ARRAY_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			} else {
				tree->code = createCode(ARRAY_OP, tree->left->symbol, tree->right->symbol, tree->symbol);
			}

			break;
		case RETRIEVE:
			
			if (tree->left->code) {
				tree->code = tree->left->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
				
				code->next = createCode(RETRIEVE_OP, tree->left->symbol, NULL, tree->symbol);
			} else {
				tree->code = createCode(RETRIEVE_OP, tree->left->symbol, NULL, tree->symbol);
			}
			
			break;
		case IF_TREE:
			
			tree->code = tree->left->code;
		
			code = tree->code;
		
			while (code->next)
				code = code->next;
			
			generateNewLabelID();
			Symbol *trueSymbol = insertGlobal(_labelID, UNKNOWN);
			code->next = createCode(BRANCH, tree->left->symbol, NULL, trueSymbol);
			code = code->next;
			generateNewLabelID();
			Symbol *falseSymbol = insertGlobal(_labelID, UNKNOWN);
			code->next = createCode(JUMP, falseSymbol, NULL, NULL);
			code = code->next;
			code->next = createCode(LABEL, trueSymbol, NULL, NULL);
			code = code->next;
			
			if (tree->right && tree->right->code) {
				code->next = tree->right->code;
				
				while (code->next)
					code = code->next;
			}
			
			if (tree->opt) {
				generateNewLabelID();
				Symbol *afterSymbol = insertGlobal(_labelID, UNKNOWN);
				code->next = createCode(JUMP, afterSymbol, NULL, NULL);
				code = code->next;
				code->next = createCode(LABEL, falseSymbol, NULL, NULL);
				code = code->next;
				code->next = tree->opt->code;
				
				while (code->next)
					code = code->next;
					
				code->next = createCode(LABEL, afterSymbol, NULL, NULL);				
			} else {
				code->next = createCode(LABEL, falseSymbol, NULL, NULL);
			}
			
			break;
		case WHILE_TREE:
			
			generateNewLabelID();
			Symbol *conditionSymbol = insertGlobal(_labelID, UNKNOWN);
			tree->code = createCode(JUMP, conditionSymbol, NULL, NULL);
			code = tree->code;
			generateNewLabelID();
			Symbol *trueSym = insertGlobal(_labelID, UNKNOWN);
			code->next = createCode(LABEL, trueSym, NULL, NULL);
			code = code->next;
			
			if (tree->right && tree->right->code) {
				code->next = tree->right->code;
				
				while (code->next)
					code = code->next;
			}
			
			if (tree->opt) {
				code->next = tree->opt->code;
				
				while (code->next)
					code = code->next;
			}
			
			code->next = createCode(LABEL, conditionSymbol, NULL, NULL);
			code = code->next;
			if (tree->left)
				code->next = tree->left->code;
			
			while (code->next)
				code = code->next;
			
			if (tree->left)
				code->next = createCode(BRANCH, tree->left->symbol, NULL, trueSym);
			else
				code->next = createCode(JUMP, trueSym, NULL, NULL);
			
			break;
		case RETURN_TREE:
			if (!tree->left) {
				tree->code = createCode(RETURN_OP, NULL, NULL, tree->symbol);
			} else {
				
				if (tree->left->code) {
					tree->code = tree->left->code;

					code = tree->code;

					while (code->next)
						code = code->next;
					code->next = createCode(RETURN_OP, tree->left->symbol, NULL, tree->symbol);
				} else {
					tree->code = createCode(RETURN_OP, tree->left->symbol, NULL, tree->symbol);
				}
			}
			break;
		case ASSIGNMENT:
			
			if (tree->right->code) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
				
				if (tree->left->code) {
					code = tree->left->code;
					
					while(code->next)
						code = code->next;
				}
				
				code->next = createCode(ASSIGNMENT_OP, tree->right->symbol, NULL, tree->left->symbol);
			} else if (tree->left->code) {
				tree->code = tree->left->code;
				
				code = tree->code;
				
				while(code->next)
					code = code->next;
				
				code->next = createCode(ASSIGNMENT_OP, tree->right->symbol, NULL, tree->left->symbol);
			} else {
				tree->code = createCode(ASSIGNMENT_OP, tree->right->symbol, NULL, tree->left->symbol);
			}
			
			break;
		case STATEMENT:
			if (tree->right) {
				tree->code = tree->right->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = tree->left->code;
			} else {
				tree->code = tree->left->code;
			}
			break;
		case FUNCTION_CALL:
			if (tree->left) {
				tree->code = tree->left->code;
			
				code = tree->code;
			
				while (code->next)
					code = code->next;
			
				code->next = createCode(ENTER, tree->symbol, NULL, NULL);
			} else {
				tree->code = createCode(ENTER, tree->symbol, NULL, NULL);
			}
			break;
		case PARAMETER:
			code = tree->right->code;
			
			if (code) {
				tree->code = code;
				while (code->next)
					code = code->next;
				
				code->next = createCode(PUSH_PARAM, tree->right->symbol, NULL, NULL);
				code = code->next;
			} else {
				code = createCode(PUSH_PARAM, tree->right->symbol, NULL, NULL);
				tree->code = code;
			}
			
			if (tree->left)
				code->next = tree->left->code;
			
			break;
		case DECLARATION:
			break;
		case SYMBOL:
			break;
		case FORMAL:
			break;
		case FUNCTION_ROOT:
			if (tree->left && tree->left->code) {
				tree->code = tree->left->code;
					
				code = tree->code;
					
				while (code->next)
					code = code->next;

				if (tree->right)
					code->next = tree->right->code;
			} else {
				if (tree->right)
					tree->code = tree->right->code;
			}
			break;
		default:
			break;
	}
	
	return tree->code;
}

/* Function: writeCode
 * Parameters: Code *code
 * Description: Converts the given three address code list into mips assemblycode.
 * Returns: none
 * Preconditions: none
 */
void writeCode(Code *code) {
	if (!code || !_generateCode)
		return;
	
	switch (code->opcode) {
		case ADD_OP:
			writeExpressionCode("add", "+", code);
			break;
		case SUB_OP:
			writeExpressionCode("sub", "-", code);
			break;
		case MULT_OP:
			writeExpressionCode("mul", "*", code);
			break;
		case DIV_OP:
			writeExpressionCode("div", "/", code);
			break;
		case NEG_OP:
			printf("\n");
		
			if (code->source1->location) {
					
				printf("\t# -%s\n", code->source1->identifier);
					
				if (code->source1->type == CHAR_TYPE) {
					printf("\tlb\t\t$t0, %s\n", code->source1->location);
				} else if (code->source1->reference) {
					printf("\tlw\t\t$t0, %s\n", code->source1->location);
				} else {
					printf("\tlw\t\t$t0, %s\n", code->source1->location);
				}
				
				if (code->source1->type == CHAR_ARRAY)
					printf("\tlb\t\t$t0, 0($t0)\n");
				if (code->source1->type == INT_ARRAY)
					printf("\tlw\t\t$t0, 0($t0)\n");
					
			} else {
					
				if (code->source1->type == CHAR_TYPE) {
					if (code->source1->value.charVal == '\n') {
						printf("\t# -'\\n'\n");
						printf("\tli\t\t$t0, 10		# 10 is ascii value for '\\n'\n");
					} else if (code->source1->value.charVal == '\0') {
						printf("\t# -'\\0'\n");
						printf("\tli\t\t$t0, 0		# 0 is ascii value for '\\0'\n");
					} else {
						printf("\t# -'%c'\n", code->source1->value.charVal);
						printf("\tli\t\t$t0, '%c'\n", code->source1->value.charVal);
					}
				} else {
					printf("\t# -%d\n", code->source1->value.intVal);
					printf("\tli\t\t$t0, %d\n", code->source1->value.intVal);
				}
				
			}
			
			printf("\tneg\t\t$t0, $t0\n");
		
			if (code->destination->type == CHAR_TYPE)
				printf("\tsb\t\t$t0, ");
			else
				printf("\tsw\t\t$t0, ");
			
			if (_offset != 0 && strncmp(code->destination->location, "_", 1) != 0)
				printf("%d + %s\n", _offset, code->destination->location);
			else
				printf("%s\n", code->destination->location);
			
			break;
		case NOT_OP:
			printf("\n");
			
			printf("\tlw\t\t$t0, %s\n", code->source1->location);
			printf("\txori\t$t0, $t0, 1\n");
			printf("\tsw\t\t$t0, %s\n", code->destination->location);

			break;
		case EQUAL_OP:
			writeExpressionCode("seq", "==", code);
			break;
		case NOT_EQUAL_OP:
			writeExpressionCode("sne", "!=", code);
			break;
		case GREATER_THAN_OP:
			writeExpressionCode("sgt", ">", code);
			break;
		case GREATER_EQUAL_OP:
			writeExpressionCode("sge", ">=", code);
			break;
		case LESS_THAN_OP:
			writeExpressionCode("slt", "<", code);
			break;
		case LESS_EQUAL_OP:
			writeExpressionCode("sle", "<=", code);
			break;
		case AND_OP:
			printf("\n");
			
			printf("\tlw\t\t$t0, %s\n", code->source1->location);
			printf("\tlw\t\t$t1, %s\n", code->source2->location);
			printf("\tand\t\t$t0, $t0, $t1\n");
			printf("\tsw\t\t$t0, %s\n", code->destination->location);
			
			break;
		case OR_OP:
			printf("\n");
			
			printf("\tlw\t\t$t0, %s\n", code->source1->location);
			printf("\tlw\t\t$t1, %s\n", code->source2->location);
			printf("\tor\t\t$t0, $t0, $t1\n");
			printf("\tsw\t\t$t0, %s\n", code->destination->location);
			
			break;
		case RETRIEVE_OP:
			printf("\n");
			
			printf("\t# retrieve return value from %s\n", code->source1->identifier);
			
			if (code->destination->type == CHAR_TYPE) {
				printf("\tsb\t\t$v0, ");
			} else {
				printf("\tsw\t\t$v0, ");
			}
			
			if (_offset != 0 && strncmp(code->destination->location, "_", 1) != 0)
				printf("%d + %s\n", _offset, code->destination->location);
			else
				printf("%s\n", code->destination->location);
			
			break;
		case BRANCH:
			printf("\n");
			printf("\tlw\t\t$t0, %s\n", code->source1->location);
			printf("\tbgtz\t$t0, _%s\n", code->destination->identifier);
			break;
		case JUMP:
			printf("\n");
			printf("\tj\t\t_%s\n", code->source1->identifier);
			break;
		case LABEL:
			printf("\n");
			printf("_%s:\n", code->source1->identifier);
			break;
		case RETURN_OP:
			printf("\n");
			if (!code->source1) {
				printf("\t# return\n");
				printf("\tj\t\t__%sReturn\n", code->destination->identifier);
			} else {
				
				if (code->source1->location) {

					printf("\t# return %s\n", code->source1->identifier);

					if (code->source1->type == CHAR_ARRAY) {
						printf("\tlw\t\t$t0, %s\n", code->source1->location);
						printf("\tlb\t\t$t0, 0($t0)\n");
					} else if (code->source1->type == INT_ARRAY) {
						printf("\tlw\t\t$t0, %s\n", code->source1->location);
						printf("\tlw\t\t$t0, 0($t0)\n");
					} else if (code->source1->type == CHAR_TYPE) {
						printf("\tlb\t\t$t0, %s\n", code->source1->location);
					} else {
						printf("\tlw\t\t$t0, %s\n", code->source1->location);
					}

				} else {

					if (code->source1->type == CHAR_TYPE) {
						if (code->source1->value.charVal == '\n') {
							printf("\t# return '\\n'\n");
							printf("\tli\t\t$t0, 10		# 10 is ascii value for '\\n'\n");
						} else if (code->source1->value.charVal == '\0') {
							printf("\t# return '\\0'\n");
							printf("\tli\t\t$t0, 0		# 0 is ascii value for '\\0'\n");
						} else {
							printf("\t# return '%c'\n", code->source1->value.charVal);
							printf("\tli\t\t$t0, '%c'\n", code->source1->value.charVal);
						}
					} else {
						printf("\t# return %d\n", code->source1->value.intVal);
						printf("\tli\t\t$t0, %d\n", code->source1->value.intVal);
					}

				}
				
				printf("\tadd\t\t$v0, $t0, $0\n");
				printf("\tj\t\t__%sReturn\n", code->destination->identifier);
			}
			break;
		case ARRAY_OP:
			printf("\n");
				
			if (code->source2->location) {
				
				printf("\t# %s[%s]\n", code->source1->identifier, code->source2->identifier);
				
				if (code->source2->type == CHAR_ARRAY) {
					printf("\tlw\t\t$t1, %s\n", code->source2->location);
					printf("\tlb\t\t$t1, 0($t1)\n");
				} else if (code->source2->type == INT_ARRAY) {
					printf("\tlw\t\t$t1, %s\n", code->source2->location);
					printf("\tlw\t\t$t1, 0($t1)\n");
				} else if (code->source2->type == CHAR_TYPE) {
					printf("\tlb\t\t$t1, %s\n", code->source2->location);
				} else {
					printf("\tlw\t\t$t1, %s\n", code->source2->location);
				}
					
			} else {
					
				if (code->source2->type == CHAR_TYPE) {
					if (code->source2->value.charVal == '\n') {
						printf("\t# %s['\\n']\n", code->source1->identifier);
						printf("\tli\t\t$t1, 10		# 10 is ascii value for '\\n'\n");
					} else if (code->source2->value.charVal == '\0') {
						printf("\t# %s[\\0']\n", code->source1->identifier);
						printf("\tli\t\t$t1, 0		# 0 is ascii value for '\\0'\n");
					} else {
						printf("\t# %s['%c']\n", code->source1->identifier, code->source2->value.charVal);
						printf("\tli\t\t$t1, '%c'\n", code->source2->value.charVal);
					}
				} else {
					printf("\t# %s[%d]\n", code->source1->identifier, code->source2->value.intVal);
					printf("\tli\t\t$t1, %d\n", code->source2->value.intVal);
				}
				
			}
			
			if (code->destination->type == INT_ARRAY)
				printf("\tsll\t\t$t1, $t1, 2\t\t# index * 4 (size of int)\n");
			
			if (code->source1->reference) {
				printf("\tlw\t\t$t0, %s\n", code->source1->location);
				code->destination->reference = TRUE;
			} else {
				printf("\tla\t\t$t0, %s\n", code->source1->location);
			}
				
			printf("\tadd\t\t$t0, $t0, $t1\n");
			printf("\tsw\t\t$t0, ");
			
			if (_offset != 0 && strncmp(code->destination->location, "_", 1) != 0)
				printf("%d + %s\n", _offset, code->destination->location);
			else
				printf("%s\n", code->destination->location);
			
			break;
		case ASSIGNMENT_OP:
			printf("\n");
			
			if (code->source1->location) {
				
				printf("\t# %s = %s\n", code->destination->identifier, code->source1->identifier);

				if (code->source1->type == CHAR_ARRAY) {
					printf("\tlw\t\t$t0, %s\n", code->source1->location);
					printf("\tlb\t\t$t0, 0($t0)\n");
				} else if (code->source1->type == INT_ARRAY) {
					printf("\tlw\t\t$t0, %s\n", code->source1->location);
					printf("\tlw\t\t$t0, 0($t0)\n");
				} else if (code->source1->type == CHAR_TYPE) {
					printf("\tlb\t\t$t0, %s\n", code->source1->location);
				} else {
					printf("\tlw\t\t$t0, %s\n", code->source1->location);
				}
					
			} else {
				
				if (code->source1->type == CHAR_TYPE) {
					if (code->source1->value.charVal == '\n') {
						printf("\t# %s = '\\n'\n", code->destination->identifier);
						printf("\tli\t\t$t0, 10		# 10 is ascii value for '\\n'\n");
					} else if (code->source1->value.charVal == '\0') {
						printf("\t# %s = '\\0'\n", code->destination->identifier);
						printf("\tli\t\t$t0, 0		# 0 is ascii value for '\\0'\n");
					} else {
						printf("\t# %s = '%c'\n", code->destination->identifier, code->source1->value.charVal);
						printf("\tli\t\t$t0, '%c'\n", code->source1->value.charVal);
					}
				} else {
					printf("\t# %s = %d\n", code->destination->identifier, code->source1->value.intVal);
					printf("\tli\t\t$t0, %d\n", code->source1->value.intVal);
				}
				
			}
			
			if (code->destination->type == CHAR_ARRAY)
				printf("\tlw\t\t$t1, ");
			else if (code->destination->type == INT_ARRAY)
				printf("\tlw\t\t$t1, ");
			else if (code->destination->type == CHAR_TYPE)
				printf("\tsb\t\t$t0, ");
			else
				printf("\tsw\t\t$t0, ");
			
			if (_offset != 0 && strncmp(code->destination->location, "_", 1) != 0)
				printf("%d + %s\n", _offset, code->destination->location);
			else
				printf("%s\n", code->destination->location);
				
			if (code->destination->type == CHAR_ARRAY)
				printf("\tsb\t\t$t0, 0($t1)\n");	
				
			if (code->destination->type == INT_ARRAY)
				printf("\tsw\t\t$t0, 0($t1)\n");
				
			break;
		case ENTER:
			printf("\n");
			printf("\t# calling %s\n", code->source1->identifier);
			
			if (strcmp(code->source1->identifier, "main") == 0)
				printf("\tjal\t\tmain\n", code->source1->identifier);
			else
				printf("\tjal\t\t_%s\n", code->source1->identifier);
			
			Parameter *currParam = code->source1->parameterListHead;
			int bytesToPop = 0;

			if (currParam && currParam->type != VOID_TYPE) {
				printf("\n\t# popping pushed parameters\n");
				
				while (currParam) {
					bytesToPop += 4;
					currParam = currParam->next;
				}
				
				printf("\taddu\t$sp, $sp, %d\n", bytesToPop);
				_offset -= bytesToPop;
			}
			break;
		case LEAVE:
			break;
		case PUSH_PARAM:
			printf("\n");
			
			if (code->source1->location) {
				
				printf("\t# pushing parameter %s\n", code->source1->identifier);
				if (code->source1->type == CHAR_ARRAY) {
					if (code->source1->reference) {
						if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
							printf("\tlw\t\t$t0, %d + %s\n", _offset, code->source1->location);
						else
							printf("\tlw\t\t$t0, %s\n", code->source1->location);
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tsw\t\t$t0, 0($sp)\n");
					} else if (strncmp(code->source1->identifier, "_temp", 5) == 0
							&& !code->source1->value.strVal) {
						// char array being indexed
						if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
							printf("\tlw\t\t$t0, %d + %s\n", _offset, code->source1->location);
						else
							printf("\tlw\t\t$t0, %s\n", code->source1->location);
						printf("\tlb\t\t$t0, 0($t0)\n");
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tsw\t\t$t0, 0($sp)\n");
					} else {
						// char array being passed whole
						if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
							printf("\tla\t\t$t0, %d + %s\n", _offset, code->source1->location);
						else
							printf("\tla\t\t$t0, %s\n", code->source1->location);
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tsw\t\t$t0, 0($sp)\n");
					}
				} else if (code->source1->type == INT_ARRAY) {
					if (code->source1->reference) {
						if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
							printf("\tlw\t\t$t0, %d + %s\n", _offset, code->source1->location);
						else
							printf("\tlw\t\t$t0, %s\n", code->source1->location);
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tsw\t\t$t0, 0($sp)\n");
					} else if (strncmp(code->source1->identifier, "_temp", 5) == 0) {
						// int array being indexed
						if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
							printf("\tlw\t\t$t0, %d + %s\n", _offset, code->source1->location);
						else
							printf("\tlw\t\t$t0, %s\n", code->source1->location);
						printf("\tlw\t\t$t0, 0($t0)\n");
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tsw\t\t$t0, 0($sp)\n");
					} else {
						// int array being passed whole
						if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
							printf("\tla\t\t$t0, %d + %s\n", _offset, code->source1->location);
						else
							printf("\tla\t\t$t0, %s\n", code->source1->location);
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tsw\t\t$t0, 0($sp)\n");
					}
				} else if (code->source1->type == CHAR_TYPE) {
					if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
						printf("\tlb\t\t$t0, %d + %s\n", _offset, code->source1->location);
					else
						printf("\tlb\t\t$t0, %s\n", code->source1->location);
					printf("\tsubu\t$sp, $sp, 4\n");
					printf("\tsw\t\t$t0, 0($sp)\n");
				} else if (code->source1->type == INT_TYPE) {
					if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
						printf("\tlw\t\t$t0, %d + %s\n", _offset, code->source1->location);
					else
						printf("\tlw\t\t$t0, %s\n", code->source1->location);
					printf("\tsubu\t$sp, $sp, 4\n");
					printf("\tsw\t\t$t0, 0($sp)\n");
				} else {
					if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
						printf("\tla\t\t$t0, %d + %s\n", _offset, code->source1->location);
					else
						printf("\tla\t\t$t0, %s\n", code->source1->location);
					printf("\tsubu\t$sp, $sp, 4\n");
					printf("\tsw\t\t$t0, 0($sp)\n");
				}
				
			} else {
				
				if (code->source1->type == CHAR_TYPE) {
					if (code->source1->value.charVal == '\n') {
						printf("\t# pushing parameter '\\n'\n", code->source1->value.charVal);
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tli\t\t$t0, 10\n", code->source1->value.charVal);
						printf("\tsw\t\t$t0, 0($sp)\n");
					} else if (code->source1->value.charVal == '\0') {
						printf("\t# pushing parameter '\\0'\n", code->source1->value.charVal);
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tli\t\t$t0, 0\n", code->source1->value.charVal);
						printf("\tsw\t\t$t0, 0($sp)\n");
					} else {
						printf("\t# pushing parameter '%c'\n", code->source1->value.charVal);
						printf("\tsubu\t$sp, $sp, 4\n");
						printf("\tli\t\t$t0, '%c'\n", code->source1->value.charVal);
						printf("\tsw\t\t$t0, 0($sp)\n");
					}
					
				} else {
					printf("\t# pushing parameter %d\n", code->source1->value.intVal);
					printf("\tsubu\t$sp, $sp, 4\n");
					printf("\tli\t\t$t0, %d\n", code->source1->value.intVal);
					printf("\tsw\t\t$t0, 0($sp)\n");
				}
				
			}
			
			_offset += 4;
			break;
		case DECLARATION_OP:
			break;
		default:
			break;
	}
	
	writeCode(code->next);
}

void writeExpressionCode(char *mnemonic, char *operator, Code *code) {
	printf("\n");
	
	if (code->source1->location) {

		if (code->source2->location) {
			
			printf("\t# %s %s %s\n", code->source2->identifier, operator, code->source1->identifier);
			
			if (code->source2->type == CHAR_TYPE) {
				printf("\tlb\t\t$t1, ");
			} else if (code->source2->reference) {
				printf("\tlw\t\t$t1, ");
			} else {
				printf("\tlw\t\t$t1, ");
			}
			
			if (_offset != 0 && strncmp(code->source2->location, "_", 1) != 0)
				printf("%d + %s\n", _offset, code->source2->location);
			else
				printf("%s\n", code->source2->location);
			
			if (code->source2->type == CHAR_ARRAY)
				printf("\tlb\t\t$t1, 0($t1)\n");
			if (code->source2->type == INT_ARRAY)
				printf("\tlw\t\t$t1, 0($t1)\n");
				
		} else {
			
			if (code->source2->type == CHAR_TYPE) {
				if (code->source2->value.charVal == '\n') {
					printf("\t# '\\n' %s %s\n", operator, code->source1->identifier);
					printf("\tli\t\t$t1, 10		# 10 is ascii value for '\\n'\n");
				} else if (code->source2->value.charVal == '\0') {
					printf("\t# '\\0' %s %s\n", operator, code->source1->identifier);
					printf("\tli\t\t$t1, 0		# 0 is ascii value for '\\0'\n");
				} else {
					printf("\t# '%c' %s %s\n", code->source2->value.charVal, operator, code->source1->identifier);
					printf("\tli\t\t$t1, '%c'\n", code->source2->value.charVal);
				}
			} else {
				printf("\t# %d %s %s\n", code->source2->value.intVal, operator, code->source1->identifier);
				printf("\tli\t\t$t1, %d\n", code->source2->value.intVal);
			}
				
		}
		
		if (code->source1->type == CHAR_TYPE) {
			printf("\tlb\t\t$t0, ");
		} else if (code->source1->reference) {
			printf("\tlw\t\t$t0, ");
		} else {
			printf("\tlw\t\t$t0, ");
		}
		
		if (_offset != 0 && strncmp(code->source1->location, "_", 1) != 0)
			printf("%d + %s\n", _offset, code->source1->location);
		else
			printf("%s\n", code->source1->location);
		
		if (code->source1->type == CHAR_ARRAY)
			printf("\tlb\t\t$t0, 0($t0)\n");
		if (code->source1->type == INT_ARRAY)
			printf("\tlw\t\t$t0, 0($t0)\n");
		
	} else {
		
		if (code->source2->location) {
			
			if (code->source1->type == CHAR_TYPE) {
				if (code->source1->value.charVal == '\n') {
					printf("\t# %s %s '\\n'\n", code->source2->identifier, operator);
					printf("\tli\t\t$t0, 10		# 10 is ascii value for '\\n'\n");
				} else if (code->source1->value.charVal == '\0') {
					printf("\t# %s %s '\\0'\n", code->source2->identifier, operator);
					printf("\tli\t\t$t0, 0		# 0 is ascii value for '\\0'\n");
				} else {
					printf("\t# %s %s '%c'\n", code->source2->identifier, operator, code->source1->value.charVal);
					printf("\tli\t\t$t0, '%c'\n", code->source1->value.charVal);
				}
			} else {
				printf("\t# %s %s %d\n", code->source2->identifier, operator, code->source1->value.intVal);
				printf("\tli\t\t$t0, %d\n", code->source1->value.intVal);
			}
			
			if (code->source2->type == CHAR_TYPE) {
				printf("\tlb\t\t$t1, ");
			} else if (code->source2->reference) {
				printf("\tlw\t\t$t1, ");
			} else {
				printf("\tlw\t\t$t1, ");				
			}
			
			if (_offset != 0 && strncmp(code->source2->location, "_", 1) != 0)
				printf("%d + %s\n", _offset, code->source2->location);
			else
				printf("%s\n", code->source2->location);
			
			if (code->source2->type == CHAR_ARRAY)
				printf("\tlb\t\t$t1, 0($t1)\n");
			if (code->source2->type == INT_ARRAY)
				printf("\tlw\t\t$t1, 0($t1)\n");
		
		} else {
			
			printf("\t# %s %s %s\n", code->source2->identifier, operator, code->source1->identifier);
		
			if (code->source1->type == CHAR_TYPE) {
				if (code->source1->value.charVal == '\n') {
					printf("\tli\t\t$t0, 10		# 10 is ascii value for '\\n'\n");
				} else if (code->source1->value.charVal == '\0') {
					printf("\tli\t\t$t0, 0		# 0 is ascii value for '\\0'\n");
				} else {
					printf("\tli\t\t$t0, '%c'\n", code->source1->value.charVal);
				}
			} else {
				printf("\tli\t\t$t0, %d\n", code->source1->value.intVal);
			}
			
			if (code->source2->type == CHAR_TYPE) {
				if (code->source2->value.charVal == '\n') {
					printf("\tli\t\t$t1, 10		# 10 is ascii value for '\\n'\n");
				} else if (code->source2->value.charVal == '\0') {
					printf("\tli\t\t$t1, 0		# 0 is ascii value for '\\0'\n");
				} else {
					printf("\tli\t\t$t1, '%c'\n", code->source2->value.charVal);
				}
			} else {
				printf("\tli\t\t$t1, %d\n", code->source2->value.intVal);
			}

		}
	}
	
	printf("\t%s\t\t$t0, $t1, $t0\n", mnemonic);

	if (code->destination->type == CHAR_TYPE)
		printf("\tsb\t\t$t0, ");
	else
		printf("\tsw\t\t$t0, ");
		
	if (_offset != 0 && strncmp(code->destination->location, "_", 1) != 0)
		printf("%d + %s\n", _offset, code->destination->location);
	else
		printf("%s\n", code->destination->location);
}

/* Function: typeError
 * Parameters: char *errorMessage
 * Description: Called when semantic errors are found. Prints error message and
 *					turns code generation off.
 * Returns: void
 * Preconditions: none
 */
void typeError(char *errorMessage) {
	fprintf(stderr, "TYPE ERROR: line %d: %s\n", yylineno, errorMessage);
	_generateCode = FALSE;
}

/* Function: generateNewTempID
 * Parameters: none
 * Description: Updates to a new unique temporary variable ID.
 * Returns: none
 * Preconditions: none
 */
void generateNewTempID() {
	sprintf(_tempID, "_temp%d", _tempNum++);
}

/* Function: generateNewLabelID
 * Parameters: none
 * Description: Updates to a new unique label ID.
 * Returns: none
 * Preconditions: none
 */
void generateNewLabelID() {
	sprintf(_labelID, "_label%d", _labelNum++);
}
