#include "database.h"
#include "error.h"
Database::Database(const char *name, DatabaseOne *db_one){
    db_name = name;
    dbms = db_one;
}
Database::~Database(){

}
const char *Database::name() const{
    return db_name.c_str();
}
DatabaseOne *Database::db_one(){
    return dbms;
}
void Database::drop(){
    std::map<std::string, Table*>::iterator it = tables.begin();
    while (it != tables.end()){
        Table *tbl = (*it).second;
        tbl->drop();
        delete tbl;
        it++;
    }
    tables.clear();
}
int Database::drop_table(const char *tbl_name, char *buf){
    std::map<std::string, Table*>::iterator it;
    it = tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".", tbl_name, this->name());
        return ENOTBL;
    }
    Table *tbl = (*it).second;
    tbl->drop();
    delete tbl;
    tables.erase(it);
    sprintf(buf, "Table \"%s\" in Database\"%s\" dropped.", tbl_name, this->name());
    return NOERR;
}

int Database::create_table(const char *name, struct COL_DEF_LIST *def, char *buf){
    std::map<std::string, Table*>::iterator it = tables.find(std::string(name));
    if (it != tables.end()){
        sprintf(buf, "Table \"%s\" exists in Database \"%s\"\n", name, this->name());
        return EDUPTBL;
    }
    struct COL_DEF_LIST *ptr = def;
    int n_col = 0, ret_code = NOERR;
    std::map<int, void*> default_val;/* column -> data */
    std::vector<std::pair<int, std::string> > cols;/* pair<data_type, column_name>*/
    while (ptr){
        if (ptr->attr & 8){
            int dt;
            void *val = dbms->eval_static_ast(ptr->def_val, &dt);
            if (val == NULL){
                sprintf(buf, "Invalid default value for column \"%s\"", ptr->name);
                ret_code = EINVDEF;
                break;
            }
            val = dbms->convert(val, dt, &(ptr->type));
            default_val.insert(std::pair<int, void*>(n_col, val));
        }
        cols.push_back(std::pair<int, std::string>(ptr->type, std::string(ptr->name)));
        n_col++;
    }
    Table *tbl = new Table(name, this, cols, default_val);
    tables.insert(std::pair<std::string, Table*>(std::string(name), tbl));
    sprintf(buf, "Table \"%s\" created.", name);
    return NOERR;
}

int Database::insert_into(const char *tbl_name, struct COL_LISTING *col_list, struct EXPR_LIST *val_list, char *buf){
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}

int Database::insert_into(const char *tbl_name, struct COL_LISTING *col_list, struct SELECT_STMT *sub_query, char *buf){
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}

int Database::update(const char *tbl_name, struct COL_LISTING *col_list, struct EXPR_LIST *val_list, struct EXPR *where, char *buf){
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}
int Database::update(const char *tbl_name, struct COL_LISTING *col_list, struct SELECT_STMT *sub_query, struct EXPR *where, char *buf){
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}
int Database::delete_from(const char *tbl_name, struct EXPR *where, char *buf){
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}
