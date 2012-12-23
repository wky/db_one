#ifndef __DATABASE__
#define __DATABASE__
#include "table.h"
#include <string>
#include <map>

class Database
{
private:
    std::string db_name;
    std::map<std::string, Table*> tables;
public:
    Database(const char *);
    const char *name() const;
    void drop();
    int drop_table(const char *);
    ~Database();
};

#endif