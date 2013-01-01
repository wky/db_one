#include "sqlfuncs.h"
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char my_parse_msg[MAXLINE];
extern STMT_AST *ast;
extern int yydebug;

struct EXPR *newEXPR_NAME(char *name){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_NAME;
    expr->self.name = name;
    return expr;
}

struct EXPR *newEXPR_NAMEFIELD(char *name1, char *name2){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_NAMEFIELD;
    expr->self.name_field = make_name_field(name1, name2);
    return expr;
}

struct EXPR *newEXPR_STRING(char *str){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_STRING;
    expr->self.str = str;
    return expr;
}

struct EXPR *newEXPR_INTNUM(long val){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_INTNUM;
    expr->self.intval = val;
    return expr;
}
struct EXPR *newEXPR_APPROXNUM(double val){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_APPROXNUM;
    expr->self.floatval = val;
    return expr;
}
struct EXPR *newEXPR_BOOLEAN(bool val){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_BOOLEAN;
    expr->self.boolval = val;
    return expr;
}
struct EXPR *newEXPR_CMP(int cmp, struct EXPR *l, struct EXPR *r)
{
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_CMP;
    expr->self.cmptok = cmp;
    expr->child.real_child[0] = l;
    expr->child.real_child[1] = r;
    return expr;
}
struct EXPR *newEXPR_OP(int op, struct EXPR *l, struct EXPR *r){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_OP;
    expr->self.optok = op;
    expr->child.real_child[0] = l;
    expr->child.real_child[1] = r;
    return expr;
}
struct EXPR *newEXPR_RANGE(struct EXPR *test, struct EXPR *from, struct EXPR *to){
    struct EXPR *expr = new struct EXPR;
    expr->type = EXPR_IN_RANGE;
    expr->self.test = test;
    expr->child.range[0] = from;
    expr->child.range[1] = to;
    return expr;
}
struct EXPR *newEXPR_SUBQ(bool in, struct EXPR *test, struct SELECT_STMT *sub_query){
    struct EXPR *expr = new struct EXPR;
    expr->type = in?EXPR_IN_SUB:EXPR_NOTIN_SUB;
    expr->self.test = test;
    expr->child.sub_query = sub_query;
    return expr;
}
struct EXPR *newEXPR_LIST(bool in, struct EXPR *test, struct EXPR_LIST *list){
    struct EXPR *expr = new struct EXPR;
    expr->type = in?EXPR_IN_LIST:EXPR_NOTIN_LIST;
    expr->self.test = test;
    expr->child.list = list;
    return expr;
}

struct STMT_AST *newSTMT_AST(int type, char *name){
    struct STMT_AST *ast = new struct STMT_AST;
    ast->type = type;
    ast->name = name;
    return ast;
}

struct TABLE_OP *newTABLE_OP(int type, char *name, struct COL_DEF_LIST *def,
    struct COL_LISTING *list, struct INS_SRC *src, struct EXPR *where)
{
    struct TABLE_OP *ast = new struct TABLE_OP;
    ast->type = type;
    ast->name = name;
    if (type == AST_CREATE_TABLE)
        ast->columns.definition = def;
    else
        ast->columns.listing = list;
    ast->src = src;
    ast->where = where;
    return ast;
}
struct SELECT_STMT*newSELECT(int type, struct SELECT_LIST *list, 
    struct REF_LIST *ref, struct EXPR *where, struct ORDER_LIST *order)
{
    struct SELECT_STMT *ast = new struct SELECT_STMT;
    ast->type = type;
    ast->select_list = list;
    ast->ref_list = ref;
    ast->where = where;
    ast->order_list = order;
    return ast;
}

void select_list_append(struct SELECT_LIST *list, struct SELECT_LIST *next){
    while (list->next != NULL)
        list = list->next;
    list->next = next;
}

void col_list_append(struct COL_LISTING *list, char *name){
    while (list->next != NULL)
        list = list->next;
    list->next = new COL_LISTING;
    list->next->name = name;
    list->next->next = NULL;
}

void order_list_append(struct ORDER_LIST *list, struct ORDER_LIST *next){
    while (list->next != NULL)
        list = list->next;
    list->next = next;
}
void ref_list_append(struct REF_LIST *list, struct REF_LIST *next){
    while (list->next != NULL)
        list = list->next;
    list->next = next;
}
/*
void insert_list_append(struct INS_EXPR_LIST *list, struct INS_EXPR_LIST *next){
    while (list->next != NULL)
        list = list->next;
    list->next = next;
}
*/
void col_def_list_append(struct COL_DEF_LIST *list, struct COL_DEF_LIST *next){
    while (list->next != NULL)
        list = list->next;
    list->next = next;
}
void expr_list_append(struct EXPR_LIST *list, struct EXPR *next){
    while (list->next != NULL)
        list = list->next;
    list->next = new EXPR_LIST;
    list->next->expr = next;
    list->next->next = NULL;
}

char *make_name_field(char *name1, char *name2){
    int len1 = strlen(name1);
    char *str = new char[len1 + strlen(name2) + 2];
    strcpy(str, name1);
    strcpy(str + len1 + 1, name2);
    delete[] name1;
    delete[] name2;
    return str;
}

void free_COL_DEF_LIST(struct COL_DEF_LIST *ptr){
    struct COL_DEF_LIST *next;
    do {
        next = ptr->next;
        delete[] ptr->name;
        /*
        if (ptr->attr | 4)
            delete[] ptr->reference; */
        if (ptr->attr & 8)
            free_ast(ptr->def_val);
        delete ptr;
        ptr = next;
    }while (next);
}
/*
void free_INS_EXPR_LIST(struct INS_EXPR_LIST *ptr){
    struct INS_EXPR_LIST *next;
    do{
        next = ptr->next;
        if (ptr->type)
            free_ast(ptr->expr);
        delete ptr;
        ptr = next;
    } while (next);
}
*/
void free_COL_LISTING(struct COL_LISTING *ptr){
    struct COL_LISTING *next;
    do{
        next = ptr->next;
        delete[] ptr->name;
        delete ptr;
        ptr = next;
    } while (next);   
}
void free_SELECT_LIST(struct SELECT_LIST *ptr){
    struct SELECT_LIST *next;
    do{
        next = ptr->next;
        free_ast(ptr->expr);
        if (ptr->alias)
            delete[] ptr->alias;
        delete ptr;
        ptr = next;
    }while (next);
}
void free_EXPR_LIST(struct EXPR_LIST *ptr){
    struct EXPR_LIST *next;
    do{
        next = ptr->next;
        if (ptr->expr)
            free_ast(ptr->expr);
        delete ptr;
        ptr = next;
    } while (next);   
}
void free_ORDER_LIST(struct ORDER_LIST *ptr){
    struct ORDER_LIST *next;
    do{
        next = ptr->next;
        free_ast(ptr->expr);
        delete ptr;
        ptr = next;
    } while (next);   
}
void free_REF_LIST(struct REF_LIST *ptr){
    struct REF_LIST *next;
    do{
        next = ptr->next;
        if (ptr->type == 2)
            free_ast(ptr->table.sub_query);
        else
            delete[] ptr->table.name;
        if (ptr->join_param){
            free_REF_LIST(ptr->join_param->join_with);
            free_ast(ptr->join_param->join_cond);
            delete ptr->join_param;
        }
        if (ptr->alias)
            delete[] ptr->alias;
        delete ptr;
        ptr = next;
    } while (next);
}

void free_ast(void *node){
    if (node == NULL)
        return;
    struct EXPR *expr = (struct EXPR *)node;
    struct STMT_AST *stmt = (struct STMT_AST *)node;
    struct TABLE_OP *create = (struct TABLE_OP *)node;
    struct TABLE_OP *table_op = (struct TABLE_OP *)node;
    struct SELECT_STMT *select = (struct SELECT_STMT *)node;
    switch (stmt->type){
        case AST_CREATE_DB:
        case AST_USE_DB:
        case AST_DROP_DB:
        case AST_DROP_TABLE:
            delete[] stmt->name;
            delete stmt;
            break;
        case AST_CREATE_TABLE:
            delete[] create->name;
            free_COL_DEF_LIST(create->columns.definition);
            delete create;
            break;
        case AST_INSERT:
        case AST_UPDATE:
        case AST_DELETE:
            delete[] table_op->name;
            if (table_op->src){
                if (table_op->src->type)
                    free_ast(table_op->src->contents.sub_query);
                else
                    free_EXPR_LIST(table_op->src->contents.list);
            }
            if (table_op->where)
                free_ast(table_op->where);
            if (table_op->columns.listing)
                free_COL_LISTING(table_op->columns.listing);
            delete table_op;
            break;
        case AST_SELECT:
            if (select->select_list->type)
                free_SELECT_LIST(select->select_list);
            else
                delete select->select_list;
            free_REF_LIST(select->ref_list);
            if (select->order_list)
                free_ORDER_LIST(select->order_list);
            if (select->where)
                free_ast(select->where);
            break;
        case EXPR_NAME:
        case EXPR_NAMEFIELD:
        case EXPR_STRING:
            delete[] expr->self.name;
            delete expr;
            break;
        case EXPR_INTNUM:
        case EXPR_APPROXNUM:
        case EXPR_BOOLEAN:
            delete expr;
            break;
        case EXPR_IN_RANGE:
            free_ast(expr->self.test);
        case EXPR_CMP:
        case EXPR_OP:
            free_ast(expr->child.real_child[0]);
            if (expr->child.real_child[1])
                free_ast(expr->child.real_child[1]);
            delete expr;
            break;
        case EXPR_IN_LIST:
        case EXPR_NOTIN_LIST:
            free_ast(expr->self.test);
            free_EXPR_LIST(expr->child.list);
            delete expr;
            break;
        case EXPR_IN_SUB:
        case EXPR_NOTIN_SUB:
            free_ast(expr->self.test);
            free_ast(expr->child.sub_query);
            delete expr;
            break;
        default:
            break;
    }
}

static char cmp_names[][16] = {"equal", "greater/equal", "greater",
"less/equal", "less", "not equal", "unknown"};

const char *GET_CMP_NAME(int cmptok){
    if (cmptok >=0 && cmptok <= 5)
        return cmp_names[cmptok];
    else
        return cmp_names[6];
}

static char op_names[][10] = {"add", "sub", "neg", "mul", "div", 
"mod", "bit_and", "bit_or", "bit_xor", "bit_flip", "logic_and", 
"logic_or", "logic_xor", "logic_not", "unknown"};

const char *GET_OP_NAME(int optok){
    if (optok >= 0 && optok < 14)
        return op_names[optok];
    else
        return op_names[14];
}

char *new_strdup(char *str, int len){
    char *new_str = new char[len+1];
    strncpy(new_str, str, len+1);
    return new_str;
}

void yyerror(const char *s, ...)
{
    va_list ap; 
    va_start(ap, s);
    vsprintf(my_parse_msg, s, ap);
}
/*
int main(int argc, char const *argv[])
{
    yydebug = 1;
    printf(" %d \n%s\n", yyparse(), my_parse_msg);
    free_ast(ast);
    return 0;
}
*/