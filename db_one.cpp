#include "db_one.h"
#include "sqlfuncs.h"
#include "mysql.tab.h"
#include "mysql.lex.h"
#include <stdio.h>
#include <stdlib.h>

/* dynamically allocated, must be freed */
extern STMT_AST * ast;

extern char my_parse_msg[MAXLINE];
extern int yydebug;

DatabaseOne::DatabaseOne(){
    current_db = NULL;
}

DatabaseOne::~DatabaseOne(){

}

bool DatabaseOne::init(){
    return true;
}

QueryResult *DatabaseOne::run_query(char * sql){
    int parse_ret;
    QueryResult *res;
    //yydebug = 1;
    YY_BUFFER_STATE bp = yy_scan_string(sql);
    yy_switch_to_buffer(bp);
    parse_ret = yyparse();
    yy_delete_buffer(bp);
    if (parse_ret){
        res = new QueryResult(ESYNTAX, my_parse_msg);
        return res;
    }
    if (ast == NULL)
        return NULL;
    std::map<std::string, Database*>::iterator it;
    int ret_code;
    switch (ast->type){
        case AST_CREATE_DB:
            if (db.find(std::string(ast->name)) == db.end()){
                Database *d = new Database(ast->name);
                db.insert(std::pair<std::string, Database*>(std::string(ast->name), d));
                sprintf(sql, "Database \"%s\" created.", ast->name);
                res = new QueryResult(NOERR, sql);
                current_db = d;
            }else{
                sprintf(sql, "Database \"%s\" exists.", ast->name);
                res = new QueryResult(EDUPDB, sql);
            }
            break;
        case AST_USE_DB:
            it = db.find(std::string(ast->name));
            if (it == db.end()){
                sprintf(sql, "Database \"%s\" does not exist.", ast->name);
                res = new QueryResult(ENODB, sql);
            }else{
                current_db = (*it).second;
                sprintf(sql, "Switched to Database \"%s\".", ast->name);
                res = new QueryResult(NOERR, sql);
            }
            break;
        case AST_DROP_DB:
            it = db.find(std::string(ast->name));
            if (it == db.end()){
                sprintf(sql, "Database \"%s\" does not exist.", ast->name);
                res = new QueryResult(ENODB, sql);
            }else{
                current_db = (*it).second;
                current_db->drop();
                delete current_db;
                current_db = NULL;
                db.erase(it);
                sprintf(sql, "Database \"%s\" dropped.", ast->name);
                res = new QueryResult(NOERR, sql);
            }
            break;
        case AST_DROP_TABLE:
            if (current_db == NULL){
                sprintf(sql, "Which Database?");
                res = new QueryResult(ENOSELDB, sql);
                break;
            }
            ret_code = current_db->drop_table(ast->name);
            if (ret_code == NOERR)
                sprintf(sql, "Table \"%s\" in Database\"%s\" dropped.", ast->name, current_db->name());
            else
                sprintf(sql, "Table \"%s\" does not exist in Database\"%s\".", ast->name, current_db->name());
            res = new QueryResult(ret_code, sql);
            break;
        case AST_CREATE_TABLE:
        case AST_INSERT:
        case AST_UPDATE:
        case AST_DELETE:
            res = this->run_table_op((struct TABLE_OP *)ast);
            break;
        case AST_SELECT:
            res = this->run_select((struct SELECT_STMT *)ast);
            break;
        case EXPR_NAME:
        case EXPR_NAMEFIELD:
        case EXPR_STRING:
        case EXPR_INTNUM:
        case EXPR_APPROXNUM:
        case EXPR_BOOLEAN:
        case EXPR_IN_RANGE:
        case EXPR_CMP:
        case EXPR_OP:
        case EXPR_IN_LIST:
        case EXPR_NOTIN_LIST:
        case EXPR_IN_SUB:
        case EXPR_NOTIN_SUB:
        default:
            break;
    }
    free_ast(ast);
    return res;
}
QueryResult *DatabaseOne::run_table_op(struct TABLE_OP *table_op){
    return new QueryResult(ENOIMPL, "not implemented.");
}
QueryResult *DatabaseOne::run_select(struct SELECT_STMT *select){
    return new QueryResult(ENOIMPL, "not implemented.");
}

bool DatabaseOne::shutdown(){
    return true;
}
