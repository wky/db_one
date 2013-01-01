#include "eval_ast.h"
#include "sqlfuncs.h"
#include "table.h"
#include "database.h"
#include "error.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <map>
#include <string>

#define ABORT_NULL(ptr) \
    do{\
        if ((ptr) == NULL){\
            *dt_ptr = DT_UNKNOWN;\
            return NULL;\
        }\
    }while(false)

#define PRINT_ERR(...) \
    do{\
        if (err_buf != NULL)\
            sprintf(__VA_ARGS__);\
    }while(false)

bool treat_as_static = true;
std::map<std::string, Table*> *tbl_ref_map = NULL;
char *err_buf = NULL;
Database *current_db = NULL;

void *retrieve(char *tbl_name, char *col_name, int *dt_ptr){
    if (tbl_ref_map == NULL){
        PRINT_ERR(err_buf, "Fatal Error. Internal state corrupted.");
        *dt_ptr = DT_UNKNOWN;
        return NULL;
    }
    Table *tbl = NULL;
    std::map<std::string, Table*>::iterator it;
    if (tbl_name){
        it = tbl_ref_map->find(std::string(tbl_name));
        if (it == tbl_ref_map->end()){
            PRINT_ERR(err_buf, "Table \"%s\" not unrecognized.", tbl_name);
            *dt_ptr = DT_UNKNOWN;
            return NULL;
        }
        tbl = (*it).second;
    }else{
        it = tbl_ref_map->begin();
        while (it != tbl_ref_map->end()){
            tbl = (*it).second;
            if (tbl->column_exist(col_name))
                break;
        }
    }
    if (tbl == NULL)
        tbl = (*(tbl_ref_map->begin())).second;
    void *ret = tbl->retrieve_data(col_name, dt_ptr);
    if (ret == NULL){
        PRINT_ERR(err_buf, "No data found for Column \"%s\" in Table \"%s\".", 
                col_name, tbl->name().c_str());
        return NULL;
    }
    int tmp_dt = *dt_ptr;
    if (tmp_dt & DT_INT){
        *dt_ptr = DT_LONG;
        ret = dt_convert(ret, tmp_dt, dt_ptr);
    }else if (tmp_dt & DT_FLOAT){
        *dt_ptr = DT_DOUBLE;
        ret = dt_convert(ret, tmp_dt, dt_ptr);
    }
    return ret;
}

void *judge_comparison(int cmptok, void *l_ptr, int l_dt, void *r_ptr, int r_dt, int *dt_ptr){
    tmp_num_val *val = new tmp_num_val;
    int tmp_dt;
    *dt_ptr = DT_BOOL | NEED_FREE_MASK;
    if ((l_dt & DT_DOUBLE) || (r_dt & DT_DOUBLE)){
        if ((l_dt & DT_BOOL) || (r_dt & DT_BOOL))
            *dt_ptr = DT_UNKNOWN;
        else{
            tmp_dt = DT_DOUBLE;
            if ((l_dt & DT_TEXT) || (l_dt & DT_LONG)){
                l_ptr = dt_convert(l_ptr, l_dt, &tmp_dt);
                l_dt = tmp_dt;
            }else if ((r_dt & DT_TEXT) || (r_dt & DT_LONG)){
                r_ptr = dt_convert(r_ptr, r_dt, &tmp_dt);
                r_dt = tmp_dt;
            }
            switch (cmptok){
                case CMP_E:
                    val->boolval = (*(double*)l_ptr) == (*(double*)r_ptr); break;
                case CMP_GE:
                    val->boolval = (*(double*)l_ptr) >= (*(double*)r_ptr); break;
                case CMP_G:
                    val->boolval = (*(double*)l_ptr) > (*(double*)r_ptr); break;
                case CMP_LE:
                    val->boolval = (*(double*)l_ptr) <= (*(double*)r_ptr); break;
                case CMP_L:
                    val->boolval = (*(double*)l_ptr) < (*(double*)r_ptr); break;
                case CMP_NE:
                    val->boolval = (*(double*)l_ptr) != (*(double*)r_ptr); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
            }
        }
    }else if ((l_dt & DT_LONG) || (r_dt & DT_LONG)){
        if ((l_dt & DT_BOOL) || (r_dt & DT_BOOL))
            *dt_ptr = DT_UNKNOWN;
        else{
            tmp_dt = DT_LONG;
            if (l_dt & DT_TEXT){
                l_ptr = dt_convert(l_ptr, l_dt, &tmp_dt);
                l_dt = tmp_dt;
            }else if (r_dt & DT_TEXT){
                r_ptr = dt_convert(r_ptr, r_dt, &tmp_dt);
                r_dt = tmp_dt;
            }
            switch (cmptok){
                case CMP_E:
                    val->boolval = (*(long*)l_ptr) == (*(long*)r_ptr); break;
                case CMP_GE:
                    val->boolval = (*(long*)l_ptr) >= (*(long*)r_ptr); break;
                case CMP_G:
                    val->boolval = (*(long*)l_ptr) > (*(long*)r_ptr); break;
                case CMP_LE:
                    val->boolval = (*(long*)l_ptr) <= (*(long*)r_ptr); break;
                case CMP_L:
                    val->boolval = (*(long*)l_ptr) < (*(long*)r_ptr); break;
                case CMP_NE:
                    val->boolval = (*(long*)l_ptr) != (*(long*)r_ptr); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
            }
        }
    }else if ((l_dt & DT_BOOL) && (r_dt & DT_BOOL)){
        switch (cmptok){
            case CMP_E:
                val->boolval = (*(bool*)l_ptr) == (*(bool*)r_ptr); break;
            case CMP_NE:
                val->boolval = (*(bool*)l_ptr) != (*(bool*)r_ptr); break;
            default:
                *dt_ptr = DT_UNKNOWN;
        }
    }else if ((l_dt & DT_TEXT) && (r_dt & DT_TEXT)){
        int cmp = strcmp((char *)l_ptr, (char *)r_ptr);
        switch (cmptok){
            case CMP_E:
                val->boolval = cmp == 0; break;
            case CMP_GE:
                val->boolval = cmp >= 0; break;
            case CMP_G:
                val->boolval = cmp > 0; break;
            case CMP_LE:
                val->boolval = cmp <= 0; break;
            case CMP_L:
                val->boolval = cmp < 0; break;
            case CMP_NE:
                val->boolval = cmp != 0; break;
            default:
                *dt_ptr = DT_UNKNOWN;
        }
    }else
        *dt_ptr = DT_UNKNOWN;
    if (l_dt & NEED_FREE_MASK){
        if (l_dt & DT_TEXT)
            delete[] (char*)l_ptr;
        else 
            delete (tmp_num_val*)l_ptr;
    }
    if (r_dt & NEED_FREE_MASK){
        if (r_dt & DT_TEXT)
            delete[] (char*)r_ptr;
        else
            delete (tmp_num_val*)r_ptr;
    }
    if (*dt_ptr == DT_UNKNOWN){
        PRINT_ERR(err_buf, "Unsupported comparison \"%s\" between type %s and %s.", 
                GET_CMP_NAME(cmptok), GET_TYPE_NAME(l_dt), GET_TYPE_NAME(r_dt));
        delete val;
        return NULL;
    }
    else return val;
}

void *calculate_result(int optok, void *l_ptr, int l_dt, void *r_ptr, int r_dt, int *dt_ptr){
    tmp_num_val *val = new tmp_num_val;
    int tmp_dt;
    if ((l_dt & DT_DOUBLE) || (r_dt & DT_DOUBLE)){
        if (l_dt & DT_BOOL){
            *dt_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)l_ptr) && (*(double*)r_ptr != 0.0); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)l_ptr) || (*(double*)r_ptr != 0.0); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
            }
        }else if (r_dt & DT_BOOL){
            *dt_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)r_ptr) && (*(double*)l_ptr != 0.0); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)r_ptr) || (*(double*)l_ptr != 0.0); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
            }
        }else{
            tmp_dt = DT_DOUBLE;
            if ((l_dt & DT_TEXT) || (l_dt & DT_LONG)){
                l_ptr = dt_convert(l_ptr, l_dt, &tmp_dt);
                l_dt = tmp_dt;
            }
            if ((r_dt & DT_TEXT) || (r_dt & DT_LONG)){
                r_ptr = dt_convert(r_ptr, r_dt, &tmp_dt);
                r_dt = tmp_dt;
            }
            *dt_ptr = DT_DOUBLE | NEED_FREE_MASK;
            switch (optok){
                case OP_ADD:
                    val->floatval = (*(double*)l_ptr) + (*(double*)r_ptr); break;
                case OP_SUB:
                    val->floatval = (*(double*)l_ptr) - (*(double*)r_ptr); break;
                case OP_MUL:
                    val->floatval = (*(double*)l_ptr) * (*(double*)r_ptr); break;
                case OP_DIV:
                    if (*(double*)r_ptr == 0.0){
                        PRINT_ERR(err_buf, "Floating Point division by zero.");
                        *dt_ptr = DT_UNKNOWN;
                        break;
                    }
                    val->floatval = (*(double*)l_ptr) / (*(double*)r_ptr); break;
                case OP_NEG:
                    val->floatval = - (*(double*)l_ptr); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
            }
        }
    }else if ((l_dt & DT_LONG) || (r_dt & DT_LONG)){
        if (l_dt & DT_BOOL){
            *dt_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)l_ptr) && (*(long*)r_ptr); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)l_ptr) || (*(long*)r_ptr); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
            }
        }else if (r_dt & DT_BOOL){
            *dt_ptr = DT_BOOL | NEED_FREE_MASK;
            switch(optok){
                case OP_LOGAND:
                    val->boolval = (*(bool*)r_ptr) && (*(long*)l_ptr); break;
                case OP_LOGOR:
                    val->boolval = (*(bool*)r_ptr) || (*(long*)l_ptr); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
            }
        }else{
            tmp_dt = DT_LONG;
            if (l_dt & DT_TEXT){
                l_ptr = dt_convert(l_ptr, l_dt, &tmp_dt);
                l_dt = tmp_dt;
            }else if (r_dt & DT_TEXT){
                r_ptr = dt_convert(r_ptr, r_dt, &tmp_dt);
                r_dt = tmp_dt;
            }
            *dt_ptr = DT_LONG | NEED_FREE_MASK;
            switch (optok){
                case OP_ADD:
                    val->intval = (*(long*)l_ptr) + (*(long*)r_ptr); break;
                case OP_SUB:
                    val->intval = (*(long*)l_ptr) - (*(long*)r_ptr); break;
                case OP_NEG:
                    val->intval = -(*(long*)l_ptr); break;
                case OP_MUL:
                    val->intval = (*(long*)l_ptr) * (*(long*)r_ptr); break;
                case OP_DIV:
                    if (*(long*)r_ptr == 0l){
                        PRINT_ERR(err_buf, "Integer division by zero.");
                        *dt_ptr = DT_UNKNOWN;
                        break;
                    }
                    val->intval = (*(long*)l_ptr) / (*(long*)r_ptr); break;
                case OP_MOD:
                    val->intval = (*(long*)l_ptr) % (*(long*)r_ptr); break;
                case OP_BITAND:
                    val->intval = (*(long*)l_ptr) & (*(long*)r_ptr); break;
                case OP_BITOR:
                    val->intval = (*(long*)l_ptr) | (*(long*)r_ptr); break;
                case OP_BITXOR:
                    val->intval = (*(long*)l_ptr) ^ (*(long*)r_ptr); break;
                case OP_BITFLIP:
                    val->intval = ~(*(long*)l_ptr); break;
                default:
                    *dt_ptr = DT_UNKNOWN;
                    break;
            }
            if (*dt_ptr == DT_UNKNOWN){
                *dt_ptr = DT_BOOL | NEED_FREE_MASK;
                switch (optok){
                    case OP_LOGAND:
                        val->boolval = (*(long*)l_ptr) && (*(long*)r_ptr); break;
                    case OP_LOGOR:
                        val->boolval = (*(long*)l_ptr) || (*(long*)r_ptr); break;
                    case OP_LOGNOT:
                        val->boolval = ~(*(long*)l_ptr); break;
                    default:
                        *dt_ptr = DT_UNKNOWN;
                }
            }
        }
    }else if ((l_dt & DT_BOOL) || (r_dt & DT_BOOL)){
        *dt_ptr = DT_BOOL | NEED_FREE_MASK;
        switch(optok){
            case OP_LOGAND:
                val->boolval = (*(bool*)l_ptr) && (*(bool*)r_ptr); break;
            case OP_LOGOR:
                val->boolval = (*(bool*)l_ptr) || (*(bool*)r_ptr); break;
            case OP_LOGNOT:
                val->boolval = !(*(bool*)l_ptr); break;
            default:
                *dt_ptr = DT_UNKNOWN;
        }
    }else if ((l_dt & DT_TEXT) && (r_dt & DT_TEXT)){
        if (optok == OP_ADD){
            *dt_ptr = DT_TEXT | NEED_FREE_MASK;
            int l_len = strlen((char *)l_ptr);
            int ap_len = l_len + strlen((char *)r_ptr);
            delete val;
            val = (tmp_num_val *)new char[ap_len + 1];
            strcpy((char *)val, (char *)l_ptr);
            strcpy((char *)val + l_len, (char *)r_ptr);
        }else
            *dt_ptr = DT_UNKNOWN;
    }else
        *dt_ptr = DT_UNKNOWN;
    if (l_dt & NEED_FREE_MASK){
        if (l_dt & DT_TEXT)
            delete[] (char*)l_ptr;
        else
            delete (tmp_num_val*)l_ptr;
    }
    if (r_dt & NEED_FREE_MASK){
        if (r_dt & DT_TEXT)
            delete[] (char*)r_ptr;
        else
            delete (tmp_num_val*)r_ptr;
    }
    if (*dt_ptr == DT_UNKNOWN){
        PRINT_ERR(err_buf, "Unsupported operation \"%s\" between type %s and %s.", 
                GET_OP_NAME(optok), GET_TYPE_NAME(l_dt), GET_TYPE_NAME(r_dt));
        delete val;
        return NULL;
    }
    else return val;
}

void *eval_ast(struct EXPR *expr, int *dt_ptr){
    ABORT_NULL(expr);
    tmp_num_val *val;
    bool expect_bool = false;
    int l_dt, r_dt, ret_code;
    void *l_ptr, *r_ptr;
    struct EXPR_LIST *list_ptr;
    Table *subq;
    switch (expr->type){
        case EXPR_NAME:
            if (treat_as_static == false)
                return retrieve(NULL, expr->self.name, dt_ptr);
        case EXPR_NAMEFIELD:
            if (treat_as_static == false){
                char *col = expr->self.name + strlen(expr->self.name) + 1;
                return retrieve(expr->self.name, col, dt_ptr);
            }
        case EXPR_STRING:
            *dt_ptr = DT_TEXT | NEED_FREE_MASK;
            return new_strdup(expr->self.name, strlen(expr->self.name));
        case EXPR_INTNUM:
            *dt_ptr = DT_LONG | NEED_FREE_MASK;
            val = new tmp_num_val;
            val->intval = expr->self.intval;
            return val;
        case EXPR_APPROXNUM:
            *dt_ptr = DT_DOUBLE | NEED_FREE_MASK;
            val = new tmp_num_val;
            val->floatval = expr->self.floatval;
            return val;
        case EXPR_BOOLEAN:
            *dt_ptr = DT_BOOL | NEED_FREE_MASK;
            val = new tmp_num_val;
            val->boolval = expr->self.boolval;
            return val;
        case EXPR_CMP:
            l_ptr = eval_ast(expr->child.real_child[0], &l_dt);
            ABORT_NULL(l_ptr);
            r_ptr = eval_ast(expr->child.real_child[1], &r_dt);
            ABORT_NULL(r_ptr);
            return judge_comparison(expr->self.cmptok, l_ptr, l_dt, r_ptr, r_dt, dt_ptr);
        case EXPR_OP:
            l_ptr = eval_ast(expr->child.real_child[0], &l_dt);
            ABORT_NULL(l_ptr);
            if (expr->child.real_child[1]){
                r_ptr = eval_ast(expr->child.real_child[1], &r_dt);
                ABORT_NULL(r_ptr);
            }else{
                r_ptr = NULL;
                r_dt = DT_UNKNOWN;
            }
            return calculate_result(expr->self.optok, l_ptr, l_dt, r_ptr, r_dt, dt_ptr);
        case EXPR_IN_RANGE:
            val = (tmp_num_val *)eval_ast(expr->self.test, dt_ptr);
            ABORT_NULL(val);
            l_ptr = eval_ast(expr->child.range[0], &l_dt);
            ABORT_NULL(l_ptr);
            r_ptr = judge_comparison(CMP_GE, val, *dt_ptr, l_ptr, l_dt, &r_dt);
            ABORT_NULL(r_ptr);
            if (*(bool*)r_ptr == false){
                *dt_ptr = r_dt;
                return r_ptr;
            }
            l_ptr = eval_ast(expr->child.range[1], &l_dt);
            ABORT_NULL(l_ptr);
            r_ptr = judge_comparison(CMP_GE, val, *dt_ptr, l_ptr, l_dt, &r_dt);
            ABORT_NULL(r_ptr);
            *dt_ptr = r_dt;
            return r_ptr;
        case EXPR_IN_LIST:
            expect_bool = true;
        case EXPR_NOTIN_LIST:
            /*dyn_val = new tmp_num_val;
            /dyn_val->boolval = expect_bool;*/
            l_ptr = eval_ast(expr->self.test, &l_dt);
            if (l_ptr == NULL){
                *dt_ptr = DT_UNKNOWN;
                return NULL;
            }
            list_ptr = expr->child.list;
            while (list_ptr != NULL /*&& dyn_val->boolval == expect_bool*/){
                r_ptr = eval_ast(list_ptr->expr, &r_dt);
                val = (tmp_num_val *)judge_comparison(CMP_E, l_ptr, l_dt, r_ptr, r_dt, dt_ptr);
                if (val == NULL){
                    *dt_ptr = DT_UNKNOWN;
                    return NULL;
                }
                if (expect_bool){
                    if (val->boolval)
                        return val;
                }else{
                    if (val->boolval){
                        val->boolval = false;
                        return val;
                    }
                }
                list_ptr = list_ptr->next;
            }
            val = new tmp_num_val;
            val->boolval = !expect_bool;
            *dt_ptr = DT_BOOL | NEED_FREE_MASK;
            return val;
        case EXPR_IN_SUB:
        case EXPR_NOTIN_SUB:
            val = (tmp_num_val *)eval_ast(expr->self.test, dt_ptr);
            ABORT_NULL(val);
            ret_code = current_db->run_select(expr->child.sub_query, &subq, err_buf);
            if (ret_code != NOERR){
                *dt_ptr = DT_UNKNOWN;
                return NULL;
            }
            /*
                iterate through every row in subq
            */
            PRINT_ERR(err_buf, "Not Implemented.");
            *dt_ptr = DT_UNKNOWN;
            return NULL;
        default:
            *dt_ptr = DT_UNKNOWN;
            return NULL;
    }

    
}
void *dt_convert(void *data, int from_type, int *to_type){
    int need_free = from_type & NEED_FREE_MASK;
    from_type &= ~NEED_FREE_MASK;
    tmp_num_val *val;
    void *ptr;
    switch (*to_type & ~NEED_FREE_MASK){
        case DT_CHAR: 
        switch (from_type){
            case DT_BOOL:   *(char*)data = (*(bool*)data)? 'T': 'F'; break;
            case DT_INT:
            case DT_LONG:   *(char*)data = (char)(*(long*)data); break;
            case DT_FLOAT:
            case DT_DOUBLE: *(char*)data = (char)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; val->charval = ((char*)data)[0];
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_INT:
        case DT_LONG:
        switch (from_type){
            case DT_CHAR:   *(long*)data = (long)(*(char*)data); break;
            case DT_BOOL:   *(long*)data = (long)(*(bool*)data); break;
            case DT_INT:    *(long*)data = (long)(*(int*)data); break;
            case DT_FLOAT:  *(long*)data = (long)(*(float*)data); break;
            case DT_DOUBLE: *(long*)data = (long)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; *(long*)val = atol((char*)data);  break;
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_FLOAT:
        switch (from_type){
            case DT_BOOL:   *(float*)data = (float)(*(bool*)data); break;
            case DT_CHAR:   *(float*)data = (float)(*(char*)data); break;
            case DT_INT:    *(float*)data = (float)(*(int*)data); break;
            case DT_LONG:   *(float*)data = (float)(*(long*)data); break;
            case DT_DOUBLE: *(float*)data = (float)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; *(float*)val = (float)atof((char*)data);
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_DOUBLE:
        switch (from_type){
            case DT_BOOL:   *(double*)data = (double)(*(bool*)data); break;
            case DT_CHAR:   *(double*)data = (double)(*(char*)data); break;
            case DT_INT:    *(double*)data = (double)(*(int*)data); break;
            case DT_LONG:   *(double*)data = (double)(*(long*)data); break;
            case DT_DOUBLE: *(double*)data = (double)(*(double*)data); break;
            case DT_TEXT:   val = new tmp_num_val; *(double*)val = atof((char*)data);
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        case DT_TEXT:
        switch (from_type){
            case DT_BOOL:   ptr = data; data = new char[6]; strcpy((char*)data, (*(bool*)ptr)?"TRUE":"FALSE");
                            if (need_free) delete (tmp_num_val*)ptr;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_CHAR:   ((char*)data)[1] = '\0'; *to_type |= need_free; break;
            case DT_INT:    ptr = data; data = new char[SHORTLEN]; sprintf((char*)data, "%d", *(int*)ptr);
                            if (need_free) delete (tmp_num_val*)ptr;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_LONG:   ptr = data; data = new char[SHORTLEN]; sprintf((char*)data, "%ld", *(long*)ptr);
                            if (need_free) delete (tmp_num_val*)ptr;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_FLOAT:  ptr = data; data = new char[SHORTLEN]; sprintf((char*)data, "%f", *(float*)ptr);
                            if (need_free) delete (tmp_num_val*)ptr;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_DOUBLE: ptr = data; data = new char[SHORTLEN]; sprintf((char*)data, "%lf", *(double*)ptr);
                            if (need_free) delete (tmp_num_val*)ptr;
                            *to_type |= NEED_FREE_MASK; break;
            case DT_TEXT:   *to_type |= need_free; break;
        }break;
        case DT_BOOL:
        switch (from_type){
            case DT_CHAR:   *(bool*)data = ((*(char*)data) != 0); break;
            case DT_INT:    *(bool*)data = ((*(int*)data) != 0); break;
            case DT_LONG:   *(bool*)data = ((*(long*)data) != 0l); break;
            case DT_FLOAT:  *(bool*)data = ((*(float*)data) != 0.0); break;
            case DT_DOUBLE: *(bool*)data = ((*(double*)data) != 0.0); break;
            case DT_TEXT:   val = new tmp_num_val; val->boolval = (((char*)data)[0] != '\0');
                            if (need_free) delete[] (char*)data;
                            *to_type |= NEED_FREE_MASK; data = val; break;
        }*to_type |= need_free; break;
        default:
            break;
    }
    return data;
}
void delete_tmp(void *ptr){
    delete (tmp_num_val*)ptr;
}
