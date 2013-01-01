#include "table.h"
#include "eval_ast.h"
#include "error.h"

extern bool treat_as_static;
extern std::map<std::string, Table*> *tbl_ref_map;
extern char *err_buf;

Table::Table(const char *name, Database *db, 
    std::vector<std::pair<int, std::string> >& cols, std::map<int, void*>& defs)
    : tbl_name(name), assoc_db(db), dbms(db->db_one()), col_list(cols), defaults(defs)
{   
    for (int c = 0; c < cols.size(); c++)
        col_map.insert(std::pair<std::string, int>(cols[c].second, c));
    std::map<int, void*>::iterator it = defaults.begin();
    while (it != defaults.end()){
        int dt = col_list[(*it).first].first;
        if ((dt & NEED_FREE_MASK) == 0){
            DataUnion *dat = new DataUnion;
            switch (dt & ~NEED_FREE_MASK){
                case DT_CHAR:   dat->c = *(char*)((*it).second); break;
                case DT_INT:    dat->i = *(int*)((*it).second); break;
                case DT_LONG:   dat->l = *(long*)((*it).second); break;
                case DT_FLOAT:  dat->f = *(float*)((*it).second); break;
                case DT_DOUBLE: dat->d = *(double*)((*it).second); break;
                case DT_TEXT:   dat->s = new_strdup((char*)((*it).second), strlen((char*)((*it).second))); break;
                case DT_BOOL:   dat->b = *(bool*)((*it).second); break;
            }
            col_list[(*it).first].first |= NEED_FREE_MASK;
        }
        it++;
    }
        /*
        printf("Column #%d (%s): data type %s", c, cols[c].second.c_str(), GET_TYPE_NAME(cols[c].first & ~NEED_FREE_MASK));
        it = defs.find(c);
        if (it != defs.end()){
            printf(" with default value ");
            switch (cols[c].first & ~NEED_FREE_MASK){
                case DT_CHAR:   printf("\'%c\'", *(char*)((*it).second)); break;
                case DT_INT:    printf("%d", *(int*)((*it).second)); break;
                case DT_LONG:   printf("%ld", *(long*)((*it).second)); break;
                case DT_FLOAT:  printf("%f", *(float*)((*it).second)); break;
                case DT_DOUBLE: printf("%lf", *(double*)((*it).second)); break;
                case DT_TEXT:   printf("\"%s\"", (char*)((*it).second)); break;
                case DT_BOOL:   printf("%s", (*(bool*)((*it).second))?"true(bool)":"false(bool)"); break;
                default:
                    printf("bad value.");
                    break;
            }
            putchar('\n');
            it++;
        }*/
}
std::string& Table::name(){
    return tbl_name;
}
bool Table::column_exist(std::string& col){
    return col_map.find(col) != col_map.end();
}
bool Table::column_exist(char *col){
    return col_map.find(std::string(col)) != col_map.end();
}
void *Table::retrieve_data(std::string& col, int *dt_ptr){
    std::map<std::string, int>::iterator it = col_map.find(col);
    if (it == col_map.end()){
        *dt_ptr = DT_UNKNOWN;
        return NULL;
    }
    *dt_ptr = col_list[(*it).second].first & ~NEED_FREE_MASK;
    if (*dt_ptr & DT_TEXT)
        return current_row[(*it).second].s;
    return (void *)(current_row + (*it).second);
}
void *Table::retrieve_data(char *col, int *dt_ptr){
    std::map<std::string, int>::iterator it = col_map.find(std::string(col));
    if (it == col_map.end()){
        *dt_ptr = DT_UNKNOWN;
        return NULL;
    }
    *dt_ptr = col_list[(*it).second].first & ~NEED_FREE_MASK;
    if (*dt_ptr & DT_TEXT)
        return current_row[(*it).second].s;
    return (void *)(current_row + (*it).second);
}
int Table::insert(std::vector<std::string>& col, 
    std::vector<std::pair<int, void*> >& val, char *buf)
{
    std::vector<int> ins_col(col.size());
    for (int i = 0; i < col.size(); i++){
        std::map<std::string, int>::iterator it = col_map.find(col[i]);
        if (it == col_map.end()){
            sprintf(buf, "Column \"%s\" does not exist in Table \"%s\"",
                col[i].c_str(), tbl_name.c_str());
            return ENOCOL;
        }
        ins_col[i] = (*it).second;
        int new_dt = col_list[ins_col[i]].first & ~NEED_FREE_MASK;
        void *ptr = dt_convert(val[i].second, val[i].first, &new_dt);
        val[i].first = new_dt;
        val[i].second = ptr;
    }
    DataUnion *new_dat = new DataUnion[col_list.size()];
    for (int i = 0; i < col_list.size(); i++){
        int j;
        for (j = 0; j < ins_col.size(); j++)
            if (ins_col[j] == i)
                break;
        if (j < ins_col.size() && val[j].second)
            this->copy_data(new_dat + i, i, val[j].second);
        else
            this->copy_data(new_dat + i, i);
    }
    data.push_back(new_dat);
    return NOERR;
}
int Table::update_where(std::vector<std::string>& col, 
    std::vector<std::pair<int, void*> >& val, struct EXPR *where, char *buf){
    treat_as_static = false;
    int ret_code = NOERR, modified_cnt = 0;
    tbl_ref_map = new std::map<std::string, Table*>();
    tbl_ref_map->insert(std::pair<std::string, Table*>(this->name(), this));
    err_buf = buf;
    std::vector<int> ins_col(col.size());
    for (int i = 0; i < col.size(); i++){
        std::map<std::string, int>::iterator it = col_map.find(col[i]);
        if (it == col_map.end()){
            sprintf(buf, "Column \"%s\" does not exist in Table \"%s\"",
                col[i].c_str(), tbl_name.c_str());
            return ENOCOL;
        }
        ins_col[i] = (*it).second;
        int new_dt = col_list[ins_col[i]].first & ~NEED_FREE_MASK;
        void *ptr = dt_convert(val[i].second, val[i].first, &new_dt);
        val[i].first = new_dt;
        val[i].second = ptr;
    }
    for (int i = 0; i < data.size(); i++){
        current_row = data[i];
        int dt, dt_bool = DT_BOOL;
        void *cond = eval_ast(where, &dt);
        if (cond == NULL){
            ret_code = EWHERE;
            err_buf = NULL;
            delete tbl_ref_map;
            return ret_code;
        }
        cond = dt_convert(cond, dt, &dt_bool);
        if (*(bool*)cond){
            modified_cnt++;
            for (int j = 0; j < ins_col.size(); j++){
                if (val[j].second)
                    this->copy_data(data[i] + ins_col[j], ins_col[j], val[j].second);
                else
                    this->copy_data(data[i] + ins_col[j], ins_col[j]);
            }
        }
        if (dt_bool & NEED_FREE_MASK)
            delete_tmp(cond);
    }
    err_buf = NULL;
    sprintf(buf, "%d rows modified.", modified_cnt);
    delete tbl_ref_map;
    return NOERR;
}
void Table::copy_data(DataUnion *ptr, int col, void *dat){
    switch (col_list[col].first & ~NEED_FREE_MASK){
        case DT_CHAR:   ptr->c = *(char*)dat; break;
        case DT_INT:    ptr->i = *(int*)dat; break;
        case DT_LONG:   ptr->l = *(long*)dat; break;
        case DT_FLOAT:  ptr->f = *(float*)dat; break;
        case DT_DOUBLE: ptr->d = *(double*)dat; break;
        case DT_TEXT:   ptr->s = new_strdup((char*)dat, strlen((char*)dat)); break;
        case DT_BOOL:   ptr->b = *(bool*)dat; break;
        default:        break;
    }
}
void Table::copy_data(DataUnion *ptr, int col){
    std::map<int, void*>::iterator it = defaults.find(col);
    if (it == defaults.end()){
        ptr->l = 0;
        return;
    }
    this->copy_data(ptr, col, (*it).second);
}
int Table::delete_where(struct EXPR *where){
    int n_left = data.size(), i = 0;
    treat_as_static = false;
    tbl_ref_map = new std::map<std::string, Table*>();
    tbl_ref_map->insert(std::pair<std::string, Table*>(this->name(), this));
    while (i < n_left){
        current_row = data[i];
        int dt, dt_bool = DT_BOOL;
        void *cond = eval_ast(where, &dt);
        if (cond == NULL)
            break;
        cond = dt_convert(cond, dt, &dt_bool);
        if (*(bool*)cond){
            delete[] current_row;
            n_left--;
            data[i] = data[n_left];
        }else
            i++;
        if (dt_bool & NEED_FREE_MASK)
            delete_tmp(cond);
    }
    int del_cnt = data.size() - n_left;
    data.resize(n_left);
    delete tbl_ref_map;
    return del_cnt;
}
Table::~Table(){
    this->drop();
}
void Table::drop(){
    std::map<int, void*>::iterator it = defaults.begin();
    for (; it != defaults.end(); it++)
        if (col_list[(*it).first].first & NEED_FREE_MASK){
            if (col_list[(*it).first].first & DT_TEXT)
                delete[] (char*)((*it).second);
            else 
                delete_tmp((*it).second);
        }
    defaults.clear();
    for (int i = 0; i < data.size(); ++i)
        delete[] data[i];
    data.clear();
}
