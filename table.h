#ifndef __TABLE__
#define __TABLE__
#include "database.h"
#include "db_one.h"
#include "types.h"
#include <string>
#include <vector>
#include <list>
#include <map>
class Database;
class DatabaseOne;

class Table
{
private:
    DatabaseOne *dbms;
    Database *assoc_db;
    std::map<std::string, int> col_map;
    std::vector<std::pair<int, std::string> > col_list;
    std::map<int, void*> defaults;
    std::string tbl_name;
    std::list<DataUnion*> data;
public:
    Table(const char *, Database *, std::vector<std::pair<int, std::string> >&, std::map<int, void*>&);
    int insert(std::vector<std::string>&, std::vector<std::pair<int, void*> >&, char *);
    int copy_data(DataUnion *, int, int, void *, char *);
    void copy_data(DataUnion *, int);
    void drop();
    ~Table();
};
#endif