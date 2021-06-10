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

S apply_unary_atomic(S atomic_function, S xs) { M(atomic_function, xs);
  if (xs.null())
    return atomic_function.error(MISSING);
  if (xs.atom())
    return xs.error(INVALID);
  if (xs.cdr().t())
    return xs.error(REDUNDANT);
  const S first = xs.car();
  if (atomic_function.eq(EVAL))
    return first.car().eval();
  if (atomic_function.eq( CAR)) 
    return first.car();
  if (atomic_function.eq(CDR))
    return first.cdr();
  if (atomic_function.eq(NULL))
    return first.null() ? T : NIL;
  if (atomic_function.eq(ATOM))
    return first.atom() ? T : NIL;
  return bug(atomic_function);
}

S apply_binary_atomic(S atomic_function, S xs) {M(atomic_function, xs);
  if (xs.null())
    return atomic_function.error(MISSING);
  if (xs.atom())
    return xs.error(INVALID);
  if (xs.cdr().null())
    return xs.error(MISSING);
  if (xs.cdr().atom())
    return xs.error(INVALID);
  if (xs.cdr().cdr().t())
    return xs.error(INVALID);

  const S first = xs.car();
  const S second = xs.cdr().car();;

  if (atomic_function.eq(CONS))
    return first.cons(second);
  if (atomic_function.eq(EQ))
    return first.eq(second) ? T : NIL;
  if (atomic_function.eq(SET))
    return set(first, second);
  return bug(atomic_function.cons(xs));
}

S apply_eager_atomic(S atomic_function, S actuals) {
  D(atomic_function, actuals);
  static const S unaries = list(CAR, CDR, ATOM, NULL, EVAL);
  if (exists(atomic_function, unaries)) 
    return apply_unary_atomic(atomic_function, actuals);
  return apply_binary_atomic(atomic_function, actuals);
}

S apply_atomic(S atomic_function, S actuals) { M(atomic_function, actuals);
  if (atomic_function.eq(COND)) 
    return evaluate_cond(actuals);
  if (atomic_function.eq(QUOTE)) 
    return actuals; 
  return apply_eager_atomic(atomic_function, evaluate_list(actuals));
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
