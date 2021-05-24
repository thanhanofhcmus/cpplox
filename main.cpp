#include <iostream>
#include "Lox.h"

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cout << "Usage: cpplox [script]\n";
        return 64;
    } else if (argc == 2) {
        Lox::RunFile(argv[1]);        
    } else {
        Lox::RunPrompt();
    }
}
