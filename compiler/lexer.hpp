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
    std::string source;
    const size_t sourceSize;
    size_t currentIndex = 0;

    std::string readIdentifier();
    std::string readInteger();
    std::string readString();
};
