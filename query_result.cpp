#include "query_result.h"
#include <stdlib.h>
#include <string.h>

QueryResult::QueryResult(int error, const char *message){
    err_code = error;
    strncpy(msg, message, MAXLINE);
    tbl = NULL;
}
QueryResult::QueryResult(int error, const char *message, Table *res_tbl){
    err_code = error;
    strncpy(msg, message, MAXLINE);
    tbl = res_tbl;
}

QueryResult::~QueryResult(){
    delete tbl;
}

int QueryResult::result_count(){
    if (tbl != NULL)
        return tbl->rows_cnt();
    else
        return 0;
}

char *QueryResult::message(){
    return this->msg;
}

int QueryResult::get_code(){
    return err_code;
}
    /* number of columns returned */
int QueryResult::column_count(){
    if (tbl != NULL)
        return tbl->cols_cnt();
    else
        return 0;
}
    /* copy name of column to pointer */
const char *QueryResult::column_name(int col){
    return tbl->col_name(col).c_str();
}
    /* data type of column */
int QueryResult::column_type(int col){
    if (tbl != NULL)
        return tbl->col_dt(col);
    else
        return DT_UNKNOWN;
}
    /* iterate through rows */
bool QueryResult::next_row(){
    return tbl->next();
}

bool QueryResult::previous_row(){
    return tbl->prev();
}
    /* write data at column to pointer */
void *QueryResult::get_data(int col){
    return tbl->retrieve_data(col);
}
