cmake_minimum_required(VERSION 3.28)
project(Ember)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include the header files
include_directories("include")

# Build your main code as a library
add_library(ember_core
    src/tokenizer.cpp
)

# Executable for your compiler (e.g., make.cpp)
add_executable(compiler src/compiler.cpp)
target_link_libraries(compiler ember_core)

# Enable testing and add the tests subdirectory
enable_testing()
add_subdirectory(testing)