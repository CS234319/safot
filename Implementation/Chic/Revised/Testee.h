#import "basics.h"
#import "print.h"
#import "parser.cc"
#import <string.h>
#import "debugging.h"
#import "except.h"
#undef PRODUCTION
#import "mode.h"
#import "a-list.h"

#import "atoms.h"

#define EXPECT_NIL(v) EXPECT_EQ(v,NIL)
#define EXPECT_T(v) EXPECT_EQ(v,T)
#define EXPECT_NOT_NIL(v) EXPECT_NE(v,NIL)
#define EXPECT_STRUE(e) EXPECT_TRUE(e.t())
#define EXPECT_SFALSE(e) EXPECT_TRUE(e.null())

extern std::ostream& operator<<(std::ostream &os, S s);
extern bool operator == (const S s1, const S s2); 
inline bool operator != (const S s1, const S s2)  { return ! (s1 == s2); }

namespace Tested {
  inline S defun(S name, S parameters, S body) { return Engine::set(name, list(LAMBDA, parameters, body)); }
  inline S ndefun(S name, S parameters, S body) { return Engine::set(name, list(NLAMBDA, parameters, body)); }

  extern S parse(const char *s)                      ; 
  inline S prepare(S s)                              { return s; } 
  inline S prepare(String s)                         { return parse(s); } 
  inline S eval(String s)                            { return prepare(s).eval(); }
  inline S eval(S s)                                 { return s.eval(); }

  inline auto operator == (const S s1, String s2)    { return prepare(s1) == prepare(s2); } 
  inline auto operator == (String s1, S s2)          { return prepare(s1) == prepare(s2); } 
  void reset();
}

#include "unchic.h"
#import <gtest/gtest.h>

struct Test: ::testing::Test { Test() {silent();} ~Test(){Tested::reset();} };
#define SUITE(name) struct name:Test{};
#define FIXTURE(name, parent, body) \
  struct name: parent {  \
    name() { CAREFULLY_EXPECT(NE, NIL,eval(body)); } \
  };



using namespace Tested;
#define LINE_STRING STRINGIZE(__LINE__)
#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x

#define UNIQUE "UNIQUE" LINE_STRING

#define EVAL_EQ(x,y)    CAREFULLY_EXPECT(EQ, eval(x), prepare(y));
#define EVAL_XX(x,y,z)  EXPECT_EXCEPTION(eval(x), prepare(y), prepare(z)); 

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

#define EXPECT_EXCEPTION(x, content, error) { \
  bool caught = true; \
  try{\
    x;\
    caught = false; \
  } catch (Pair p) { \
    fflush(stdout); \
    S code = S(p.cdr); \
    S details = S(p.car); \
    EXPECT_EQ(code, error)  << "Error code is: " << code;  \
    EXPECT_EQ(details, content) << "Error body is: " << details;  \
  } \
  if (!caught) \
    ADD_FAILURE() << "Evaluating " << #x << " should have thrown " << S(content,error); \
}
