#ifndef __DATABASE__
#define __DATABASE__

#include "table.h"
#include "db_one.h"
#include "sqlfuncs.h"
#include <string>
#include <map>
#include <vector>

class DatabaseOne;
class Table;

class Database
{
private:
    DatabaseOne *dbms;
    std::string db_name;
    std::map<std::string, Table*> tables;
    int make_table(struct REF_LIST *, Table **, std::string& , bool *, char *);
    void make_cartesian_product(std::vector<std::vector<int> >&, 
        std::vector<int>&, std::vector<std::pair<std::string, Table*> >&, struct EXPR *);
    void iterate_select(std::vector<std::vector<int> >&, std::vector<int>&,
        std::vector<int>&, int, std::vector<std::pair<std::string, Table*> >&, struct EXPR *);
public:
    Database(const char *, DatabaseOne *);
    std::string& name();
    DatabaseOne *db_one();
    void drop();
    int drop_table(const char *, char *);
    int create_table(const char *, struct COL_DEF_LIST *, char *);
    int insert_into(const char *, struct COL_LISTING *, struct EXPR_LIST *, char *);
    int insert_into(const char *, struct COL_LISTING *, struct SELECT_STMT *, char *);
    int update(const char *, struct COL_LISTING *, struct EXPR_LIST *, struct EXPR *, char *);
    int update(const char *, struct COL_LISTING *, struct SELECT_STMT *, struct EXPR *, char *);
    int delete_from(const char *, struct EXPR *, char *);
    int run_select(struct SELECT_STMT *, Table **, char *);
    ~Database();
};

#endif