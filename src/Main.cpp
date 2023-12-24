// Main.cpp

#include <iostream>
#include "antlr/HooLexer.h"
#include "antlr/HooParser.h"
#include "HooVisitor.h"

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.hoo>" << std::endl;
        return 1;
    }

    const std::string inputFileName(argv[1]);
    antlr4::ANTLRInputStream input;
    try {
        std::ifstream inputFile(inputFileName);
        input.load(inputFile);
    } catch (const std::exception& e) {
        std::cerr << "Error reading input file: " << e.what() << std::endl;
        return 1;
    }

    HooLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    HooParser parser(&tokens);

    // Parse the input
    antlr4::tree::ParseTree* tree = parser.unit();

    // Create and use the custom visitor
    HooBaseVisitor visitor;
    visitor.visit(tree);
    return 0;
}
