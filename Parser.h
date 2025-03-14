//
// Created by Abram Pittman and Jaidan Sullivan 10/6/2024.
//

#pragma once
#include <string>

class Parser {
private:
    std::string input;       // Full program input
    size_t currentIndex;     // Current index in the input
    std::string currentToken; // Current lexeme being analyzed
    std::string syntaxError; // Stores details of any syntax error

    // Utility methods
    void skipWhitespace();           // Skip any whitespace characters
    std::string getNextToken();      // Retrieve the next token from the input
    bool match(const std::string& token); // Check if the current token matches a specific string
    char peekChar() const;           // Peek at the next character in the input
    char getChar();                  // Consume and return the next character in the input

    // Parsing methods
    bool parseStmt();      // Parse a statement
    bool parseAssignment(); // Parse an assignment statement
    bool parseIfStmt();     // Parse an if statement
    bool parseExpr();       // Parse an expression

public:
    Parser(const std::string& input);  // Constructor with input program
    bool parse();   // Parse the input program and display results
    bool parseProgram();   // Parse the full program (make this public)
};
