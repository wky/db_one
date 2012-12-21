#ifndef __DBONE__
#define __DBONE__
#include "query_result.h"
#include "types.h"
class DatabaseOne
{
private:
    QueryResult *run_ast();
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
