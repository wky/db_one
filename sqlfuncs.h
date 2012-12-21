#ifdef __SQLFUNCS__
#define __SQLFUNCS__
#include <stdarg.h>
#include <stdio.h>
char yy_message[MAXLINE];

/* define token numbers */
enum CompareToken{
    E,
    GE,
    G,
    LE,
    L,
    NE,
};

enum OperatorToken{
    ADD,
    SUB,
    NEG,
    MUL,
    DIV,
    MOD,
    BITAND,
    BITOR,
    BITXOR,
    BITFLIP,
    LOGAND,
    LOGOR,
    LOGXOR,
    LOGNOT
};

enum AST_TYPE{
    UNKNOWN = 0,
    CREATE_DB,
    USE_DB,
    DROP_DB,
    DROP_TABLE,

    CREATE_TABLE,
    INSERT,
    UPDATE,
    DELETE,
    SELECT,
    
    NAME = 101,
    NAMEFIELD,
    STRING,
    INTNUM,
    APPROXNUM,
    BOOLEAN,
    CMP,
    OP,
    IN_RANGE,
    IN_LIST,
    NOTIN_LIST,
    IN_SUB,
    NOTIN_SUB,
    EXPR_LIST
};

struct STMT_AST{
    AST_TYPE type;
    char *name;
};

struct TABLE_OP{
    AST_TYPE type;
    char *name;
    union{
        COL_DEF_LIST *definition;
        COL_LISTING *listing;
    }columns;
    INS_SRC *src;
    EXPR *where;
};

struct COL_DEF_LIST{
    char *name;
    DataType type;
    int opt_len;
    enum{
        PRI_KEY = 3,
        UNIQUE_KEY = 1,
        REFERENCE = 4,
        DEFAULT = 8
    }attr_type;
    union{
        char *reference;
        EXPR *def_val;
    }attr;
    COL_DEF_LIST *next;
};

struct COL_LISTING
{
    char *name;
    COL_LISTING *next;
};

struct INS_SRC
{
    enum{
        EXPR_LIST,
        SUB_QUERY
    }type;
    union{
        SELECT_STMT *sub_query;
        INS_EXPR_LIST *list;
    }contents;
};

struct INS_EXPR_LIST
{
    enum{
        DEFAULT,
        EXPR
    }type;
    EXPR *expr;
    INS_EXPR_LIST *next;
};

struct SELECT_STMT{
    AST_TYPE type;
    enum{
        all,
        distinct
    }option;
    SELECT_LIST *select_list;
    REF_LIST *ref_list;
    ORDER_LIST *order_list
    EXPR *where;

};
struct SELECT_LIST
{
    enum{
        ALL,
        LIST
    }type;
    EXPR *expr;
    char *alias;
    SELECT_LIST *next;
};

struct REF_LIST
{
    enum{
        NAME,
        NAMEFIELD,
        SUB_QUERY
    }type;
    union{
        char *name;
        char *name_field;
        SELECT_STMT *sub_query;
    }table;
    char *alias;
    JOIN_PARAM *join_param;
    REF_LIST *next;
};

struct JOIN_PARAM{
    REF_LIST *join_with;
    EXPR *join_cond;
};

struct ORDER_LIST
{
    enum{
        ASC,
        DESC
    }type;
    EXPR *expr;
    ORDER_LIST *next;
};

struct EXPR{
    AST_TYPE type;
    union{
        char *name;
        char *name_field;
        char *str;
        int intval;
        double floatval;
        bool boolval;
        CompareToken cmptok;
        OperatorToken optok;
        EXPR *list_expr;
    }self;
    union{
        EXPR *real_child[2];
        EXPR *range[2];
        EXPR *list_next;
        SELECT_STMT *sub_query;
    }child;
};

EXPR *newEXPR_NAME(char *);
EXPR *newEXPR_NAMEFIELD(char *, char *);
EXPR *newEXPR_STRING(char *);
EXPR *newEXPR_INTNUM(long);
EXPR *newEXPR_APPROXNUM(long);
EXPR *newEXPR_BOOLEAN(bool);
EXPR *newEXPR_CMP(CompareToken, EXPR *, EXPR *);
EXPR *newEXPR_OP(OperatorToken, EXPR *, EXPR *);
EXPR *newEXPR_RANGE(bool, EXPR *, EXPR *, EXPR *);
EXPR *newEXPR_SUBQ(bool, EXPR *, SELECT_STMT *);
EXPR *newEXPR_LIST(bool, EXPR *, EXPR *);
EXPR *newEXPR_LIST_NODE(EXPR *, EXPR *);

STMT_AST *newSTMT_AST(AST_TYPE, char *);
TABLE_OP *newTABLE_OP(AST_TYPE, char *, COL_DEF_LIST *, COL_LISTING *, INS_SRC *, EXPR *);
SELECT_STMT*newSELECT(AST_TYPE, SELECT_LIST *, REF_LIST *, EXPR *, ORDER_LIST *);

void select_list_append(SELECT_LIST *, SELECT_LIST *);
void col_list_append(COL_LISTING *, char *);
void order_list_append(ORDER_LIST *, ORDER_LIST *);
void ref_list_append(REF_LIST *, REF_LIST *);
void insert_list_append(INS_EXPR_LIST *, INS_EXPR_LIST *);
char *make_name_field(char *, char *); /* delete two char*s then allocate new one */
void free_ast(STMT_AST *);
void yyerror(char*, ...);
#endif