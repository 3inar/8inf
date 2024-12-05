#ifndef __HANDLERS_H__
#define __HANDLERS_H__

#include "rts.h"

enum operator{ADD, MUL, SUB, DIV, MOD, CMP, GTH};

void print(rts_t *);
void newline(rts_t *);

void integer_operator(rts_t *, enum operator);

void duplicate(rts_t *);
void swap(rts_t *);

#endif
