#pragma once
#include <stdexcept>
#include <memory>

#include "lexer.hpp"
#include "ast_node.hpp"


class Parser
{
public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    std::unique_ptr<ASTNode> parse()
    {
        return parseAssignment();
    }

private:
    const std::vector<Token>& tokens;
    size_t currentIndex = 0;

    // Helper to retrieve the current token
    inline const Token& currentToken() const;

    std::unique_ptr<ASTNode> parseAssignment();

    std::unique_ptr<ASTNode> parseExpression();

    std::unique_ptr<ASTNode> parsePrimary();

    std::unique_ptr<ASTNode> parseIdentifier();
};
