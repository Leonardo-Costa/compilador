#include "funcs.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL,"");
  const char *fileName = argv[1];

  if (argc != 2) {
    return 1;
  }

  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo");
    return 1;
  }

  while (1) {
    LexemeInfo lexemeInfo = lexer(file);

    if (strcmp(lexemeInfo.lexeme, "NO_LEXEME_FOUND") != 0) {
      char *tokenName = getTokenName(lexemeInfo.token);
      if (lexemeInfo.token != 1) {
        printf("Line: %d, Lexeme: %s, Token: %s\n", lexemeInfo.line,
               lexemeInfo.lexeme, tokenName ? tokenName : "NULL");
      }
    }
    if (strcmp(lexemeInfo.lexeme, "EOF") == 0) {
      break;
    }
  }

  fclose(file);

  return 0;
}