#include <string>


enum class TokenType
{
    IDENTIFIER,
    ASSIGNMENT,
    INTEGER,
    OPERATOR
};


struct Token
{
    Token(TokenType t, const std::string& v) : type(t), identifier(v) {}

    TokenType type;
    const std::string identifier;
};
