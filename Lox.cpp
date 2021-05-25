#include "Lox.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include "Scanner.h"

bool Lox::had_error = false;

void Lox::RunFile(const char *path) {
    std::ifstream fin(path, std::ios::in | std::ios::ate);
    size_t size = fin.tellg();
    String source(size, ' ');
    fin.seekg(0, std::ios::beg);

    source.assign(std::istreambuf_iterator<char>(fin),
                  std::istreambuf_iterator<char>());

    Run(source);
}

void Lox::RunPrompt() {
    for (;;) {
        std::cout << "> ";
        String line;
        std::getline(std::cin, line);
        if (line.length() == 0) break;
        Run(line);
    }
}

void Lox::Run(String cref source) {
    auto tokens = Scanner(source).ScanTokens();

    for (Token cref token : tokens) {
        std::cout << token.ToString() << '\n';
    }
}

void Lox::Error(int line, String cref message) {
    Report(line, "", message);
}

void Lox::Report(int line, String cref where, String cref message) {
    std::cerr << "Line " << line << "] Error" << where << ": " << message << '\n';
    had_error = true;
}

bool Lox::HadError() {
    return had_error;
}