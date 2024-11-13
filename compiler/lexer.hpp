#pragma once
#include <vector>
#include "token.hpp"


class Lexer
{
public:
    Lexer(const std::string& src);

    // Tokenize the source code and return a list of tokens
    std::vector<Token> lexerize();

private:
    // Get the identifier at `currentIndex` and move `currentIndex` by the length of the identifier
    std::string readIdentifier();

    // Get the integer at `currentIndex` and move `currentIndex` by the length of the integer
    std::string readInteger();

    std::string source;
    const size_t sourceSize;
    size_t currentIndex = 0;
};
