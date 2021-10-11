#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <editline.h>
#include <ctype.h>
#include <math.h>

#include "cvector.h"
#include "badi.h"
#include "badmath.h"

char *help = ""
"Usage: badi [file]\n"
"\n"
"Examples:\n"
"  $ badi\n"
" OR\n"
"  $ badi hello.bad\n"
"\n"
"For support, please view the README.\n";

char *term_help = ""
"In badi, you can type raw bad and it will interpreter it.\n"
"badi == bad interpreter\n"
"Example: `(+ 1 1)`` will return `2`\n"
"FYI: Everything has a return value except for (exit). Even this command returns 0.\n"
"For support, please view the README.\n";

char *source = "https://github.com/jessehorne/bad\n";

cvector_vector_type(float) variables_float = NULL;
TOKENS variables_name = NULL;

/* methods holds all built-in methods */
char *methods[] = {"help", "exit", "dvar", "source"};
int method_count = 4;


/* token types */
enum TOKENTYPE {
  TMETHOD, TVAR, TINT, TFLOAT, TSTRING, TINVALID, TNULL
};

/* Validate command line arguments to badi */
bool cmd_validate_args(char *argv[])
{
  return argv[1] != NULL;
}

/* Get first command line argument to badi */
const char *cmd_first(char *argv[])
{
  if (argv[1] == NULL) {
    return "";
  }

  return argv[1];
}

/*
 * TOKENS tokens_car(TOKENS t)
 *
 * Returns a TOKENS list containing only the first token of 't';
 * Example: [1, 2, 3] returns [1]
 *
*/
TOKENS tokens_car(TOKENS t)
{
  TOKENS nt = NULL;

  cvector_push_back(nt, t[0]);

  return nt;
}

/*
 * TOKENS tokens_cdr(TOKENS t)
 *
 * Returns all tokens except the first.
 * Example: [1, 2, 3] returns [2, 3]
 *
*/
TOKENS tokens_cdr(TOKENS t)
{
  TOKENS nt = NULL;

  for (int i=1; i<cvector_size(t); i++) {
    cvector_push_back(nt, t[i]);
  }

  return nt;
}

/*
 * TOKENS tokens_inside(TOKENS t)
 *
 * Returns a TOKENS list exclusing the first and last of 't';
 * Example: [1, 2, 3] returns [2]
 *
*/
TOKENS tokens_inside(TOKENS t)
{
  TOKENS nt = NULL;

  for (int i=1; i<cvector_size(t)-1; i++) {
    cvector_push_back(nt, t[i]);
  }

  return nt;
}

/*
 * int tokens_find(char *str, TOKENS t) -> int
 *
 * Returns the index of 't' that matches with 'str'
 * Returns -1 if nothing was found.
 *
*/
int tokens_find(char *str, TOKENS t)
{
  int location = -1;

  for (int i=0; i<cvector_size(t); i++) {
    if (strcmp(t[i], str)) {
      location = i;

      return location;
    }
  }

  return location;
}

/*
 * void tokens_to_str(char *str, TOKENS tokens, int size)
 *
 * Set's 'str' to be the concatenated version of all stringsi n 't'.
 *
*/
void tokens_to_str(char *str, TOKENS t, int size)
{
  for (int i=0; i<size; i++) {
    str[i] = t[i][0];
  }

  str[size] = '\0';
}

/*
 * TOKENS tokenize(char *code)
 *
 * Partially-Tokenizes a code-string.
 * Example: "(+ 1 (* 2 2))" returns ["+", "1", "(* 2 2)"]
*/
TOKENS tokenize(char *code)
{
  // Format string
  cvector_vector_type(char) formatted = NULL;

  for (int i=0; i<strlen(code); i++) {
    if (i == 0 && code[i] == '(') {
      continue;
    }

    if (code[i] == '(') {
      cvector_push_back(formatted, ' ');
      cvector_push_back(formatted, '(');
      cvector_push_back(formatted, ' ');
    } else if (code[i] == ')') {
      cvector_push_back(formatted, ' ');
      cvector_push_back(formatted, ')');
      cvector_push_back(formatted, ' ');
    } else {
      cvector_push_back(formatted, code[i]);
    }
  }

  int formatted_size = cvector_size(formatted);

  char formatted_str[formatted_size+1];

  for (int i=0; i<formatted_size; i++) {
    formatted_str[i] = formatted[i];
  }

  formatted_str[formatted_size] = '\0';

  // Split by space
  TOKENS chars = NULL;

  char *current;

  current = strtok(formatted_str, " ");

  while (current != NULL) {
    cvector_push_back(chars, current);
    current = strtok(NULL, " ");
  }

  // Tokenize
  TOKENS tokens = NULL;
  TOKENS expr = NULL;

  int chars_size = cvector_size(chars);

  int level = 0;

  // Loop through chars...
  // If (, use level to mark that we're inside of an expression
  // When find closing ), create string from expr and add to tokens
  // Otherwise, just add to tokens
  for (int i=0; i<chars_size; i++) {
    if (strcmp(chars[i], "(") == 0) {
      // If level > 0, we need to keep track of the ('s
      if (level > 0) {
        cvector_push_back(expr, "(");
      }

      // If (, increment level letting loop know we're in an expr and how deep
      level++;
    } else if (strcmp(chars[i], ")") == 0) {
      // When level is bigger than 1, keep the )'s in the expr
      if (level > 1) {
        cvector_push_back(expr, ")");
      }

      // When level is 1, we're closing an expr
      // Now we should copy over expr to a string and format it properly
      if (level == 1) {
        int str_size = 0;

        // This counts the total number of chars we'll need...
        // I need to make this better. Too many loops...
        for (int x=0; x<cvector_size(expr); x++) {
          str_size += strlen(expr[x]);
        }

        str_size += 2; // For ( and )?

        char *expr_str = (char *) malloc(sizeof(char) * (str_size*2) + 1);
        int count = 0;

        for (int x=0; x<cvector_size(expr); x++) {
          if (x == 0) {
            // Put (, then first, then space
            expr_str[count] = '(';
            count++;

            for (int y=0; y<strlen(expr[x]); y++) {
              expr_str[count] = expr[x][y];
              count++;
            }

            expr_str[count] = ' ';
            count++;
          } else if (x == 1) {
            // put x then space
            for (int y=0; y<strlen(expr[x]); y++) {
              expr_str[count] = expr[x][y];
              count++;
            }
          } else {
            // put space then x
            expr_str[count] = ' ';
            count++;

            for (int y=0; y<strlen(expr[x]); y++) {
              expr_str[count] = expr[x][y];
              count++;
            }
          }

        }

        expr_str[count] = ')';
        expr_str[count+1] = '\0';


        // Now we need to put the string into tokens and clear the expr for later use
        cvector_push_back(tokens, expr_str);

        expr = NULL;
      }

      // If ), decrement level.
      level--;

    } else {
      // If level > 0, add all other chars to expr
      // Else: add to tokens
      if (level > 0) {
        cvector_push_back(expr, chars[i]);
      } else {
        cvector_push_back(tokens, chars[i]);
      }
    }

  }

  return tokens;
}

/*
 * int eval_token_int(char *n)
 *
 * Returns the int value from a string.
 * Example: "100" returns 100
*/
int eval_token_int(char *n)
{
  // Assuming it's a number
  char* eptr;
  int a = strtol(n, &eptr, 10);

  return a;
}

/*
 * char *token_type(char* t)
 *
 * Returns the type of "t"
 *
 * Example: "help" returns TMETHOD
 * Example: "abc" returns TVAR
 * Example: "1" returns TINT
 * Example: "1.0" returns TFLOAT
 * Example: "\"cat\"" returns TSTRING
*/
enum TOKENTYPE token_type(char* t)
{
  // Is method?
  for (int i=0; i<method_count; i++) {
    if (strcmp(methods[i], t) == 0) {
      return TMETHOD;
    }
  }

  // Is var?
  for (int i=0; i<cvector_size(variables_name); i++) {
    if (strcmp(variables_name[i], t) == 0) {
      return TVAR;
    }
  }

  // is int or float?
  enum TOKENTYPE numtype = token_numtype(t);

  if (numtype != TINVALID) {
    return numtype;
  }

  if (strcmp(t, "nil") == 0) {
    return TNULL;
  }

  return TINVALID;
}

/*
 * float eval_token_float(char *n)
 *
 * Returns the float value from a string.
 * Example: "100.01 returns 100.01
*/
float eval_token_float(char *n)
{
  if (n[0] == '(') {
    return eval(tokenize(n));
  }

  // Check if token is TVAR
  enum TOKENTYPE tt = token_type(n);

  if (tt == TVAR) {
    for (int i=0; i<cvector_size(variables_name); i++) {
      if (strcmp(variables_name[i], n) == 0) {
        return variables_float[i];
      }
    }
  }

  // Assuming it's a number
  char* eptr;
  float a = strtof(n, &eptr);

  return a;
}


/*
 * enum TOKENTYPE token_numtype(char *t)
 *
 * Returns the numeral type of a token or TNULL or TINVALID (if not a number)
 * Example: "100" returns TINT
 * Example: "-100.01" returns TFLOAT
 * Example: "-a" returns TINVALID
 * Example: "nil" returns TNULL
*/
enum TOKENTYPE token_numtype(char *t)
{
  // Is int?
  int isFloat = 0;
  int invalid = 0;
  int dotCount = 0;
  int isNegative = 0;
  /* TODO: also incorporate lengths to determine specific size
           e.g long long, int, etc */

  int str_size = strlen(t);

  if (str_size == 0) return TINVALID;

  // Check if negative
  if (t[0] == '-') {
    isNegative = 1;

    // If negative, first char after - should be digit
    if (str_size == 1) return TINVALID;

    if (isdigit(t[1]) == 0) {
      return TINVALID;
    }
  }

  for (int i=0; i<str_size; i++) {
    // has '.'?
    if (t[i] == '.') {
      isFloat = 1;
      dotCount += 1;

      // Float only needs 1 dot :)
      if (dotCount > 1) {
        return TINVALID;
      }

      // If the dot is at the end, it's invaild!
      if (i == (str_size-1)) {
        invalid = 1;
        break;
      }

      continue;
    }

    // If not digit, invalid!
    if (isNegative) {
      if (i > 0 && isdigit(t[i]) == 0) {
        invalid = 1;
        break;
      }
    } else {
      if (isdigit(t[i]) == 0) {

      }
    }

    // If not a digit, check if negative then check next digit
    // If not a digit, its invalid!
    if (isdigit(t[i]) == 0) {
      if (isNegative) {
        if (strlen(t) == 1) return TINVALID;

        if (isdigit(t[i]) == 0) return TINVALID;
      } else {
        return TINVALID;
      }
    }

  }

  if (invalid) {
    return TINVALID;
  }

  if (isFloat) {
    return TFLOAT;
  } else {
    return TINT;
  }

  return TINVALID;
}

/*
 * int eval(TOKENS t)
 *
 * Returns the int return value from the execusion of all tokens in 't'
*/
float eval(TOKENS t)
{
  int token_count = cvector_size(t);

  for (int i=0; i<token_count; i++) {
    if (t[i][0] == '(') {
      // If it begins with (, it needs to be tokenized
      return eval(tokenize(t[i]));
    } else if (t[i][0] == ')') {
      // Nothing to do here, yet?
    } else {
      // Get the type..
      // Can be a Symbol, Number, String or NIL

      // dumb methods
      if (strcmp(t[i], "help") == 0) {
        puts(term_help);
      } else if (strcmp(t[i], "source") == 0) {
        puts(source);
      } else if (strcmp(t[i], "exit") == 0) {
        exit(0);
      }

      // Get first and second arguments
      // Check their type
      // If their type is "variable", check to see if it is defined
      // If not, convert accordingly and blindly pass in (TODO: fix later)

      // Get the tokens type :>
      enum TOKENTYPE tt = token_type(t[i]);

      // operators
      if (strcmp(t[i], "+") == 0) {
        return eval_add_float(t[i+1], t[i+2]);
      } else if (strcmp(t[i], "-") == 0) {
        return eval_sub_float(t[i+1], t[i+2]);
      } else if (strcmp(t[i], "*") == 0) {
        return eval_mul_float(t[i+1], t[i+2]);
      } else if (strcmp(t[i], "/") == 0) {
        return eval_div_float(t[i+1], t[i+2]);
      } else if (strcmp(t[i], "<") == 0) {
        return eval_cmp_lt(t[i+1], t[i+2]);
      } else if (strcmp(t[i], ">") == 0) {
        return eval_cmp_gt(t[i+1], t[i+2]);
      } else if (strcmp(t[i], "<=") == 0) {
        return eval_cmp_lte(t[i+1], t[i+2]);
      } else if (strcmp(t[i], ">=") == 0) {
        return eval_cmp_gte(t[i+1], t[i+2]);
      } else {
        // methods
        if (tt == TMETHOD) {
          if (strcmp(t[i], "dvar") == 0) {
            // Add variable name to variables_name if doesn't exist
            // otherwise change it (TODO)
            char *var_name = (char *)malloc(sizeof(char) * sizeof(t[i+1]));
            strcpy(var_name, t[i+1]);

            float var = eval_token_float(t[i+2]);

            cvector_push_back(variables_name, var_name);
            cvector_push_back(variables_float, var);
            // add value to variables_int
            return var;
          }
        } else if (tt == TVAR) {
          for (int x=0; x<cvector_size(variables_name); x++) {
            if (strcmp(variables_name[x], t[i]) == 0) {
              return variables_float[x];
            }
          }

        } else {
          printf("Invalid token.\n");
        }
      }

    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  const char *first = cmd_first(argv);

  if (strcmp(first, "help") == 0) {
    printf("%s", help);
  } else if (strcmp(first, "") == 0) {
    // Start repl
    puts("Welcome to bad! Try (help) or (source) or (exit).");
    char *p;

    while ((p = readline("badi> ")) != NULL) {
      TOKENS t = tokenize(p);
      float ret = eval(t);

      if (fmod(ret, 1.0) != 0.0) {
        // float return
        printf("Return: %f\n", ret);
      } else {
        // int return
        printf("Return: %d\n", (int)ret);
      }

      free(p);
    }
  } else if (strcmp(first, "tests") == 0) {
    /* TODO */
    /* This should run a bunch of tests. */

    float test = 1.0 + 1.0;

    printf("Float: %f\n", test);
  } else {
    printf("Invalid command: %s\n", first);
    printf("%s", help);
  }

  return 0;
}
