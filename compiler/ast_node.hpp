#pragma once
#include <string>
#include <vector>
#include <memory>


enum class ASTNodeType
{
    ASSIGNMENT,
    BINARY_OP,
    INTEGER,
    IDENTIFIER
};


struct ASTNode
{
    ASTNodeType type;
    std::string value; // For identifiers or integer literals
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    ASTNode(ASTNodeType nodeType, std::string val = "") : type(nodeType), value(std::move(val)) {}
};
