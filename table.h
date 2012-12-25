#ifndef __TABLE__
#define __TABLE__
#include "database.h"
#include "db_one.h"
#include <string>
class Database;
class DatabaseOne;
class Table
{
private:
    DatabaseOne *dbms;
    Database *assoc_db;
    std::string tbl_name;
public:
    Table(const char *, Database *);
    void drop();
    ~Table();
};
#endif