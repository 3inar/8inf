#include <stdlib.h>

#include "rts.h"

rts_t *stack_init() {
  rts_t *st = calloc(1, sizeof(rts_t));

  return st;
}

void stack_destroy(rts_t *st) {
  free(st);
}

word_t pop(rts_t *st) {
  st->top--;
  return st->buf[st->top];
}

void push(word_t wd, rts_t *st) {
  st->buf[st->top] = wd;
  st->top++;
}
