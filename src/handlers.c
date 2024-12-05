#include <stdio.h>

#include "handlers.h"
#include "rts.h"

void integer_operator(rts_t *st, enum operator op) {
  word_t b = pop(st);
  word_t a = pop(st);

  int z;

  switch (op) {
    case ADD: z = a.intval + b.intval; break;
    case SUB: z = a.intval - b.intval; break;
    case MUL: z = a.intval * b.intval; break;
    case DIV: z = a.intval / b.intval; break;
    case MOD: z = a.intval % b.intval; break;
    case CMP: z = a.intval == b.intval ? 1 : 0; break;
    case GTH: z = a.intval > b.intval ? 1 : 0; break;
  }

  word_t res = {.type=TYPE_INT, .intval=z};
  push(res, st);   
}

void duplicate(rts_t *st) {
  word_t wd = pop(st);
  push(wd, st); 
  push(wd, st);
}

void swap(rts_t *st) {
  word_t a = pop(st);
  word_t b = pop(st);
  push(a, st); 
  push(b, st);
}

void print(rts_t *st) {
  word_t wd = pop(st);
  if (wd.type == TYPE_STR) printf("%s", wd.strval);
  else printf("%i", wd.intval);
}

void newline(rts_t *st) {
  printf("\n");
}
