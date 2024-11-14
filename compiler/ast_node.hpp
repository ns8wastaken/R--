#include <memory>
#include <vector>
#include <string>


enum class ASTNodeType
{
    ASSIGNMENT,
    IDENTIFIER,
    OPERATOR,
    INTEGER_CONSTANT,
    STRING_CONSTANT
};


struct ASTNode
{
    ASTNodeType type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(ASTNodeType t, const std::string& v) : type(t), value(v) {}
};
