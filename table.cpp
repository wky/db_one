#include "table.h"

Table::Table(const char *name, Database *db, 
    std::vector<std::pair<int, std::string> >& cols, std::map<int, void*>& defs)
    : tbl_name(name), assoc_db(db), dbms(db->db_one()), col_list(cols), defaults(defs)
{   
    std::map<int, void*>::iterator it;
    for (int c = 0; c < cols.size(); c++){
        col_map.insert(std::pair<std::string, int>(cols[c].second, c));
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
}
int Table::copy_data(DataUnion *ptr, int col, int dt, void *dat, char *buf){
    int c_dt = col_list[col].first & ~NEED_FREE_MASK;
    void *c_dat = dbms->convert(dat, dt, &c_dt);
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
Table::~Table(){
    if (!defaults.empty())
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
}
