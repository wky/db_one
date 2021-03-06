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
extern Database *eval_db;
DatabaseOne::DatabaseOne(){
    this->current_db = NULL;
}

DatabaseOne::~DatabaseOne(){
    this->shutdown();
    yylex_destroy();
}

bool DatabaseOne::init(){
    return true;
}

QueryResult *DatabaseOne::run_query(char * sql){
    int parse_ret;
    QueryResult *res = NULL;
    /* yydebug = 1;*/
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
    int ret_code = NOERR;
    struct TABLE_OP *table_op = (struct TABLE_OP *)ast;
    Table *select_res;
    switch (ast->type){
        case AST_CREATE_DB:
            if (db.find(std::string(ast->name)) == db.end()){
                Database *d = new Database(ast->name, this);
                db.insert(std::pair<std::string, Database*>(std::string(ast->name), d));
                sprintf(sql, "Database \"%s\" created.", ast->name);
                res = new QueryResult(NOERR, sql);
                this->current_db = d;
                eval_db = d;
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
                this->current_db = (*it).second;
                eval_db = (*it).second;
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
                ((*it).second)->drop();
                delete (*it).second;
                eval_db = NULL;
                this->current_db = NULL;
                db.erase(it);
                sprintf(sql, "Database \"%s\" dropped.", ast->name);
                res = new QueryResult(NOERR, sql);
            }
            break;
        case AST_DROP_TABLE:
            if (this->current_db == NULL){
                sprintf(sql, "In Which Database?");
                res = new QueryResult(ENOSELDB, sql);
                break;
            }
            ret_code = this->current_db->drop_table(ast->name, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_CREATE_TABLE:
            if (this->current_db == NULL){
                sprintf(sql, "In Which Database?");
                res = new QueryResult(ENOSELDB, sql);
                break;
            }
            ret_code = this->current_db->create_table(table_op->name, table_op->columns.definition, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_INSERT:
            if (this->current_db == NULL){
                sprintf(sql, "In Which Database?");
                res = new QueryResult(ENOSELDB, sql);
                break;
            }
            if (table_op->src->type == 0)
                ret_code = this->current_db->insert_into(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.list, sql);
            else if (table_op->src->type == 1)
                ret_code = this->current_db->insert_into(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.sub_query, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_UPDATE:
            if (this->current_db == NULL){
                sprintf(sql, "In Which Database?");
                res = new QueryResult(ENOSELDB, sql);
                break;
            }
            if (table_op->src->type == 0)
                ret_code = this->current_db->update(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.list, table_op->where, sql);
            else if (table_op->src->type == 1)
                ret_code = this->current_db->update(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.sub_query, table_op->where, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_DELETE:
            if (this->current_db == NULL){
                sprintf(sql, "In Which Database?");
                res = new QueryResult(ENOSELDB, sql);
                break;
            }
            ret_code = this->current_db->delete_from(table_op->name, table_op->where, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_SELECT:
            if (this->current_db == NULL){
                sprintf(sql, "In Which Database?");
                res = new QueryResult(ENOSELDB, sql);
                break;
            }
            ret_code = this->current_db->run_select((struct SELECT_STMT *)ast, &select_res, sql);
            res = new QueryResult(ret_code, sql, select_res);
            break;
        default:
            break;
    }
    free_ast(ast);
    return res;
}

bool DatabaseOne::shutdown(){
    std::map<std::string, Database*>::iterator it = db.begin();
    while (it != db.end()){
        delete (*it).second;
        it++;
    }
    db.clear();
    return true;
}
