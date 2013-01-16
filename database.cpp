#include "database.h"
#include "error.h"
#include "eval_ast.h"
#include <algorithm>
#include <cstdio>


extern bool treat_as_static;
extern std::map<std::string, Table*> *tbl_ref_map;
extern char *err_buf;
extern Database *current_db;

class Compare{
private:
    std::vector<struct EXPR*>& cmp_expr;
    std::vector<bool>& order;
    std::vector<std::pair<std::string, Table*> >& tables;
public:
    Compare(std::vector<struct EXPR*>&exprs, std::vector<bool>& asc,
        std::vector<std::pair<std::string, Table*> >& tbl_ref_list)
        :cmp_expr(exprs), order(asc), tables(tbl_ref_list){}

    bool operator()(const std::vector<int>& a, const std::vector<int>& b){
        int i, j, l_dt, r_dt, res_dt;
        void *l_ptr, *r_ptr, *res;
        bool cmp_res = false, cont;
        for (i = 0; i < cmp_expr.size(); i++){
            cont = false;
            for (j = 0; j < tables.size(); j++)
                tables[j].second->set_current_row(a[j]);
            l_ptr = eval_ast(cmp_expr[i], &l_dt);
            if (l_ptr == NULL)
                goto end0;
            for (j = 0; j < tables.size(); j++)
                tables[j].second->set_current_row(b[j]);
            r_ptr = eval_ast(cmp_expr[i], &r_dt);
            if (r_ptr == NULL)
                goto end1;
            res = judge_comparison(order[i]?CMP_G:CMP_L, l_ptr, l_dt,
                r_ptr, r_dt, &res_dt);
            if (res == NULL)
                goto end2;
            if (*(bool*)res){
                cmp_res = true;
                goto end3;
            }
            optional_free(res, res_dt);
            res = judge_comparison(CMP_E, l_ptr, l_dt,
                r_ptr, r_dt, &res_dt);
            if (res == NULL)
                goto end2;
            if (!(*(bool*)res))
                goto end3;
            cont = true;
            end3:
                optional_free(res, res_dt);
            end2:
                optional_free(r_ptr, r_dt);
            end1:
                optional_free(l_ptr, l_dt);
            end0:
                if (!cont)
                    break;
        }
        return cmp_res;
    }
};

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
        delete tbl;
        it++;
    }
    tables.clear();
}

int Database::drop_table(const char *tbl_name, char *buf){
    std::map<std::string, Table*>::iterator it;
    it = tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".",
            tbl_name, this->name().c_str());
        return ENOTBL;
    }
    Table *tbl = (*it).second;
    tbl->drop();
    delete tbl;
    tables.erase(it);
    sprintf(buf, "Table \"%s\" in Database \"%s\" dropped.", tbl_name, 
        this->name().c_str());
    return NOERR;
}

static void free_col_data(std::vector<std::pair<int, void*> >& val_vec){
    for (int i = 0; i < val_vec.size(); i++)
        optional_free(val_vec[i].second, val_vec[i].first);
}

int Database::create_table(const char *name, struct COL_DEF_LIST *def, 
    char *buf)
{
    std::map<std::string, Table*>::iterator it = 
        tables.find(std::string(name));
    if (it != tables.end()){
        sprintf(buf, "Table \"%s\" exists in Database \"%s\"", name,
            this->name().c_str());
        return EDUPTBL;
    }
    struct COL_DEF_LIST *ptr = def;
    int n_col = 0, ret_code = NOERR;
    std::map<int, void*> default_val;
    /* column -> data */
    std::vector<std::pair<int, std::string> > cols;
    /* pair<data_type, column_name>*/
    bool previous_static = treat_as_static;
    treat_as_static = true;
    while (ptr){
        if (ptr->attr & 8){
            int dt;
            void *val = eval_ast(ptr->def_val, &dt);
            if (val == NULL){
                sprintf(buf, "Invalid default value for column \"%s\"",
                    ptr->name);
                ret_code = EINVAL;
                break;
            }
            val = dt_convert(val, dt, &(ptr->type));
            default_val.insert(std::pair<int, void*>(n_col, val));
        }
        cols.push_back(std::pair<int, std::string>(ptr->type,
            std::string(ptr->name)));
        n_col++;
        ptr = ptr->next;
    }
    treat_as_static = previous_static;
    if (ptr)
        return ret_code;
    Table *tbl = new Table(name, this, cols, default_val);
    tables.insert(std::pair<std::string, Table*>(std::string(name), tbl));
    sprintf(buf, "Table \"%s\" created.", name);
    return NOERR;
}

int Database::insert_into(const char *tbl_name, struct COL_LISTING *col_list,
    struct EXPR_LIST *val_list, char *buf)
{
    std::map<std::string, Table*>::iterator it =
        tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".", 
            tbl_name, this->name().c_str());
        return ENOTBL;
    }
    struct COL_LISTING *col_ptr = col_list;
    struct EXPR_LIST *val_ptr = val_list;
    std::vector<std::string> col_vec;
    std::vector<std::pair<int, void*> > val_vec; /* type, data */
    int ret_code = NOERR;
    bool previous_static = treat_as_static;
    treat_as_static = true;
    while (col_ptr != NULL && val_ptr != NULL){
        col_vec.push_back(std::string(col_ptr->name));
        int dt = DT_UNKNOWN;
        void *data = NULL;
        if (val_ptr->expr != NULL){
            data = eval_ast(val_ptr->expr, &dt);
            if (data == NULL){
                sprintf(buf, "Invalid value for column \"%s\"",
                    col_ptr->name);
                ret_code = EINVAL;
                break;
            }
        }
        val_vec.push_back(std::pair<int, void*>(dt, data));
        col_ptr = col_ptr->next;
        val_ptr = val_ptr->next;
    }
    treat_as_static = previous_static;
    if (ret_code != NOERR){
        free_col_data(val_vec);
        return ret_code;
    }
    if (col_ptr || val_ptr){
        sprintf(buf, "Number of insert elements and number of columns\
            does not match.");
        return ESYNTAX;
    }
    Table *tbl = (*it).second;
    ret_code = tbl->insert(col_vec, val_vec, buf);
    free_col_data(val_vec);
    if (ret_code == NOERR)
        sprintf(buf, "Success.");
    return ret_code;
}

int Database::insert_into(const char *tbl_name, struct COL_LISTING *col_list, 
    struct SELECT_STMT *sub_query, char *buf)
{
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}

int Database::update(const char *tbl_name, struct COL_LISTING *col_list, 
    struct EXPR_LIST *val_list, struct EXPR *where, char *buf)
{
    std::map<std::string, Table*>::iterator it =
        tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".", 
            tbl_name, this->name().c_str());
        return ENOTBL;
    }
    struct COL_LISTING *col_ptr = col_list;
    struct EXPR_LIST *val_ptr = val_list;
    std::vector<std::string> col_vec;
    std::vector<std::pair<int, void*> > val_vec; /* type, data */
    int ret_code = NOERR;
    bool previous_static = treat_as_static;
    treat_as_static = true;
    while (col_ptr != NULL && val_ptr != NULL){
        col_vec.push_back(std::string(col_ptr->name));
        int dt = DT_UNKNOWN;
        void *data = NULL;
        if (val_ptr->expr != NULL){
            data = eval_ast(val_ptr->expr, &dt);
            if (data == NULL){
                sprintf(buf, "Invalid value for column \"%s\"",
                    col_ptr->name);
                ret_code = EINVAL;
                break;
            }
        }
        val_vec.push_back(std::pair<int, void*>(dt, data));
        col_ptr = col_ptr->next;
        val_ptr = val_ptr->next;
    }
    treat_as_static = previous_static;
    if (ret_code != NOERR){
        free_col_data(val_vec);
        return ret_code;
    }
    if (col_ptr || val_ptr){
        sprintf(buf, "Number of insert elements and number of columns\
            does not match.");
        return ESYNTAX;
    }
    Table *tbl = (*it).second;
    ret_code = tbl->update_where(col_vec, val_vec, where, buf);
    free_col_data(val_vec);
    return ret_code;
}

int Database::update(const char *tbl_name, struct COL_LISTING *col_list, 
    struct SELECT_STMT *sub_query, struct EXPR *where, char *buf)
{
    sprintf(buf, "Not implemented.");
    return ENOIMPL;
}

int Database::delete_from(const char *tbl_name, struct EXPR *where,
    char *buf)
{
    std::map<std::string, Table*>::iterator it =
        tables.find(std::string(tbl_name));
    if (it == tables.end()){
        sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".",
            tbl_name, this->name().c_str());
        return ENOTBL;
    }
    int del_cnt = (*it).second->delete_where(where);
    sprintf(buf, "In Table \"%s\" %d Row(s) deleted.", tbl_name, del_cnt);
    return NOERR;
}

int Database::make_table(struct REF_LIST *ref_ptr, Table **tbl_ptr_addr,
    std::string& alias, bool *tmp_tbl, char *buf)
{
    std::map<std::string, Table*>::iterator it;
    int ret_code;
    if (ref_ptr->type == 0){
        std::map<std::string, Table*>::iterator it = 
            tables.find(std::string(ref_ptr->table.name));
        if (it == tables.end()){
            sprintf(buf, "Table \"%s\" does not exist in Database\"%s\".",
                ref_ptr->table.name, this->name().c_str());
            return ENOTBL;
        }
        *tbl_ptr_addr = (*it).second;
        *tmp_tbl = false;
    }else if (ref_ptr->type == 2){
        Table *tbl;
        ret_code = this->run_select(ref_ptr->table.sub_query, &tbl, buf);
        if (ret_code != NOERR)
            return ret_code;
        *tbl_ptr_addr = tbl;
        *tmp_tbl = true;
    }
    if (ref_ptr->alias != NULL)
        alias = ref_ptr->alias;
    else
        alias = (*tbl_ptr_addr)->name();
    if (ref_ptr->join_param == NULL)
        return NOERR;
    else{
        sprintf(buf, "JOIN can be done by referring multiple tables.");
        return ENOIMPL;
    }
    /*
    Table *r_tbl;
    bool r_tmp;
    std::string r_name;
    struct EXPR *join_cond = ref_ptr->join_param->join_cond;
    ret_code = this->make_table(ref_ptr->join_param->join_with, 
        &r_tbl, r_name, r_tmp, buf);
    if (ret_code != NOERR){
        if (*tmp_tbl)
            delete l_tbl;
        return ret_code;
    }
    return NOERR;
    std::map<std::string, Table*> *previous_map = tbl_ref_map;
    tbl_ref_map = new std::map<std::string, Table*>();
    char *previous_buf = err_buf;
    err_buf = buf;
    bool previous_static = treat_as_static;
    treat_as_static = false;



    treat_as_static = previous_static;
    err_buf = previous_buf;
    tbl_ref_map = previous_map;
    */
}

void Database::iterate_select(std::vector<std::vector<int> >&products,
    std::vector<int>& row_ref, std::vector<int>& total_rows, int level,
    std::vector<std::pair<std::string, Table*> >& tbl_ref_list,
    struct EXPR *where)
{
    if (level == tbl_ref_list.size()){
        if (where == NULL){
            products.push_back(row_ref);
            return;
        }
        for (int i = 0; i < level; ++i)
            tbl_ref_list[i].second->set_current_row(row_ref[i]);
        int dt_bool = DT_BOOL, dt;
        void *cond = eval_ast(where, &dt);
        if (cond == NULL)
            return;
        cond = dt_convert(cond, dt, &dt_bool);
        if (*(bool*)cond)
            products.push_back(row_ref);
        optional_free(cond, dt_bool);
        return;
    }
    row_ref[level] = 0;
    while (row_ref[level] < total_rows[level]){
        this->iterate_select(products, row_ref, total_rows, level + 1,
            tbl_ref_list, where);
        row_ref[level]++;
    }
}

void Database::make_cartesian_product(
    std::vector<std::vector<int> >& products, std::vector<int>& row_ref,
    std::vector<std::pair<std::string, Table*> >& tbl_ref_list,
    struct EXPR *where)
{
    std::vector<int> total_rows(tbl_ref_list.size());
    for (int i = 0; i < tbl_ref_list.size(); i++){
        total_rows[i] = tbl_ref_list[i].second->rows_cnt();
        if (total_rows[i] == 0)
            return;
    }
    this->iterate_select(products, row_ref, total_rows, 0, tbl_ref_list, where);
}

int Database::run_select(struct SELECT_STMT *select, Table **tbl_ptr_addr,
    char *buf)
{
    *tbl_ptr_addr = NULL;
    std::map<std::string, Table*> *previous_map = tbl_ref_map;
    tbl_ref_map = new std::map<std::string, Table*>();
    char *previous_buf = err_buf;
    err_buf = buf;
    bool previous_static = treat_as_static;
    treat_as_static = false;
    std::vector<std::pair<std::string, Table*> > tbl_ref_list;
    std::vector<bool> tbl_is_tmp;
    int tbl_cnt = 0, ret_code = NOERR;
    struct REF_LIST *ref_ptr = select->ref_list;
    Table *tbl;
    std::string alias;
    bool is_tmp = false;
    while (ref_ptr != NULL){
        ret_code = this->make_table(ref_ptr, &tbl, alias, &is_tmp, buf);
        if (ret_code != NOERR)
            break;
        std::pair<std::string, Table*> tbl_pair(alias, tbl);
        tbl_ref_list.push_back(tbl_pair);
        tbl_is_tmp.push_back(is_tmp);
        tbl_ref_map->insert(tbl_pair);        
        tbl_cnt++;
        ref_ptr = ref_ptr->next;
    }
    if (ret_code != NOERR){
        delete tbl_ref_map;
        treat_as_static = previous_static;
        tbl_ref_map = previous_map;
        err_buf = previous_buf;
        for (int i = 0; i < tbl_ref_list.size(); ++i)
            if (tbl_is_tmp[i])
                delete tbl_ref_list[i].second;
        return ret_code;
    }
    std::vector<std::vector<int> > products;
    std::vector<int> row_ref(tbl_cnt);
    this->make_cartesian_product(products, row_ref, tbl_ref_list,
        select->where);
    if (select->order_list){
        std::vector<struct EXPR*> cmp_expr;
        std::vector<bool> order;
        struct ORDER_LIST *order_ptr = select->order_list;
        while (order_ptr != NULL){
            cmp_expr.push_back(order_ptr->expr);
            order.push_back(order_ptr->type == 1);
            order_ptr = order_ptr->next;
        }
        stable_sort(products.begin(), products.end(),
            Compare(cmp_expr, order, tbl_ref_list));
    }
    struct SELECT_LIST *sel_ptr = select->select_list;
    std::vector<std::pair<int, std::string> > col_def;
    std::map<int, void*> no_val;
    int total_cols = 0;
    if (sel_ptr->type == 0){
        for (int i = 0; i < tbl_ref_list.size(); i++){
            Table *sub_tbl = tbl_ref_list[i].second;
            for (int j = 0; j < sub_tbl->cols_cnt(); j++)
                col_def.push_back(std::pair<int, std::string>(
                    sub_tbl->col_dt(j),
                    tbl_ref_list[i].first + "_" + sub_tbl->col_name(j)));
            total_cols += sub_tbl->cols_cnt();
        }
        Table *result_tbl = new Table("_tmp_", this, col_def, no_val);
        std::vector<DataUnion *>& raw_data = result_tbl->access_raw_data();
        raw_data.resize(products.size());
        for (int i = 0; i < raw_data.size(); i++){
            raw_data[i] = new DataUnion[total_cols];
            int base_idx = 0;
            for (int j = 0; j < tbl_ref_list.size(); j++){
                Table *sub_tbl = tbl_ref_list[j].second;
                sub_tbl->set_current_row(products[i][j]);
                for (int k = 0; k < sub_tbl->cols_cnt(); k++)
                    sub_tbl->copy_column(raw_data[i] + base_idx + k, k);
                base_idx += sub_tbl->cols_cnt();
            }
        }
        *tbl_ptr_addr = result_tbl;
    }else{
        if (products.empty())
            *tbl_ptr_addr = new Table("_tmp_", this, col_def, no_val);
        else{
            for (int i = 0; i < tbl_ref_list.size(); i++)
                tbl_ref_list[i].second->set_current_row(products[0][i]);
            std::vector<struct EXPR*> col_expr;
            while (sel_ptr != NULL){
                int dt;
                void *dat = eval_ast(sel_ptr->expr, &dt);
                if (dat == NULL || dt == DT_UNKNOWN){
                    ret_code = EINVAL;
                    break;
                }
                col_def.push_back(std::pair<int, std::string>(
                    dt & ~NEED_FREE_MASK, std::string(sel_ptr->alias)));
                optional_free(dat, dt);
                col_expr.push_back(sel_ptr->expr);
                sel_ptr = sel_ptr->next;
                total_cols++;
            }
            if (ret_code == NOERR){
                Table *result_tbl = new Table("_tmp_", this, col_def,
                    no_val);
                std::vector<DataUnion *>& raw_data = 
                    result_tbl->access_raw_data();
                raw_data.resize(products.size());
                for (int i = 0; i < products.size(); i++){
                    raw_data[i] = new DataUnion[total_cols];
                    for (int j = 0; j < tbl_ref_list.size(); j++)
                        tbl_ref_list[j].second->
                            set_current_row(products[i][j]);
                    for (int j = 0; j < col_expr.size(); j++){
                        int dt;
                        void *dat = eval_ast(col_expr[j], &dt);
                        if (dat == NULL || dt == DT_UNKNOWN){
                            ret_code = EINVAL;
                            break;
                        }
                        result_tbl->copy_data(raw_data[i] + j, j, dat);
                        optional_free(dat, dt);
                    }
                    if (ret_code != NOERR){
                        for (int j = 0; j < i ; j++)
                            delete raw_data[j];
                        raw_data.clear();
                        delete result_tbl;
                        break;
                    }
                }
                *tbl_ptr_addr = result_tbl;
            }
        }
    }
    for (int i = 0; i < tbl_ref_list.size(); ++i)
        if (tbl_is_tmp[i])
            delete tbl_ref_list[i].second;
    delete tbl_ref_map;
    treat_as_static = previous_static;
    tbl_ref_map = previous_map;
    err_buf = previous_buf;
    if (ret_code != NOERR)
        return ret_code;
    sprintf(buf, "Success.");
    return NOERR;
}










