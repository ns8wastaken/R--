#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "ast_node.hpp"

class Parser
{
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    std::shared_ptr<ASTNode> parse()
    {
        return parseAssignment();
    }

private:
    std::vector<Token> tokens;
    size_t currentIndex = 0;

    std::shared_ptr<ASTNode> parseAssignment()
    {
        std::shared_ptr<ASTNode> identifier = parseIdentifier();

        expectToken(TokenType::ASSIGNMENT);

        std::shared_ptr<ASTNode> expression = parseExpression();
        std::shared_ptr<ASTNode> node       = std::make_shared<ASTNode>(ASTNodeType::ASSIGNMENT, "=");

        node->children.push_back(identifier);
        node->children.push_back(expression);

        return node;
    }

    std::shared_ptr<ASTNode> parseExpression()
    {
        std::shared_ptr<ASTNode> left = parsePrimary();

        while (currentIndex < tokens.size() && tokens[currentIndex].type == TokenType::OPERATOR) {
            Token operatorToken            = tokens[currentIndex++];
            std::shared_ptr<ASTNode> right = parsePrimary();
            std::shared_ptr<ASTNode> node  = std::make_shared<ASTNode>(ASTNodeType::OPERATOR, operatorToken.identifier);

            node->children.push_back(left);
            node->children.push_back(right);

            left = node;
        }

        return left;
    }

    std::shared_ptr<ASTNode> parsePrimary()
    {
        if (tokens[currentIndex].type == TokenType::INTEGER_CONSTANT) {
            return parseInteger();
        }

        else if (tokens[currentIndex].type == TokenType::IDENTIFIER) {
            return parseIdentifier();
        }

        throw std::runtime_error("Unexpected token.");
    }

    std::shared_ptr<ASTNode> parseIdentifier()
    {
        Token token = tokens[currentIndex++];
        return std::make_shared<ASTNode>(ASTNodeType::IDENTIFIER, token.identifier);
    }

    std::shared_ptr<ASTNode> parseInteger()
    {
        Token token = tokens[currentIndex++];
        return std::make_shared<ASTNode>(ASTNodeType::INTEGER_CONSTANT, token.identifier);
    }

    void expectToken(TokenType type)
    {
        if (tokens[currentIndex].type != type) {
            throw std::runtime_error("Unexpected token type");
        }

        currentIndex++;
    }
};
