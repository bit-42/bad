#ifndef BAD_MATH_H
#define BAD_MATH_H

int eval_add(char *arg1, char *arg2);
int eval_sub(char *arg1, char *arg2);
int eval_mul(char *arg1, char *arg2);
int eval_div(char *arg1, char *arg2);

float eval_add_float(char *arg1, char *arg2);
float eval_sub_float(char *arg1, char *arg2);
float eval_mul_float(char *arg1, char *arg2);
float eval_div_float(char *arg1, char *arg2);

float eval_cmp_lt(char *, char*);
float eval_cmp_gt(char *, char*);
float eval_cmp_lte(char *, char*);
float eval_cmp_gte(char *, char*);

#endif
