#include <stdio.h>

#include "inc/badi.h"
#include "inc/badmath.h"

int eval_add(char *arg1, char *arg2)
{
  int first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_int(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_int(arg2);
  }

  return (first+second);
}

int eval_sub(char *arg1, char *arg2)
{
  int first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_int(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_int(arg2);
  }

  return (first-second);
}

int eval_mul(char *arg1, char *arg2)
{
  int first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_int(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_int(arg2);
  }

  return (first*second);
}

int eval_div(char *arg1, char *arg2)
{
  int first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_int(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_int(arg2);
  }

  return (first/second);
}

/* FLOATS */
float eval_add_float(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first+second);
}

float eval_sub_float(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first-second);
}

float eval_mul_float(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first*second);
}

float eval_div_float(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first/second);
}

/* LOGIC */
float eval_cmp_lt(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first < second);
}

float eval_cmp_gt(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first > second);
}

float eval_cmp_lte(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first <= second);
}

float eval_cmp_gte(char *arg1, char *arg2)
{
  float first, second;

  // Eval just in case
  if (arg1[0] == '(') {
    first = eval(tokenize(arg1));
  } else {
    first = eval_token_float(arg1);
  }

  if (arg2[0] == '(') {
    second = eval(tokenize(arg2));
  } else {
    second = eval_token_float(arg2);
  }

  return (first >= second);
}
