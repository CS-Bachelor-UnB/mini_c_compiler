/* A Bison parser, made by GNU Bison 3.4.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 114 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
