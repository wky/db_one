%option noyywrap nodefault yylineno case-insensitive
%{
#include "sql.tab.h"
#include "sqlfuncs.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
void yyerror(char *s, ...);
int oldstate;
%}

%x COMMENT 
%s BTWMODE /*BETWEEN <> AND <> */

%%

/* START KEYWORDS */
ADD         { return ADD; }
ALL     { return ALL; }
<BTWMODE>AND    { BEGIN INITIAL; return AND; }
AND     { return ANDOP; }
ANY     { return ANY; }
AS      { return AS; }
ASC     { return ASC; }
AUTO_INCREMENT  { return AUTO_INCREMENT; }
BEFORE  { return BEFORE; }
BETWEEN { BEGIN BTWMODE; return BETWEEN; }
BY      { return BY; }
CHAR(ACTER)?    { return CHAR; }
CREATE  { return CREATE; }
DATABASE    { return DATABASE; }
DATABASES   { return DATABASES; }
DELETE  { return DELETE; }
DESC    { return DESC; }
DISTINCT    { return DISTINCT; }
FLOAT8|DOUBLE   { return DOUBLE; }
DROP    { return DROP; }
FLOAT4? { return FLOAT; }
FROM    { return FROM; }
IN      { return IN; }
INNER   { return INNER; }
INSENSITIVE { return INSENSITIVE; }
INSERT  { return INSERT; }
INT4?|INT(EGER)?    { return INT; }
INTO    { return INTO; }
JOIN    { return JOIN; }
KEY     { return KEY; }
LIKE    { return LIKE; }
INT8|LONG   { return LONG; }
MOD     { return MOD; }
NOT     { return NOT; }
OR      { return OR; }
ORDER   { return ORDER; }
PRIMARY { return PRIMARY; }
REFERENCE  { return REFERENCE; }
SELECT  { return SELECT; }
SENSITIVE   { return SENSITIVE; }
SET     { return SET; }
TABLE   { return TABLE; }
TEXT    { return TEXT; }
UNIQUE  { return UNIQUE; }
UPDATE  { return UPDATE; }
USE     { return USE; }
VALUES? { return VALUES; }
WHERE   { return WHERE; }
XOR     { return XOR; }

/* END KEYWORDS */

/* (DECIMAL) NUMBERS */
-?[0-9]+    { yylval.intval = atol(yytext); return INTNUM; }
-?[0-9]+"."[0-9]*   |
-?"."[0-9]+ |
-?[0-9]+E[-+]?[0-9]+    |
-?[0-9]+"."[0-9]*E[-+]?[0-9]+   |
-?"."[0-9]+E[-+]?[0-9]+     { yylval.floatval = atof(yytext); return APPROXNUM; }

/* BOOLEANS */
TRUE    { yylval.intval = 1; return BOOL; } 
UNKNOWN { yylval.intval = -1; return BOOL; } 
FALSE   { yylval.intval = 0; return BOOL; }

/* STRINGS */
'(\\.|''|[^'\n])*' |
\"(\\.|\"\"|[^"\n])*\"  { yylval.strval = strdup(yytext); return STRING; }


'(\\.|[^'\n])*$     { yyerror("Unterminated string %s", yytext); } 
\"(\\.|[^"\n])*$    { yyerror("Unterminated string %s", yytext); }

/* HEX AND BINARY NUMBERS */
0X[0-9A-F]+     { yylval.intval = strtol(yytext, NULL, 16); return INTNUM; }
0B[01]+         { yylval.intval = strtol(yytext + 2, NULL, 2); return INTNUM; }


/* OPERATORS */
[-+&~|/%*(),.;!]    { return yytext[0]; }
"&&"    { return ANDOP; }
"||"    { return OR; }

"="     { yylval.token = OperatorToken.E; return COMP; }
">="    { yylval.token = OperatorToken.GE; return COMP; }
">"     { yylval.token = OperatorToken.G; return COMP; }
"<="    { yylval.token = OperatorToken.LE; return COMP; }
"<"     { yylval.token = OperatorToken.L; return COMP; }
"!="    { yylval.token = OperatorToken.NE; return COMP; }

"<<"    { yylval.token = OperatorToken.SHL; return SHIFT; }
">>"    { yylval.token = OperatorToken.SHR; return SHIFT; }

/* NAMES */
[A-Za-z][A-Za-z0-9_]*   { yylval.strval = strdup(yytext); return NAME; }
`[^`/\\.\n]+`           { yylval.strval = strdup(yytext+1); yylval.strval[yyleng-2] = 0; return NAME; }
`[^`\n]*$               { yyerror("unterminated quoted name %s", yytext); }

/* COMMENTS */
#.*         ;
"--"[ \t].* ;
"/*"            { oldstate = YY_START; BEGIN COMMENT; }
<COMMENT>"*/"   { BEGIN oldstate; }
<COMMENT>.|\n   ;
<COMMENT><<EOF>>    { yyerror("unclosed comment"); }

[ \t\n]
.       { yyerror("mystery character '%c'", *yytext); }

%%