#ifndef __DBONE__
#define __DBONE__
#include "query_result.h"
#include "database.h"
#include "types.h"
#include <map>
#include <string>

class DatabaseOne
{
private:
    Database *current_db;
    std::map<std::string, Database*> db;
    QueryResult *run_select(struct SELECT_STMT *);
    QueryResult *run_table_op(struct TABLE_OP *);
public:
    /* supply config file name */
    DatabaseOne();
    ~DatabaseOne();
    /* initialise */
    bool init();
    /* perform the query */
    QueryResult *run_query(char *);
    /* clean up*/
    bool shutdown();
};
#endif
