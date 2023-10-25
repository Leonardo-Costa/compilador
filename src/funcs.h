#ifndef FUNCS_H
#define FUNCS_H
#include <stdio.h>
#include <stdlib.h>

enum Token {
  ASM,      // Keyword "asm"
  AUTO,     // Keyword "auto"
  BREAK,    // Keyword "break"
  CASE,     // Keyword "case"
  CHAR,     // Keyword "char"
  CONST,    // Keyword "const"
  CONTINUE, // Keyword "continue"
  DEFAULT,  // Keyword "default"
  DO,       // Keyword "do"
  DOUBLE,   // Keyword "double"
  ELSE,     // Keyword "else"
  ENUM,     // Keyword "enum"
  EXTERN,   // Keyword "extern"
  FLOAT,    // Keyword "float"
  FOR,      // Keyword "for"
  GOTO,     // Keyword "goto"
  IF,       // Keyword "if"
  INT,      // Keyword "int"
  LONG,     // Keyword "long"
  REGISTER, // Keyword "register"
  RETURN,   // Keyword "return"
  SHORT,    // Keyword "short"
  SIGNED,   // Keyword "signed"
  SIZEOF,   // Keyword "sizeof"
  STATIC,   // Keyword "static"
  STRUCT,   // Keyword "struct"
  SWITCH,   // Keyword "switch"
  TYPEDEF,  // Keyword "typedef"
  UNION,    // Keyword "union"
  UNSIGNED, // Keyword "unsigned"
  VOID,     // Keyword "void"
  VOLATILE, // Keyword "volatile"
  WHILE,    // Keyword "while"
  ID        // identifier
};

typedef struct {
  int prox_char;
  int linha;
  char data[256];
} Buffer;

typedef struct {
  char lexeme[65];  // Armazena o lexema
  enum Token token; // Armazena o token
  int linha;        // Armazena a linha
} LexemeInfo;

Buffer *allocate_buffer(int size);
void deallocate_buffer(Buffer *buffer);
void fill_buffer(FILE *file, Buffer *buffer);
char get_next_char(FILE *file, Buffer *buffer);

#endif
