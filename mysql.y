%{
#include <stdlib.h>
#include <stdarg.h> 
#include <string.h>
void yyerror(char *s, ...);
void emit(char *s, ...);
%}

%union {
    char charval;
    long intval;
    double floatval;
    char *strval;
    OperatorToken optok;
}

/* token with values */
%token <strval> NAME
%token <strval> STRING
%token <intval> INTNUM 
%token <intval> BOOL
%token <floatval> APPROXNUM

/* precedence levels*/
%left OR
%left XOR
%left ANDOP
%nonassoc IN LIKE 
%left NOT '!'
%left BETWEEN
%left <optok> COMPARISON /* = <> < > <= >= <=> */ 
%left '|'
%left '&'
%left <optok> SHIFT /* << >> */
%left '+' '-'
%left '*' '/' '%' MOD
%left '^'
%nonassoc UMINUS

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
%token DATABASES
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
%token OR
%token ORDER
%token PRIMARY
%token REFERENCE
%token SELECT
%token SENSITIVE
%token SET
%token TABLE
%token TEXT
%token UNIQUE
%token UPDATE
%token USE
%token VALUES
%token WHERE
%token XOR

%start stmt_list

%%

$accept: stmt_list $end

expr: NAME
    | NAME '.' NAME
    | STRING
    | INTNUM
    | APPROXNUM
    | BOOL
    ;
expr: expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | expr MOD expr
    | '-' expr %prec UMINUS
    | expr ANDOP expr
    | expr OR expr
    | expr XOR expr
    | expr '|' expr
    | expr '&' expr
    | expr '^' expr
    | expr SHIFT expr
    | NOT expr
    | '!' expr
    | expr COMPARISON expr
    ;
expr: expr BETWEEN expr AND expr %prec BETWEEN
    | expr IN '(' val_list ')'
    | expr NOT IN '(' val_list ')'
    | expr IN '(' select_stmt ')'
    | expr NOT IN '(' select_stmt ')'
    | expr LIKE expr
    ;
val_list: expr
        | expr ',' val_list
        ;

stmt_list: stmt ';'
         | stmt_list stmt ';'
         ;
stmt: create_database_stmt
    | use_database_stmt
    | drop_database_stmt
    | create_table_stmt
    | drop_table_stmt
    | select_stmt
    | insert_stmt
    | updata_stmt
    | delete_stmt
    ;
create_database_stmt: CREATE DATABASE NAME
                    ;

use_database_stmt: USE DATABASE NAME
                 ;

drop_database_stmt: DROP DATABASE NAME
                  ;

create_table_stmt: CREATE TABLE NAME '(' new_col_list ')'
                 ;

new_col_list: create_def
            | new_col_list ',' create_def
            ;
create_def: NAME data_type opt_attr
          ;

data_type: CHAR
         | INT
         | LONG
         | FLOAT
         | DOUBLE
         | TEXT opt_default_len
         ;
opt_default_len: /* empty */
               | '(' INTNUM ')'
               ;

opt_attr: /* empty */
        | opt_attr DEFAULT expr
        | opt_attr AUTO_INCREMENT
        | opt_attr UNIQUE KEY
        | opt_attr PRIMARY KEY
        | opt_attr KEY
        | opt_attr REFERENCE NAME
        ;

drop_table_stmt: DROP TABLE NAME
               ;

select_stmt: SELECT select_opt select_expr_list FROM ref_list opt_where opt_orderby
           ;

select_opt: /* empty */
          | ALL
          | DISTINCT
          ;
select_expr_list: select_expr
                | select_expr_list ',' select_expr
                | '*'
                ;

select_expr: expr opt_alias
           ;

ref_list: table_ref
        | ref_list ',' table_ref
        ;

table_ref: table_factor opt_join
         ;

table_factor: NAME opt_alias
            | NAME '.' NAME opt_alias
            | table_subquery AS NAME
            ;

table_subquery: '(' select_stmt ')'
              ;

opt_join: INNER JOIN table_factor opt_join_cond
        ;
opt_join_cond: /* empty */
             | ON expr
             ;
opt_alias: /* empty */
         | AS NAME
         ;

opt_where: /* empty */
         | WHERE expr
         ;

opt_orderby: /* empty */
           | ORDER BY order_list
           ;

order_list: col_order
          | order_list ',' col_order
          ;

col_order: col_expr opt_asc_desc
         ;

opt_asc_desc: /* empty */
            | ASC
            | DESC
            ;

insert_stmt: INSERT INTO NAME "(" column_list ")" insert_source
           ;

column_list: NAME
           | column_list ',' NAME
           ;

insert_source: VALUES '(' insert_val_list ')'
             | table_subquery
             ;

insert_val_list: insert_val
               | insert_val_list ',' insert_val
               ;

insert_val: expr
          | DEFAULT
          ;

delete_stmt: DELETE FROM table_factor opt_where
           ; 

update_stmt: UPDATE NAME SET "(" column_list ")" insert_source opt_where
           ;


%%














