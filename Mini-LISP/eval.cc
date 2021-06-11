#include "eval.h"
#include "a-list.h"
#include "basics.h"

#define BUGGY 1

#if !BUGGY
#undef D
#undef M
#define D(...) 0
#define M(...) 0
#else 
#include "dump.h"
#include "io.h"
#endif

const S ATOMIC_FUNCTIONS = list(
  CAR,   CDR,  CONS,
  ATOM,  NULL, EQ,  COND, 
  ERROR, SET,  EVAL, QUOTE
);

inline bool atomic(S name) { return exists(name, ATOMIC_FUNCTIONS); }

/** Assertions like */ 
S bug(S s) { return s.error(T); }

#define FUN(Return, Name, ArgumentType) \
  Return Name(ArgumentType _) { \
    auto $$ = Name; \
    M3("[",_,"]"); \
    Return __ =  

#define IS(X)    \
    X; \
    M2("-->", __); \
    return __; \
  } 

FUN(S, evaluate_list, S) IS(
  _.null() ? NIL : _.car().eval().cons($$(_.cdr()))
) 

FUN(S, evaluate_cond, S)  IS( 
    _.null() ?  NIL:
    _.car().atom() ?  _.car().error(COND):
      _.car().car().eval().t() ? _.car().cdr().car().eval():
        $$(_.cdr()) ;
)

S only(S s) {
  s.pair() || die(s);  
  S a = evaluate_list(s.cdr());
  a.null() && s.error(MISSING).t();
  a.atom() && s.error(INVALID).t();
  a.cdr().t() && s.error(REDUNDANT).t(); 
  return a.car();
}

S apply_atomic(S s) { M(s);
  S f = s.car();
  if (f.eq(QUOTE))
    return s.cdr().car();
  if (f.eq(COND))
    return evaluate_cond(s.cdr());
  if (f.eq(CAR)) 
    return only(s).car();
  if (f.eq(CDR)) 
    return only(s).cdr();
  if (f.eq(ATOM))
    return only(s).atom() ? T : NIL; 
  if (f.eq(NULL))
    return only(s).null() ? T : NIL; 
  if (f.eq(EVAL))
    return only(s).eval();
  if (f.eq(NULL))
    return only(s).null();
  return bug(s);
}


S evaluate_atomic(S s) { M(s);
  return apply_atomic(s);
}

FUN(S, eval, S) IS( 
  _.atom() ? lookup(_):
    atomic(_.car()) ? evaluate_atomic(_):
      apply($$(_.car()), _.cdr())
)


S NLAMBDA("nlambda"), LAMBDA("lambda");

S apply(S s, S args) {
  return NIL;
}

S defun(S name, S parameters, S body) {
  return set(name, list(LAMBDA, parameters, body));
}

S ndefun(S name, S parameters, S body) {
  return set(name, list(NLAMBDA, parameters, body));
}
