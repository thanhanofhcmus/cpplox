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
    std::stack<int> nested_comment{};
    int start = 0;
    int current = 0;
    int line = 1;

    static const std::map<String, TokenType> keywords;

public:

    explicit Scanner(String _source)
        :source(std::move(_source))  {}

    std::vector<Token> ScanTokens();

private:

    void ScanToken();

    [[nodiscard]]
    bool IsAtEnd() const;

    char Advance();

    [[nodiscard]]
    char Peek() const;

    [[nodiscard]]
    char PeekNext() const;

    bool Match(char expected);

    [[nodiscard]]
    static bool IsDigit(char c) ;

    [[nodiscard]]
    static bool IsAlpha(char c) ;

    [[nodiscard]]
    static bool IsAlphaNumeric(char c) ;

    void StringLiteral();

    void NumberLiteral();

    void Identifier();

    void AddToken(TokenType type, Literal cref literal = {});
};