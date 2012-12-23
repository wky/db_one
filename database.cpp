#include "database.h"
#include "error.h"
Database::Database(const char *name){
    db_name = name;
}
Database::~Database(){

}
const char *Database::name() const{
    return db_name.c_str();
}
void Database::drop(){

}
int Database::drop_table(const char *tbl_name){
    std::map<std::string, Table*>::iterator it;
    it = tables.find(std::string(tbl_name));
    if (it == tables.end())
        return ENOTBL;
    Table *tbl = (*it).second;
    tbl->drop();
    delete tbl;
    return NOERR;
}