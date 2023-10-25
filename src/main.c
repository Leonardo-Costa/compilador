#include "funcs.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

const char *keywords[] = {"asm",    "auto",     "break",   "case",   "char",
                          "const",  "continue", "default", "do",     "double",
                          "else",   "enum",     "extern",  "float",  "for",
                          "goto",   "if",       "int",     "long",   "register",
                          "return", "short",    "signed",  "sizeof", "static",
                          "struct", "switch",   "typedef", "union",  "unsigned",
                          "void",   "volatile", "while"};

const char *tokenArray[] = {
    "ASM",      "AUTO",     "BREAK",  "CASE",    "CHAR",   "CONST",
    "CONTINUE", "DEFAULT",  "DO",     "DOUBLE",  "ELSE",   "ENUM",
    "EXTERN",   "FLOAT",    "FOR",    "GOTO",    "IF",     "INT",
    "LONG",     "REGISTER", "RETURN", "SHORT",   "SIGNED", "SIZEOF",
    "STATIC",   "STRUCT",   "SWITCH", "TYPEDEF", "UNION",  "UNSIGNED",
    "VOID",     "VOLATILE", "WHILE",  "ID"};

enum Token classify_lexeme(char *lexeme) {
  for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
    if (strcmp(lexeme, keywords[i]) == 0) {
      return (enum Token)i;
    }
  }
  return ID;
}

void populateLexemeInfo(LexemeInfo *lexemeInfoPtr, char lexeme[65],
                        enum Token token, int linha) {
  strcpy(lexemeInfoPtr->lexeme, lexeme);
  lexemeInfoPtr->token = token;
  lexemeInfoPtr->linha = linha;
}

void printLexemeInfo(LexemeInfo *lexemeInforPtr) {
  printf("Linha: %d, Lexema: %s, Token: %s\n", lexemeInforPtr->linha,
         lexemeInforPtr->lexeme, tokenArray[lexemeInforPtr->token]);
}

bool checkIfLetter(char character) {
  return (character >= 'A' && character <= 'Z') ||
         (character >= 'a' && character <= 'z');
}

int main(int argc, char *argv[]) {
  const char *fileName = argv[1];

  // retorna erro se a quantidade de argumentos passada nao for igual a 2
  if (argc != 2) {
    return 1;
  }

  // abre o arquivo e retorna um erro caso nao seja possível
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo");
    return 1;
  }

  // alloca um buffer de tamanho 256 e retorna um erro caso nao seja possivel
  Buffer *buffer = allocate_buffer(256);
  if (buffer == NULL) {
    printf("Erro ao alocar o buffer.\n");
    fclose(file);
    return 1;
  }

  buffer->prox_char = 0;
  char character;

  LexemeInfo lexemeInfo;
  LexemeInfo *lexemeInfoPtr = &lexemeInfo;

  char lexeme[65] = "";
  int lexemeIndex = 0;

  enum Token token;

  while (1) {
    // le caractere por caractere do buffer
    char character = get_next_char(file, buffer);
    printf("%c\n", character);

    if (checkIfLetter(character)) {
      // printf("%c eh letra", character);
      lexeme[lexemeIndex] = character;
      lexemeIndex++;
    } else {
      if (strcmp(lexeme, "") != 0) {
        enum Token token = classify_lexeme(lexeme);

        populateLexemeInfo(lexemeInfoPtr, lexeme, token, buffer->linha);
        printLexemeInfo(lexemeInfoPtr);
      }

      lexemeIndex = 0;
      for (int i = 0; i < 65; i++) {
        lexeme[i] = '\0';
      }
    }
    // para o loop de leitura se o caractere lido for de fim de arquivo
    if (character == EOF) {
      break;
    }
    if (character == '\n') {
      buffer->linha++;
    }
  }

  fclose(file);

  return 0;
}