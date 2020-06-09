#include "problem.h"

namespace fp::diagnostic {

problem& problem::add_primary(fp::source_location location, std::string text) {
    locations_.push_back(diagnostic::location {
        .kind = location_kind::PRIMARY,
        .source_location = std::move(location),
        .text = std::move(text)
    });
    return *this;
}

problem& problem::add_supplement(
    fp::source_location location,
    std::string text
) {
    locations_.push_back(diagnostic::location {
        .kind = location_kind::SUPPLEMENT,
        .source_location = std::move(location),
        .text = std::move(text)
    });
    return *this;
}

problem& problem::add_contextual(fp::source_location location) {
    locations_.push_back(diagnostic::location {
        .kind = location_kind::CONTEXTUAL,
        .source_location = std::move(location)
    });
    return *this;
}

problem::problem(diagnostic::severity severity, std::string text) :
    severity_(severity), text_(std::move(text)) {}

problem warning(std::string text) {
    return {severity::WARNING, std::move(text)};
}

problem error(std::string text) {
    return {severity::ERROR, std::move(text)};
}

} // namespace fp::diagnostic
