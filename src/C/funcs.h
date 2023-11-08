#ifndef FUNCS_H
#define FUNCS_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "lexer/lexer.h"


typedef struct {
  int prox_char;
  int linha;
  char data[256];
} Buffer;

typedef struct {
  char lexeme[65];  // Armazena o lexema
  int linha;        // Armazena a linha
} LexemeInfo;

Buffer *allocate_buffer(int size);
void deallocate_buffer(Buffer *buffer);
void fill_buffer(FILE *file, Buffer *buffer);
char get_next_char(FILE *file, Buffer *buffer);

#endif
