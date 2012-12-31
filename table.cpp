#include "table.h"
#include "eval_ast.h"

extern bool treat_as_static;
extern std::map<std::string, Table*> *tbl_ref_map;
extern char *err_buf;

Table::Table(const char *name, Database *db, 
    std::vector<std::pair<int, std::string> >& cols, std::map<int, void*>& defs)
    : tbl_name(name), assoc_db(db), dbms(db->db_one()), col_list(cols), defaults(defs)
{   
    for (int c = 0; c < cols.size(); c++){
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
    }putchar('\n');*/
    }
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
    return (void *)(current_row + (*it).second);
}
void *Table::retrieve_data(char *col, int *dt_ptr){
    std::map<std::string, int>::iterator it = col_map.find(std::string(col));
    if (it == col_map.end()){
        *dt_ptr = DT_UNKNOWN;
        return NULL;
    }
    return (void *)(current_row + (*it).second);
}
int Table::insert(std::vector<std::string>& col, 
    std::vector<std::pair<int, void*> >& val, char *buf)
{
    std::vector<int> ins_col(col_list.size());
    for (int i = 0; i < col.size(); i++){
        std::map<std::string, int>::iterator it = col_map.find(col[i]);
        if (it == col_map.end()){
            sprintf(buf, "Column \"%s\" does not exist in Table \"%s\"",
                col[i].c_str(), tbl_name.c_str());
            return ENOCOL;
        }
        ins_col[i] = (*it).second;
    }
    DataUnion *new_dat = new DataUnion[col_list.size()];
    memset(new_dat, 0, sizeof(DataUnion) * col_list.size());
    for (int i = 0; i < ins_col.size(); i++){
        if (val[i].second){
            int ret_code = this->copy_data(new_dat + ins_col[i], ins_col[i],
                val[i].first, val[i].second, buf);
            if (ret_code != NOERR)
                return ret_code;
        }else
            this->copy_data(new_dat + ins_col[i], ins_col[i]);
    }
    data.push_back(new_dat);
    return NOERR;
}
int Table::update_where(std::vector<std::string>& col, 
    std::vector<std::pair<int, void*> >& val, struct EXPR *where, char *buf){
    treat_as_static = false;
    tbl_ref_map = new std::map<std::string, Table*>();
    tbl_ref_map->insert(std::pair<std::string, Table*>(this->name(), this));
    err_buf = buf;
    std::vector<int> ins_col(col_list.size());
    for (int i = 0; i < col.size(); i++){
        std::map<std::string, int>::iterator it = col_map.find(col[i]);
        if (it == col_map.end()){
            sprintf(buf, "Column \"%s\" does not exist in Table \"%s\"",
                col[i].c_str(), tbl_name.c_str());
            return ENOCOL;
        }
        ins_col[i] = (*it).second;
    }
    for (int i = 0; i < data.size(); i++){
        current_row = data[i];
        int dt, dt_bool = DT_BOOL;
        void *cond = eval_ast(where, &dt);
        if (cond == NULL) break;
        cond = dt_convert(cond, dt, &dt_bool);
        if (cond == NULL) break;
        if (*(bool*)cond){
            for (int j = 0; j < ins_col.size(); j++){
                if (val[i].second){
                    int ret_code = this->copy_data(data[i] + ins_col[j], ins_col[j],
                            val[j].first, val[j].second, buf);
                    if (ret_code != NOERR){
                        if (dt_bool & NEED_FREE_MASK)
                            delete_tmp(cond);
                        err_buf = NULL;
                        delete tbl_ref_map;
                        return ret_code;
                    }
                }else
                    this->copy_data(data[i] + ins_col[j], ins_col[j]);
            }
        }
        if (dt_bool & NEED_FREE_MASK)
            delete_tmp(cond);
    }
    err_buf = NULL;
    delete tbl_ref_map;
    return NOERR;
}
int Table::copy_data(DataUnion *ptr, int col, int dt, void *dat, char *buf){
    int c_dt = col_list[col].first & ~NEED_FREE_MASK;
    void *c_dat = dt_convert(dat, dt, &c_dt);
    if (c_dat == NULL){
        sprintf(buf, "Invalid value for column \"%s\"", col_list[col].second.c_str());
        return EINVAL;
    }
    switch (c_dt & ~NEED_FREE_MASK){
        case DT_CHAR:   ptr->c = *(char*)c_dat; break;
        case DT_INT:    ptr->i = *(int*)c_dat; break;
        case DT_LONG:   ptr->l = *(long*)c_dat; break;
        case DT_FLOAT:  ptr->f = *(float*)c_dat; break;
        case DT_DOUBLE: ptr->d = *(double*)c_dat; break;
        case DT_TEXT:   ptr->s = new_strdup((char*)c_dat, strlen((char*)c_dat)); break;
        case DT_BOOL:   ptr->b = *(bool*)c_dat; break;
        default:        break;
    }
    if (c_dt & NEED_FREE_MASK){
        if (c_dt & DT_TEXT)
            delete[] (char*)c_dat;
        else
            delete_tmp(c_dat);
    }
    return NOERR;
}
void Table::copy_data(DataUnion *ptr, int col){
    std::map<int, void*>::iterator it = defaults.find(col);
    if (it == defaults.end()){
        memset(ptr, 0, sizeof(DataUnion));
        return;
    }
    void *def = (*it).second;
    switch (col_list[col].first & ~NEED_FREE_MASK){
        case DT_CHAR:   ptr->c = *(char*)def; break;
        case DT_INT:    ptr->i = *(int*)def; break;
        case DT_LONG:   ptr->l = *(long*)def; break;
        case DT_FLOAT:  ptr->f = *(float*)def; break;
        case DT_DOUBLE: ptr->d = *(double*)def; break;
        case DT_TEXT:   ptr->s = new_strdup((char*)def, strlen((char*)def)); break;
        case DT_BOOL:   ptr->b = *(bool*)def; break;
        default:        break;
    }
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
        if (cond == NULL) break;
        cond = dt_convert(cond, dt, &dt_bool);
        if (cond == NULL) break;
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
