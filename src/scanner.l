%{
#include "utilities.h"
#include "symbolTable.h"
#include "syntaxTree.h"
#include "y.tab.h"
extern int errorCount;
%}

%option yylineno

identifier		[a-zA-Z][a-zA-Z0-9_]*
intConst		[0-9]+
floatConst		[0-9]+\.[0-9]+
charConst		'[\x20-\x26\x28-\x5B\x5D-\x7E]'|'\\n'|'\\0'
strConst		\"[\x20\x21\x23-\x7E]*\"
lineComment		\/\/[^\n]*
wspace			[ \t\n]
catchAll		[\x00-\x7E]

/* Citation: This comment state machine was found in Flex & Bison written by 
*  John Levine, published by O'Reilly. Pages 93 & 94.
*/

%x COMMENT

%%

"/*"				{ BEGIN(COMMENT); }
<COMMENT>"*/"		{ BEGIN(INITIAL); }
<COMMENT>([^*]|\x0A)+|.
<COMMENT><<EOF>>	{ fprintf(stderr, 
							"SYNTAX ERROR: Unexpected EOF inside comment\n");
 					  exit(1);
					}

"char"			return(CHAR);
"int"			return(INT);
"float"			return(FLOAT);
"void"			return(VOID);
"if"			return(IF);
"else"			return(ELSE);
"while"			return(WHILE);
"for"			return(FOR);
"return"		return(RETURN);
"extern"		return(EXTERN);
"=="			return(DBLEQ);
"!="			return(NOTEQ);
"<="			return(LTEQ);
">="			return(GTEQ);
"&&"			return(LOGICAND);
"||"			return(LOGICOR);
";"				return(yytext[0]);
","				return(yytext[0]);
"("				return(yytext[0]);
")"				return(yytext[0]);
"["				return(yytext[0]);
"]"				return(yytext[0]);
"{"				return(yytext[0]);
"}"				return(yytext[0]);
"="				return(yytext[0]);
"+"				return(yytext[0]);
"-"				return(yytext[0]);
"*"				return(yytext[0]);
"/"				return(yytext[0]);
"!"				return(yytext[0]);
"<"				return(yytext[0]);
">"				return(yytext[0]);
{wspace}		;
{lineComment}	;
{identifier}	{ yylval.string = strdup(yytext); } return(ID);
{intConst}		{ yylval.integer = atoi(yytext); } return(INTCON);
{floatConst}	{ yylval.real = atof(yytext); } return(FLOATCON);
{charConst}		{ 
					if (yytext[1] == '\\') {
						if (yytext[2] == 'n')
							yylval.character = '\n';
						else
							yylval.character = '\0';
					} else {
						yylval.character = yytext[1];
					}
				 } return(CHARCON);
{strConst}		{ yylval.string = strdup(yytext); } return(STRCON);
{catchAll}		return(OTHER);

%%
