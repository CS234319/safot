// Poor man's edition of a bit cleaner C/C++
#define Implementation (__INCLUDE_LEVEL__ == 0)

<<<<<<< HEAD
#define Return(X) return ((__ = (X)),(__));
=======
#define unique(X)       CONCATENATE(X,__COUNTER__)

#define COUNT(whatever...)   COUNT1(whatever,9, 8, 7, 6, 5, 4, 3,2,1,0)
#define COUNT1(_1,_2,_3,_4,_5,_6,_7,_8,_9, N, ...) N
>>>>>>> 64596d9 (checkpoint)

static_assert(COUNT() == 1);
static_assert(COUNT(1) == 1);
static_assert(COUNT(1,2) == 2);
static_assert(COUNT(1,2,3) == 3);
static_assert(COUNT(1,2,3,4) == 4);

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


#import <functional>
#import <iostream>

#define Type struct
#define Representation(whatever...) union {whatever; };

#define fail ({0; throw *this; this;})

#define perhap(whatever...) struct{whatever;};
#define by(whatever...)      :whatever {}
#define selfing(whatever...) is(((whatever),*this))
#define doing(whatever...)   { whatever; }
#define from(whatever...)    (whatever)
#define is(whatever)      { return (whatever); }
#define with(whatever...)    (whatever) const
#define taking(whatever...)  (whatever)
#define nothing
#define then ,  
#define query(X)      X
#define action(X)      X
#define below ;
#define feature(X)     inline X() const

<<<<<<< HEAD
<<<<<<< HEAD
#define Initializing(T)  T::T
#define Create(X)   explicit X
#define Make(X)     public: static X make
=======
#define Initializing(T) T::T
=======
#define Filling(T)    T::T
>>>>>>> a5d5e07 (checkpoint)
#define Fill(X)       explicit X
<<<<<<< HEAD
#define Make            static Self make
>>>>>>> 64596d9 (checkpoint)
=======
#define Make          static Self make
>>>>>>> d1db79c (checkpoint)

#define Feature(X)     inline auto X() const

#define Query(X)      auto X
#define Property(X)   X() const

#define Typed(T)       T

#define Module          namespace
#define Provides        extern
#define Hides           static
#define Unit int

#define Service static struct

#define As(T)  operator T() const
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
#define Alias(X)        typedef X 

#define Service static struct
#define Fluenter(name) auto name()
#define Fluent(name) Self &name

#define Selfer(X)       Self X
#define pairing(x,y) (x,y)
#define do(whatever...)  ((whatever), 0)
#define Capsule(whatever...) private: whatever; public:

#define Occasionally(Special, General, Etc...) \
  Type Special: General {\
    typedef General Super;\
    typedef Special Self;\
    template<typename... Ts>  \
      Fill (Special) from(Ts... ts) by(General(ts...))\
    Feature(super) is(*(const General *)this) \
    Etc\
  };\

#define Perspective(P, Inner, Etc...) \
  Type P { \
    P(const P&) = default;\
    Representation(Inner _) \
    Fill(P) from(Inner __) by(_(_)) \
    operator Inner() const is(_) \
    Etc\
  };


/*@ The Primitive Types@
Our byte addressable underlining machine offers three primitive types: byte,
Short, and, Long whose sizes are 8, 16, and 32 bits respectively.  These types
are fixed width signed integers, represented in two's complement, and are
similar to the types byte, short, and int of the Java virtual machine. Punning
is allowed, and used extensively: A Long is constituted by two consecutive
halves. No particular byte ghalves ordering is assumed. */


#import <cstdint>         // Standard header providing integer types with widths
Alias(int8_t)  Byte; /// JVM's byte                |  8 bits signed integer | character in an atom
Alias(int16_t) Short; /// like  JVM's short | 16 bits signed integer | Knob of an S-expression
Alias(int32_t) Long; ///   like  JVM's int    | 32 bits signed integer | an dotted Pair S-expression
Alias(int64_t) Integer; ///  like JVM's long    | 32 bits signed integer | an dotted Pair S-expression
Alias(bool)    Boolean; /// JVM's byte                |  8 bits signed integer | character in an atom
Alias(char) Character; // Representation of character
Alias(const Character) Letter; // Representation of character
Alias(Letter *const) String;   // Representation of immutable srings

// typedef enum { ok } OK;
template<typename T> constexpr inline T max(T s1, T s2)   is( s1 > s2 ? s1 : s2)
template<typename T> constexpr inline T min(T s1, T s2)   is( s1 < s2 ? s1 : s2)
template<typename T> constexpr inline T range(T s1, T s2) is(s2 - s1 + 1)


// typedef std::function<int()> Action;
Alias(std::function<long long()>) Provider;
Alias(std::function<bool()>) Predicate;

#define Perform(something,etc...) {etc{something}}

#define maintaining(maintenane...) MAP(maintain,maintenane)
#define expecting(expectations...) MAP(expect,expectations)
#define promising(promises...)     MAP(promise, promises)

#define maintain(e)   expect(e) promise(e)
#define promise(p)    Promise unique(Promise) from (CONTEXT(p), PREDICATE(p));

<<<<<<< HEAD
<<<<<<< HEAD
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

// typedef std::function<int()> Action;
// typedef std::function<long long()> Provider;
// #import <iostream>

Type Context { 
   typedef std::function<bool()> Predicate;
=======
#define expect(e)     Expectation unique(Expectation) (CONTEXT(e), [&]{ return(e); });                                                  \
=======
#define expect(e)     Expectation unique(Expectation) from (CONTEXT(e), PREDICATE(e));
>>>>>>> a5d5e07 (checkpoint)

#define CONTEXT(X)    Context(__FILE__, __LINE__, __PRETTY_FUNCTION__, #X) 
#define PREDICATE(X)  Predicate([&]{ return(X); }) 


Type Context { 
>>>>>>> 64596d9 (checkpoint)
  String file;
  Integer line;
  String context;
  String expression;
<<<<<<< HEAD
  Create (Context) 
=======
  Fill (Context) 
>>>>>>> 64596d9 (checkpoint)
    from (String f, Integer l, String c, String e) 
      by(file(f), line(l), context(c), expression(e))
  Unit report() is(
      fprintf(stderr,"%s(%d)/%s: '%s' \n\t", file, line,context,expression)) 
};

#define Occasionally(Special, General, Etc...) \
  Type Special: General {\
    Alias(General) Super;\
    Alias(Special) Self;\
    template<typename... Ts>  \
      Fill (Special) from(Ts... ts) by(General(ts...))\
    Feature(super) is(*(const General *)this) \
    Etc\
  };\


Occasionally(Assertion, Context,
  Predicate holds;
  Unit check() is (holds() or report() and fail) 
  Fill(Assertion) from(const Context& c, const Predicate& m) by(Super(c), holds(m))
)

Occasionally(Expectation, Assertion,
  Unit report() is ((Super::report(), fprintf(stderr,"unmet expectation")))   
  Fill(Expectation) from(Context c, Predicate m) by(Super(c, m))
)

#define Done(X) ~X() 

Occasionally(Promise, Assertion,
  Unit report() is ((Super::report(),fprintf(stderr,"unkept promise")))   
  Done(Promise) doing(check())
)

<<<<<<< HEAD
#define CONTEXT(P,whatever...) \
  Context(__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, whatever)

#define promising(promises...)     MAP(PROMISE, promises)
#define expecting(expectations...) MAP(EXPECT, expectations)

#define EXPECT(e)                  unique(Expectation)(CONTEXT(e), PREDICATE(e)) 
#define PROMISE(e)                 unique(Promise)(CONTEXT(e), PREDICATE(e)) 

=======
>>>>>>> 64596d9 (checkpoint)
#define __EXPRESSION(X) <<#X<<"="<<X<<"; "

#define X1(x1)
#define X2(x1,x2)           __EXPRESSION(x2)
#define X3(x1,x2,x3)        __EXPRESSION(x2)  __EXPRESSION(x3)
#define X4(x1,x2,x3,x4)     __EXPRESSION(x2)  __EXPRESSION(x3) __EXPRESSION(x4)
#define X5(x1,x2,x3,x4,x5)  __EXPRESSION(x2)  __EXPRESSION(x3) __EXPRESSION(x4) __EXPRESSION(x5)

#define GET_MACRO(_0,_1,_2,_3,_4, _5, NAME,...) NAME
#define ELABORATE(...)  GET_MACRO(_0,__VA_ARGS__,X5, X4,X3,X2,X1,X0)(__VA_ARGS__)

#define VA_ARGS(...) DELME, ##__VA_ARGS__
<<<<<<< HEAD
=======


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


>>>>>>> 64596d9 (checkpoint)
