# Compile and Run C Code

To compile and run the C code, use the following command in your terminal:

```
python main.py -r
```

# Lexer
The lexer in the compiler repository, as defined in lexer.c and lexer.h, implements a lexical analyzer using a tabular automaton. Here's a summary of how it works:

Initialization: The initializeAutomaton function sets up the automaton with an initial state, resets the read string and lexeme buffers, and initializes the transition table with default values.

Keywords and Tokens: It defines a list of keywords (like "if", "int", "return", etc.) and their corresponding token indices. The checkIfKeyword function checks if a lexeme is a keyword and returns the appropriate token index.

Character Classification: The lexer classifies characters into different categories (letters, numbers, special characters, etc.) and uses these classifications to determine transitions between states.

Transitions: The setTransition function defines the transitions between states for different character inputs. It can set transitions for specific characters or inversely for all characters except a specific one.

Buffer Management: The lexer uses a buffer to manage the input file's characters. The get_next_char function reads the next character from the buffer, handling the end of the file and new lines.

Token Generation: The processInput function processes each character read from the input and performs state transitions. When an accepting state is reached, it identifies the lexeme and generates a token.

Automaton Configuration: The configureAutomaton function is responsible for setting up the automaton with transitions and final states before starting the lexing process.

Lexing Process: The lexer function is the main entry point for the lexing process. It uses the automaton to read characters from the file, process them, and return lexeme information, including the lexeme itself, the line number, and the token type.

The lexer is designed to recognize various tokens such as identifiers, numbers, and special characters, and it can handle comments and whitespace. The automaton's states and transitions are set up to recognize the syntax of the C-Minus language as specified in the source code.