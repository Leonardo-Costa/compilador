#include "lexer.h"
#include <assert.h>

void test_initializeAutomaton() {
  TabularAutomaton automaton;
  initializeAutomaton(&automaton);

  assert(automaton.initial_state == 0);
  assert(automaton.current_state == 0);

  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      assert(automaton.transition_table[i][j] == -1);
    }
  }

  for (int i = 0; i < 256; i++) {
    assert(automaton.read_string[i] == '\0');
    assert(automaton.lexeme[i] == '\0');
  }
  printf("test_initializeAutomaton passed\n");
}

void test_with_keywords() {
  assert(checkIfKeyword("else") == 26);
  assert(checkIfKeyword("if") == 27);
  assert(checkIfKeyword("int") == 28);
  assert(checkIfKeyword("return") == 29);
  assert(checkIfKeyword("void") == 30);
  assert(checkIfKeyword("while") == 31);
  printf("test_with_keywords passed\n");
}

void test_with_non_keyword_string() {
  assert(checkIfKeyword("nonkeyword") == -1);
  printf("test_with_non_keyword_string passed\n");
}

void test_with_edge_cases() {
  assert(checkIfKeyword("") == -1);
  assert(checkIfKeyword("astringnotinarray") == -1);
  printf("test_with_edge_cases passed\n");
}

void test_with_case_sensitivity() {
  assert(checkIfKeyword("Else") == -1);
  assert(checkIfKeyword("IF") == -1);
  printf("test_with_case_sensitivity passed\n");
}

void test_for_index_27() {
  assert(getTokenTypeFromIndex(27) == COMMENT);
  printf("test_for_index_27 passed\n");
}

void test_for_valid_index_range() {
  assert(getTokenTypeFromIndex(0) == (TokenTypeCMinus)0);
  assert(getTokenTypeFromIndex(EOF_TOKEN - 1) ==
         (TokenTypeCMinus)(EOF_TOKEN - 1));
  printf("test_for_valid_index_range passed\n");
}

void test_for_invalid_index() {
  assert(getTokenTypeFromIndex(-1) == EOF_TOKEN);
  assert(getTokenTypeFromIndex(EOF_TOKEN) == EOF_TOKEN);
  assert(getTokenTypeFromIndex(EOF_TOKEN + 1) == EOF_TOKEN);
  printf("test_for_invalid_index passed\n");
}

void test_for_each_token_name() {
  char *expectedNames[] = {
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
  int numTokens = sizeof(expectedNames) / sizeof(expectedNames[0]);

  for (int i = 0; i < numTokens; i++) {
    char *name = getTokenName(i);
    assert(name != NULL);
    assert(strcmp(name, expectedNames[i]) == 0);
    free(name);
  }
  printf("test_for_each_token_name passed\n");
}

void test_for_invalid_token_indexes() {
  char *name = getTokenName(-1);
  assert(name != NULL);
  assert(strcmp(name, "UNKNOWN_TOKEN") == 0);
  free(name);

  name = getTokenName(EOF_TOKEN);
  assert(name != NULL);
  assert(strcmp(name, "UNKNOWN_TOKEN") == 0);
  free(name);

  name = getTokenName(EOF_TOKEN + 1);
  assert(name != NULL);
  assert(strcmp(name, "UNKNOWN_TOKEN") == 0);
  free(name);

  printf("test_for_invalid_token_indexes passed\n");
}

void test_for_specific_characters() {
  assert(returnCharIndex('l') == 0);
  assert(returnCharIndex('n') == 1);
  assert(returnCharIndex('<') == 2);
  assert(returnCharIndex('>') == 3);
  assert(returnCharIndex('=') == 4);
  assert(returnCharIndex('!') == 5);
  assert(returnCharIndex('/') == 6);
  assert(returnCharIndex('*') == 7);
  assert(returnCharIndex('+') == 8);
  assert(returnCharIndex('-') == 9);
  assert(returnCharIndex(';') == 10);
  assert(returnCharIndex(',') == 11);
  assert(returnCharIndex('(') == 12);
  assert(returnCharIndex(')') == 13);
  assert(returnCharIndex('[') == 14);
  assert(returnCharIndex(']') == 15);
  assert(returnCharIndex('{') == 16);
  assert(returnCharIndex('}') == 17);
  assert(returnCharIndex(' ') == 18);
  assert(returnCharIndex('\n') == 19);
  assert(returnCharIndex('\t') == 20);
  printf("test_for_specific_characters passed\n");
}

void test_for_unhandled_characters() {
  assert(returnCharIndex('#') == -1);
  assert(returnCharIndex('@') == -1);
  assert(returnCharIndex('%') == -1);
  assert(returnCharIndex('^') == -1);
  assert(returnCharIndex('&') == -1);
  assert(returnCharIndex('?') == -1);
  printf("test_for_unhandled_characters passed\n");
}

void test_direct_transition() {
  TabularAutomaton automaton;
  int testState = 1;
  char testChar = 'a';
  int nextState = 2;

  setTransition(&automaton, testState, testChar, nextState, false);
  assert(automaton.transition_table[testState][returnCharIndex(testChar)] ==
         nextState);
  printf("test_direct_transition passed\n");
}

void test_inverse_transition() {
  TabularAutomaton automaton;
  int testState = 1;
  char testChar = 'a';
  int nextState = 2;

  setTransition(&automaton, testState, testChar, nextState, true);

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (i != returnCharIndex(testChar)) {
      assert(automaton.transition_table[testState][i] == nextState);
    }
  }
  printf("test_inverse_transition passed\n");
}

void test_boundary_conditions() {
  TabularAutomaton automaton;
  setTransition(&automaton, 0, 'a', 1, false);
  assert(automaton.transition_table[0][returnCharIndex('a')] == 1);

  setTransition(&automaton, 26, 'z', 27, false);
  assert(automaton.transition_table[26][returnCharIndex('z')] == 27);

  printf("test_boundary_conditions passed\n");
}

void test_unhandled_characters() {
  TabularAutomaton automaton;
  int testState = 1;
  char testChar = '#';
  int nextState = 2;

  setTransition(&automaton, testState, testChar, nextState, false);
  assert(automaton.transition_table[testState][returnCharIndex(testChar)] ==
         nextState);
  printf("test_unhandled_characters passed\n");
}

void test_setting_final_state() {
  TabularAutomaton automaton;

  setFinalState(&automaton, 5);
  assert(automaton.final_state == 5);
  printf("test_setting_final_state with positive value passed\n");
}

void test_accepting_state() {
  TabularAutomaton automaton;
  automaton.final_state = 3;
  automaton.current_state = 3;

  assert(isAcceptingState(&automaton) != 0);
  printf("test_accepting_state passed\n");
}

void test_non_accepting_state() {
  TabularAutomaton automaton;
  automaton.final_state = 3;
  automaton.current_state = 1;

  assert(isAcceptingState(&automaton) == 0);
  printf("test_non_accepting_state passed\n");
}

void test_with_various_states() {
  TabularAutomaton automaton;

  for (int i = 0; i < 5; i++) {
    automaton.final_state = i;
    for (int j = 0; j < 5; j++) {
      automaton.current_state = j;
      assert(isAcceptingState(&automaton) == (i == j));
    }
  }
  printf("test_with_various_states passed\n");
}

void test_clearing_non_empty_string() {
  TabularAutomaton automaton;
  strncpy(automaton.read_string, "Test string", 100);

  clearReadString(&automaton);
  for (int i = 0; i < sizeof(automaton.read_string); i++) {
    assert(automaton.read_string[i] == '\0');
  }
  printf("test_clearing_non_empty_string passed\n");
}

void test_clearing_empty_string() {
  TabularAutomaton automaton;
  memset(automaton.read_string, '\0', sizeof(automaton.read_string));

  clearReadString(&automaton);
  for (int i = 0; i < sizeof(automaton.read_string); i++) {
    assert(automaton.read_string[i] == '\0');
  }
  printf("test_clearing_empty_string passed\n");
}

void test_with_lowercase_letters() {
  for (char c = 'a'; c <= 'z'; c++) {
    assert(isLetter(c) != 0);
  }
  printf("test_with_lowercase_letters passed\n");
}

void test_with_uppercase_letters() {
  for (char c = 'A'; c <= 'Z'; c++) {
    assert(isLetter(c) != 0);
  }
  printf("test_with_uppercase_letters passed\n");
}

void test_with_non_letter_characters() {
  char nonLetters[] = "0123456789`~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/? \n\t";
  for (int i = 0; nonLetters[i] != '\0'; i++) {
    assert(isLetter(nonLetters[i]) == 0);
  }
  printf("test_with_non_letter_characters passed\n");
}

void test_boundary_cases() {
  assert(isLetter('@') == 0);
  assert(isLetter('[') == 0);
  assert(isLetter('`') == 0);
  assert(isLetter('{') == 0);
  printf("test_boundary_cases passed\n");
}

void test_with_standard_special_characters() {
  char specialChars[] = {'+', '-', ',', ';', '(', ')', '{', '}', '[', ']'};
  for (int i = 0; i < sizeof(specialChars) / sizeof(specialChars[0]); i++) {
    assert(isStandartSpecialCharacter(specialChars[i]) != 0);
  }
  printf("test_with_standard_special_characters passed\n");
}

void test_with_non_special_characters() {
  char nonSpecialChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY"
                           "Z0123456789`~!@#$%^&*_=\\|:\"'<.>? \n\t";
  for (int i = 0; nonSpecialChars[i] != '\0'; i++) {
    assert(isStandartSpecialCharacter(nonSpecialChars[i]) == 0);
  }
  printf("test_with_non_special_characters passed\n");
}

void test_is_number_with_standard_special_characters() {
  char specialChars[] = {'+', '-', ',', ';', '(', ')', '{', '}', '[', ']'};
  for (int i = 0; i < sizeof(specialChars) / sizeof(specialChars[0]); i++) {
    assert(isStandartSpecialCharacter(specialChars[i]) != 0);
  }
  printf("test_is_number_with_standard_special_characters passed\n");
}

void test_is_number_with_non_special_characters() {
  char nonSpecialChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY"
                           "Z0123456789`~!@#$%^&*_=\\|:\"'<.>? \n\t";
  for (int i = 0; nonSpecialChars[i] != '\0'; i++) {
    assert(isStandartSpecialCharacter(nonSpecialChars[i]) == 0);
  }
  printf("test_is_number_with_non_special_characters passed\n");
}

void test_with_normal_strings_and_characters() {
  char *result = joinCharAndString("Test", 'A');
  assert(result != NULL);
  assert(strcmp(result, "TestA") == 0);
  free(result);

  result = joinCharAndString("Hello", '!');
  assert(result != NULL);
  assert(strcmp(result, "Hello!") == 0);
  free(result);

  printf("test_with_normal_strings_and_characters passed\n");
}

void test_with_empty_string() {
  char *result = joinCharAndString("", 'Z');
  assert(result != NULL);
  assert(strcmp(result, "Z") == 0);
  free(result);

  printf("test_with_empty_string passed\n");
}

void test_resulting_string_length() {
  char *result = joinCharAndString("ABC", 'D');
  assert(result != NULL);
  assert(strlen(result) == 4);
  free(result);

  printf("test_resulting_string_length passed\n");
}

void test_with_letters() {
  for (char c = 'a'; c <= 'z'; c++) {
    assert(getLocalCharacter(c) == 'l');
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    assert(getLocalCharacter(c) == 'l');
  }
  printf("test_with_letters passed\n");
}

void test_with_numbers() {
  for (char c = '0'; c <= '9'; c++) {
    assert(getLocalCharacter(c) == 'n');
  }
  printf("test_with_numbers passed\n");
}

void test_with_non_alphanumeric_characters() {
  char nonAlphanumericChars[] = "`~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/? \n\t";
  for (int i = 0; nonAlphanumericChars[i] != '\0'; i++) {
    assert(getLocalCharacter(nonAlphanumericChars[i]) ==
           nonAlphanumericChars[i]);
  }
  printf("test_with_non_alphanumeric_characters passed\n");
}

void test_with_non_empty_file() {
  FILE *mockFile = fopen("../mocks/mock_file.txt", "w+");
  fprintf(mockFile, "Test\nLine2");
  rewind(mockFile);

  Buffer buffer;
  memset(&buffer, '\0', sizeof(buffer));

  assert(get_next_char(mockFile, &buffer) == 'T');
  assert(get_next_char(mockFile, &buffer) == 'e');
  fclose(mockFile);
  printf("test_with_non_empty_file passed\n");
}

void test_end_of_file() {
  FILE *mockFile = fopen("../mocks/empty_file.txt", "w+");
  Buffer buffer;
  memset(&buffer, '\0', sizeof(buffer));

  assert(get_next_char(mockFile, &buffer) == EOF);
  fclose(mockFile);
  printf("test_end_of_file passed\n");
}

void test_buffer_reset() {
  FILE *mockFile = fopen("../mocks/mock_file_newline.txt", "w+");
  fprintf(mockFile, "\n");
  rewind(mockFile);

  Buffer buffer;
  memset(&buffer, '\0', sizeof(buffer));

  get_next_char(mockFile, &buffer);
  assert(buffer.prox_char == 0);
  fclose(mockFile);
  printf("test_buffer_reset passed\n");
}

void test_continuous_reading() {
  FILE *mockFile = fopen("../mocks/mock_file_continuous.txt", "w+");
  fprintf(mockFile, "AB\nCD");
  rewind(mockFile);

  Buffer buffer;
  memset(&buffer, '\0', sizeof(buffer));

  assert(get_next_char(mockFile, &buffer) == 'A');
  assert(get_next_char(mockFile, &buffer) == 'B');
  assert(get_next_char(mockFile, &buffer) == '\n');
  assert(get_next_char(mockFile, &buffer) == 'C');
  fclose(mockFile);
  printf("test_continuous_reading passed\n");
}

void test_successful_allocation() {
  int size = 100;
  Buffer *buffer = allocate_buffer(size);

  assert(buffer != NULL);
  assert(buffer->prox_char == 0);
  assert(buffer->linha == 1);
  for (int i = 0; i < size; i++) {
    assert(buffer->data[i] == '\0');
  }
  free(buffer);

  printf("test_successful_allocation passed\n");
}

void test_deallocating_valid_buffer() {
  Buffer *buffer = allocate_buffer(100);
  deallocate_buffer(buffer);
  printf("test_deallocating_valid_buffer passed\n");
}

void test_with_null_pointer() {
  Buffer *buffer = NULL;
  deallocate_buffer(buffer);
  printf("test_with_null_pointer passed\n");
}

int main() {
  test_initializeAutomaton();
  test_with_keywords();
  test_with_non_keyword_string();
  test_with_edge_cases();
  test_with_case_sensitivity();
  test_for_index_27();
  test_for_valid_index_range();
  test_for_invalid_index();
  test_for_each_token_name();
  test_for_invalid_token_indexes();
  test_for_specific_characters();
  test_for_unhandled_characters();
  test_direct_transition();
  test_inverse_transition();
  test_boundary_conditions();
  test_unhandled_characters();
  test_setting_final_state();
  test_accepting_state();
  test_non_accepting_state();
  test_with_various_states();
  test_clearing_non_empty_string();
  test_clearing_empty_string();
  test_with_lowercase_letters();
  test_with_uppercase_letters();
  test_with_non_letter_characters();
  test_boundary_cases();
  test_with_standard_special_characters();
  test_with_non_special_characters();
  test_is_number_with_standard_special_characters();
  test_is_number_with_non_special_characters();
  test_with_normal_strings_and_characters();
  test_with_empty_string();
  test_resulting_string_length();
  test_with_letters();
  test_with_numbers();
  test_with_non_alphanumeric_characters();
  test_with_non_empty_file();
  test_end_of_file();
  test_buffer_reset();
  test_continuous_reading();
  test_successful_allocation();
  test_deallocating_valid_buffer();
  test_with_null_pointer();
  return 0;
}