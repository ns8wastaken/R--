#include "parser.hpp"
#include "lexer.cpp"


inline const Token& Parser::currentToken() const
{
    if (currentIndex < tokens.size())
        return tokens[currentIndex];

    // throw std::runtime_error("Unexpected end of tokens");
    throw std::runtime_error("Uh oh, no more tokens!");
}


std::unique_ptr<ASTNode> Parser::parseAssignment()
{
    std::unique_ptr<ASTNode> identifierNode = parseIdentifier();

    if (currentToken().type != TokenType::ASSIGNMENT) {
        throw std::runtime_error("Expected assignment operator '='");
    }

    ++currentIndex;

    std::unique_ptr<ASTNode> expressionNode = parseExpression();
    std::unique_ptr<ASTNode> assignmentNode = std::make_unique<ASTNode>(ASTNodeType::ASSIGNMENT);

    assignmentNode->left  = std::move(identifierNode);
    assignmentNode->right = std::move(expressionNode);

    return assignmentNode;
}


std::unique_ptr<ASTNode> Parser::parseExpression()
{
    std::unique_ptr<ASTNode> left = parsePrimary();

    while (currentToken().type == TokenType::OPERATOR && currentToken().value == "+") {
        ++currentIndex;

        std::unique_ptr<ASTNode> right    = parsePrimary();
        std::unique_ptr<ASTNode> mainNode = std::make_unique<ASTNode>(ASTNodeType::BINARY_OP, "+");

        mainNode->left  = std::move(left);
        mainNode->right = std::move(right);

        left = std::move(mainNode);
    }

    return left;
}


std::unique_ptr<ASTNode> Parser::parsePrimary()
{
    if (currentToken().type == TokenType::INTEGER_CONSTANT) {
        std::unique_ptr<ASTNode> node = std::make_unique<ASTNode>(ASTNodeType::INTEGER, currentToken().value);
        ++currentIndex;
        return node;
    }

    else if (currentToken().type == TokenType::IDENTIFIER) {
        return parseIdentifier();
    }

    throw std::runtime_error("Expected an identifier or integer");
}


std::unique_ptr<ASTNode> Parser::parseIdentifier()
{
    if (currentToken().type != TokenType::IDENTIFIER)
        throw std::runtime_error("Expected an identifier");

    std::unique_ptr<ASTNode> node = std::make_unique<ASTNode>(ASTNodeType::IDENTIFIER, currentToken().value);
    ++currentIndex;
    return node;
}
