#include "eval.h"
#include "a-list.h"
#include "basics.h"

#define BUGGY 1

#if !BUGGY
#undef D
#undef M
#undef M2
#undef M3
#define D(...) 0
#define M(...) 0
#define M2(...) 0
#define M3(...) 0
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
    const auto $$ = Name; \
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
    _.car().atom() ? _.car().error(COND):
      _.car().car().eval().t() ? _.car().cdr().eval():
        $$(_.cdr()) ;
)

S only(S s) {
  s.pair() || die(s);  
  s.cdr().cdr().t() && s.error(REDUNDANT).t(); 
  S a = evaluate_list(s.cdr());
  a.null() && s.error(MISSING).t();
  a.atom() && s.error(INVALID).t();
  return a.car();
}

S evaluate_atomic_function(S s) { M(s);
  S f = s.car();
  if (f.eq(QUOTE))
    return s.cdr().car();
  if (f.eq(CAR)) { 
    s.more2() || s.error(REDUNDANT).t();
    s.less2() || s.error(MISSING).t();
    s.n2() || s.error(CAR).t();
    return s.$2$().car();
  }
  if (f.eq(COND))
    return evaluate_cond(s.cdr());
  if (f.eq(CDR)) 
    return only(s).cdr();
  if (f.eq(ATOM))
    return only(s).atom() ? T : NIL; 
  if (f.eq(NULL))
    return only(s).null() ? T : NIL; 
  if (f.eq(EVAL))
    return only(s).eval();
  return bug(s);
}

S NLAMBDA("nlambda"), LAMBDA("lambda");


S apply(S f, S args) {
  f.n3() || f.cons(args).error(INVALID).t();   
  const auto saved_alist = alist;
  const auto actuals = f.$1$().eq(NLAMBDA)? args : f.$1$().eq(LAMBDA) ? evaluate_list(args) : f.cons(args).error(INVALID);
  alist = bind(f.$2$(), actuals, alist);
  const auto result = f.$3$().eval();
  alist = saved_alist;
  return result;
}

S apply_defined_function(S f, S args) {
  apply(f,args);
}

FUN(S, eval, S) IS( 
  _.atom() ? lookup(_):
    atomic(_.car()) ? evaluate_atomic_function(_):
      apply_defined_function($$(_.car()), _.cdr())
)

S defun(S name, S parameters, S body) {
  return set(name, list(LAMBDA, parameters, body));
}

S ndefun(S name, S parameters, S body) {
  return set(name, list(NLAMBDA, parameters, body));
}
