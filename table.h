#ifndef __TABLE__
#define __TABLE__
#include "database.h"
#include "db_one.h"
#include "types.h"
#include <string>
#include <vector>
#include <map>

class Database;
class DatabaseOne;

class Table
{
private:
    std::string tbl_name;
    Database *assoc_db;
    DatabaseOne *dbms;
    std::map<std::string, int> col_map;
    std::vector<std::pair<int, std::string> > col_list;
    std::map<int, void *> defaults;
    std::vector<DataUnion *> data;
    DataUnion *current_row;
    void copy_data(DataUnion *, int, void *);
    void copy_data(DataUnion *, int);
public:
    Table(const char *, Database *, std::vector<std::pair<int, std::string> >&, std::map<int, void*>&);
    int insert(std::vector<std::string>&, std::vector<std::pair<int, void*> >&, char *);
    int delete_where(struct EXPR *);
    int update_where(std::vector<std::string>&, std::vector<std::pair<int, void*> >&, struct EXPR *, char *);
    void drop();
    bool column_exist(std::string&);
    bool column_exist(char *);
    std::string& name();
    void *retrieve_data(std::string&, int *);
    void *retrieve_data(char *, int *);
    ~Table();
};
#endif