import diagnostic;

export as class diagnostic_report {
    max_errors: u64,
    errors:     list[diagnostic],
    warnings:   list[diagnostic]
};

impl for diagnostic_report {
    get errors;
    get warnings;
};

impl for diagnostic_report {
    report(d: diagnostic) {
        if d.severity == diagnostic::severity::ERROR {
            errors.append(d);
            if errors.size >= max_errors { throw compilation_error(); }
        } else {
            warnings.append(d);
        }
    }
};
