#include "query_result.h"

QueryResult::QueryResult(int error, char *message){
    err_code = error;
    strncpy(msg, message, MAXLINE);
}

QueryResult::~QueryResult(){
    /* nothing */
}

int QueryResult::result_count(){
    return 0;
}
    /* copy error message to pointer */
void QueryResult::message(char * buf){
    strcpy(buf, message);
}
    /* number of columns returned */
int QueryResult::column_count(){
    return 0;
}
    /* copy name of column to pointer */
void QueryResult::column_name(int col, char * name){
    name[0] = '\0';
}
    /* data type of column */
DataType QueryResult::column_type(int col){
    return DataType.UNKNOWN;
}
    /* iterate through rows */
bool QueryResult::next_row(){
    return false;
}

bool QueryResult::previous_row(){
    return false;
}
    /* write data at column to pointer */
void QueryResult::get_data(int col, void* ptr){

}
