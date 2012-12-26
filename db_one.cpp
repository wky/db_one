#include "db_one.h"
#include "sqlfuncs.h"
#include "mysql.tab.h"
#include "mysql.lex.h"
#include <stdio.h>
#include <stdlib.h>

union tmp_num_val{
    long intval;
    double floatval;
    bool boolval;
    char charval;
};

#define CHECK_CURRENT_DB \
    do {\
        if (current_db == NULL){ \
            sprintf(sql, "In Which Database?"); \
            res = new QueryResult(ENOSELDB, sql); \
            break; \
        }\
    }while(0)

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
    struct TABLE_OP *table_op = (struct TABLE_OP *)ast;
    switch (ast->type){
        case AST_CREATE_DB:
            if (db.find(std::string(ast->name)) == db.end()){
                Database *d = new Database(ast->name, this);
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
            CHECK_CURRENT_DB;
            ret_code = current_db->drop_table(ast->name, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_CREATE_TABLE:
            CHECK_CURRENT_DB;
            ret_code = current_db->create_table(table_op->name, table_op->columns.definition, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_INSERT:
            CHECK_CURRENT_DB;
            if (table_op->src->type == 0)
                ret_code = current_db->insert_into(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.list, sql);
            else if (table_op->src->type == 1)
                ret_code = current_db->insert_into(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.sub_query, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_UPDATE:
            CHECK_CURRENT_DB;
            if (table_op->src->type == 0)
                ret_code = current_db->update(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.list, table_op->where, sql);
            else if (table_op->src->type == 1)
                ret_code = current_db->update(table_op->name, table_op->columns.listing, 
                    table_op->src->contents.sub_query, table_op->where, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_DELETE:
            CHECK_CURRENT_DB;
            ret_code = current_db->delete_from(table_op->name, table_op->where, sql);
            res = new QueryResult(ret_code, sql);
            break;
        case AST_SELECT:
            CHECK_CURRENT_DB;
            res = this->run_select((struct SELECT_STMT *)ast);
            break;
        default:
            break;
    }
    free_ast(ast);
    return res;
}
QueryResult *DatabaseOne::run_select(struct SELECT_STMT *select){
    return new QueryResult(ENOIMPL, "not implemented.");
}
void *DatabaseOne::eval_static_ast(struct EXPR *expr, int *type_ptr){
    switch (expr->type){
        case EXPR_NAME:
        case EXPR_NAMEFIELD:
        case EXPR_STRING:
            *type_ptr = DT_TEXT;
            return expr->self.name;
        case EXPR_INTNUM:
            *type_ptr = DT_LONG;
            return &(expr->self.intval);
        case EXPR_APPROXNUM:
            *type_ptr = DT_DOUBLE;
            return &(expr->self.floatval);
        case EXPR_BOOLEAN:
            *type_ptr = DT_BOOL;
            return &(expr->self.boolval);
        case EXPR_OP:
            break;
        default:
            *type_ptr = DT_UNKNOWN;
            return NULL;
    }
    int l_type, r_type;
    /* no support for string operations */
    void *l_ptr = eval_static_ast(expr->child.real_child[0], &l_type);
    if (l_type == DT_TEXT || l_ptr == NULL){
        *type_ptr = DT_UNKNOWN;
        return NULL;
    }
    void *r_ptr = NULL;
    if (expr->child.real_child[1]){
        r_ptr = eval_static_ast(expr->child.real_child[0], &r_type);
        if (r_type == DT_TEXT || r_ptr == NULL){
            *type_ptr = DT_UNKNOWN;
            return NULL;
        }
    }
    tmp_num_val *val = new tmp_num_val;
    if (l_type == DT_DOUBLE || r_type == DT_DOUBLE){
        if (l_type == DT_BOOL){
            *type_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(expr->self.optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)l_ptr) && (*(double*)r_ptr != 0.0); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)l_ptr) || (*(double*)r_ptr != 0.0); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    delete val;
            }
        }else if (r_type == DT_BOOL){
            *type_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(expr->self.optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)r_ptr) && (*(double*)l_ptr != 0.0); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)r_ptr) || (*(double*)l_ptr != 0.0); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    delete val;
            }
        }else if (l_type == DT_LONG){
            *type_ptr = DT_DOUBLE | NEED_FREE_MASK;
            switch (expr->self.optok){
                case OP_ADD:
                    val->floatval = (double)(*(long*)l_ptr) + (*(double*)r_ptr); break;
                case OP_SUB:
                    val->floatval = (double)(*(long*)l_ptr) - (*(double*)r_ptr); break;
                case OP_MUL:
                    val->floatval = (double)(*(long*)l_ptr) * (*(double*)r_ptr); break;
                case OP_DIV:
                    val->floatval = (double)(*(long*)l_ptr) / (*(double*)r_ptr); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    delete val;
            }
        }else if (r_type == DT_LONG){
            *type_ptr = DT_DOUBLE | NEED_FREE_MASK;
            switch (expr->self.optok){
                case OP_ADD:
                    val->floatval = (*(double*)l_ptr) + (double)(*(long*)r_ptr); break;
                case OP_SUB:
                    val->floatval = (*(double*)l_ptr) - (double)(*(long*)r_ptr); break;
                case OP_MUL:
                    val->floatval = (*(double*)l_ptr) * (double)(*(long*)r_ptr); break;
                case OP_DIV:
                    val->floatval = (*(double*)l_ptr) / (double)(*(long*)r_ptr); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    delete val;
            }
        }else{
            *type_ptr = DT_DOUBLE | NEED_FREE_MASK;
            switch (expr->self.optok){
                case OP_ADD:
                    val->floatval = (*(double*)l_ptr) + (*(double*)r_ptr); break;
                case OP_SUB:
                    val->floatval = (*(double*)l_ptr) - (*(double*)r_ptr); break;
                case OP_MUL:
                    val->floatval = (*(double*)l_ptr) * (*(double*)r_ptr); break;
                case OP_DIV:
                    val->floatval = (*(double*)l_ptr) / (*(double*)r_ptr); break;
                case OP_NEG:
                    val->floatval = - (*(double*)l_ptr); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    delete val;
            }
        }
    }else if (l_type == DT_LONG || r_type == DT_LONG){
        if (l_type == DT_BOOL){
            *type_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(expr->self.optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)l_ptr) && (*(long*)r_ptr); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)l_ptr) || (*(long*)r_ptr); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    delete val;
            }
        }else if (r_type == DT_BOOL){
            *type_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(expr->self.optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)r_ptr) && (*(long*)l_ptr); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)r_ptr) || (*(long*)l_ptr); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    delete val;
            }
        }else{
            *type_ptr = DT_LONG | NEED_FREE_MASK;
            switch (expr->self.optok){
                case OP_ADD:
                    val->intval = (*(long*)l_ptr) + (*(long*)r_ptr); break;
                case OP_SUB:
                    val->intval = (*(long*)l_ptr) - (*(long*)r_ptr); break;
                case OP_NEG:
                    val->intval = -(*(long*)l_ptr); break;
                case OP_MUL:
                    val->intval = (*(long*)l_ptr) * (*(long*)r_ptr); break;
                case OP_DIV:
                    val->intval = (*(long*)l_ptr) / (*(long*)r_ptr); break;
                case OP_MOD:
                    val->intval = (*(long*)l_ptr) % (*(long*)r_ptr); break;
                case OP_BITAND:
                    val->intval = (*(long*)l_ptr) & (*(long*)r_ptr); break;
                case OP_BITOR:
                    val->intval = (*(long*)l_ptr) | (*(long*)r_ptr); break;
                case OP_BITXOR:
                    val->intval = (*(long*)l_ptr) ^ (*(long*)r_ptr); break;
                case OP_BITFLIP:
                    val->intval = ~(*(long*)l_ptr); break;
                default:
                    *type_ptr = DT_UNKNOWN;
                    break;
            }
            if (*type_ptr == DT_UNKNOWN){
                *type_ptr = DT_BOOL | NEED_FREE_MASK;
                switch (expr->self.optok){
                    case OP_LOGAND:
                        val->boolval = (*(long*)l_ptr) && (*(long*)r_ptr); break;
                    case OP_LOGOR:
                        val->boolval = (*(long*)l_ptr) || (*(long*)r_ptr); break;
                    case OP_LOGNOT:
                        val->boolval = ~(*(long*)l_ptr); break;
                    default:
                        *type_ptr = DT_UNKNOWN;
                        delete val;
                        break;
                }
            }
        }
    }else{
        *type_ptr = DT_BOOL | NEED_FREE_MASK;
        switch(expr->self.optok){
            case OP_LOGAND:
                val->boolval = (*(bool*)l_ptr) && (*(bool*)r_ptr); break;
            case OP_LOGOR:
                val->boolval = (*(bool*)l_ptr) || (*(bool*)r_ptr); break;
            case OP_LOGNOT:
                val->boolval = !(*(bool*)l_ptr); break;
            default:
                *type_ptr = DT_UNKNOWN;
                delete val;
                break;
        }
    }
    if (l_type | NEED_FREE_MASK)
        delete (tmp_num_val*)l_ptr;
    if (r_type | NEED_FREE_MASK)
        delete (tmp_num_val*)r_ptr;
    if (*type_ptr == DT_UNKNOWN)
        return NULL;
    else
        return val;
}
void *DatabaseOne::convert(void *data, int from_type, int *to_type){
    int need_free = from_type & NEED_FREE_MASK;
    from_type &= ~NEED_FREE_MASK;
    tmp_num_val *val;
    void *ptr;
    switch (*to_type){
        case DT_CHAR: 
        switch (from_type){
            case DT_BOOL:   *(char*)data = (*(bool*)data)? 'T': 'F'; break;
            case DT_LONG:   *(char*)data = (char)(*(long*)data); break;
            case DT_DOUBLE: *(char*)data = (char)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; val->charval = ((char*)data)[0];
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_INT:
        case DT_LONG:
        switch (from_type){
            case DT_BOOL:   *(long*)data = (long)(*(bool*)data); break;
            case DT_DOUBLE: *(long*)data = (long)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; *(long*)val = atol((char*)data);  break;
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_FLOAT:
        switch (from_type){
            case DT_BOOL:   *(float*)data = (float)(*(bool*)data); break;
            case DT_LONG:   *(float*)data = (float)(*(long*)data); break;
            case DT_DOUBLE: *(float*)data = (float)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; *(float*)val = (float)atof((char*)data);
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_DOUBLE:
        switch (from_type){
            case DT_BOOL:   *(double*)data = (double)(*(bool*)data); break;
            case DT_LONG:   *(double*)data = (double)(*(long*)data); break;
            case DT_DOUBLE: *(double*)data = (double)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; *(double*)val = atof((char*)data);
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_TEXT:
        switch (from_type){
            case DT_BOOL:   ptr = data; data = new char[6]; strcpy((char*)data, (*(bool*)ptr)?"TRUE":"FALSE");
                            if (need_free) delete (tmp_num_val*)data;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_LONG:   ptr = data; data = new char[SHORTLEN]; sprintf((char*)data, "%ld", *(long*)ptr);
                            if (need_free) delete (tmp_num_val*)data;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_DOUBLE: ptr = data; data = new char[SHORTLEN]; sprintf((char*)data, "%lf", *(double*)ptr);
                            if (need_free) delete (tmp_num_val*)data;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_TEXT:   *to_type |= need_free; break;
        }break;
        case DT_BOOL:
        switch (from_type){
            case DT_LONG:   *(bool*)data = ((*(long*)data) != 0ll); break;
            case DT_DOUBLE: *(bool*)data = ((*(double*)data) != 0.0); break;
            case DT_TEXT:   val = new tmp_num_val; val->boolval = (((char*)data)[0] != '\0');
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        default:
            break;
    }
    return data;
}
void function(EXPR *expr){
    switch(expr->type){
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
            break;
        default:
            break;
    }
}
bool DatabaseOne::shutdown(){
    return true;
}
