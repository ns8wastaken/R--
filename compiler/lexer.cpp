#include "lexer.hpp"


Lexer::Lexer(const std::string& src) : source(src), sourceSize(src.size())
{}


std::vector<Token> Lexer::lexerize()
{
    std::vector<Token> tokens = {};

    while (currentIndex < source.size()) {
        char currentChar = source[currentIndex];

        if (std::isspace(currentChar)) {
            currentIndex++;
        }

        else if (currentChar == '"') {
            tokens.push_back(Token(TokenType::STRING_CONSTANT, readString()));
        }

        else if (std::isalpha(currentChar)) {
            tokens.push_back(Token(TokenType::IDENTIFIER, readIdentifier()));
        }

        else if (std::isdigit(currentChar)) {
            tokens.push_back(Token(TokenType::INTEGER_CONSTANT, readInteger()));
        }

        else if (currentChar == '=') {
            tokens.push_back(Token(TokenType::ASSIGNMENT, "="));
            currentIndex++;
        }

        else if (currentChar == '+') {
            tokens.push_back(Token(TokenType::OPERATOR, "+"));
            currentIndex++;
        }

        // else {
        //     tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, currentChar)));
        //     currentIndex++;
        // }
    }

    return tokens;
}


std::string Lexer::readIdentifier()
{
    size_t start = currentIndex;
    while (currentIndex < source.size() && std::isalnum(source[currentIndex])) {
        currentIndex++;
    }
    return source.substr(start, currentIndex - start);
}


std::string Lexer::readInteger()
{
    size_t start = currentIndex;
    while (currentIndex < source.size() && std::isdigit(source[currentIndex])) {
        currentIndex++;
    }
    return source.substr(start, currentIndex - start);
}


std::string Lexer::readString()
{
    size_t start = ++currentIndex;
    while (currentIndex < source.size() && source[currentIndex] != '"') {
        currentIndex++;
    }
    currentIndex++;
    return source.substr(start, currentIndex - start - 1);
}
