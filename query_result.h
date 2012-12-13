#ifndef __QUERYRESULT__
#define __QUERYRESULT__
#include "types.h"
#include "error.h"
class QueryResult
{
public:
    QueryResult();
    ~QueryResult();
    /* negative return value indicates error */
    int result_count();
    /* copy error message to pointer */
    void error_message(char *);
    /* number of columns returned */
    int column_count();
    /* copy name of column to pointer */
    void column_name(int, char *);
    /* data type of column */
    DataType column_type(int);
    /* iterate through rows */
    bool next_row();
    bool previous_row();
    /* write data at column to pointer */
    void get_data(int, void*);
};
#endif