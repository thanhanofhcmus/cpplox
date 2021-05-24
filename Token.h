#pragma once

#include "Base.h"

enum class TokenType {
    LeftParen, RightParen,
    LeftBrace, RightBrace,
    Comma, Dot, SemiColon,
    Plus, Minus, Slash, Star,

    Bang, BangEqual,
    Equal, EqualEqual,
    Greater, GreaterEqual,
    Less, LessEqual,

    Identifiter, String, Number,

    And, Class, Else, False, Fun, For,
    If, Nil, Or, Print, Return,
    Super, This, True, Var, While,

    Eof,
};

inline auto TokenTypeName(TokenType type) {
    using TT = TokenType;
    switch (type) {
    case TT::LeftParen:     return "LeftParen";
    case TT::RightParen:    return "RightParen";
    case TT::LeftBrace:     return "LeftBrace";
    case TT::RightBrace:    return "RightBrace";
    case TT::Comma:         return "Comma";
    case TT::Dot:           return "Dot";
    case TT::SemiColon:     return "SemiColon";
    case TT::Plus:          return "Plus";
    case TT::Minus:         return "Minus";
    case TT::Star:          return "Star";
    case TT::Slash:         return "Slash";
    case TT::Bang:          return "Bang";
    case TT::BangEqual:     return "BangEqual";
    case TT::Equal:         return "Equal";
    case TT::EqualEqual:    return "EqualEqual";
    case TT::Greater:       return "Greater";
    case TT::GreaterEqual:  return "GreaterEqual";
    case TT::Less:          return "Less";
    case TT::LessEqual:     return "LessEqual";
    case TT::Identifiter:   return "Identifiter";
    case TT::String:        return "String";
    case TT::Number:        return "Number";
    case TT::And:           return "And";
    case TT::Class:         return "Class";
    case TT::Else:          return "Else";
    case TT::False:         return "False";
    case TT::Fun:           return "Fun";
    case TT::For:           return "For";
    case TT::If:            return "If";
    case TT::Nil:           return "Nil";
    case TT::Or:            return "Or";
    case TT::Print:         return "Print";
    case TT::Return:        return "Return";
    case TT::Super:         return "Super";
    case TT::This:          return "This";
    case TT::True:          return "True";
    case TT::Var:           return "Var";
    case TT::While:         return "While";
    case TT::Eof:           return "EOF";
    }
    return "Unknow type";
}

class Token {
private:

    const TokenType type;
    const String lexeme;
    const Literal literal;
    const int line;

public:

    Token(TokenType _type, int _line, String cref _lexeme = "", Literal cref _literal = {})
        : type(_type), lexeme(_lexeme), literal(_literal), line(_line) {}

    String ToString() const {
        constexpr size_t uni_size = 12;
        String type_name = TokenTypeName(type);
        type_name += String(uni_size - type_name.size(), ' ');

        return std::to_string(line) + " | " + type_name + " | " + lexeme;
    }
};
