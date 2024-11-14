#pragma once
#include <string>


enum class TokenType
{
    IDENTIFIER,
    ASSIGNMENT,
    OPERATOR,
    INTEGER_CONSTANT,
    STRING_CONSTANT
};


struct Token
{
    Token(TokenType t, const std::string& v) : type(t), value(v) {}

    TokenType type;
    const std::string value;
};
