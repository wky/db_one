#ifndef __DATABASE__
#define __DATABASE__
#include "table.h"
#include "db_one.h"
#include <string>
#include <map>
class DatabaseOne;
class Table;
class Database
{
private:
    DatabaseOne *dbms;
    std::string db_name;
    std::map<std::string, Table*> tables;
public:
    Database(const char *, DatabaseOne *);
    const char *name() const;
    DatabaseOne *db_one();
    void drop();
    int drop_table(const char *, char *);
    int create_table(const char *, struct COL_DEF_LIST *, char *);
    int insert_into(const char *, struct COL_LISTING *, struct EXPR_LIST *, char *);
    int insert_into(const char *, struct COL_LISTING *, struct SELECT_STMT *, char *);
    int update(const char *, struct COL_LISTING *, struct EXPR_LIST *, struct EXPR *, char *);
    int update(const char *, struct COL_LISTING *, struct SELECT_STMT *, struct EXPR *, char *);
    int delete_from(const char *, struct EXPR *, char *);
    ~Database();
};

#endif