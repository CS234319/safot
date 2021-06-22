#ifndef CHIC_H 
#define CHIC_H
// Poor man's edition of a bit cleaner C/C++

#include <functional>
#include <iostream>

typedef std::function<bool()> Predicate;

#define UNIQUE(X)       UNIQUE1(X,__LINE__)
#define UNIQUE1(X,Y)    UNIQUE2(X,Y)
#define UNIQUE2(X,Y)    X##Y

#define THROW throw *this

#define __EXPRESSION(X) <<#X<<"="<<X<<"; "

#define X1(x1)           
#define X2(x1,x2)           __EXPRESSION(x2) 
#define X3(x1,x2,x3)        __EXPRESSION(x2)  __EXPRESSION(x3) 
#define X4(x1,x2,x3,x4)     __EXPRESSION(x2)  __EXPRESSION(x3) __EXPRESSION(x4)
#define X5(x1,x2,x3,x4,x5)  __EXPRESSION(x2)  __EXPRESSION(x3) __EXPRESSION(x4) __EXPRESSION(x5)

#define GET_MACRO(_0,_1,_2,_3,_4, _5, NAME,...) NAME
#define ELABORATE(...)  GET_MACRO(_0,__VA_ARGS__,X5, X4,X3,X2,X1,X0)(__VA_ARGS__)
#define ITERATE(...) \
  (__EXPRESSION,__VA_ARGS__)

#define VA_ARGS(...) DELME, ##__VA_ARGS__

#define Surely(P, ...) \
  struct UNIQUE(Surely) {                                                \
    typedef const char *const String;                                    \
    String file;                                                         \
    const long line;                                                     \
    String context, expression;                                          \
    UNIQUE(Surely)(String f, long l, String c, String e, Predicate p,    \
        Predicate elaborate):                                            \
      file(f), line(l), context(c), expression(e) {        \
        if (p()) return;                                         \
        (void) fprintf(stderr,"%s(%d)/%s: '%s' \n\t failed presumption\n",\
           file, line, context, expression);                             \
           elaborate();                                                  \
    }                                                                    \
  } UNIQUE(Surely)                                                       \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P,                        \
      [&]{ return P; },                                                  \
      [&]{ std::cerr ELABORATE(VA_ARGS(__VA_ARGS__)) << "\n"; return false;} \
     );                                                                  \
;


#define Expect(P, ...) \
  struct UNIQUE(Expect) {                                                \
    typedef const char *const String;                                    \
    String file;                                                         \
    const long line;                                                     \
    String context, expression;                                          \
    UNIQUE(Expect)(String f, long l, String c, String e, Predicate p,    \
        Predicate elaborate):                                            \
      file(f), line(l), context(c), expression(e) {        \
        if (p()) return;                                         \
        (void) fprintf(stderr,"%s(%d)/%s: '%s' \n\t unmet expectation\n",\
           file, line, context, expression);                             \
           elaborate();                                                  \
        THROW;                                                           \
    }                                                                    \
  } UNIQUE(Expect)                                                       \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P,                        \
      [&]{ return P; },                                                  \
      [&]{ std::cerr ELABORATE(VA_ARGS(__VA_ARGS__)) << "\n"; return false;} \
     );                                                                  \
;

#define Promise(P,...) \
  struct UNIQUE(Promise) {                                               \
    typedef const char *const String;                                    \
    String file;                                                         \
    const long line;                                                     \
    String context, expression;                                          \
    Predicate predicate;                                                 \
    Predicate elaborate;                                                    \
    UNIQUE(Promise)(String f, long l, String c, String e, Predicate p, Predicate a):  \
      file(f), line(l), context(c), expression(e), predicate(p), elaborate(a) {}       \
    ~UNIQUE(Promise)() {                                                 \
       if (predicate()) return;                                          \
       (void) fprintf(stderr,"%s(%d)/%s: '%s' = broken promise\n",       \
           file, line, context, expression);                             \
           elaborate();                                                  \
             THROW;                                                      \
    }                                                                    \
  } UNIQUE(promise)                                                      \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, [&]{return P;},        \
      [&]{std::cerr ELABORATE(VA_ARGS(__VA_ARGS__))<<"\n";return false;} \
     );                                                                  \
;




#define EXPECT_TT  EXPECT_TRUE
#define EXPECT_FF  EXPECT_FALSE

#define Keep(X) Expect(P) Promise(X)
#define xCurrent(X) ([=]{return X;})()

#define Return(X) return ((__ = (X)),(__)); 

#define FUN(Return, Name, ArgumentType) \
  Return Name(ArgumentType _) { \
    const auto $$ = Name; \
    M3("[",_,"]"); \
    Return __ =  

#define IS(X)    \
    X; \
    M2("-->", __); \
    return __; \
  } 




#include <cstdint>         // Standard header providing integer types with widths 
#define Provides extern
#define Let constexpr 
#define let const auto 
#define Allocate 
#define function   
#define property inline  
#define procedure void  
#define array(type) type *const
#define variable(type) type & 
#define constant(type) const type 
#define action void
#define modifier 
#define perspective(...) struct{__VA_ARGS__;};
#define Representation union
#define Type struct
#define Constructor(X)  X 
#define Property(X)     X() const
#define Mutator(X)      X 
#define Selfer(X)       Self X 
#define Is(X)           { return X; }
#define	returns(x) const {return x;}
#define by(...) :__VA_ARGS__{}

#ifndef Type
#error
#endif

/*@ The Primitive Types@
Our byte addressable underlining machine offers three primitive types: byte,
Short, and, Long whose sizes are 8, 16, and 32 bits respectively.  These types
are fixed width signed integers, represented in two's complement, and are
similar to the types byte, short, and int of the Java virtual machine. Punning
is allowed, and used extensively: A Long is constituted by two consecutive
halves. No particular byte or halves ordering is assumed. */

typedef int8_t  Byte; /// JVM's byte                |  8 bits signed integer | character in an atom
typedef int16_t Short; /// like  JVM's short | 16 bits signed integer | Knob of an S-expression 
typedef int32_t Long; ///   like  JVM's int    | 32 bits signed integer | an dotted Cons S-expression   
typedef int64_t Integer; ///  like JVM's long    | 32 bits signed integer | an dotted Cons S-expression   
typedef bool    Boolean; /// JVM's byte                |  8 bits signed integer | character in an atom
typedef const char *const Text; // Representation of immutable srings


// typedef enum { ok } OK;
template<typename T> constexpr inline T max(T s1, T s2) { return s1 > s2 ? s1 : s2; } 
template<typename T> constexpr inline T min(T s1, T s2) { return s1 < s2 ? s1 : s2; } 
template<typename T> constexpr inline T range(T s1, T s2) { return s2 - s1 + 1; } 
/*@ The Primitive Types@
Our byte addressable underlining machine offers three primitive types: byte,
Short, and, Long whose sizes are 8, 16, and 32 bits respectively.  These types
are fixed width signed integers, represented in two's complement, and are
similar to the types byte, short, and int of the Java virtual machine. Punning
is allowed, and used extensively: A Long is constituted by two consecutive
halves. No particular byte or halves ordering is assumed. */

typedef int8_t  byte; /// JVM's byte              |  8 bits signed integer | character in an atom
typedef int16_t Short; /// Short a Long/JVM's short | 16 bits signed integer | Knob of an S-expression 
typedef int32_t Long; /// Machine Long/JVM's int  | 32 bits signed integer | an dotted Cons S-expression   

#endif // CHIC_H


#ifdef UNCHIC
#undef CHIC_H
#undef  Provides          
#undef  Let               
#undef  let                       
#undef  Allocate
#undef  function
#undef  property          
#undef  procedure         
#undef  array
#undef  variable
#undef  constant
#undef  action            
#undef  Type
#undef  modifier
#undef  perspective
#undef  Representation    
#undef  asdfasdType              
#undef  returns
#undef  by
#endif
