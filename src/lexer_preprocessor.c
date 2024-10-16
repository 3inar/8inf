#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "lexer_preprocessor.h"

char *read_file(char *source_file) {
  char *buffer;
  size_t len;
  FILE *f = fopen(source_file, "rb");

  // find length of file
  fseek (f, 0, SEEK_END);
  len = ftell (f);
  fseek (f, 0, SEEK_SET);

  // allocate space, read file
  buffer = malloc(len);
  fread (buffer, 1, len, f);
  fclose (f);

  return buffer;
}

// replace all newlines with a space
void strip_newlines(char *str) {
  for (char *pt = str; *pt != '\0'; pt++) {
    if (*pt == '\n') *pt = ' ';
  }
}

// replace all (comments) with spaces
void strip_comments(char *str) {
  for (char *pt = str; *pt != '\0'; pt++) {
    if (*pt == '(') {
      while (*pt != ')') {
        assert(*pt != '\0'); // no neverending comments allowed
        *pt = ' ';
        pt++;
      }

      *pt = ' ';
      pt++;
    }
  }
}

char** load_program(char *src_file) {
  // allocate space for the program to live in
  char **program = calloc(MAXWORDS, sizeof(char*));

  char *buffer = read_file(src_file);

  // preprocessing
  strip_newlines(buffer);
  strip_comments(buffer);

  char *token = buffer; 
  char *end;
  char terminator;

  // breaks the program text into meaningfulwords and places each word in the
  // global program array
  int i = 0;
  while (*token != '\0') {
    while (*token == ' ') token++;
    end = token;
    
    // if token starts with ~ it is a string and we must scan up to the 
    // closing ~, otherwise we're looking for a space
    if (*token == '~') {
      terminator = '~';
      end++;
    } else { 
      terminator = ' ';
    }

    // finds end of token
    while (*end != terminator && *end != '\0') end++;
    
    if (*end == '~') end++;

    // copy the token to its own string pointed to by the program array
    if (token < end) {
      int nchar  = end - token;
      program[i] = malloc(sizeof(char)*(nchar + 1));
      memcpy(program[i], token, sizeof(char)*nchar);
      program[i][nchar] = '\0';
      i++;
    }

    token = end + 1;
  }

  free(buffer);

  return program;
}
