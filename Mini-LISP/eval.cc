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
S bug(S s) {
  return s.error(T);
}

#define FUN(Return, Name, ArgumentType) \
  Return Name(ArgumentType _) { \
    auto $$ = Name; \
    M(_); \
    Return __ =  

#define IS(X)    \
    X; \
    M("RETURN", __); \
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

S apply_atomic(S f, S a) { M(f, a);
  if (f.eq(QUOTE))
    return a.car();
  if (f.eq(COND))
    return evaluate_cond(a);
  if (f.eq(CAR)) {
    S xs = evaluate_list(a);
    D(xs);
    return xs.car().car();
  }
  if (f.eq(EVAL))
    return evaluate_list(a).eval();
  if (f.eq(CDR))
    return evaluate_list(a).car().cdr();
  if (f.eq(NULL))
    return a.null(); 
  if (f.eq(ATOM))
    return evaluate_list(a).atom(); 
  return bug(f.cons(a));
}


S evaluate_atomic(S s) { M(s);
  return apply_atomic(s.car(), s.cdr());
}

FUN(S, eval, S) IS( 
  _.atom() ? lookup(_):
    atomic(_.car()) ? evaluate_atomic(_):
      apply($$(_.car()), _.cdr())
)



S xevaluate_list(S xs) { M(xs);
    auto x = xevaluate_list;
    auto result = xs.null() ?  NIL: xs.car().eval().cons(evaluate_list(xs.cdr()));
    D(result);
    return result;
}



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
