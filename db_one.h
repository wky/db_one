#ifndef __DBONE__
#define __DBONE__
#include "query_result.h"
class DatabaseOne
{
public:
    /* supply config file name */
    DatabaseOne(char *);
    ~DatabaseOne();
    /* initialise */
    bool init();
    /* perform the query */
    QueryResult *run_query(char *);
    /* clean up*/
    bool shutdown();
};
#endif
