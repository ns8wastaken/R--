#include <iostream>

#include "compiler.hpp"
#include "parser.cpp"


[[nodiscard]] std::string readFile(const std::ifstream& file)
{
    std::ostringstream sstr;
    sstr << file.rdbuf();
    return sstr.str();
}


int main(int argc, char* argv[])
{
    std::ifstream sourceFile(argv[1]);

    Lexer lexer(readFile(sourceFile));

    std::vector<Token> v = lexer.lexerize();

    for (const Token& t : v) {
        std::cout << static_cast<int>(t.type) << " \"" << t.value << "\"\n";
    }
}