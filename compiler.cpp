#include <iostream>
#include <fstream>

bool isSyntaxValid(int&, char* argv[]);

int main(int argc, char* argv[]) {
    // Confirm executable syntax is being followed : ./compiler [program.em]
    if (!isSyntaxValid(argc, argv)) {
        return EXIT_FAILURE;
    }

    // Pull program.em file stream (FS)
    std::ifstream inFS(argv[1]);
    std::string inS;

    inFS.seekg(0, std::ios::end);
    inS.resize(inFS.tellg());
    inFS.seekg(0, std::ios::beg);
    inFS.read(&inS[0], inS.size());

    // Tokenize FS

    // Display tokenized FS

    // Translate into Assembly

    // Write to file

    // NOTE: Currently handling program assembling and linking externally.
    return EXIT_SUCCESS;
}

bool isSyntaxValid(int& argc, char* argv[]) {
    if (argc == 2) {
        return true;
    }

    std::cout << "Invalid usage. Please follow the syntax: ./compiler [program.em]" << std::endl;
    return false;
}



