#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define NUM_STATES 28
#define ALPHABET_SIZE 20


typedef struct TabularAutomaton
{
    int transition_table[NUM_STATES][ALPHABET_SIZE];
    int current_state;
    int prior_state;
    int final_state;
    int initial_state;
    char read_string[256];
    char last_character;
    char lexeme[256];
} TabularAutomaton;

typedef struct
{
    int prox_char;
    int linha;
    char data[256];
} Buffer;

typedef enum
{
    NA,
    NA2,
    ID,
    NUM,
    LT,
    LTE,
    GT,
    GTE,
    ATTR,
    EQ,
    NA3,
    NE,
    SUM,
    MULT,
    COMMENT_END,
    DIV,
    COMMENT_START,
    SUB,
    OPEN_PAR,
    CLOSE_PAR,
    OPEN_CUR,
    CLOSE_CUR,
    OPEN_BRA,
    CLOSE_BRA,
    SEMICOLON,
    COMMA,
    KW_ELSE,
    KW_IF,
    KW_INT,
    KW_RETURN,
    KW_VOID,
    KW_WHILE,
    COMMENT,
    EOF_TOKEN
} TokenTypeCMinus;

typedef struct
{
    char *lexeme;
    int line;
    TokenTypeCMinus token;
} LexemeInfo;

enum States
{
    q0 = -1,
    q1 = 0,
    q2,
    q3,
    q4,
    q5,
    q6,
    q7,
    q8,
    q9,
    q10,
    q11,
    q12,
    q13,
    q14,
    q15,
    q16,
    q17,
    q18,
    q19,
    q20,
    q21,
    q22,
    q23,
    q24,
    q25,
    q26,
    q27,
    q28,
};

void initializeAutomaton(TabularAutomaton *automaton);
int returnCharIndex(char character);
void setTransition(TabularAutomaton *automaton, int state, char character, int next_state, bool inverse);
void setFinalState(TabularAutomaton *automaton, int finalState);
int isAcceptingState(TabularAutomaton *automaton);
void clearReadString(TabularAutomaton *automaton);
int isLetter(char character);
bool isStandartSpecialCharacter(char character);
bool isNumber(char character);
char *joinCharAndString(const char *str, char character);
bool processInput(TabularAutomaton *automaton, const char character, bool keepState);
void setTransitions(TabularAutomaton *automaton);
void configureAutomaton(TabularAutomaton *automaton, Buffer **buffer, FILE *file);
char get_next_char(FILE *file, Buffer *buffer);
LexemeInfo lexer(FILE *file);
Buffer *allocate_buffer(int size);
void deallocate_buffer(Buffer *buffer);
void fill_buffer(FILE *file, Buffer *buffer);
char *getTokenName(int token);

#endif /* LEXER_H */
