#ifndef __QUERYRESULT__
#define __QUERYRESULT__
#include "types.h"
#include "error.h"
#include "table.h"
class Table;

class QueryResult
{
private:
    char msg[MAXLINE];
    int err_code;
    Table *tbl;
public:
    QueryResult(int, const char *);
    QueryResult(int, const char *, Table *);
    ~QueryResult();
    int result_count();
    /* copy error message to pointer */
    char *message();
    int get_code();
    /* number of columns returned */
    int column_count();
    const char *column_name(int);
    /* data type of column */
    int column_type(int);
    /* iterate through rows */
    bool next_row();
    bool previous_row();
    void *get_data(int);
};
#endif
