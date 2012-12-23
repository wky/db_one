%option noyywrap nodefault yylineno case-insensitive
%{
#include "sqlfuncs.h"
#include "mysql.tab.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
void yyerror(char *s, ...);
int oldstate;
%}

%x COMMENT 
%s BTWMODE

%%

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
DEFAULT     { return DEFAULT; }
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
ON      { return ON; }
OR      { return OR; }
ORDER   { return ORDER; }
PRIMARY { return PRIMARY; }
REFERENCE  { return REFERENCE; }
SELECT  { return SELECT; }
SET     { return SET; }
TABLE   { return TABLE; }
TEXT    { return TEXT; }
UNIQUE  { return UNIQUE; }
UPDATE  { return UPDATE; }
USE     { return USE; }
VALUES? { return VALUES; }
WHERE   { return WHERE; }
XOR     { return XOR; }

-?[0-9]+    { yylval.intval = atol(yytext); return INTNUM; }
-?[0-9]+"."[0-9]*   |
-?"."[0-9]+ |
-?[0-9]+E[-+]?[0-9]+    |
-?[0-9]+"."[0-9]*E[-+]?[0-9]+   |
-?"."[0-9]+E[-+]?[0-9]+     { yylval.floatval = atof(yytext); return APPROXNUM; }

TRUE    { yylval.intval = 1; return BOOL; } 
UNKNOWN { yylval.intval = -1; return BOOL; } 
FALSE   { yylval.intval = 0; return BOOL; }

'(\\.|''|[^'\n])*' |
\"(\\.|\"\"|[^"\n])*\"  { yylval.strval = new_strdup(yytext, yyleng); return STRING; }


'(\\.|[^'\n])*$     { yyerror("Unterminated string %s", yytext); } 
\"(\\.|[^"\n])*$    { yyerror("Unterminated string %s", yytext); }

0X[0-9A-F]+     { yylval.intval = strtol(yytext, NULL, 16); return INTNUM; }
0B[01]+         { yylval.intval = strtol(yytext + 2, NULL, 2); return INTNUM; }


[-+&~|/%*(),.;!]    { return yytext[0]; }
"&&"    { return ANDOP; }
"||"    { return OR; }

"="     { yylval.cmptok = CMP_E; return COMPARISON; }
">="    { yylval.cmptok = CMP_GE; return COMPARISON; }
">"     { yylval.cmptok = CMP_G; return COMPARISON; }
"<="    { yylval.cmptok = CMP_LE; return COMPARISON; }
"<"     { yylval.cmptok = CMP_L; return COMPARISON; }
"!="    { yylval.cmptok = CMP_NE; return COMPARISON; }

[A-Za-z][A-Za-z0-9_]*   { yylval.strval = new_strdup(yytext, yyleng); return NAME; }
`[^`/\\.\n]+`           { yylval.strval = new_strdup(yytext+1, yyleng - 1); yylval.strval[yyleng-2] = 0; return NAME; }
`[^`\n]*$               { yyerror("unterminated quoted name %s", yytext); }

#.*         ;
"--"[ \t].* ;
"/*"            { oldstate = YY_START; BEGIN COMMENT; }
<COMMENT>"*/"   { BEGIN oldstate; }
<COMMENT>.|\n   ;
<COMMENT><<EOF>>    { yyerror("unclosed comment"); }

[ \t\n]
.       { yyerror("mystery character '%c'", *yytext); }

%%