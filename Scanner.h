#pragma once

#include "Base.h"
#include "Token.h"
#include <vector>
#include <stack>
#include <map>

class Scanner {
private:

    const String source;
    std::vector<Token> tokens{};
    std::stack<bool> nested_comment{};
    int start = 0;
    int current = 0;
    int line = 1;

    static const std::map<String, TokenType> keywords;

public:

    Scanner(String cref _source)
        :source(_source)  {}

    std::vector<Token> ScanTokens();

private:

    void ScanToken();

    bool IsAtEnd() const;

    char Advance();

    char Peek() const;

    char PeekNext() const;

    bool Match(char expected);

    bool IsDigit(char c) const;

    bool IsAlpha(char c) const;

    bool IsAlphaNumeric(char c) const;

    void StringLiteral();

    void NumberLiteral();

    void Identifiter();

    void AddToken(TokenType type, Literal cref literal = {});

};