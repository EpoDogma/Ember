#include <iostream>
#include <cstdlib>
#include <filesystem>

/*
The purpose of this file is to act as a makefile with basic functionality. It will automatically see if the make.cpp 
has been updated and recompile accordingly. It will then compile the compile.cpp file, run it using the default or 
entered .em file, assemble it using nasm, and link it using ld.
The generated executable will be have the same name as in input file without it's extension.
*/

int main(int argc, char* argv[]) {
    // args (./main, program.em, outputName)
    std::string inputFileName = "./testing/program.em";
    std::string command;
    if (argc > 1) {
        inputFileName = argv[1];
    }

    // If make.cpp has been altered since compilation of make executable
    if (std::filesystem::last_write_time("./src/make.cpp") > std::filesystem::last_write_time("make")) {
        command = "g++ -o make ./src/make.cpp";
        system(command.c_str());
    }
    
    command = "g++ -o compiler ./src/compiler.cpp";
    system(command.c_str());

    command = "./compiler " + inputFileName;
    system(command.c_str());

    command = "nasm -o ./product/program.o -f elf64 ./product/program.asm";
    system(command.c_str());

    int nameSize = inputFileName.find_last_of(".") - inputFileName.find_last_of("/") - 1;

    command = "ld -o " + inputFileName.substr(inputFileName.find_last_of("/") + 1, nameSize) + " ./product/program.o";
    system(command.c_str());

    return 0;
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