#include <cstdio>
#include "db_one.h"
#include "query_result.h"
char sql_buf[MAXLINE];

int main(int argc, char const *argv[])
{
    DatabaseOne *db;
    printf("hello world\n");
    db = new DatabaseOne();
    db->init();
    while (1){
        printf(">");
        fgets(sql_buf, MAXLINE, stdin);
        QueryResult * res = db->run_query(sql_buf);
        if (!res){
            printf("fatal error.\n");
            break;
        }
        res->message(sql_buf);
        printf("%s\n", sql_buf);
        int cnt = res->result_count();
        if (cnt < 0){
            delete res;
            continue;
        }
        delete res;
    }
    db->shutdown();
    delete db;
    return 0;
}