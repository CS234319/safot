#include "io.h"
#include "basics.h"

inline auto operator == (const S s1,const S s2) { 
  if (s1.handle == s2.handle)
    return true;
  if (s1.atom() || s2.atom())
    return false;
  return s1.car() == s2.car() && s1.cdr() == s2.cdr();
}

inline auto operator != (const S s1,const S s2) { 
 return !(s1.handle == s2.handle); }

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

#define EXPECT_NIL(v) EXPECT_EQ(v,NIL)
#define EXPECT_T(v) EXPECT_EQ(v,T)

#define CAREFULLY_EXPECT_NIL(v,...) \
  try { \
    EXPECT_NIL(v) __VA_ARGS__ ;  \
  } catch (Pair p) { \
    ADD_FAILURE() << p << " exception while checking [" \
        << " NIL " << #v "] \t" __VA_ARGS__ ; \
  }  

#define CAREFULLY_EXPECT_FALSE(v,...) \
  try { \
    EXPECT_FALSE(v) __VA_ARGS__ ;  \
  } catch (Pair p) { \
    ADD_FAILURE() << p << " exception in EXPECT_FALSE" \
      << #v "] \t" __VA_ARGS__ ; \
  }  


#define CAREFULLY_EXPECT_TRUE(v,...) \
  try { \
    EXPECT_TRUE(v) __VA_ARGS__ ;  \
  } catch (Pair p) { \
    ADD_FAILURE() << p << " exception in EXPECT_TRUE" \
      << #v "] \t" __VA_ARGS__ ; \
  }  

#define CAREFULLY_EXPECT_T(v,...) \
  try { \
    EXPECT_T(v) __VA_ARGS__ ;  \
  } catch (Pair p) { \
    ADD_FAILURE() << p << " exception while checking ["  \
        << " T " << #v "] \t" __VA_ARGS__ ; \
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
    fflush(stdout); \
    EXPECT_EQ(S(p.cdr), code)  << "Actual error code is: " << S(p.cdr);  \
    EXPECT_EQ(S(p.car), value) << "Error body is: " << S(p.car);  \
  } \
  if (!caught) \
    ADD_FAILURE() << "Evaluating " << #x << " should have thrown " << S(value,code); \
}
