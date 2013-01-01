/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 187 "mysql.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

