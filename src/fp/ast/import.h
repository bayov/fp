#pragma once

#include <list>

#include <boost/range/adaptor/transformed.hpp>

#include <fp/ast/base_node.h>
#include <fp/ast/node.h>

namespace fp::ast {

class import : public base_node {
public:

    import(
        lex::token_iterator keyword,
        std::list<lex::token_iterator> identifiers
    ) :
        base_node(keyword, identifiers.back()),
        m_identifiers(std::move(identifiers))
    {}

    auto identifiers() const {
        return m_identifiers | boost::adaptors::transformed([](auto&& id) {
            return id->attribute.template as<lex::token::IDENTIFIER>();
        });
    }

private:

    std::list<lex::token_iterator> m_identifiers;

};

} // namespace fp::ast
