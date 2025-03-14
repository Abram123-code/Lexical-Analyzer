//
// Created by Abram Pittman and Jaidan Sullivan 10/6/2024.
//

#include "Parser.h"
#include <iostream>  // Include the iostream header for cout

// Constructor: Initialize the parser with the program input
Parser::Parser(const std::string& input) : input(input), currentIndex(0), syntaxError("") {}

// Skip over whitespace
void Parser::skipWhitespace() {
    while (currentIndex < input.size() && std::isspace(input[currentIndex])) {
        ++currentIndex;
    }
}

// Peek at the next character
char Parser::peekChar() const {
    return currentIndex < input.size() ? input[currentIndex] : '\0';
}

// Consume and return the next character
char Parser::getChar() {
    return currentIndex < input.size() ? input[currentIndex++] : '\0';
}

// Retrieve the next token from the input
std::string Parser::getNextToken() {
    skipWhitespace();
    if (std::isalpha(peekChar()) || peekChar() == '_') {
        // Parse an identifier or keyword
        std::string token;
        while (std::isalnum(peekChar()) || peekChar() == '_') {
            token += getChar();
        }
        return token;
    } else if (std::isdigit(peekChar())) {
        // Parse a number
        std::string token;
        while (std::isdigit(peekChar()) || peekChar() == '.') {
            token += getChar();
        }
        return token;
    } else {
        // Parse a single character token
        return std::string(1, getChar());
    }
}

// Check if the current token matches the expected token
bool Parser::match(const std::string& token) {
    if (currentToken == token) {
        currentToken = getNextToken();  // Move to the next token
        return true;
    }
    return false;
}

// Main entry point to parse the program
bool Parser::parse() {
    currentToken = getNextToken();  // Get the first token
    if (parseProgram()) {
        std::cout << "The program is generated by the grammar." << std::endl;  // Use std::cout
        return true;
    } else {
        std::cout << "The program cannot be generated by the EBNF Described Language." << std::endl;  // Use std::cout
        return false;
    }
}

// Parse the full program (a sequence of statements)
bool Parser::parseProgram() {
    while (!currentToken.empty()) {
        if (!parseStmt()) {
            return false;
        }
    }
    return true;
}

// Parse a statement: assignment or if statement
bool Parser::parseStmt() {
    return parseAssignment() || parseIfStmt();
}

// Parse an assignment: <identifier> = <expr> ;
bool Parser::parseAssignment() {
    if (std::isalpha(currentToken[0])) {
        if (match(currentToken) && match("=") && parseExpr() && match(";")) {
            return true;
        }
    }
    return false;
}

// Parse an if statement: if ( <expr> ) <stmt>
bool Parser::parseIfStmt() {
    return match("if") && match("(") && parseExpr() && match(")") && parseStmt();
}

// Parse an expression (for simplicity, just assume any identifier or number is valid)
bool Parser::parseExpr() {
    return std::isalpha(currentToken[0]) || std::isdigit(currentToken[0]) ? match(currentToken) : false;
}
