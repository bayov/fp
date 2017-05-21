import std::Printable;
import source_location;

export as class diagnostic {
    ::severity =        variant { ERROR, WARNING };
    ::supplement =      (source: source_location, text: string);
    ::note =            (text: string, source: source_location?);
    ::fix_suggestion =  (source: source_location, replacement: input);

    severity:           ::severity,
    source:             source_location,
    text:               string,
    supplements:        list[supplement],
    notes:              list[note],
    fix_suggestions:    list[fix_suggestion]
};

# constructors
impl for diagnostic {

    ::construct(severity: ::severity, source: source_location, text: string) {
        construct severity = severity;
        construct source = source;
        construct text = text;
    };

    ::error(source: source_location, text: string) =>
        diagnostic(::ERROR, source, text);

    ::warning(source: source_location, text: string) =>
        diagnostic(::WARNING, source, text);

};

# getters
impl for diagnostic {
    get severity;
    get source;
    get text;
    get supplements;
    get notes;
    get fix_suggestions;
};

impl for diagnostic {

    add_supplement(source: source_location, text: string = "") =>
        supplements.append({ source, text });

    add_note(text: string, source: source_location?) =>
        notes.append({ text, source });

    add_fix_suggestion(source: source_location, replacement: input) =>
        fix_suggestion.append({ source, replacement });

};

impl Printable for diagnostic {
    print(os: &ostream) => { ... };
};
