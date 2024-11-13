#include "compiler.hpp"

#include "lexer.cpp"
#include "parser.cpp"

#include <iostream>


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
        std::cout << static_cast<int>(t.type) << " \"" << t.identifier << "\"\n";
    }
}