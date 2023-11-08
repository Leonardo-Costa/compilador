#include "funcs.h"

int main(int argc, char *argv[])
{
  const char *fileName = argv[1];

  if (argc != 2)
  {
    return 1;
  }

  FILE *file = fopen(fileName, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo");
    return 1;
  }

  Buffer *buffer = allocate_buffer(256);
  if (buffer == NULL)
  {
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

  while (1)
  {
    // le caractere por caractere do buffer
    char character = get_next_char(file, buffer);

    char *lexeme = lexer(character);

    if (strcmp(lexeme, "NO_LEXEME_FOUND") != 0)
    {
      printf("Lexeme: %s\n", lexeme);
      free(lexeme); // Make sure to free the dynamically allocated memory.
    }
    // para o loop de leitura se o caractere lido for de fim de arquivo
    if (character == EOF)
    {
      break;
    }
    if (character == '\n')
    {
      buffer->linha++;
    }
  }

  fclose(file);

  return 0;
}