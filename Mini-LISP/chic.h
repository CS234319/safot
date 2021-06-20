#ifndef CHIC_H 
#define CHIC_H
// Poor man's edition of a bit cleaner C/C++

#include <functional>
typedef std::function<bool ()> Predicate;

#define UNIQUE(X)       UNIQUE1(X,__LINE__)
#define UNIQUE1(X,Y)    UNIQUE2(X,Y)
#define UNIQUE2(X,Y)    X##Y

#define THROW ;
#define Promise(P) \
  struct UNIQUE(Promise) {                                               \
    typedef const char *const String;                                    \
    String file;                                                         \
    const long line;                                                     \
    String context, expression;                                          \
    Predicate predicate;                                                 \
    UNIQUE(Promise)(String f, long l, String c, String e, Predicate p):  \
      file(f), line(l), context(c), expression(e), predicate(p) {}       \
    ~UNIQUE(Promise)() {                                                 \
       if (predicate()) return;                                          \
       (void) fprintf(stderr,"%s(%d)/%s: '%s' = broken promise\n",       \
           file, line, context, expression);                             \
             THROW;                                                \ 
    }                                                                    \
  } UNIQUE(promise)                                                      \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, [&]{return P;})        \
;

//       throw this;                                                      \

#define Expect(P) \
  struct UNIQUE(Expect) {                                                \
    typedef const char *const String;                                    \
    String file;                                                         \
    const long line;                                                     \
    String context, expression;                                          \
    Predicate predicate;                                                 \
    UNIQUE(Expect)(String f, long l, String c, String e, Predicate p):   \
      file(f), line(l), context(c), expression(e), predicate(p) {        \
        if (predicate()) return;                                         \
         (void) fprintf(stderr,"%s(%d)/%s: '%s' = unmet expectation\n",  \
             file, line, context, expression);                           \
             THROW;                                                \ 
    }                                                                    \
  } UNIQUE(Expect)                                                       \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, [&]{return P;})        \
;


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




//
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
typedef int16_t Short; /// Short a Long/JVM's short | 16 bits signed integer | Knob of an S-expression 
typedef int32_t Long; /// Machine Long/JVM's int    | 32 bits signed integer | an dotted Cons S-expression   
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

#ifndef Type
#error
#endif

#ifndef Type
#error
#endif

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
