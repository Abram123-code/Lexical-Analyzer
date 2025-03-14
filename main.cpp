// Created by Abram Pittman and Jaidan Sullivan 10/6/2024.

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>
#include "Parser.h"


// Enum to represent different token types
enum class TokenType {
    INT,
    FLOAT,
    IDENTIFIER,
    ASSIGN,
    SEMICOLON,
    OPERATOR,
    IF,
    LESS_THAN,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    UNKNOWN,
    END_OF_FILE
};

// Structure to represent a token
struct Token {
    TokenType type;
    std::string lexeme;
};

// Function to create a token
Token createToken(TokenType type, const std::string& lexeme) {
    return Token{type, lexeme};
}

// Function to identify token type
TokenType getTokenType(const std::string& lexeme) {
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"int", TokenType::INT},
        {"float", TokenType::FLOAT},
        {"if", TokenType::IF}
    };

    if (keywords.count(lexeme)) {
        return keywords.at(lexeme);
    } else if (std::isdigit(lexeme[0])) {
        return lexeme.find('.') != std::string::npos ? TokenType::FLOAT : TokenType::INT;
    } else if (std::isalpha(lexeme[0]) || lexeme[0] == '_') {
        return TokenType::IDENTIFIER;
    } else if (lexeme == "=") {
        return TokenType::ASSIGN;
    } else if (lexeme == ";") {
        return TokenType::SEMICOLON;
    } else if (lexeme == "<") {
        return TokenType::LESS_THAN;
    } else if (lexeme == "(") {
        return TokenType::LEFT_PAREN;
    } else if (lexeme == ")") {
        return TokenType::RIGHT_PAREN;
    } else if (lexeme == "{") {
        return TokenType::LEFT_BRACE;
    } else if (lexeme == "}") {
        return TokenType::RIGHT_BRACE;
    } else {
        return TokenType::UNKNOWN;
    }
}

// Function to tokenize a line of code
void tokenize(const std::string& line) {
    std::string lexeme;
    for (size_t i = 0; i < line.length(); ++i) {
        char ch = line[i];

        // Ignore comments
        if (line.substr(i, 2) == "//") {
            break; // Ignore the rest of the line
        }

        if (std::isspace(ch)) {
            // Process accumulated lexeme
            if (!lexeme.empty()) {
                Token token = createToken(getTokenType(lexeme), lexeme);
                std::cout << "Token: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme << std::endl;
                lexeme.clear();
            }
        } else if (std::isalnum(ch) || ch == '_') {
            lexeme += ch; // Accumulate identifier or number
        } else {
            // Handle individual characters (operators and symbols)
            if (!lexeme.empty()) {
                Token token = createToken(getTokenType(lexeme), lexeme);
                std::cout << "Token: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme << std::endl;
                lexeme.clear();
            }
            lexeme += ch; // Single character token
            Token token = createToken(getTokenType(lexeme), lexeme);
            std::cout << "Token: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme << std::endl;
            lexeme.clear();
        }
    }
    // Handle any remaining lexeme
    if (!lexeme.empty()) {
        Token token = createToken(getTokenType(lexeme), lexeme);
        std::cout << "Token: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme << std::endl;
    }
}

int main() {
    // Open the first input file
    std::ifstream inputFile1("C:/Users/abram/CLionProjects/Comp360project1/Test1.txt");
    if (!inputFile1.is_open()) {
        std::cerr << "Error: Cannot open the file 'Test1.txt'!" << std::endl;
        return 1;
    }

    // Open the second input file
    std::ifstream inputFile2("C:/Users/abram/CLionProjects/Comp360project1/Test2.txt");
    if (!inputFile2.is_open()) {
        std::cerr << "Error: Cannot open the file 'Test2.txt'!" << std::endl;
        inputFile1.close(); // Close the first file before exiting
        return 1;
    }

    // Tokenize and parse the first file
    std::string fileContents1((std::istreambuf_iterator<char>(inputFile1)), std::istreambuf_iterator<char>());
    inputFile1.clear();
    inputFile1.seekg(0);

    std::string line;
    std::cout << "Testing Test1.txt:\n";
    while (std::getline(inputFile1, line)) {
        tokenize(line);
    }

    Parser parser1(fileContents1); // Create parser for the first file
    parser1.parse();

    // Tokenize and parse the second file
    std::string fileContents2((std::istreambuf_iterator<char>(inputFile2)), std::istreambuf_iterator<char>());
    inputFile2.clear();
    inputFile2.seekg(0);

    std::cout << "\nTesting Test2.txt:\n";
    while (std::getline(inputFile2, line)) {
        tokenize(line);
    }

    Parser parser2(fileContents2);
    parser2.parse(); // Parse the second file

    // Close both files
    inputFile1.close();
    inputFile2.close();

    return 0;
}
