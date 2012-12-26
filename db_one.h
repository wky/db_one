#ifndef __DBONE__
#define __DBONE__
#include "query_result.h"
#include "database.h"
#include "types.h"
#include <map>
#include <string>
class Database;
class DatabaseOne
{
private:
    Database *current_db;
    std::map<std::string, Database*> db;
    QueryResult *run_select(struct SELECT_STMT *);
public:
    /* supply config file name */
    DatabaseOne();
    ~DatabaseOne();
    /* initialise */
    bool init();
    /* perform the query */
    QueryResult *run_query(char *);
    void *eval_static_ast(struct EXPR *, int *);
    void *convert(void *, int, int*);
    /* clean up*/
    bool shutdown();
};
#endif
