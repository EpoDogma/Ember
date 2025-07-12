#include <iostream>
#include <cstdlib> // system()
#include <filesystem> // last_write_time()
#include <unistd.h> // execvp()

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
        std::cout << "Changes were found in the makefile. Updating and re-executing make binary." << std::endl;
        
        command = "g++ -o make ./src/make.cpp";
        system(command.c_str());

        // Re-run the new 'make' binary with the same arguments
        execvp("./make", argv); // replace current process
        perror("Failed to change executing binary to newly compile make file. Re run this command. Failure reason");
        return 1;
    }
    
    command = "g++ -o compiler ./src/compiler.cpp";
    system(command.c_str());

    command = "./compiler " + inputFileName;
    system(command.c_str());

    command = "nasm -o ./product/program.o -f elf64 ./product/program.asm";
    system(command.c_str());

    int nameSize = inputFileName.find_last_of(".") - inputFileName.find_last_of("/");

    command = "ld -o " + inputFileName.substr(inputFileName.find_last_of("/") + 1, nameSize - 1) + " ./product/program.o";
    system(command.c_str());

    return 0;
}