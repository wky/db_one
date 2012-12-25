#include "table.h"
Table::Table(const char *name, Database *db){
    tbl_name = name;
    assoc_db = db;
    dbms = db->db_one();
}
Table::~Table(){

}
void Table::drop(){

}