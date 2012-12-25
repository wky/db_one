#ifndef __SQLFUNCS__
#define __SQLFUNCS__

#define CMP_E   0
#define CMP_GE  1
#define CMP_G   2
#define CMP_LE  3
#define CMP_L   4
#define CMP_NE  5

#define OP_ADD      0
#define OP_SUB      1
#define OP_NEG      2
#define OP_MUL      3
#define OP_DIV      4
#define OP_MOD      5
#define OP_BITAND   6
#define OP_BITOR    7
#define OP_BITXOR   8
#define OP_BITFLIP  9
#define OP_LOGAND   10
#define OP_LOGOR    11
#define OP_LOGXOR   12
#define OP_LOGNOT   13

#define AST_UNKNOWN         0
#define AST_CREATE_DB       1
#define AST_USE_DB          2
#define AST_DROP_DB         3
#define AST_DROP_TABLE      4

#define AST_CREATE_TABLE    5
#define AST_INSERT          6
#define AST_UPDATE          7
#define AST_DELETE          8
#define AST_SELECT          9
    
#define EXPR_NAME           10
#define EXPR_NAMEFIELD      11
#define EXPR_STRING         12
#define EXPR_INTNUM         13
#define EXPR_APPROXNUM      14
#define EXPR_BOOLEAN        15
#define EXPR_CMP            16
#define EXPR_OP             17
#define EXPR_IN_RANGE       18
#define EXPR_IN_LIST        19
#define EXPR_NOTIN_LIST     20
#define EXPR_IN_SUB         21
#define EXPR_NOTIN_SUB      22



struct STMT_AST{
    int type;
    char *name;
};

struct TABLE_OP{
    int type;
    char *name;
    union{
        struct COL_DEF_LIST *definition;
        struct COL_LISTING *listing;
    }columns;
    struct INS_SRC *src;
    struct EXPR *where;
};

struct COL_DEF_LIST{
    char *name;
    int type;
    /* unique key   1
       primary key  3
       reference    4
       with default 8  
    */
    int attr;
    char *reference; /* reference on primary key of another table */
    struct EXPR *def_val;
    struct COL_DEF_LIST *next;
};

struct COL_LISTING
{
    char *name;
    struct COL_LISTING *next;
};

struct INS_SRC
{
    /*  list=0/subquery=1 */
    int type;

    union{
        struct EXPR_LIST *list;
        struct SELECT_STMT *sub_query;
    }contents;
};

/*
struct INS_EXPR_LIST
{
     default=0 / expr=1 
    int type;

    struct EXPR *expr;
    struct INS_EXPR_LIST *next;
};
*/

struct SELECT_STMT{
    int type;

    /* all=0/distinct=1 */
    int option;
    
    struct SELECT_LIST *select_list;
    struct REF_LIST *ref_list;
    struct ORDER_LIST *order_list;
    struct EXPR *where;
};
struct SELECT_LIST
{
    /* all = 0/list=1 */
    int type;
    struct EXPR *expr;
    char *alias;
    struct SELECT_LIST *next;
};

struct REF_LIST
{
    /* name=0/name_field=1/subquery=2 */
    int type;
    union{
        char *name;
        char *name_field;
        struct SELECT_STMT *sub_query;
    }table;
    char *alias;
    struct JOIN_PARAM *join_param;
    struct REF_LIST *next;
};

struct JOIN_PARAM{
    struct REF_LIST *join_with;
    struct EXPR *join_cond;
};

struct ORDER_LIST
{
    /* asc = 0/desc = 1 */
    int type;
    struct EXPR *expr;
    struct ORDER_LIST *next;
};

struct EXPR{
    int type;
    union{
        char *name;
        char *name_field;
        char *str;
        long intval;
        double floatval;
        bool boolval;
        int cmptok;
        int optok;
        struct EXPR *test;
    }self;
    union{
        struct EXPR *real_child[2];
        struct EXPR *range[2];
        struct EXPR_LIST *list;
        struct SELECT_STMT *sub_query;
    }child;
};
struct EXPR_LIST
{
    struct EXPR *expr;
    struct EXPR_LIST *next;
};

struct EXPR *newEXPR_NAME(char *);
struct EXPR *newEXPR_NAMEFIELD(char *, char *);
struct EXPR *newEXPR_STRING(char *);
struct EXPR *newEXPR_INTNUM(long);
struct EXPR *newEXPR_APPROXNUM(double);
struct EXPR *newEXPR_BOOLEAN(bool);
struct EXPR *newEXPR_CMP(int, struct EXPR *, struct EXPR *);
struct EXPR *newEXPR_OP(int, struct EXPR *, struct EXPR *);
struct EXPR *newEXPR_RANGE(struct EXPR *, struct EXPR *, struct EXPR *);
struct EXPR *newEXPR_SUBQ(bool, struct EXPR *, struct SELECT_STMT *);
struct EXPR *newEXPR_LIST(bool, struct EXPR *, struct EXPR_LIST *);

struct STMT_AST *newSTMT_AST(int, char *);
struct TABLE_OP *newTABLE_OP(int, char *, struct COL_DEF_LIST *, struct COL_LISTING *, struct INS_SRC *, struct EXPR *);
struct SELECT_STMT*newSELECT(int, struct SELECT_LIST *, struct REF_LIST *, struct EXPR *, struct ORDER_LIST *);

void select_list_append(struct SELECT_LIST *, struct SELECT_LIST *);
void col_list_append(struct COL_LISTING *, char *);
void order_list_append(struct ORDER_LIST *, struct ORDER_LIST *);
void ref_list_append(struct REF_LIST *, struct REF_LIST *);
/* void insert_list_append(struct INS_EXPR_LIST *, struct INS_EXPR_LIST *); */
void expr_list_append(struct EXPR_LIST *, struct EXPR *);
char *make_name_field(char *, char *); /* delete two char*s then allocate new one */
void free_ast(void *);
char *new_strdup(char *, int);
void yyerror(const char*, ...);
extern int yyparse();
#endif
