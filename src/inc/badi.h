#ifndef BADI_H
#define BADI_H

#include "cvector.h"

/*
 * Used by cvector.h to determine how often to call realloc
 * If this is enabled, vectors will double in capacity each time it runs out of
 * space. By uncommenting this, we save on calls to realloc at the expense of
 * potentially using more memory than we need to.
 */
// #define CVECTOR_LOGARITHMIC_GROWTH


/*
 * help
 *
*/
typedef cvector_vector_type(char *) TOKENS;

/*
 * tokenize(char *code) -> vector (see cvector.h)
 *
 * Tokenizes a code-string and returns a vector.
*/
TOKENS tokenize(char *code);
float eval(TOKENS t);

TOKENS tokens_car(TOKENS tokens);
TOKENS tokens_cdr(TOKENS tokens);
TOKENS tokens_inside(TOKENS tokens);

void tokens_to_str(char *str, TOKENS tokens, int size);

int eval_token_int(char *n);
float eval_token_float(char *n);

enum TOKENTYPE token_numtype(char *t);

#endif
