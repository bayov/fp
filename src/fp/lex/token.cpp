#include "token.h"

namespace fp::lex {

std::string_view token_string_representation(token t) {
    switch (t) {
        case token::ERROR:          return "ERROR";
        
        case token::QUOTE:          return "\"";
        case token::COMMA:          return ",";
        case token::ANNOTATION:     return ":";
        case token::SCOPE:          return "::";
        case token::SEMICOLON:      return ";";
        case token::OPTIONAL:       return "?";
        case token::DECORATOR:      return "@";
        case token::BIT_NOT:        return "~";
        case token::MEMBER_ACCESS:  return ".";
        case token::RANGE:          return "..";
        case token::CLOSED_RANGE:   return "...";

        // brackets
        case token::L_PAREN:        return "(";
        case token::R_PAREN:        return ")";
        case token::L_BRACKET:      return "[";
        case token::R_BRACKET:      return "]";
        case token::L_BRACE:        return "{";
        case token::R_BRACE:        return "}";

        // keywords
        case token::AND:            return "and";
        case token::AS:             return "as";
        case token::BREAK:          return "break";
        case token::CASE:           return "case";
        case token::CATCH:          return "catch";
        case token::CLASS:          return "class";
        case token::CONCEPT:        return "concept";
        case token::CONTINUE:       return "continue";
        case token::DEFAULT:        return "default";
        case token::DO:             return "do";
        case token::ELSE:           return "else";
        case token::ENUM:           return "enum";
        case token::EXPORT:         return "export";
        case token::FOR:            return "for";
        case token::IF:             return "if";
        case token::IMPLICIT:       return "implicit";
        case token::IMPORT:         return "import";
        case token::IN:             return "in";
        case token::MUT:            return "mut";
        case token::NOT:            return "not";
        case token::OF:             return "of";
        case token::OR:             return "or";
        case token::RETURN:         return "return";
        case token::SWITCH:         return "switch";
        case token::THROW:          return "throw";
        case token::TRY:            return "try";
        case token::WHILE:          return "while";

        // arrows
        case token::TYPE_ARROW:     return "->";
        case token::LAMBDA_ARROW:   return "=>";

        // arithmetic
        case token::PLUS:           return "+";
        case token::MINUS:          return "-";
        case token::MUL:            return "*";
        case token::DIV:            return "/";
        case token::MOD:            return "%";
        case token::POW:            return "**";
        case token::BIT_AND:        return "&";
        case token::BIT_OR:         return "|";
        case token::XOR:            return "^";
        case token::LSHIFT:         return "<<";
        case token::RSHIFT:         return ">>";

        // assignments
        case token::ASSIGN:         return "=";
        case token::PLUS_ASSIGN:    return "+=";
        case token::MINUS_ASSIGN:   return "-=";
        case token::MUL_ASSIGN:     return "*=";
        case token::DIV_ASSIGN:     return "/=";
        case token::MOD_ASSIGN:     return "%=";
        case token::POW_ASSIGN:     return "**=";
        case token::BIT_AND_ASSIGN: return "&=";
        case token::BIT_OR_ASSIGN:  return "|=";
        case token::XOR_ASSIGN:     return "^=";
        case token::LSHIFT_ASSIGN:  return "<<=";
        case token::RSHIFT_ASSIGN:  return ">>=";

        // comparisons
        case token::EQ:             return "==";
        case token::NE:             return "!=";
        case token::LT:             return "<";
        case token::GT:             return ">";
        case token::LTE:            return "<=";
        case token::GTE:            return ">=";

        // increment & decrement
        case token::INC:            return "++";
        case token::DEC:            return "--";

        // containing attributes
        case token::COMMENT:        return "COMMENT";
        case token::IDENTIFIER:     return "IDENTIFIER";
        case token::INTEGER:        return "INTEGER";
        case token::REAL:           return "REAL";
        case token::CHAR:           return "CHAR";
        case token::STRING:         return "STRING";
    }
    throw std::runtime_error("should not reach here");
}

std::ostream& operator<<(std::ostream& os, token t) {
    return os << token_string_representation(t);
}

} // namespace fp::lex
