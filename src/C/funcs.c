#include "funcs.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

Buffer *allocate_buffer(int size) {
  Buffer *buffer = (Buffer *)malloc(sizeof(Buffer));
  if (buffer == NULL) {
    return NULL;
  }

  buffer->prox_char = 0;
  buffer->linha = 1;
  for (int i=0; i < size; i++) {
    buffer->data[i] = '\0';
  }
  return buffer;
}

void deallocate_buffer(Buffer *buffer) {
  if (buffer != NULL) {
    free(buffer);
  }
}

char get_char(Buffer *buffer) {
  int i = buffer->prox_char;
  buffer->prox_char += 1;
  return buffer->data[i];
}

char get_next_char(FILE *file, Buffer *buffer) {
  if (buffer->data[buffer->prox_char] == '\0') {
    if (fgets(buffer->data, 256, file) == NULL) {
      return EOF;
    }
    buffer->prox_char = 0;
  }    
  if (buffer->data[buffer->prox_char] == '\n') {
    if (fgets(buffer->data, 256, file) == NULL) {
      return EOF;
    }
    buffer->prox_char = 0;
    return '\n';
    }
  return get_char(buffer);
}
