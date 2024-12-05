#ifndef __THESTACK_H__
#define __THESTACK_H__

#define STACK_SIZE 1024

#define TYPE_STR 's'
#define TYPE_INT 'i'


typedef struct word {
  char type;
  int intval;
  char *strval;
} word_t;

typedef struct thestack {
  unsigned int top;
  word_t buf[STACK_SIZE];
} rts_t;

rts_t *stack_init();
void stack_destroy(rts_t *);

word_t pop(rts_t *);
void push(word_t, rts_t *);

#endif
