#include "Scanner.h"
#include "Lox.h"
#include <cctype>

using TT = TokenType;

const std::map<String, TokenType> Scanner::keywords = [] { // NOLINT
    std::map<String, TokenType> kws;
    kws.insert({"and",    TT::And});
    kws.insert({"class",  TT::Class});
    kws.insert({"else",   TT::Else});
    kws.insert({"false",  TT::False});
    kws.insert({"fun",    TT::Fun});
    kws.insert({"for",    TT::For});
    kws.insert({"if",     TT::If});
    kws.insert({"nil",    TT::Nil});
    kws.insert({"or",     TT::Or});
    kws.insert({"print",  TT::Print});
    kws.insert({"return", TT::Return});
    kws.insert({"super",  TT::Super});
    kws.insert({"this",   TT::This});
    kws.insert({"true",   TT::True});
    kws.insert({"var",    TT::Var});
    kws.insert({"while",  TT::While});
    return kws;
}();

std::vector<Token> Scanner::ScanTokens() {
    while (!IsAtEnd() && !Lox::HadError()) {
        start = current;
        ScanToken();
    }

    tokens.emplace_back(TT::Eof, line);

    return tokens;
}

void Scanner::ScanToken() {
    char c = Advance();

    if (!nested_comment.empty()) {
        if (c == '\n') {
            ++line;
        }
        else if (c == '/' && Peek() == '*') {
            nested_comment.push(1);
            Advance();
        }
        else if (c == '*' && Peek() == '/') {
            nested_comment.pop();
            Advance();
            Advance();
        }

        return;
    }

    switch (c) {
    case ' ': case '\t': case '\r':     break;
    case '(': AddToken(TT::LeftParen);  break;
    case ')': AddToken(TT::RightParen); break;
    case '{': AddToken(TT::LeftBrace);  break;
    case '}': AddToken(TT::RightBrace); break;
    case ',': AddToken(TT::Comma);      break;
    case '.': AddToken(TT::Dot);        break;
    case ';': AddToken(TT::SemiColon);  break;
    case '+': AddToken(TT::Plus);       break;
    case '-': AddToken(TT::Minus);      break;
    case '*': AddToken(TT::Star);       break;
    case '!': AddToken(Match('=') ? TT::BangEqual    : TT::Bang);    break;
    case '=': AddToken(Match('=') ? TT::EqualEqual   : TT::Equal);   break;
    case '>': AddToken(Match('=') ? TT::GreaterEqual : TT::Greater); break;
    case '<': AddToken(Match('=') ? TT::LessEqual    : TT::Less);    break;
    case '\n': line++; break;
    case '"': StringLiteral(); break;
    case '/': {
            if (Match('/')) {
                while (!IsAtEnd() && Peek() != '\n')
                    Advance();
            } else if (Match('*')) {
                nested_comment.push(1);
            } else {
                AddToken(TT::Slash);
            }
        } break;
    default: {
            if (IsDigit(c)) {
                NumberLiteral();
            } else if (IsAlpha(c)) {
                Identifier();
            } else {
                Lox::Error(line, "Undefined character");
            }
        } break;
    }
}

bool Scanner::IsAtEnd() const {
    return current >= source.length();
}

char Scanner::Advance() {
    return source[current++];
}

char Scanner::Peek() const {
    if (IsAtEnd())
        return 0;
    return source[current];
}

char Scanner::PeekNext() const {
    if (current + 1 >= source.length())
        return 0;
    return source[current + 1];
}

bool Scanner::Match(char expected) {
    if (Peek() != expected)
        return false;
    ++current;
    return true;
}

bool Scanner::IsDigit(char c) {
    return std::isdigit(c);
}

bool Scanner::IsAlpha(char c) {
    return std::isalpha(c) || c == '_';
}

bool Scanner::IsAlphaNumeric(char c) {
    return IsDigit(c) || IsAlpha(c);
}

void Scanner::StringLiteral() {
    while (!IsAtEnd() && Peek() != '"') {
        if (Peek() == '\n')
            ++line;
        Advance();
    }

    if (IsAtEnd())
        Lox::Error(line, "Unterminated string.");

    Advance();

    String literal = source.substr(start, current - start - 2);
    AddToken(TT::String, Literal(literal));
}

void Scanner::NumberLiteral() {
    while (IsDigit(Peek()))
        Advance();

    if (Peek() == '.' && IsDigit(PeekNext())) {
        Advance();
        while (IsDigit(Peek()))
            Advance();
    }

    Number literal = std::stod(source.substr(start, current - start));
    AddToken(TT::Number, Literal(literal));
}

void Scanner::Identifier() {
    while (IsAlphaNumeric(Peek()))
        Advance();

    String text = source.substr(start, current - start);
    auto it = keywords.find(text);
    TokenType type = it == keywords.end() ? TT::Identifier : it->second;
    AddToken(type);
}

void Scanner::AddToken(TokenType type, Literal cref literal) {
    String lexeme = source.substr(start, current - start);
    tokens.emplace_back(type, line, lexeme, literal);
}