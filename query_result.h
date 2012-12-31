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
public:
    QueryResult(int, const char *);
    QueryResult(int, const char *, Table *);
    ~QueryResult();
    /* returns data or not */
    //bool returns_data();
    /* negative return value indicates error */
    int result_count();
    /* copy error message to pointer */
    void message(char *);
    /* number of columns returned */
    int column_count();
    /* copy name of column to pointer */
    void column_name(int, char *);
    /* data type of column */
    int column_type(int);
    /* iterate through rows */
    bool next_row();
    bool previous_row();
    /* write data at column to pointer */
    void get_data(int, void*);
};
#endif
