#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer_preprocessor.h"

#include "handlers.h"
#include "rts.h"

char **program;
rts_t *stack;

// helper function that prints out the stack
void stackdump(rts_t *st) {
  for (int i = st->top - 1; i >= 0; i--) {
    word_t wd = st->buf[i];
    if (wd.type==TYPE_STR) printf("%i: %s\n", i, wd.strval);
    else printf("%i: %i\n", i, wd.intval);
  }
}

// helper function that prints out the program
void programdump(char **prog) {
  for (char **pc = prog; *pc != NULL; pc++) {
    printf("program[%i]: %s\n", (int) (pc - program), *pc);
  }
}

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("no program supplied\n");
    return 0;
  }

  // program is an array of strings; the end of the program is signified by a
  // NULL pointer.
  program = load_program(argv[1]);

  // prints out the words in the program array; uncomment to get an idea of how
  // the program is stored in memory.
  // programdump(program);

  stack = stack_init();

  char **pc = program;

  for (char **pc = program; *pc != NULL; pc++) {
    // word is a string:
    if (*pc[0] == '~') {
      size_t len = strlen(*pc);
      word_t tmp = {.type=TYPE_STR, .strval=calloc(len, sizeof(char))};
      memcpy(tmp.strval, *pc + 1, len-2);

      push(tmp, stack);

    // word is an operation:
    } else if (*pc[0] == '.') {

      // i/o ops:
      if (strcmp(*pc, ".print")==0) 
        print(stack);
      else if (strcmp(*pc, ".newline")==0) 
        newline(stack);
      
      // integer ops:
      else if (strcmp(*pc, ".+")==0) 
        integer_operator(stack, ADD);
      else if (strcmp(*pc, ".-")==0) 
        integer_operator(stack, SUB);
      else if (strcmp(*pc, ".*")==0) 
        integer_operator(stack, MUL);
      else if (strcmp(*pc, "./")==0) 
        integer_operator(stack, DIV);
      else if (strcmp(*pc, ".mod")==0) 
        integer_operator(stack, MOD);
      else if (strcmp(*pc, ".=?")==0) 
        integer_operator(stack, CMP);
      else if (strcmp(*pc, ".>?")==0) 
        integer_operator(stack, GTH);

      // stack ops
      else if (strcmp(*pc, ".dup")==0) 
        duplicate(stack);
      else if (strcmp(*pc, ".swap")==0) 
        swap(stack);

      // control flow ops must be handled where we have access to the program
      // counter
      else if (strcmp(*pc, ".cjump")==0) { 
        word_t jumpto = pop(stack); 
        word_t check = pop(stack); 

        // -1 since we know the pc will increment at end of this for loop
        if (check.intval) pc = pc + jumpto.intval - 1;
      }

      // op not supported:
      else { 
        printf("unrecognizable word: %s\n", *pc); return -1; 
      }

    // word is an int or unrecognized:
    } else {
      char *endptr;
      int z = strtol(*pc, &endptr, 10);
      if (*endptr != '\0') {
        printf("unrecognizable word: %s\n", *pc); return -1; 
      } else {
        word_t tmp = {.type=TYPE_INT, .intval=z };
        push(tmp, stack);
      }
    }
  }
  
  return 0;
}
