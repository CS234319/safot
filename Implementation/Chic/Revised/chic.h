// Poor man's edition of a bit cleaner C/C++
#define Implementation (__INCLUDE_LEVEL__ == 0)


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


#define Type struct
#define Representation(whatever...) union {whatever; };

#define perhap(whatever...) struct{whatever;};
#define fail ({0; throw *this; this;})
#define by(whatever...)      :whatever {}
#define from(whatever...)    (whatever)
#define is(whatever...)       { return (whatever); }
#define query(X)      X
#define action(X)      X
#define selfing(whatever...)  { return (whatever), *this; }
#define below ;

#define Initializing(T)  T::T
#define Create(X)  explicit X
#define Make(X)     public: static X make

#define Feature(X)     inline auto X() const

#define Query(X)      auto X
#define Property(X)   X() const

#define Typed(T)      T
#define feature(X)     inline X() const
#define with(whatever...)    (whatever) const
#define taking(whatever...)  (whatever)
#define nothing

#define Module          namespace
#define Provides        extern
#define Unit int

#define Service static struct

#import <cstdint>         // Standard header providing integer types with widths
#define As(t)  operator t() const
#define Let constexpr
#define let const auto
#define variable auto
#define Hiding static
#define Allocate
#define procedure void
#define array(type) type *const
#define variable(type) type &
#define constant(type) const type
#define modifier
#define Mutator(X)      X


#define Service static struct
#define Fluenter(name) auto name()
#define Fluent(name) Self &name


#define Selfer(X)       Self X
#define pairing(x,y) (x,y)
#define do(whatever...)  ((whatever), 0)
#define Capsule(whatever...) private: whatever; public:

//     Create(Special) from(nothing) by(Super(nothing))  \

#define Occasionally(Special, General, Etc...) \
  Type Special: General {\
    typedef General Super;\
    typedef Special Self;\
    template<typename... Ts>  \
      Create (Special) from(Ts... ts) by(General(ts...))\
    Feature(super) is(*(const General *)this) \
    Etc\
  };\

#define Perspective(P, Matter, Etc...) \
  Type P { \
    P(const P&) = default;\
    Representation(Matter matter) \
    Create(P) from(Matter m) by(matter(m)) \
    explicit operator Matter() const is(matter) \
    Etc\
  };


/*@ The Primitive Types@
Our byte addressable underlining machine offers three primitive types: byte,
Short, and, Long whose sizes are 8, 16, and 32 bits respectively.  These types
are fixed width signed integers, represented in two's complement, and are
similar to the types byte, short, and int of the Java virtual machine. Punning
is allowed, and used extensively: A Long is constituted by two consecutive
halves. No particular byte ghalves ordering is assumed. */

typedef int8_t  Byte; /// JVM's byte                |  8 bits signed integer | character in an atom
typedef int16_t Short; /// like  JVM's short | 16 bits signed integer | Knob of an S-expression
typedef int32_t Long; ///   like  JVM's int    | 32 bits signed integer | an dotted Pair S-expression
typedef int64_t Integer; ///  like JVM's long    | 32 bits signed integer | an dotted Pair S-expression
typedef bool    Boolean; /// JVM's byte                |  8 bits signed integer | character in an atom
typedef const char Letter; // Representation of character
typedef const char *const String;   // Representation of immutable srings

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
halves. No particular byte ghalves ordering is assumed. */


#define DESCENDING
#define COUNT(whatever...)   COUNT1(whatever,9, 8, 7, 6, 5, 4, 3,2,1,0)
#define COUNT1(_1,_2,_3,_4,_5,_6,_7,_8,_9, N, ...) N

#define unique(X)       X##COUNTER

#define TO_STRING(arg)  TO_STRING1(arg)
#define TO_STRING1(arg) TO_STRING2(arg)
#define TO_STRING2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define MAP(what, etc...) CONCATENATE(_fe,COUNT(etc))(what,etc)

#define _fe0(what, etc...)
#define _fe1(what, x, etc...) what(x)_fe0(what, etc)
#define _fe2(what, x, etc...) what(x)_fe1(what, etc)
#define _fe3(what, x, etc...) what(x)_fe2(what, etc)
#define _fe4(what, x, etc...) what(x)_fe3(what, etc)
#define _fe5(what, x, etc...) what(x)_fe4(what, etc)
#define _fe6(what, x, etc...) what(x)_fe5(what, etc)
#define _fe7(what, x, etc...) what(x)_fe6(what, etc)
#define _fe8(what, x, etc...) what(x)_fe7(what, etc)
#define _fe9(what, x, etc...) what(x)_fe8(what, etc)

static_assert(COUNT() == 1);
static_assert(COUNT(1) == 1);
static_assert(COUNT(1,2) == 2);
static_assert(COUNT(1,2,3) == 3);
static_assert(COUNT(1,2,3,4) == 4);

#import <functional>
#import <iostream>

// typedef std::function<int()> Action;
// typedef std::function<long long()> Provider;
//

Type Context { 
   typedef std::function<bool()> Predicate;
  Text file;
  Integer line;
  Text context;
  Text expression;
  Create (Context) 
    from (String f, Integer l, String c, String e) 
      by(file(f), line(l), context(c), expression(e))
  Unit report() is(
      fprintf(stderr,"%s(%d)/%s: '%s' \n\t", 
        file, line,context,expression)) 
};

Occasionally(Assertion, Context,
  Predicate holds;
  Make(Assertion) from(Context c, Predicate m) by (Context(c), holds(m))
  Unit check() is (holds() or report() and fail) 
)

Occasionally(Expectation, Assertion,
  struct T {
    T() {
      check();
    }
  } check;
  Unit report() is (Super::report(),fprintf(stderr,"unmet expectation"))   
)

Occasionally(Promise, Assertion,
  Unit report() is (Super::report(),fprintf(stderr,"unkept promise"))   
  ~Promise() from(nothing) is (check())
)

;

#define CONTEXT(P,whatever...) \
  Context(__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, whatever)

#define expecting(expectations...) const Expectation MAP(EXPECT,expectations);
#define Expect(e, whatever...)     unique(Expectation)(CONTEXT(x,whatever) 

#define __EXPRESSION(X) <<#X<<"="<<X<<"; "

#define X1(x1)
#define X2(x1,x2)           __EXPRESSION(x2)
#define X3(x1,x2,x3)        __EXPRESSION(x2)  __EXPRESSION(x3)
#define X4(x1,x2,x3,x4)     __EXPRESSION(x2)  __EXPRESSION(x3) __EXPRESSION(x4)
#define X5(x1,x2,x3,x4,x5)  __EXPRESSION(x2)  __EXPRESSION(x3) __EXPRESSION(x4) __EXPRESSION(x5)

#define GET_MACRO(_0,_1,_2,_3,_4, _5, NAME,...) NAME
#define ELABORATE(...)  GET_MACRO(_0,__VA_ARGS__,X5, X4,X3,X2,X1,X0)(__VA_ARGS__)

#define VA_ARGS(...) DELME, ##__VA_ARGS__

#define surely(P, etc...) \
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
      [&]{ std::cerr ELABORATE(VA_ARGS(etc)) << "\n"; return false;} \
     );                                                                  \
;

#define promising(promises...) MAP(promise, expectations)

#define Keep(X) expect(X) promise(X)
#define xCurrent(X) ([=]{return X;})()
