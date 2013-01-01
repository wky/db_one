#ifndef __DBONE__
#define __DBONE__

#include "query_result.h"
#include "database.h"
#include "types.h"
#include <map>
#include <string>

class Database;
class QueryResult;

class DatabaseOne
{
private:
    Database *current_db;
    std::map<std::string, Database*> db;
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
