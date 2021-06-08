#include "io.h"
inline auto operator == (const S s1,const S s2) { return s1.handle == s2.handle; }
inline auto operator != (const S s1,const S s2) { return s1.handle != s2.handle; }
inline auto operator !(const S s) { return s.null(); }

inline S parse(const char *s) {
    Parser::reset();
    Parser::supply(strdup(s));
    if (Parser::status() != Parser::Status::accept) {
        throw std::runtime_error("Unexpected parse_sr error"); // should not be here - we assume all unittest inputs are valid
    }
    return Parser::result();
}

inline S parse(const std::string& s) {
    return parse(s.c_str());
}
