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
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     STRING = 259,
     INTNUM = 260,
     BOOL = 261,
     APPROXNUM = 262,
     OR = 263,
     XOR = 264,
     ANDOP = 265,
     LIKE = 266,
     IN = 267,
     NOT = 268,
     BETWEEN = 269,
     COMPARISON = 270,
     MOD = 271,
     UMINUS = 272,
     BITFLIP = 273,
     ADD = 274,
     ALL = 275,
     AND = 276,
     ANY = 277,
     AS = 278,
     ASC = 279,
     AUTO_INCREMENT = 280,
     BEFORE = 281,
     BY = 282,
     CHAR = 283,
     CREATE = 284,
     DATABASE = 285,
     DEFAULT = 286,
     DELETE = 287,
     DESC = 288,
     DISTINCT = 289,
     DOUBLE = 290,
     DROP = 291,
     FLOAT = 292,
     FROM = 293,
     INNER = 294,
     INSENSITIVE = 295,
     INSERT = 296,
     INT = 297,
     INTO = 298,
     JOIN = 299,
     KEY = 300,
     LONG = 301,
     ON = 302,
     ORDER = 303,
     PRIMARY = 304,
     REFERENCE = 305,
     SELECT = 306,
     SET = 307,
     TABLE = 308,
     TEXT = 309,
     UNIQUE = 310,
     UPDATE = 311,
     USE = 312,
     VALUES = 313,
     WHERE = 314
   };
#endif
/* Tokens.  */
#define NAME 258
#define STRING 259
#define INTNUM 260
#define BOOL 261
#define APPROXNUM 262
#define OR 263
#define XOR 264
#define ANDOP 265
#define LIKE 266
#define IN 267
#define NOT 268
#define BETWEEN 269
#define COMPARISON 270
#define MOD 271
#define UMINUS 272
#define BITFLIP 273
#define ADD 274
#define ALL 275
#define AND 276
#define ANY 277
#define AS 278
#define ASC 279
#define AUTO_INCREMENT 280
#define BEFORE 281
#define BY 282
#define CHAR 283
#define CREATE 284
#define DATABASE 285
#define DEFAULT 286
#define DELETE 287
#define DESC 288
#define DISTINCT 289
#define DOUBLE 290
#define DROP 291
#define FLOAT 292
#define FROM 293
#define INNER 294
#define INSENSITIVE 295
#define INSERT 296
#define INT 297
#define INTO 298
#define JOIN 299
#define KEY 300
#define LONG 301
#define ON 302
#define ORDER 303
#define PRIMARY 304
#define REFERENCE 305
#define SELECT 306
#define SET 307
#define TABLE 308
#define TEXT 309
#define UNIQUE 310
#define UPDATE 311
#define USE 312
#define VALUES 313
#define WHERE 314




/* Copy the first part of user declarations.  */
#line 1 "mysql.ypp"

#include "sqlfuncs.h"
#include <stdlib.h>
#include <stdarg.h> 
#include <string.h>
#include "types.h"

struct STMT_AST *ast;
struct EXPR *default_expr;
/*char *ref_table;*/
int yylex();


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "mysql.ypp"
{
    long intval;
    double floatval;
    char *strval;
    int cmptok;
    struct EXPR *expr_tree;
    struct STMT_AST *stmt_ast;
    struct TABLE_OP *table_op;
    struct SELECT_STMT *sel_stmt;
    struct SELECT_LIST *select_list;
    struct COL_DEF_LIST *col_def;
    struct ORDER_LIST *order;
    struct REF_LIST *table_ref_list;
    struct JOIN_PARAM *join;
    struct INS_SRC *ins_src;
    struct INS_EXPR_LIST *ins_list;
    struct COL_LISTING *col_ref;
    struct EXPR_LIST *list;
}
/* Line 193 of yacc.c.  */
#line 247 "mysql.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 260 "mysql.tab.cpp"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    13,     2,     2,     2,    23,    18,     2,
      71,    72,    21,    19,    73,    20,    69,    22,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    74,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    25,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    17,     2,    70,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    14,    15,
      16,    24,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    11,    13,    15,    17,    21,
      25,    29,    33,    37,    41,    44,    47,    51,    55,    59,
      63,    67,    70,    73,    77,    83,    89,    96,   100,   105,
     109,   111,   113,   117,   121,   124,   127,   130,   133,   136,
     139,   142,   145,   148,   152,   156,   160,   164,   171,   173,
     177,   181,   183,   185,   187,   189,   191,   192,   195,   203,
     204,   206,   208,   210,   214,   218,   220,   224,   227,   230,
     234,   238,   239,   240,   243,   244,   247,   248,   252,   254,
     258,   261,   262,   264,   266,   274,   276,   280,   285,   287,
     296
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      78,     0,    -1,     3,    -1,     3,    69,     3,    -1,     4,
      -1,     5,    -1,     7,    -1,     6,    -1,    76,    19,    76,
      -1,    76,    20,    76,    -1,    76,    21,    76,    -1,    76,
      22,    76,    -1,    76,    23,    76,    -1,    76,    24,    76,
      -1,    20,    76,    -1,    70,    76,    -1,    76,    10,    76,
      -1,    76,     8,    76,    -1,    76,    17,    76,    -1,    76,
      18,    76,    -1,    76,    25,    76,    -1,    14,    76,    -1,
      13,    76,    -1,    76,    16,    76,    -1,    76,    15,    76,
      30,    76,    -1,    76,    12,    71,    77,    72,    -1,    76,
      14,    12,    71,    77,    72,    -1,    76,    12,    95,    -1,
      76,    14,    12,    95,    -1,    71,    76,    72,    -1,    76,
      -1,    40,    -1,    77,    73,    76,    -1,    77,    73,    40,
      -1,    79,    74,    -1,    80,    74,    -1,    81,    74,    -1,
      83,    74,    -1,    82,    74,    -1,    88,    74,    -1,   103,
      74,    -1,   106,    74,    -1,   107,    74,    -1,    38,    39,
       3,    -1,    66,    39,     3,    -1,    45,    39,     3,    -1,
      45,    62,     3,    -1,    38,    62,     3,    71,    84,    72,
      -1,    85,    -1,    84,    73,    85,    -1,     3,    86,    87,
      -1,    51,    -1,    55,    -1,    46,    -1,    44,    -1,    63,
      -1,    -1,    40,    76,    -1,    60,    89,    90,    47,    92,
      98,    99,    -1,    -1,    29,    -1,    21,    -1,    91,    -1,
      90,    73,    91,    -1,    76,    32,     3,    -1,    93,    -1,
      92,    73,    93,    -1,    94,    96,    -1,     3,    97,    -1,
      95,    32,     3,    -1,    71,    88,    72,    -1,    -1,    -1,
      32,     3,    -1,    -1,    68,    76,    -1,    -1,    57,    36,
     100,    -1,   101,    -1,   100,    73,   101,    -1,    76,   102,
      -1,    -1,    33,    -1,    42,    -1,    50,    52,     3,    71,
     104,    72,   105,    -1,     3,    -1,   104,    73,     3,    -1,
      67,    71,    77,    72,    -1,    95,    -1,    65,     3,    61,
      71,   104,    72,   105,    98,    -1,    41,    47,     3,    98,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   136,   137,   138,   140,   142,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   156,   157,
     158,   159,   160,   161,   164,   165,   166,   167,   168,   170,
     173,   174,   175,   176,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   196,   199,   202,   205,   208,   212,   213,
     215,   227,   228,   229,   230,   231,   238,   244,   247,   251,
     252,   255,   257,   258,   262,   266,   267,   270,   273,   280,
     285,   288,   298,   299,   302,   303,   306,   307,   310,   311,
     315,   319,   320,   321,   324,   328,   329,   332,   334,   347,
     351
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "BOOL",
  "APPROXNUM", "OR", "XOR", "ANDOP", "LIKE", "IN", "'!'", "NOT", "BETWEEN",
  "COMPARISON", "'|'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "MOD",
  "'^'", "UMINUS", "BITFLIP", "ADD", "ALL", "AND", "ANY", "AS", "ASC",
  "AUTO_INCREMENT", "BEFORE", "BY", "CHAR", "CREATE", "DATABASE",
  "DEFAULT", "DELETE", "DESC", "DISTINCT", "DOUBLE", "DROP", "FLOAT",
  "FROM", "INNER", "INSENSITIVE", "INSERT", "INT", "INTO", "JOIN", "KEY",
  "LONG", "ON", "ORDER", "PRIMARY", "REFERENCE", "SELECT", "SET", "TABLE",
  "TEXT", "UNIQUE", "UPDATE", "USE", "VALUES", "WHERE", "'.'", "'~'",
  "'('", "')'", "','", "';'", "$accept", "expr", "val_list", "stmt",
  "create_database_stmt", "use_database_stmt", "drop_database_stmt",
  "drop_table_stmt", "create_table_stmt", "new_col_list", "create_def",
  "data_type", "opt_attr", "select_stmt", "select_opt", "select_expr_list",
  "select_expr", "ref_list", "table_ref", "table_factor", "table_subquery",
  "opt_join", "opt_alias", "opt_where", "opt_orderby", "order_list",
  "col_order", "opt_asc_desc", "insert_stmt", "column_list",
  "insert_source", "update_stmt", "delete_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,    33,   268,   269,   270,   124,    38,    43,
      45,    42,    47,    37,   271,    94,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,    46,
     126,    40,    41,    44,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      77,    77,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    80,    81,    82,    83,    84,    84,
      85,    86,    86,    86,    86,    86,    87,    87,    88,    89,
      89,    90,    90,    90,    91,    92,    92,    93,    94,    94,
      95,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   102,   102,   102,   103,   104,   104,   105,   105,   106,
     107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       3,     2,     2,     3,     5,     5,     6,     3,     4,     3,
       1,     1,     3,     3,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     6,     1,     3,
       3,     1,     1,     1,     1,     1,     0,     2,     7,     0,
       1,     1,     1,     3,     3,     1,     3,     2,     2,     3,
       3,     0,     0,     2,     0,     2,     0,     3,     1,     3,
       2,     0,     1,     1,     7,     1,     3,     4,     1,     8,
       4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,     0,     0,     0,     1,    34,
      35,    36,    38,    37,    39,    40,    41,    42,    43,     0,
      74,    45,    46,     0,     2,     4,     5,     7,     6,     0,
       0,     0,    61,     0,     0,     0,     0,    62,     0,    44,
       0,     0,    90,     0,     0,    22,    21,    14,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    75,    85,     0,     3,    29,    17,    16,     0,
      27,     0,     0,    23,    18,    19,     8,     9,    10,    11,
      12,    13,    20,    64,    72,     0,    74,    65,    71,     0,
      63,     0,    54,    53,    51,    52,    55,    56,    47,     0,
       0,     0,    31,    30,     0,     0,     0,    28,     0,     0,
      68,     0,    76,    67,     0,     0,     0,    50,    49,     0,
      88,    84,    86,    25,     0,    70,     0,    24,    73,    66,
       0,    58,    69,    74,    57,     0,    33,    32,    26,     0,
      89,     0,    81,    77,    78,    87,    82,    83,    80,     0,
      79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   133,   134,     8,     9,    10,    11,    12,    13,    90,
      91,   127,   147,   135,    25,    56,    57,   116,   117,   118,
     119,   143,   140,    62,   161,   173,   174,   178,    15,    94,
     151,    16,    17
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -134
static const yytype_int16 yypact[] =
{
      82,   -29,   -34,   -28,   -22,    -7,    24,     5,    47,   -26,
      -6,    20,    21,    22,    23,    38,    40,    44,    95,   121,
     122,   123,   125,   130,  -134,    60,    74,   135,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,    68,
      72,  -134,  -134,    75,    83,  -134,  -134,  -134,  -134,   102,
     102,   102,  -134,   102,   102,   225,   -38,  -134,    80,  -134,
     163,   102,  -134,   167,   168,   140,   140,  -134,  -134,   166,
     102,   102,    98,   131,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   172,    -2,   102,   167,    90,
     -54,  -134,   263,  -134,   -35,  -134,  -134,   279,   293,     1,
    -134,   106,   244,   312,   200,   191,    66,    66,   154,   154,
     154,   154,  -134,  -134,   161,   137,   -56,  -134,  -134,   195,
    -134,   -33,  -134,  -134,  -134,  -134,  -134,   155,  -134,   163,
     -51,   226,  -134,   263,   -30,   156,     1,  -134,   102,   227,
    -134,    -2,   174,  -134,   229,   -51,   102,  -134,  -134,   165,
    -134,  -134,  -134,  -134,    79,  -134,     4,   303,  -134,  -134,
     198,  -134,  -134,    72,   263,    97,  -134,   263,  -134,   102,
    -134,     6,   184,   178,  -134,  -134,  -134,  -134,  -134,   102,
    -134
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,   -25,  -133,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
     124,  -134,  -134,   255,  -134,  -134,   183,  -134,   149,  -134,
     -70,  -134,  -134,   -93,  -134,  -134,    93,  -134,  -134,   188,
     147,  -134,  -134
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,   114,   100,   156,    44,    45,    46,    47,    48,    86,
      18,    21,    61,    20,    49,    50,   149,   141,   128,   129,
     115,    51,    24,   142,    65,    66,    67,    26,    68,    69,
      23,   137,   171,    19,    22,    87,    92,   130,   131,   145,
     131,   132,   153,   154,    27,    97,    98,    28,    29,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     150,     5,    55,    44,    45,    46,    47,    48,    30,   115,
     170,    53,    54,    49,    50,   150,   168,   154,   175,   154,
      51,    52,    44,    45,    46,    47,    48,    80,    81,    82,
      83,    84,    49,    50,    31,    32,    33,    34,    38,    51,
      44,    45,    46,    47,    48,    44,    45,    46,    47,    48,
      49,    50,    35,   157,    36,    49,    50,    51,    37,   166,
       1,   164,    51,     2,    39,    40,    41,     3,    42,   167,
      53,    54,     4,    43,   122,    58,   123,   132,    59,    60,
      61,   124,     5,   101,   172,   125,    63,     6,     7,    53,
      54,    88,    64,   126,   172,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    89,    53,    54,    99,
      93,    95,    53,    54,    70,   113,    71,   136,    72,    84,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    70,   139,    71,   146,    72,     5,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      78,    79,    80,    81,    82,    83,    84,   176,    77,    78,
      79,    80,    81,    82,    83,    84,   177,   144,   155,   152,
     158,   160,   162,    70,   169,    71,   165,    72,    96,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,   179,    70,   148,    71,    14,    72,    85,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     120,    70,   180,    71,   138,    72,   121,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    71,
     159,    72,   163,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    72,     0,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    76,
      77,    78,    79,    80,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
      25,     3,    72,   136,     3,     4,     5,     6,     7,    47,
      39,    39,    68,    47,    13,    14,    67,    73,    72,    73,
      71,    20,    29,   116,    49,    50,    51,     3,    53,    54,
      52,   101,   165,    62,    62,    73,    61,    72,    73,    72,
      73,    40,    72,    73,    39,    70,    71,     0,    74,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     130,    60,    87,     3,     4,     5,     6,     7,    74,    71,
     163,    70,    71,    13,    14,   145,    72,    73,    72,    73,
      20,    21,     3,     4,     5,     6,     7,    21,    22,    23,
      24,    25,    13,    14,    74,    74,    74,    74,     3,    20,
       3,     4,     5,     6,     7,     3,     4,     5,     6,     7,
      13,    14,    74,   138,    74,    13,    14,    20,    74,    40,
      38,   146,    20,    41,     3,     3,     3,    45,     3,   154,
      70,    71,    50,     3,    44,    61,    46,    40,     3,    71,
      68,    51,    60,    12,   169,    55,    71,    65,    66,    70,
      71,    71,    69,    63,   179,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     3,    70,    71,    71,
       3,     3,    70,    71,     8,     3,    10,    71,    12,    25,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     8,    32,    10,    40,    12,    60,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      19,    20,    21,    22,    23,    24,    25,    33,    18,    19,
      20,    21,    22,    23,    24,    25,    42,    32,    72,     3,
       3,    57,     3,     8,    36,    10,    71,    12,    72,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    73,     8,   129,    10,     0,    12,    32,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      87,     8,   179,    10,    30,    12,    88,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    10,
     141,    12,   145,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    12,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    17,
      18,    19,    20,    21,    22,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    41,    45,    50,    60,    65,    66,    78,    79,
      80,    81,    82,    83,    88,   103,   106,   107,    39,    62,
      47,    39,    62,    52,    29,    89,     3,    39,     0,    74,
      74,    74,    74,    74,    74,    74,    74,    74,     3,     3,
       3,     3,     3,     3,     3,     4,     5,     6,     7,    13,
      14,    20,    21,    70,    71,    76,    90,    91,    61,     3,
      71,    68,    98,    71,    69,    76,    76,    76,    76,    76,
       8,    10,    12,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    32,    47,    73,    71,     3,
      84,    85,    76,     3,   104,     3,    72,    76,    76,    71,
      95,    12,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,     3,     3,    71,    92,    93,    94,    95,
      91,   104,    44,    46,    51,    55,    63,    86,    72,    73,
      72,    73,    40,    76,    77,    88,    71,    95,    30,    32,
      97,    73,    98,    96,    32,    72,    40,    87,    85,    67,
      95,   105,     3,    72,    73,    72,    77,    76,     3,    93,
      57,    99,     3,   105,    76,    71,    40,    76,    72,    36,
      98,    77,    76,   100,   101,    72,    33,    42,   102,    73,
     101
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
      case 3: /* "NAME" */
#line 129 "mysql.ypp"
	{ delete[] (char*)((yyvaluep->strval)); };
#line 1354 "mysql.tab.cpp"
	break;
      case 4: /* "STRING" */
#line 129 "mysql.ypp"
	{ delete[] (char*)((yyvaluep->strval)); };
#line 1359 "mysql.tab.cpp"
	break;

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



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
        case 2:
#line 135 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_NAME((yyvsp[(1) - (1)].strval)); ;}
    break;

  case 3:
#line 136 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_NAMEFIELD((yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 4:
#line 137 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_STRING((yyvsp[(1) - (1)].strval)); ;}
    break;

  case 5:
#line 138 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_INTNUM((yyvsp[(1) - (1)].intval)); ;}
    break;

  case 6:
#line 140 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_APPROXNUM((yyvsp[(1) - (1)].floatval)); ;}
    break;

  case 7:
#line 142 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_BOOLEAN((yyvsp[(1) - (1)].intval)); ;}
    break;

  case 8:
#line 145 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_ADD, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 9:
#line 146 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_SUB, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 10:
#line 147 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_MUL, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 11:
#line 148 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_DIV, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 12:
#line 149 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_MOD, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 13:
#line 150 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_MOD, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 14:
#line 151 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_NEG, (yyvsp[(2) - (2)].expr_tree), NULL); ;}
    break;

  case 15:
#line 152 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_BITFLIP, (yyvsp[(2) - (2)].expr_tree), NULL); ;}
    break;

  case 16:
#line 153 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_LOGAND, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 17:
#line 154 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_LOGOR, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 18:
#line 156 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_BITOR, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 19:
#line 157 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_BITAND, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 20:
#line 158 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_BITXOR, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 21:
#line 159 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_LOGNOT, (yyvsp[(2) - (2)].expr_tree), NULL); ;}
    break;

  case 22:
#line 160 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_OP(OP_LOGNOT, (yyvsp[(2) - (2)].expr_tree), NULL); ;}
    break;

  case 23:
#line 161 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_CMP((yyvsp[(2) - (3)].cmptok), (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 24:
#line 164 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_RANGE((yyvsp[(1) - (5)].expr_tree), (yyvsp[(3) - (5)].expr_tree), (yyvsp[(5) - (5)].expr_tree)); ;}
    break;

  case 25:
#line 165 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_LIST(true, (yyvsp[(1) - (5)].expr_tree), (yyvsp[(4) - (5)].list)); ;}
    break;

  case 26:
#line 166 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_LIST(false, (yyvsp[(1) - (6)].expr_tree), (yyvsp[(5) - (6)].list)); ;}
    break;

  case 27:
#line 167 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_SUBQ(true, (yyvsp[(1) - (3)].expr_tree), (yyvsp[(3) - (3)].sel_stmt)); ;}
    break;

  case 28:
#line 168 "mysql.ypp"
    { (yyval.expr_tree) = newEXPR_SUBQ(false, (yyvsp[(1) - (4)].expr_tree), (yyvsp[(4) - (4)].sel_stmt)); ;}
    break;

  case 29:
#line 170 "mysql.ypp"
    { (yyval.expr_tree) = (yyvsp[(2) - (3)].expr_tree); ;}
    break;

  case 30:
#line 173 "mysql.ypp"
    { (yyval.list) = new EXPR_LIST; (yyval.list)->expr = (yyvsp[(1) - (1)].expr_tree); (yyval.list)->next = NULL; ;}
    break;

  case 31:
#line 174 "mysql.ypp"
    { (yyval.list) = new EXPR_LIST; (yyval.list)->expr = NULL; (yyval.list)->next = NULL; ;}
    break;

  case 32:
#line 175 "mysql.ypp"
    { (yyval.list) = (yyvsp[(1) - (3)].list); expr_list_append((yyval.list), (yyvsp[(3) - (3)].expr_tree)); ;}
    break;

  case 33:
#line 176 "mysql.ypp"
    { (yyval.list) = (yyvsp[(1) - (3)].list); expr_list_append((yyval.list), NULL); ;}
    break;

  case 34:
#line 185 "mysql.ypp"
    { ast = (yyvsp[(1) - (2)].stmt_ast); ;}
    break;

  case 35:
#line 186 "mysql.ypp"
    { ast = (yyvsp[(1) - (2)].stmt_ast); ;}
    break;

  case 36:
#line 187 "mysql.ypp"
    { ast = (yyvsp[(1) - (2)].stmt_ast); ;}
    break;

  case 37:
#line 188 "mysql.ypp"
    { ast = (STMT_AST *)(yyvsp[(1) - (2)].table_op); ;}
    break;

  case 38:
#line 189 "mysql.ypp"
    { ast = (STMT_AST *)(yyvsp[(1) - (2)].stmt_ast); ;}
    break;

  case 39:
#line 190 "mysql.ypp"
    { ast = (STMT_AST *)(yyvsp[(1) - (2)].sel_stmt); ;}
    break;

  case 40:
#line 191 "mysql.ypp"
    { ast = (STMT_AST *)(yyvsp[(1) - (2)].table_op); ;}
    break;

  case 41:
#line 192 "mysql.ypp"
    { ast = (STMT_AST *)(yyvsp[(1) - (2)].table_op); ;}
    break;

  case 42:
#line 193 "mysql.ypp"
    { ast = (STMT_AST *)(yyvsp[(1) - (2)].table_op); ;}
    break;

  case 43:
#line 196 "mysql.ypp"
    { (yyval.stmt_ast) = newSTMT_AST(AST_CREATE_DB, (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 44:
#line 199 "mysql.ypp"
    { (yyval.stmt_ast) = newSTMT_AST(AST_USE_DB, (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 45:
#line 202 "mysql.ypp"
    { (yyval.stmt_ast) = newSTMT_AST(AST_DROP_DB, (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 46:
#line 205 "mysql.ypp"
    { (yyval.stmt_ast) = newSTMT_AST(AST_DROP_TABLE, (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 47:
#line 209 "mysql.ypp"
    { (yyval.table_op) = newTABLE_OP(AST_CREATE_TABLE, (yyvsp[(3) - (6)].strval), (yyvsp[(5) - (6)].col_def), NULL, NULL, NULL); ;}
    break;

  case 49:
#line 213 "mysql.ypp"
    { (yyval.col_def) = (yyvsp[(1) - (3)].col_def); col_def_list_append((yyval.col_def), (yyvsp[(3) - (3)].col_def)); ;}
    break;

  case 50:
#line 216 "mysql.ypp"
    { (yyval.col_def) = new COL_DEF_LIST; (yyval.col_def)->name = (yyvsp[(1) - (3)].strval); (yyval.col_def)->type = (yyvsp[(2) - (3)].intval); 
              (yyval.col_def)->attr = (yyvsp[(3) - (3)].intval);
             /* if ($3 & 4)
                $$->reference = ref_table;
             */
              if ((yyvsp[(3) - (3)].intval) & 8)
                (yyval.col_def)->def_val = default_expr;
              (yyval.col_def)->next = NULL;
            ;}
    break;

  case 51:
#line 227 "mysql.ypp"
    { (yyval.intval) = DT_INT; ;}
    break;

  case 52:
#line 228 "mysql.ypp"
    { (yyval.intval) = DT_LONG; ;}
    break;

  case 53:
#line 229 "mysql.ypp"
    { (yyval.intval) = DT_FLOAT; ;}
    break;

  case 54:
#line 230 "mysql.ypp"
    { (yyval.intval) = DT_DOUBLE; ;}
    break;

  case 55:
#line 231 "mysql.ypp"
    { (yyval.intval) = DT_TEXT; ;}
    break;

  case 56:
#line 238 "mysql.ypp"
    { (yyval.intval) = 0; default_expr = NULL; /* ref_table = NULL; */ ;}
    break;

  case 57:
#line 244 "mysql.ypp"
    { (yyval.intval) = 8; default_expr = (yyvsp[(2) - (2)].expr_tree); ;}
    break;

  case 58:
#line 248 "mysql.ypp"
    { (yyval.sel_stmt) = newSELECT(AST_SELECT, (yyvsp[(3) - (7)].select_list), (yyvsp[(5) - (7)].table_ref_list), (yyvsp[(6) - (7)].expr_tree), (yyvsp[(7) - (7)].order)); (yyval.sel_stmt)->option = (yyvsp[(2) - (7)].intval); ;}
    break;

  case 59:
#line 251 "mysql.ypp"
    { (yyval.intval) = 0; ;}
    break;

  case 60:
#line 252 "mysql.ypp"
    { (yyval.intval) = 0; ;}
    break;

  case 61:
#line 256 "mysql.ypp"
    { (yyval.select_list) = new SELECT_LIST; (yyval.select_list)->type = 0; (yyval.select_list)->next = NULL; (yyval.select_list)->alias = NULL; (yyval.select_list)->expr = NULL;;}
    break;

  case 63:
#line 259 "mysql.ypp"
    { (yyval.select_list) = (yyvsp[(1) - (3)].select_list); select_list_append((yyval.select_list), (yyvsp[(3) - (3)].select_list)); ;}
    break;

  case 64:
#line 263 "mysql.ypp"
    { (yyval.select_list) = new SELECT_LIST; (yyval.select_list)->type = 1; (yyval.select_list)->expr = (yyvsp[(1) - (3)].expr_tree); (yyval.select_list)->next = NULL; (yyval.select_list)->alias = (yyvsp[(3) - (3)].strval); ;}
    break;

  case 66:
#line 267 "mysql.ypp"
    { (yyval.table_ref_list) = (yyvsp[(1) - (3)].table_ref_list); ref_list_append((yyval.table_ref_list), (yyvsp[(3) - (3)].table_ref_list)); ;}
    break;

  case 67:
#line 270 "mysql.ypp"
    { (yyval.table_ref_list) = (yyvsp[(1) - (2)].table_ref_list); (yyval.table_ref_list)->join_param = (yyvsp[(2) - (2)].join); ;}
    break;

  case 68:
#line 274 "mysql.ypp"
    { (yyval.table_ref_list) = new struct REF_LIST; (yyval.table_ref_list)->type = 0; 
                  (yyval.table_ref_list)->table.name = (yyvsp[(1) - (2)].strval); (yyval.table_ref_list)->alias = (yyvsp[(2) - (2)].strval); (yyval.table_ref_list)->next = NULL; ;}
    break;

  case 69:
#line 281 "mysql.ypp"
    { (yyval.table_ref_list) = new struct REF_LIST; (yyval.table_ref_list)->type = 2;
                  (yyval.table_ref_list)->table.sub_query = (yyvsp[(1) - (3)].sel_stmt); (yyval.table_ref_list)->alias = (yyvsp[(3) - (3)].strval); (yyval.table_ref_list)->next = NULL;;}
    break;

  case 70:
#line 285 "mysql.ypp"
    { (yyval.sel_stmt) = (yyvsp[(2) - (3)].sel_stmt); ;}
    break;

  case 71:
#line 288 "mysql.ypp"
    { (yyval.join) = NULL; ;}
    break;

  case 72:
#line 298 "mysql.ypp"
    { (yyval.strval) = NULL; ;}
    break;

  case 73:
#line 299 "mysql.ypp"
    { (yyval.strval) = (yyvsp[(2) - (2)].strval); ;}
    break;

  case 74:
#line 302 "mysql.ypp"
    { (yyval.expr_tree) = NULL; ;}
    break;

  case 75:
#line 303 "mysql.ypp"
    { (yyval.expr_tree) = (yyvsp[(2) - (2)].expr_tree); ;}
    break;

  case 76:
#line 306 "mysql.ypp"
    { (yyval.order) = NULL; ;}
    break;

  case 77:
#line 307 "mysql.ypp"
    { (yyval.order) = (yyvsp[(3) - (3)].order); ;}
    break;

  case 79:
#line 312 "mysql.ypp"
    { (yyval.order) = (yyvsp[(1) - (3)].order); order_list_append((yyval.order), (yyvsp[(3) - (3)].order)); ;}
    break;

  case 80:
#line 316 "mysql.ypp"
    { (yyval.order) = new struct ORDER_LIST; (yyval.order)->type = (yyvsp[(2) - (2)].intval); (yyval.order)->expr = (yyvsp[(1) - (2)].expr_tree); (yyval.order)->next = NULL; ;}
    break;

  case 81:
#line 319 "mysql.ypp"
    { (yyval.intval) = 0; ;}
    break;

  case 82:
#line 320 "mysql.ypp"
    { (yyval.intval) = 0; ;}
    break;

  case 83:
#line 321 "mysql.ypp"
    { (yyval.intval) = 1; ;}
    break;

  case 84:
#line 325 "mysql.ypp"
    { (yyval.table_op) = newTABLE_OP(AST_INSERT, (yyvsp[(3) - (7)].strval), NULL, (yyvsp[(5) - (7)].col_ref), (yyvsp[(7) - (7)].ins_src), NULL); ;}
    break;

  case 85:
#line 328 "mysql.ypp"
    { (yyval.col_ref) = new struct COL_LISTING; (yyval.col_ref)->name = (yyvsp[(1) - (1)].strval); (yyval.col_ref)->next = NULL; ;}
    break;

  case 86:
#line 329 "mysql.ypp"
    { (yyval.col_ref) = (yyvsp[(1) - (3)].col_ref); col_list_append((yyval.col_ref), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 87:
#line 333 "mysql.ypp"
    { (yyval.ins_src) = new struct INS_SRC; (yyval.ins_src)->type = 0; (yyval.ins_src)->contents.list = (yyvsp[(3) - (4)].list); ;}
    break;

  case 88:
#line 335 "mysql.ypp"
    { (yyval.ins_src) = new struct INS_SRC; (yyval.ins_src)->type = 1; (yyval.ins_src)->contents.sub_query = (yyvsp[(1) - (1)].sel_stmt); ;}
    break;

  case 89:
#line 348 "mysql.ypp"
    { (yyval.table_op) = newTABLE_OP(AST_UPDATE, (yyvsp[(2) - (8)].strval), NULL, (yyvsp[(5) - (8)].col_ref), (yyvsp[(7) - (8)].ins_src), (yyvsp[(8) - (8)].expr_tree)); ;}
    break;

  case 90:
#line 352 "mysql.ypp"
    { (yyval.table_op) = newTABLE_OP(AST_DELETE, (yyvsp[(3) - (4)].strval), NULL, NULL, NULL, (yyvsp[(4) - (4)].expr_tree)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2104 "mysql.tab.cpp"
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


#line 356 "mysql.ypp"







