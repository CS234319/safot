#include "eval.h"
#include "a-list.h"
#include "basics.h"

#define BUGGY 0

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

S NLAMBDA("nlambda"), LAMBDA("lambda");

const S ATOMIC_FUNCTIONS = list(
  CAR,   CDR,  CONS,
  ATOM,  NULL, EQ,  COND, 
  ERROR, SET,  EVAL, QUOTE,
  DEFUN, NDEFUN, NLAMBDA, LAMBDA
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

S defun(S name, S parameters, S body) { return set(name, list(LAMBDA, parameters, body)); }
S ndefun(S name, S parameters, S body) { return set(name, list(NLAMBDA, parameters, body)); }

FUN(S, evaluate_list, S) IS(
  _.null() ? NIL : _.car().eval().cons($$(_.cdr()))
) 

FUN(S, evaluate_cond, S)  IS( 
    _.null() ?  NIL:
    _.car().atom() ? _.car().error(COND):
      _.car().car().eval().t() ? _.car().cdr().car().eval():
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

void checkNumberOfArgs(S s) {
    S f = s.car();
    // 1 Args:
    if (f.eq(QUOTE) || f.eq(CAR) || f.eq(CDR) ||
        f.eq(ATOM) || f.eq(NULL) || f.eq(EVAL)) {
        s.more2() && s.error(REDUNDANT).t();
        s.less2() && s.error(MISSING).t();
    }

    // 2 Args:
    if (f.eq(CONS) || f.eq(SET) || f.eq(EQ) || f.eq(LAMBDA) || f.eq(NLAMBDA)) {
        s.more3() && s.error(REDUNDANT).t();
        s.less3() && s.error(MISSING).t();
    }

    // 3 Args:
    if (f.eq(NDEFUN) || f.eq(DEFUN)) {
        s.more4() && s.error(REDUNDANT).t();
        s.less4() && s.error(MISSING).t();
    }
}

S evaluate_atomic_function(S s) { M(s);
  checkNumberOfArgs(s);
  const S f = s.car();
  // Atomic functions:
  if (f.eq(CAR))    return only(s).car();
  if (f.eq(CONS))   return s.$2$().eval().cons(s.$3$().eval());
  if (f.eq(SET))    return set(s.$2$().eval(),          s.$3$().eval());
  if (f.eq(EQ))     return s.$2$().eval().eq(s.$3$().eval())   ?         T     : NIL;
  if (f.eq(COND))   return evaluate_cond(s.cdr());
  if (f.eq(CDR))    return only(s).cdr();
  if (f.eq(ATOM))   return only(s).atom()            ?         T     : NIL;
  if (f.eq(EVAL))   return only(s).eval();
  if (f.eq(ERROR))  return s.error(s.cdr());
  if (f.eq(NULL))   return only(s).null()            ?         T     : NIL;
  if (f.eq(QUOTE))  return s.cdr().car();
  if (f.eq(NLAMBDA)) return list(NLAMBDA,             s.$2$(),     s.$3$());
  if (f.eq(LAMBDA)) return list(LAMBDA,             s.$2$(),     s.$3$());
  if (f.eq(NDEFUN)) { 
    ndefun(s.$2$(), s.$3$(), s.$4$());
    return  s.$2$();
  }
  if (f.eq(DEFUN)) { 
    defun(s.$2$(), s.$3$(), s.$4$());
    return  s.$2$();
  }
  return bug(s);
}

S apply(S f, S args) {
  f.n3() || f.cons(args).error(INVALID).t();
  save(); // #ERROR DOR? Are you sure.
  const auto actuals = f.$1$().eq(NLAMBDA)? args : f.$1$().eq(LAMBDA) ? evaluate_list(args) : f.cons(args).error(INVALID);
  alist = bind(f.$2$(), actuals, alist);
  const auto result = f.$3$().eval();
  restore();
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
