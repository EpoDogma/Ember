#include <iostream>
#include <fstream>
#include <vector>

#include "../include/tokenizer.hpp"

bool isSyntaxValid(int&, char*[]);
void extractStream(std::string&, const char* name);

int main(int argc, char* argv[]) {
    if (!isSyntaxValid(argc, argv)) {
        return EXIT_FAILURE;
    }

    // Pull program.em file stream (FS)
    std::string inS;
    extractStream(inS, argv[1]);

    // Tokenize FS
    Tokenizer tkzr(inS);
    std::vector< Token > tokens(tkzr.getTokens()); // Moving memory directly w/o copying, optimization for huge files.

    // Translate into Assembly & Write to file
    std::ofstream oFS("./product/program.asm");

    oFS << "global _start\n\nsection .text\n_start:\n";
    
    for (const Token& token: tokens) {
        if (token.getType() == TokenType::_return) {
            oFS << "    mov rax, 60\n";
        }   else if (token.getType() == TokenType::int_l) {
            oFS << "    mov rdi, " << token.getData() << "\n";
        }   else if (token.getType() == TokenType::semicolon) {
            oFS << "    syscall";
        }
    }

    oFS.close();

    // NOTE: Currently handling program assembling and linking externally using make file.
    return EXIT_SUCCESS;
}

bool isSyntaxValid(int& argc, char* argv[]) {
    if (argc != 2) { // Guard Clause: Correct number of arguments.
        std::cout << "Invalid usage. Please follow the syntax: ./compiler [program.em]" << std::endl;
        return false;
    }

    std::string argument(argv[1]);
    if (argument.find(".em") == std::string::npos) {
        std::cout << "Invalid usage. Please ensure the program file ends in the .em extension." << std::endl;
        return false;
    }

    return true;
}

void extractStream(std::string& inS, const char* name) {
    std::ifstream inFS(name);

    if (inFS.fail()) {
        throw std::ios_base::failure("Unable to open file " + std::string(name));
    }

    inFS.seekg(0, std::ios::end);
    inS.resize(inFS.tellg());
    inFS.seekg(0, std::ios::beg);
    inFS.read(&inS[0], inS.size());
    inFS.close();
}
