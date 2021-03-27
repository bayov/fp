//#include <fp/util/console/width.h>
//#include <fp/common/detail/diagnostic_printer.h>

#include "report.h"

namespace fp::diagnostic {

diagnostic::problem& report::add(problem d) {
    auto& list = d.severity() == severity::ERROR ? errors_ : warnings_;
    list.push_back(std::move(d));
    if (errors_.size() >= max_errors) { throw compilation_error(); }
    return list.back();
}

//std::ostream& operator<<(std::ostream& os, const diagnostic_report& ds) {
//    for (auto&& d : ds.errors()) { os << d << std::endl; }
//    for (auto&& d : ds.warnings()) { os << d << std::endl; }
//    return os;
//}

} // namespace fp::diagnostic
