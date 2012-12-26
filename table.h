#ifndef __TABLE__
#define __TABLE__
#include "database.h"
#include "db_one.h"
#include <string>
#include <vector>
#include <map>
class Database;
class DatabaseOne;
class Table
{
private:
    DatabaseOne *dbms;
    Database *assoc_db;
    std::string tbl_name;
public:
    Table(const char *, Database *, std::vector<std::pair<int, std::string> >&, std::map<int, void*>&);
    void drop();
    ~Table();
};
#endif