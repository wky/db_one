#include "table.h"
Table::Table(const char *name, Database *db, 
    std::vector<std::pair<int, std::string> >& cols, std::map<int, void*>& defs)
{
    tbl_name = name;
    assoc_db = db;
    dbms = db->db_one();
}
Table::~Table(){

}
void Table::drop(){

}