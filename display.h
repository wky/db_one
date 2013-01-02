#ifndef _DISPLAY_
#define _DISPLAY_

#define NBLANK (int)(15)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "query_result.h"
#include "types.h"
#include "database.h"

void db_display(QueryResult *);

#endif