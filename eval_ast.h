#ifndef __EVALAST__
#define __EVALAST__
#include "types.h"
#include "sqlfuncs.h"
union tmp_num_val{
    long intval;
    double floatval;
    bool boolval;
    char charval;
};
void *judge_comparison(int, void *, int, void *, int, int*);
void *calculate_result(int, void *, int, void *, int, int*);
void *eval_ast(struct EXPR *, int *);
void *dt_convert(void *, int, int*);
void delete_tmp(void *ptr);
#endif