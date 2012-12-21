#include "sqlfuncs.h"
void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    vsprintf(yy_message, s, ap);
}

void free_ast(AST * tree){

}