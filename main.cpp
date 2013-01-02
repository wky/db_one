#include <cstdio>
#include <string.h>
#include "db_one.h"
#include "query_result.h"
#include "display.h"

char sql_buf[MAXLINE];

int main(int argc, char const *argv[])
{
    DatabaseOne *dbms;
    printf("hello world\n");
    dbms = new DatabaseOne();
    dbms->init();
    while (1){
        printf(">");
        memset(sql_buf, 0, sizeof(sql_buf));
        if (fgets(sql_buf, MAXLINE, stdin) == NULL ||
            strncasecmp(sql_buf, "quit", 4) == 0){
            printf("\ngood bye.\n");
            break;
        }
        QueryResult *res = dbms->run_query(sql_buf);
        if (!res){
            printf("fatal error.\n");
            continue;
        }
        
        db_display(res);
        
        delete res;
    }
    dbms->shutdown();
    delete dbms;
    return 0;
}