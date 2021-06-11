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

S evaluate_list(S xs) { M(xs);
  D(xs.car());
  D(xs.cdr());
  return xs.null() ?  NIL: xs.car().eval().cons(evaluate_list(xs.cdr()));
}

S evaluate_cond(S test_forms) {
  D(test_forms);
  if (test_forms.null())
    return NIL;
  if (test_forms.car().atom())
    return test_forms.car().error(COND);
  if (test_forms.car().car().eval().t())
    return test_forms.car().cdr().car().eval();
  return evaluate_cond(test_forms.cdr());
}

S apply_atomic(S f, S a) { M(f, a);
  if (f.eq(QUOTE))
    return a;
  if (f.eq(COND))
    return evaluate_cond(a);
  if (f.eq(EVAL))
    return evaluate_list(a).eval();
  if (f.eq(CAR)) 
    return evaluate_list(a).car();
  if (f.eq(CDR))
    return evaluate_list(a).cdr();
  if (f.eq(NULL))
    return a.null(); 
  if (f.eq(ATOM))
    return evaluate_list(a).atom(); 
  return bug(f.cons(a));
}

S evaluate_atomic(S s) { M(s);
  return apply_atomic(s.car(), s.cdr());
}

S NLAMBDA("nlambda"), LAMBDA("lambda");

S apply(S s, S args) {
  return NIL;
}

S eval(S s) { M(s);
  if (s.atom()) return lookup(s);
  if (atomic(s.car())) return evaluate_atomic(s);
  return apply(eval(s.car()), s.cdr());
}

S defun(S name, S parameters, S body) {
  return set(name, list(LAMBDA, parameters, body));
}

S ndefun(S name, S parameters, S body) {
  return set(name, list(NLAMBDA, parameters, body));
}
