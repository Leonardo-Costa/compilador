#include "lexer.h"

void initializeAutomaton(TabularAutomaton *automaton) {
  memset(automaton->read_string, 0, sizeof(automaton->read_string));
  memset(automaton->lexeme, 0, sizeof(automaton->read_string));
  automaton->initial_state = 0;
  automaton->current_state = automaton->initial_state;
  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      automaton->transition_table[i][j] = -1;
    }
  }
}

char *keywords[7] = {"else", "if", "int", "return", "void", "while"};

int keywords_index[6] = {26, 27, 28, 29, 30, 31};

int checkIfKeyword(char *lexeme) {
  int left = 0;
  int right = 5;

  while (left <= right) {
    int middle = left + (right - left) / 2;
    int cmp = strcmp(lexeme, keywords[middle]);

    if (cmp == 0) {
      return keywords_index[middle];
    } else if (cmp < 0) {
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  }

  return -1;
}

TokenTypeCMinus getTokenTypeFromIndex(int index) {
  if (index == 27) {
    return COMMENT;
  }
  if (index >= 0 && index < EOF_TOKEN) {
    return (TokenTypeCMinus)index;
  } else {
    return EOF_TOKEN;
  }
}

char *getTokenName(int token) {
  static char *tokenNames[] = {
      "NA",
      "EOF",
      "ID",
      "NUM",
      "LT",
      "LTE",
      "GT",
      "GTE",
      "ATTR",
      "EQ",
      "NA3",
      "NE",
      "SUM",
      "MULT",
      "COMMENT_END",
      "DIV",
      "COMMENT_START",
      "SUB",
      "OPEN_PAR",
      "CLOSE_PAR",
      "OPEN_CUR",
      "CLOSE_CUR",
      "OPEN_BRA",
      "CLOSE_BRA",
      "SEMICOLON",
      "COMMA",
      "KW_ELSE",
      "KW_IF",
      "KW_INT",
      "KW_RETURN",
      "KW_VOID",
      "KW_WHILE",
      "COMMENT",
  };

  char *tokenName;

  if (token >= 0 && token < EOF_TOKEN) {
    tokenName = tokenNames[(int)token];
  } else {
    tokenName = "UNKNOWN_TOKEN";
  }

  char *dynamicTokenName = malloc(strlen(tokenName) + 1);
  if (dynamicTokenName != NULL) {
    strcpy(dynamicTokenName, tokenName);
  }

  return dynamicTokenName;
}

int returnCharIndex(char character) {
  if (character == 'l')
    return 0; // representa as letras
  if (character == 'n')
    return 1; // representa os numeros
  if (character == '<')
    return 2;
  if (character == '>')
    return 3;
  if (character == '=')
    return 4;
  if (character == '!')
    return 5;
  if (character == '/')
    return 6;
  if (character == '*')
    return 7;
  if (character == '+')
    return 8;
  if (character == '-')
    return 9;
  if (character == ';')
    return 10;
  if (character == ',')
    return 11;
  if (character == '(')
    return 12;
  if (character == ')')
    return 13;
  if (character == '[')
    return 14;
  if (character == ']')
    return 15;
  if (character == '{')
    return 16;
  if (character == '}')
    return 17;
  if (character == ' ')
    return 18;
  if (character == '\n')
    return 19;
  if (character == '\t')
    return 20;
}

void setTransition(TabularAutomaton *automaton, int state, char character,
                   int next_state, bool inverse) {
  int char_index = returnCharIndex(character);
  if (inverse) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      if (i != char_index) {
        automaton->transition_table[state][i] = next_state;
      }
    }
  }
  if (!inverse) {
    automaton->transition_table[state][char_index] = next_state;
  }
}

void setFinalState(TabularAutomaton *automaton, int finalState) {
  automaton->final_state = finalState;
}

int isAcceptingState(TabularAutomaton *automaton) {
  return automaton->current_state == automaton->final_state;
}

void clearReadString(TabularAutomaton *automaton) {
  for (int i = 0; i < sizeof(automaton->read_string); i++) {
    automaton->read_string[i] = '\0';
  }
}

int isLetter(char character) {
  return (character >= 'a' && character <= 'z') ||
         (character >= 'A' && character <= 'Z');
}

bool isStandartSpecialCharacter(char character) {
  return (character == '+' || character == '-' || character == ',' ||
          character == ';' || character == '(' || character == ')' ||
          character == '{' || character == '}' || character == '[' ||
          character == ']');
}

bool isNumber(char character) {
  return (character == '0' || character == '1' || character == '2' ||
          character == '3' || character == '4' || character == '5' ||
          character == '6' || character == '7' || character == '8' ||
          character == '9');
}

char *joinCharAndString(const char *str, char character) {
  size_t len = strlen(str);
  char *result = (char *)malloc(len + 2);

  if (result) {
    strcpy(result, str);
    result[len] = character;
    result[len + 1] = '\0';
  }

  return result;
}

char getLocalCharacter(char character) {
  if (isLetter(character)) {
    return 'l';
  } else if (isNumber(character)) {
    return 'n';
  } else {
    return character;
  }
}

bool processInput(TabularAutomaton *automaton, const char character,
                  bool keepState, bool processAgain) {
  automaton->last_character = character;
  char local_character = getLocalCharacter(character);
  int char_index = returnCharIndex(local_character);

  if (char_index >= 0 && char_index < ALPHABET_SIZE) {
    int next_state =
        automaton->transition_table[automaton->current_state][char_index];
    if (next_state != -1) {
      if (keepState) {
        automaton->prior_state = automaton->current_state;
      }
      automaton->current_state = next_state;
    }

    // printf("Current state: %d, character: %c\n", automaton->current_state,
    // character);
    if (isAcceptingState(automaton)) {
      // printf("lexeme found: %s\n", automaton->read_string);
      strncpy(automaton->lexeme, automaton->read_string,
              strlen(automaton->read_string) + 1);
      automaton->lexeme[strlen(automaton->read_string)] = '\0';
      clearReadString(automaton);
      int tokenType = automaton->prior_state;
      automaton->current_state = automaton->initial_state;
      if (processAgain) {
        processInput(automaton, automaton->last_character, false, true);
      }
      return tokenType;
    } else if (next_state == -1) {
      printf("Error, character: %c\n", character);
      return false;
    } else {
      if (character != ' ' && character != '\n') {
        char *new_read_string =
            joinCharAndString(automaton->read_string, character);
        if (new_read_string) {
          strcpy(automaton->read_string, new_read_string);
          free(new_read_string);
        }
      }
    }
  } else {
    printf("Invalid character in input: %c\n", character);
    return false;
  }
  return false;
}

void setTransitions(TabularAutomaton *automaton) {
  setTransition(automaton, q1, ' ', q1, false);
  setTransition(automaton, q1, '\n', q1, false);
  setTransition(automaton, q1, '\t', q1, false);

  // Automato para letras de a-z e A-Z
  setTransition(automaton, q1, 'l', q3, false);
  setTransition(automaton, q3, 'l', q3, false);
  setTransition(automaton, q3, 'l', q2, true);

  // Automato para numeros de 0-9
  setTransition(automaton, q1, 'n', q4, false);
  setTransition(automaton, q4, 'n', q4, false);
  setTransition(automaton, q4, 'n', q2, true);

  // Automato para < e <=
  setTransition(automaton, q1, '<', q5, false);
  setTransition(automaton, q5, '.', q2, true);
  setTransition(automaton, q5, '=', q6, false);
  setTransition(automaton, q6, '.', q2, true);

  // Automato para > e >=
  setTransition(automaton, q1, '>', q7, false);
  setTransition(automaton, q7, '.', q2, true);
  setTransition(automaton, q7, '=', q8, false);
  setTransition(automaton, q8, '.', q2, true);

  // Automato para = e ==
  setTransition(automaton, q1, '=', q9, false);
  setTransition(automaton, q9, '.', q2, true);
  setTransition(automaton, q9, '=', q10, false);
  setTransition(automaton, q10, '.', q2, true);

  // Automato para * e */
  setTransition(automaton, q1, '*', q14, false);
  setTransition(automaton, q14, '.', q2, true);

  // Automato para / e /*
  setTransition(automaton, q1, '/', q16, false);
  setTransition(automaton, q16, '.', q2, true);

  // Automato para /* e */
  setTransition(automaton, q1, '/', q16, false);
  setTransition(automaton, q16, '*', q17, false);
  setTransition(automaton, q17, '.', q17, true);
  setTransition(automaton, q27, '.', q27, true);
  setTransition(automaton, q17, '*', q27, false);
  setTransition(automaton, q27, '/', q28, false);
  setTransition(automaton, q28, '.', q2, true);

  // Automato para !=
  setTransition(automaton, q1, '!', q11, false);
  setTransition(automaton, q11, '=', q12, false);
  setTransition(automaton, q12, '=', q2, true);

  // Automato para +
  setTransition(automaton, q1, '+', q13, false);
  setTransition(automaton, q13, '.', q2, true);

  // Automato para -
  setTransition(automaton, q1, '-', q18, false);
  setTransition(automaton, q18, '.', q2, true);

  // Automato para (
  setTransition(automaton, q1, '(', q19, false);
  setTransition(automaton, q19, '.', q2, true);

  // Automato para )
  setTransition(automaton, q1, ')', q20, false);
  setTransition(automaton, q20, '.', q2, true);

  // Automato para {
  setTransition(automaton, q1, '{', q21, false);
  setTransition(automaton, q21, '.', q2, true);

  // Automato para }
  setTransition(automaton, q1, '}', q22, false);
  setTransition(automaton, q22, '.', q2, true);

  // Automato para [
  setTransition(automaton, q1, '[', q23, false);
  setTransition(automaton, q23, '.', q2, true);

  // Automato para ]
  setTransition(automaton, q1, ']', q24, false);
  setTransition(automaton, q24, '.', q2, true);

  // Automato para ;
  setTransition(automaton, q1, ';', q25, false);
  setTransition(automaton, q25, '.', q2, true);

  // Automato para ,
  setTransition(automaton, q1, ',', q26, false);
  setTransition(automaton, q26, '.', q2, true);
}

char get_next_char(FILE *file, Buffer *buffer) {
  if (buffer->data[buffer->prox_char] == '\0') {
    if (fgets(buffer->data, 256, file) == NULL) {
      return EOF;
    }
    buffer->prox_char = 0;
  }
  char current_char = buffer->data[buffer->prox_char++];

  if (current_char == '\0' || current_char == '\n') {
    memset(buffer->data, '\0', 256);
    buffer->prox_char = 0;
  }

  return current_char;
}

Buffer *allocate_buffer(int size) {
  Buffer *buffer = (Buffer *)malloc(sizeof(Buffer));
  if (buffer == NULL) {
    return NULL;
  }

  buffer->prox_char = 0;
  buffer->linha = 1;
  for (int i = 0; i < size; i++) {
    buffer->data[i] = '\0';
  }
  return buffer;
}

void deallocate_buffer(Buffer *buffer) {
  if (buffer != NULL) {
    free(buffer);
  }
}

void configureAutomaton(TabularAutomaton *automaton, Buffer **buffer,
                        FILE *file) {
  *buffer = allocate_buffer(256);
  if (*buffer == NULL) {
    printf("Erro ao alocar o buffer.\n");
    fclose(file);
    return;
  }
  (*buffer)->prox_char = 0;
  initializeAutomaton(automaton);
  setTransitions(automaton);
  setFinalState(automaton, q2);
}

LexemeInfo lexer(FILE *file) {
  static TabularAutomaton automaton;
  static int is_initialized = 0;
  static bool endOfFile = false;
  char character;
  bool lexemeFound;
  bool newLine;
  LexemeInfo lexemeInfo;
  Buffer *buffer;

  if (!is_initialized) {
    configureAutomaton(&automaton, &buffer, file);
    is_initialized = 1;
  }

  while (!lexemeFound) {
    character = get_next_char(file, buffer);
    newLine = false;

    if (character == '\n') {
      buffer->linha++;
      newLine = true;
    }

    if (character == EOF) {
      if (!endOfFile) {
        endOfFile = true;
      } else {
        lexemeInfo.lexeme = "EOF";
        lexemeInfo.line = buffer->linha;
        lexemeInfo.token = 1;
        return lexemeInfo;
      }
      lexemeFound = processInput(&automaton, ' ', true, false);
    } else {
      lexemeFound = processInput(&automaton, character, true, true);
    }

    if (lexemeFound) {
      //   printf("lexeme found: %s, token: %d\n", automaton.lexeme,
      //  getTokenTypeFromIndex(automaton.prior_state));
      if (getTokenTypeFromIndex(automaton.prior_state) == 32) {
        lexemeFound = processInput(&automaton, character, true, true);
      }
      char *result = (char *)malloc(strlen(automaton.lexeme) + 1);
      if (result) {
        strcpy(result, automaton.lexeme);
      }
      lexemeInfo.lexeme = result;
      if (newLine) {
        lexemeInfo.line = buffer->linha - 1;
      } else {
        lexemeInfo.line = buffer->linha;
      }
      if (automaton.prior_state == 2) {
        if (checkIfKeyword(lexemeInfo.lexeme) == -1) {
          lexemeInfo.token = 2;
        } else {
          lexemeInfo.token = checkIfKeyword(lexemeInfo.lexeme);
        }
        return lexemeInfo;
      }
      lexemeInfo.token = getTokenTypeFromIndex(automaton.prior_state);
      if (lexemeInfo.token != NA) {
        return lexemeInfo;
      }
    }
  }
}
