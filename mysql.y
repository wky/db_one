 %{
#include "sqlfuncs.h"
#include <stdlib.h>
#include <stdarg.h> 
#include <string.h>
#include "types.h"

#define YYDEBUG 1
struct STMT_AST *ast;
struct EXPR *default_expr;
/*char *ref_table;*/
int yylex();
%}

%error-verbose
%debug

%union {
    long intval;
    double floatval;
    char *strval;
    int cmptok;
    struct EXPR *expr_tree;
    struct STMT_AST *stmt_ast;
    struct TABLE_OP *table_op;
    struct SELECT_STMT *sel_stmt;
    struct SELECT_LIST *select_list;
    struct COL_DEF_LIST *col_def;
    struct ORDER_LIST *order;
    struct REF_LIST *table_ref_list;
    struct JOIN_PARAM *join;
    struct INS_SRC *ins_src;
    struct INS_EXPR_LIST *ins_list;
    struct COL_LISTING *col_ref;
    struct EXPR_LIST *list;
}

/* token with values */
%token <strval> NAME
%token <strval> STRING
%token <intval> INTNUM 
%token <intval> BOOL
%token <floatval> APPROXNUM

%left OR
%left XOR
%left ANDOP
%nonassoc IN LIKE
%left NOT '!'
%left BETWEEN
%left <cmptok> COMPARISON /* = <> < > <= >= <=> */
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%' MOD
%left '^'
%nonassoc UMINUS
%nonassoc BITFLIP

%token ADD
%token ALL
%token AND
%token ANDOP
%token ANY
%token AS
%token ASC
%token AUTO_INCREMENT
%token BEFORE
%token BETWEEN
%token BY
%token CHAR
%token CREATE
%token DATABASE
%token DEFAULT
%token DELETE
%token DESC
%token DISTINCT
%token DOUBLE
%token DROP
%token FLOAT
%token FROM
%token IN
%token INNER
%token INSENSITIVE
%token INSERT
%token INT
%token INTO
%token JOIN
%token KEY
%token LIKE
%token LONG
%token MOD
%token NOT
%token ON
%token OR
%token ORDER
%token PRIMARY
%token REFERENCE
%token SELECT
%token SET
%token TABLE
%token TEXT
%token UNIQUE
%token UPDATE
%token USE
%token VALUES
%token WHERE
%token XOR

%type <expr_tree> expr opt_join_cond opt_where
%type <list> val_list
%type <stmt_ast> stmt create_database_stmt use_database_stmt drop_database_stmt drop_table_stmt
%type <table_op> create_table_stmt insert_stmt update_stmt delete_stmt
%type <sel_stmt> select_stmt table_subquery
%type <intval> data_type select_opt opt_asc_desc opt_attr
%type <col_def> new_col_list create_def
%type <select_list> select_expr select_expr_list
%type <col_ref> column_list
%type <table_ref_list> table_ref ref_list table_factor
%type <join> opt_join
%type <order> opt_orderby order_list col_order
%type <strval> opt_alias
/*
%type <ins_list> insert_val_list insert_val
*/
%type <ins_src> insert_source

%start stmt

%%

/* $accept: stmt_list $end*/

expr: NAME          { $$ = newEXPR_NAME($1); }
    | NAME '.' NAME { $$ = newEXPR_NAMEFIELD($1, $3); }
    | STRING        { $$ = newEXPR_STRING($1); }
    | INTNUM        { $$ = newEXPR_INTNUM($1); }
    /* | '-' INTNUM        { $$ = newEXPR_INTNUM($1); } */
    | APPROXNUM     { $$ = newEXPR_APPROXNUM($1); }
    /* | '-' APPROXNUM     { $$ = newEXPR_APPROXNUM($1); }*/
    | BOOL          { $$ = newEXPR_BOOLEAN($1); }
    ;

expr: expr '+' expr { $$ = newEXPR_OP(OP_ADD, $1, $3); }
    | expr '-' expr { $$ = newEXPR_OP(OP_SUB, $1, $3); }
    | expr '*' expr { $$ = newEXPR_OP(OP_MUL, $1, $3); }
    | expr '/' expr { $$ = newEXPR_OP(OP_DIV, $1, $3); }
    | expr '%' expr { $$ = newEXPR_OP(OP_MOD, $1, $3); }
    | expr MOD expr { $$ = newEXPR_OP(OP_MOD, $1, $3); }
    | '-' expr %prec UMINUS     { $$ = newEXPR_OP(OP_NEG, $2, NULL); }
    | '~' expr %prec BITFLIP    { $$ = newEXPR_OP(OP_BITFLIP, $2, NULL); }
    | expr ANDOP expr           { $$ = newEXPR_OP(OP_LOGAND, $1, $3); }
    | expr OR expr  { $$ = newEXPR_OP(OP_LOGOR, $1, $3); }
    /* | expr XOR expr { $$ = newEXPR_OP(OP_LOGXOR, $1, $3); } */
    | expr '|' expr { $$ = newEXPR_OP(OP_BITOR, $1, $3); }
    | expr '&' expr { $$ = newEXPR_OP(OP_BITAND, $1, $3); }
    | expr '^' expr { $$ = newEXPR_OP(OP_BITXOR, $1, $3); }
    | NOT expr      { $$ = newEXPR_OP(OP_LOGNOT, $2, NULL); }
    | '!' expr      { $$ = newEXPR_OP(OP_LOGNOT, $2, NULL); }
    | expr COMPARISON expr      { $$ = newEXPR_CMP($2, $1, $3); }
    ;

expr: expr BETWEEN expr AND expr %prec BETWEEN  { $$ = newEXPR_RANGE($1, $3, $5); }
    | expr IN '(' val_list ')'          { $$ = newEXPR_LIST(true, $1, $4); }
    | expr NOT IN '(' val_list ')'      { $$ = newEXPR_LIST(false, $1, $5); }
    | expr IN table_subquery       { $$ = newEXPR_SUBQ(true, $1, $3); }
    | expr NOT IN table_subquery   { $$ = newEXPR_SUBQ(false, $1, $4); }
    /* | expr LIKE expr */
    | '(' expr ')'  { $$ = $2; }
    ;

val_list: expr      { $$ = new EXPR_LIST; $$->expr = $1; $$->next = NULL; }
        | DEFAULT   { $$ = new EXPR_LIST; $$->expr = NULL; $$->next = NULL; }
        | val_list ',' expr     { $$ = $1; expr_list_append($$, $3); }
        | val_list ',' DEFAULT  { $$ = $1; expr_list_append($$, NULL); }
        ;

/*
stmt_list: stmt ';' { $$ = $1; }
         | stmt_list stmt ';'
         ;
*/

stmt: create_database_stmt ';'  { ast = $1; }
    | use_database_stmt ';'     { ast = $1; }
    | drop_database_stmt ';'    { ast = $1; }
    | create_table_stmt ';'     { ast = (STMT_AST *)$1; }
    | drop_table_stmt ';'       { ast = (STMT_AST *)$1; }
    | select_stmt ';'           { ast = (STMT_AST *)$1; }
    | insert_stmt ';'           { ast = (STMT_AST *)$1; }
    | update_stmt ';'           { ast = (STMT_AST *)$1; }
    | delete_stmt ';'           { ast = (STMT_AST *)$1; }
    ;

create_database_stmt: CREATE DATABASE NAME  { $$ = newSTMT_AST(AST_CREATE_DB, $3); }
                    ;

use_database_stmt: USE DATABASE NAME        { $$ = newSTMT_AST(AST_USE_DB, $3); }
                 ;

drop_database_stmt: DROP DATABASE NAME      { $$ = newSTMT_AST(AST_DROP_DB, $3); }
                  ;

drop_table_stmt: DROP TABLE NAME            { $$ = newSTMT_AST(AST_DROP_TABLE, $3); }
               ;

create_table_stmt: CREATE TABLE NAME '(' new_col_list ')' 
                { $$ = newTABLE_OP(AST_CREATE_TABLE, $3, $5, NULL, NULL, NULL); }
                 ;

new_col_list: create_def
            | new_col_list ',' create_def   { $$ = $1; col_def_list_append($$, $3); }
            ;
create_def: NAME data_type opt_attr
            { $$ = new COL_DEF_LIST; $$->name = $1; $$->type = $2; 
              $$->attr = $3;
             /* if ($3 & 4)
                $$->reference = ref_table;
             */
              if ($3 & 8)
                $$->def_val = default_expr;
              $$->next = NULL;
            }
          ;

data_type: CHAR     { $$ = DT_CHAR; }
         | INT      { $$ = DT_INT; }
         | LONG     { $$ = DT_LONG; }
         | FLOAT    { $$ = DT_FLOAT; }
         | DOUBLE   { $$ = DT_DOUBLE; }
         | TEXT     { $$ = DT_TEXT; }
         ;
/*
opt_default_len:  empty     { $$ = NAMELEN; }
               | '(' INTNUM ')' { $$ = $2; }
               ;
*/
opt_attr: /* empty */                   { $$ = 0; default_expr = NULL; /* ref_table = NULL; */ }
        /* | opt_attr AUTO_INCREMENT */
        /* | opt_attr UNIQUE KEY           { $$ = $1 | 1; } */
        /*| opt_attr PRIMARY KEY          { $$ = $1 | 3; } */
        /* | opt_attr KEY */
        /* | opt_attr REFERENCE NAME       { $$ = $1 | 4; ref_table = $3; } */
        |  DEFAULT expr         { $$ = 8; default_expr = $2; }
        ;

select_stmt: SELECT select_opt select_expr_list FROM ref_list opt_where opt_orderby
            { $$ = newSELECT(AST_SELECT, $3, $5, $6, $7); $$->option = $2; }
           ;

select_opt: /* empty */ { $$ = 0; }
          | ALL         { $$ = 0; }
          | DISTINCT    { $$ = 1; }
          ;
select_expr_list: '*'   
                { $$ = new SELECT_LIST; $$->type = 0; $$->next = NULL; $$->alias = NULL; $$->expr = NULL;}
                | select_expr 
                | select_expr_list ',' select_expr
                { $$ = $1; select_list_append($$, $3); }
                ;

select_expr: expr opt_alias  
            { $$ = new SELECT_LIST; $$->type = 1; $$->expr = $1; $$->next = NULL; $$->alias = $2; }   
           ;

ref_list: table_ref
        | ref_list ',' table_ref    { $$ = $1; ref_list_append($$, $3); }
        ;

table_ref: table_factor opt_join    { $$ = $1; $$->join_param = $2; }
         ;

table_factor: NAME opt_alias            
                { $$ = new struct REF_LIST; $$->type = 0; 
                  $$->table.name = $1; $$->alias = $2; $$->next = NULL; }
            | NAME '.' NAME opt_alias
                { $$ = new struct REF_LIST; $$->type = 1; 
                  $$->table.name_field = make_name_field($1, $3); $$->alias = $4; $$->next = NULL; }
            | table_subquery AS NAME
                { $$ = new struct REF_LIST; $$->type = 2;
                  $$->table.sub_query = $1; $$->alias = $3; $$->next = NULL;}
            ;

table_subquery: '(' select_stmt ')'     { $$ = $2; }
              ;

opt_join: /* empty */   { $$ = NULL; }
        | INNER JOIN table_factor opt_join_cond
        { $$ = new struct JOIN_PARAM; $$->join_cond = $4; $$->join_with = $3; }
        ;
opt_join_cond: /* empty */  { $$ = NULL; }
             | ON expr      { $$ = $2; }
             ;
opt_alias: /* empty */  { $$ = NULL; }
         | AS NAME      { $$ = $2; }
         ;

opt_where: /* empty */  { $$ = NULL; }
         | WHERE expr   { $$ = $2; }
         ;

opt_orderby: /* empty */            { $$ = NULL; }
           | ORDER BY order_list    { $$ = $3; }
           ;

order_list: col_order
          | order_list ',' col_order
          { $$ = $1; order_list_append($$, $3); }
          ;

col_order: expr opt_asc_desc
        { $$ = new struct ORDER_LIST; $$->type = $2; $$->expr = $1; $$->next = NULL; }
         ;

opt_asc_desc: /* empty */   { $$ = 0; }
            | ASC           { $$ = 0; }
            | DESC          { $$ = 1; }
            ;

insert_stmt: INSERT INTO NAME '(' column_list ')' insert_source
            { $$ = newTABLE_OP(AST_INSERT, $3, NULL, $5, $7, NULL); }
           ;

column_list: NAME   { $$ = new struct COL_LISTING; $$->name = $1; $$->next = NULL; }
           | column_list ',' NAME { $$ = $1; col_list_append($$, $3); }
           ;

insert_source: VALUES '(' val_list ')'   
                { $$ = new struct INS_SRC; $$->type = 0; $$->contents.list = $3; }
             | table_subquery
                { $$ = new struct INS_SRC; $$->type = 1; $$->contents.sub_query = $1; }
             ;
/*
insert_val_list: insert_val
               | insert_val_list ',' insert_val
               { $$ = $1; insert_list_append($$, $3); }
               ;
insert_val: DEFAULT     { $$ = new struct INS_EXPR_LIST; $$->type = 0; $$->next = NULL; }
          | expr        { $$ = new struct INS_EXPR_LIST; $$->type = 1; $$->expr = $1; $$->next = NULL; }
          ;
*/

update_stmt: UPDATE NAME SET '(' column_list ')' insert_source opt_where
            { $$ = newTABLE_OP(AST_UPDATE, $2, NULL, $5, $7, $8); }
           ;

delete_stmt: DELETE FROM NAME opt_where
            { $$ = newTABLE_OP(AST_DELETE, $3, NULL, NULL, NULL, $4); }
           ; 


%%





