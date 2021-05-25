#pragma once

#include "Base.h"

class Lox {
private:

    static bool had_error;

public:

    static void RunFile(const char* path);

    static void RunPrompt();

    static void Run(String cref source);

    static void Error(int line, String cref message);

    static void Report(int line, String cref where, String cref message);

    static bool HadError();
};