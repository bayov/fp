#include "token.h"

namespace fp::lex {

std::string_view token_name(token t) {
    switch (t) {
        case token::ERROR:          return "ERROR";

        case token::QUOTE:          return "QUOTE";
        case token::COMMA:          return "COMMA";
        case token::ANNOTATION:     return "ANNOTATION";
        case token::SCOPE:          return "SCOPE";
        case token::SEMICOLON:      return "SEMICOLON";
        case token::OPTIONAL:       return "OPTIONAL";
        case token::DECORATOR:      return "DECORATOR";
        case token::BIT_NOT:        return "BIT_NOT";
        case token::MEMBER_ACCESS:  return "MEMBER_ACCESS";
        case token::RANGE:          return "RANGE";
        case token::CLOSED_RANGE:   return "CLOSED_RANGE";

        // brackets
        case token::L_PAREN:        return "L_PAREN";
        case token::R_PAREN:        return "R_PAREN";
        case token::L_BRACKET:      return "L_BRACKET";
        case token::R_BRACKET:      return "R_BRACKET";
        case token::L_BRACE:        return "L_BRACE";
        case token::R_BRACE:        return "R_BRACE";

        // keywords
        case token::AND:            return "AND";
        case token::AS:             return "AS";
        case token::BREAK:          return "BREAK";
        case token::CASE:           return "CASE";
        case token::CATCH:          return "CATCH";
        case token::CLASS:          return "CLASS";
        case token::CONCEPT:        return "CONCEPT";
        case token::CONTINUE:       return "CONTINUE";
        case token::DEFAULT:        return "DEFAULT";
        case token::DO:             return "DO";
        case token::ELSE:           return "ELSE";
        case token::ENUM:           return "ENUM";
        case token::EXPORT:         return "EXPORT";
        case token::FOR:            return "FOR";
        case token::IF:             return "IF";
        case token::IMPLICIT:       return "IMPLICIT";
        case token::IMPORT:         return "IMPORT";
        case token::IN:             return "IN";
        case token::MUT:            return "MUT";
        case token::NOT:            return "NOT";
        case token::OF:             return "OF";
        case token::OR:             return "OR";
        case token::RETURN:         return "RETURN";
        case token::SWITCH:         return "SWITCH";
        case token::THROW:          return "THROW";
        case token::TRY:            return "TRY";
        case token::WHILE:          return "WHILE";

        // arrows
        case token::TYPE_ARROW:     return "TYPE_ARROW";
        case token::LAMBDA_ARROW:   return "LAMBDA_ARROW";

        // arithmetic
        case token::PLUS:           return "PLUS";
        case token::MINUS:          return "MINUS";
        case token::MUL:            return "MUL";
        case token::DIV:            return "DIV";
        case token::MOD:            return "MOD";
        case token::POW:            return "POW";
        case token::BIT_AND:        return "BIT_AND";
        case token::BIT_OR:         return "BIT_OR";
        case token::XOR:            return "XOR";
        case token::LSHIFT:         return "LSHIFT";
        case token::RSHIFT:         return "RSHIFT";

        // assignments
        case token::ASSIGN:         return "ASSIGN";
        case token::PLUS_ASSIGN:    return "PLUS_ASSIGN";
        case token::MINUS_ASSIGN:   return "MINUS_ASSIGN";
        case token::MUL_ASSIGN:     return "MUL_ASSIGN";
        case token::DIV_ASSIGN:     return "DIV_ASSIGN";
        case token::MOD_ASSIGN:     return "MOD_ASSIGN";
        case token::POW_ASSIGN:     return "POW_ASSIGN";
        case token::BIT_AND_ASSIGN: return "BIT_AND_ASSIGN";
        case token::BIT_OR_ASSIGN:  return "BIT_OR_ASSIGN";
        case token::XOR_ASSIGN:     return "XOR_ASSIGN";
        case token::LSHIFT_ASSIGN:  return "LSHIFT_ASSIGN";
        case token::RSHIFT_ASSIGN:  return "RSHIFT_ASSIGN";

        // comparisons
        case token::EQ:             return "EQ";
        case token::NE:             return "NE";
        case token::LT:             return "LT";
        case token::GT:             return "GT";
        case token::LTE:            return "LTE";
        case token::GTE:            return "GTE";

        // increment & decrement
        case token::INC:            return "INC";
        case token::DEC:            return "DEC";

        // containing attributes
        case token::COMMENT:        return "COMMENT";
        case token::IDENTIFIER:     return "IDENTIFIER";
        case token::NUMBER:         return "NUMBER";
        case token::CHAR:           return "CHAR";
        case token::STRING:         return "STRING";
    }
    throw std::runtime_error("should not reach here");
}

std::ostream& operator<<(std::ostream& os, token t) {
    return os << token_name(t);
}

} // namespace fp::lex
