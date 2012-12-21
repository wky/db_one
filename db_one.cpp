#include "db_one.h"
#include "sqlfuncs.h"
/* dynamically allocated, must be freed */
extern STMT_AST * ast;

extern char yy_message[MAXLINE];

DatabaseOne::DatabaseOne(){

}

DatabaseOne::~DatabaseOne(){

}

bool DatabaseOne::init(){
    return true;
}

QueryResult *DatabaseOne::run_query(char * sql){
    int parse_ret;
    YY_BUFFER_STATE bp = yy_scan_bytes(sql, MAXLINE);
    yy_switch_to_buffer(bp);
    parse_ret = yyparse();
    yy_delete_buffer(bp);
    if (parse_ret < 0){
        QueryResult *res = new QueryResult(ESYNTAX, yy_message);
        return res;
    }
    return this->run_ast();
}

QueryResult *DatabaseOne::run_ast(){
    fprintf(stderr, "nothing to do in run_ast\n");
    free_ast(ast);
    return NULL;
}

bool DatabaseOne::shutdown(){
    return true;
}
