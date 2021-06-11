#include "io.h"
#include "basics.h"

inline auto operator == (const S s1,const S s2) { 
  if (s1.handle == s2.handle)
    return true;
  if (s1.atom() || s2.atom())
    return false;
  return s1.car() == s2.car() && s1.cdr() == s2.cdr();
}

// inline auto operator != (const S s1,const S s2) { 
  // return !(s1.handle == s2.handle); }

inline S parse(const char *s) {
    Parser::reset();
    Parser::supply(strdup(s));
    if (Parser::status() != Parser::Status::accept) {
        throw std::runtime_error("Unexpected parser error"); // should not be here - we assume all unittest inputs are valid
    }
    return Parser::result();
}

inline S parse(const std::string& s) {
    return parse(s.c_str());
}

#define LINE_STRING STRINGIZE(__LINE__)
#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x

#define UNIQUE "UNIQUE" LINE_STRING

#define CAREFULLY_EXPECT2(K,m) \
  try { \
    EXPECT_##K m;  \
  } catch (Pair p) { \
    ADD_FAILURE() << p << " thrown in " #K m ; \
  }  


#define CAREFULLY_EXPECT(K,v1,v2,...) \
  try { \
    EXPECT_##K(v1,v2) __VA_ARGS__ ;  \
  } catch (Pair p) { \
    ADD_FAILURE() << p << " exception while checking [" << \
        #v1 << " " << #K << " " << #v2 "] \t" __VA_ARGS__ ; \
  }  

#define CAREFULLY(...) try { __VA_ARGS__; } catch (Pair p) { \
  ADD_FAILURE() << p << " exception on " << #__VA_ARGS__; }  

#define EXPECT_EXCEPTION(x, value, code)  \
{ \
  bool caught = true; \
  try{\
    x;\
    caught = false; \
  } catch (Pair p) { \
    EXPECT_EQ(p.cdr, code); \
    EXPECT_EQ(p.car, value); \
  } \
  if (!caught) \
    ADD_FAILURE() << "Evaluating " << #x << " should have thrown " << S(value,code); \
}
