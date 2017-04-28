#pragma once

#include <stdexcept>

#include "source_origin.h"

namespace fp {

/// Represents a compilation error.
class error : public std::exception {
public:

    error(std::string what, source_origin origin) :
        m_origin(std::move(origin)),
        m_what(std::move(what))
    {}

    const char* what() const noexcept override { return m_what.c_str(); }

    /// The origin of the error inside the source code.
    const source_origin& origin() const { return m_origin; }

private:

    std::string m_what;
    source_origin m_origin;

};

} // namespace fp
