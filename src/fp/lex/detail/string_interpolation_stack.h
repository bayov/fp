#pragma once

#include <deque>

#include <fp/source_code.h>

namespace fp::lex::detail {

/**
 * A stack of string "frame"s that is used to support string interpolation.
 *
 * String interpolation means that we have to keep a stack when tokenizing
 * strings so that we dive in and out of interpolations:
 *
 * Example:
 *
 *      "a string that contains {"another string"} that is interpolated"
 *
 * In the example above, we have to remember that when we finished tokenizing
 * the inner string, we're still inside an interpolation, and that the next
 * right-brace will return us to the context of the first string.
 *
 * A stack of size 1 means that we are currently tokenizing inside a string,
 * while a stack of size 2 means that we are currently tokenizing inside a
 * string that is itself inside a string (Yo Dawg).
 *
 * We also need to keep track of how many left-braces are still open inside an
 * interpolation, so that when we encounter a right-brace we know if we should
 * return to string context and tokenize string characters, or we're still
 * inside an interpolated expression.
 *
 * So each frame (string_interpolation_stack::frame) keeps track of how many
 * left-braces are still open inside an interpolation. When this value is 0, it
 * means that we're currently tokenizing normal string characters. When this
 * value is positive, it means we're tokenizing interpolated expressions.
 *
 * Example to visualize the stack depth when tokenizing a hellish example:
 *
 *             "bla {"qwe {1+1}" - { 2*{ foo({ 3 }) }*4 } - "qwe" } bla"
 *     frame 1 |-----|         |----------------------------|   |------|
 *     frame 2       |---------|                            |---|
 *
 * The same example above, but this time with asteriks (*) to indicate when
 * we're tokenizing expression code as opposed to string characters:
 *
 *             "bla {"qwe {1+1}" - { 2*{ foo({ 3 }) }*4 } - "qwe" } bla"
 *     frame 1 |----{|         |****************************|   |*}----|
 *     frame 2       |----{***}|                            |---|
 *
 * And the same example again, but this time with numbers showing the value
 * of `open_left_braces` in each frame:
 *
 *             "bla {"qwe {1+1}" - { 2*{ foo({ 3 }) }*4 } - "qwe" } bla"
 *     frame 1 |0---1|         |---2---3-----4---3--2---1---|   |-0----|
 *     frame 2       |0---1---0|                            |0--|
 */
struct string_interpolation_stack {
    struct frame {
        const source_iterator opening_quote;
        size_t open_left_braces = 0;
    };

    bool empty() const { return stack_.empty(); }

    /// Returns the current frame. Undefined behaviour when empty.
    frame& current_frame() { return stack_.back(); }

    /// Pushes a new frame to the stack given an iterator to its opening-quote.
    void push(source_iterator opening_quote) {
        stack_.push_back(frame { opening_quote });
    }

    /// Pop the current frame off the stack. Undefined behaviour when empty.
    void pop() { stack_.pop_back(); }

    /// Returns true if we're currently tokenizing string characters.
    bool in_string_context() {
        return !stack_.empty() && current_frame().open_left_braces == 0;
    }

private:
    std::deque<frame> stack_;
};

} // namespace fp::lex::detail
