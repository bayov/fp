#pragma once

#include <fp/common/source_origin.h>

namespace fp::ast {

/// Common data of all AST nodes.
class base {
public:

    explicit base(source_origin origin) : m_origin(std::move(origin)) {}

    /// The origin of the node inside the source code.
    const source_origin& origin() const { return m_origin; }

private:

    source_origin m_origin;

};

} // fp::ast
