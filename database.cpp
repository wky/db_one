#include "database.h"
#include "error.h"
#include "eval_ast.h"

extern bool treat_as_static;
extern std::map<std::string, Table*> *tbl_ref_map;
extern char *err_buf;
extern Database *current_db;

Database::Database(const char *name, DatabaseOne *db_one){
    db_name = name;
    dbms = db_one;
}
Database::~Database(){
    this->drop();
}
std::string& Database::name(){
    return db_name;
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
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".", tbl_name, this->name().c_str());
        return ENOTBL;
    }
    Table *tbl = (*it).second;
    tbl->drop();
    delete tbl;
    tables.erase(it);
    sprintf(buf, "Table \"%s\" in Database \"%s\" dropped.", tbl_name, this->name().c_str());
    return NOERR;
}
static void free_col_data(std::vector<std::pair<int, void*> >& val_vec){
    for (int i = 0; i < val_vec.size(); i++)
        if (val_vec[i].first & NEED_FREE_MASK){
            if (val_vec[i].first & DT_TEXT)
                delete[] (char*)(val_vec[i].second);
            else
                delete_tmp(val_vec[i].second);
        }
}
int Database::create_table(const char *name, struct COL_DEF_LIST *def, char *buf){
    std::map<std::string, Table*>::iterator it = tables.find(std::string(name));
    if (it != tables.end()){
        sprintf(buf, "Table \"%s\" exists in Database \"%s\"", name, this->name().c_str());
        return EDUPTBL;
    }
    struct COL_DEF_LIST *ptr = def;
    int n_col = 0, ret_code = NOERR;
    std::map<int, void*> default_val;/* column -> data */
    std::vector<std::pair<int, std::string> > cols;/* pair<data_type, column_name>*/
    treat_as_static = true;
    while (ptr){
        if (ptr->attr & 8){
            int dt;
            void *val = eval_ast(ptr->def_val, &dt);
            if (val == NULL){
                sprintf(buf, "Invalid default value for column \"%s\"", ptr->name);
                ret_code = EINVAL;
                break;
            }
            val = dt_convert(val, dt, &(ptr->type));
            default_val.insert(std::pair<int, void*>(n_col, val));
        }
        cols.push_back(std::pair<int, std::string>(ptr->type, std::string(ptr->name)));
        n_col++;
        ptr = ptr->next;
    }
    if (ptr)
        return ret_code;
    Table *tbl = new Table(name, this, cols, default_val);
    tables.insert(std::pair<std::string, Table*>(std::string(name), tbl));
    sprintf(buf, "Table \"%s\" created.", name);
    return NOERR;
}

int Database::insert_into(const char *tbl_name, struct COL_LISTING *col_list, struct EXPR_LIST *val_list, char *buf){
    std::map<std::string, Table*>::iterator it = tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".", tbl_name, this->name().c_str());
        return ENOTBL;
    }
    struct COL_LISTING *col_ptr = col_list;
    struct EXPR_LIST *val_ptr = val_list;
    std::vector<std::string> col_vec;
    std::vector<std::pair<int, void*> > val_vec; /* type, data */
    int ret_code = NOERR;
    treat_as_static = true;
    while (col_ptr != NULL && val_ptr != NULL){
        col_vec.push_back(std::string(col_ptr->name));
        int dt = DT_UNKNOWN;
        void *data = NULL;
        if (val_ptr->expr != NULL){
            data = eval_ast(val_ptr->expr, &dt);
            if (data == NULL){
                sprintf(buf, "Invalid value for column \"%s\"", col_ptr->name);
                ret_code = EINVAL;
                break;
            }
        }
        val_vec.push_back(std::pair<int, void*>(dt, data));
        col_ptr = col_ptr->next;
        val_ptr = val_ptr->next;
    }
    if (ret_code != NOERR){
        free_col_data(val_vec);
        return ret_code;
    }
    if (col_ptr || val_ptr){
        sprintf(buf, "Number of insert elements and number of columns does not match.");
        return ESYNTAX;
    }
    Table *tbl = (*it).second;
    ret_code = tbl->insert(col_vec, val_vec, buf);
    free_col_data(val_vec);
    if (ret_code == NOERR)
        sprintf(buf, "Success.");
    return ret_code;
}

int Database::insert_into(const char *tbl_name, struct COL_LISTING *col_list, struct SELECT_STMT *sub_query, char *buf){
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}

int Database::update(const char *tbl_name, struct COL_LISTING *col_list, struct EXPR_LIST *val_list, struct EXPR *where, char *buf){
    std::map<std::string, Table*>::iterator it = tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".", tbl_name, this->name().c_str());
        return ENOTBL;
    }
    struct COL_LISTING *col_ptr = col_list;
    struct EXPR_LIST *val_ptr = val_list;
    std::vector<std::string> col_vec;
    std::vector<std::pair<int, void*> > val_vec; /* type, data */
    int ret_code = NOERR;
    treat_as_static = true;
    while (col_ptr != NULL && val_ptr != NULL){
        col_vec.push_back(std::string(col_ptr->name));
        int dt = DT_UNKNOWN;
        void *data = NULL;
        if (val_ptr->expr != NULL){
            data = eval_ast(val_ptr->expr, &dt);
            if (data == NULL){
                sprintf(buf, "Invalid value for column \"%s\"", col_ptr->name);
                ret_code = EINVAL;
                break;
            }
        }
        val_vec.push_back(std::pair<int, void*>(dt, data));
        col_ptr = col_ptr->next;
        val_ptr = val_ptr->next;
    }
    if (ret_code != NOERR){
        free_col_data(val_vec);
        return ret_code;
    }
    if (col_ptr || val_ptr){
        sprintf(buf, "Number of insert elements and number of columns does not match.");
        return ESYNTAX;
    }
    Table *tbl = (*it).second;
    ret_code = tbl->update_where(col_vec, val_vec, where, buf);
    free_col_data(val_vec);
    return ret_code;
}
int Database::update(const char *tbl_name, struct COL_LISTING *col_list, struct SELECT_STMT *sub_query, struct EXPR *where, char *buf){
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}
int Database::delete_from(const char *tbl_name, struct EXPR *where, char *buf){
    std::map<std::string, Table*>::iterator it = tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".", tbl_name, this->name().c_str());
        return ENOTBL;
    }
    int del_cnt = (*it).second->delete_where(where);
    sprintf(buf, "In Table \"%s\" %d Row(s) deleted.", tbl_name, del_cnt);
    return NOERR;
}

int Database::run_select(struct SELECT_STMT *select, Table **tbl_ptr_addr, char *buf){
    *tbl_ptr_addr = NULL;
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}
