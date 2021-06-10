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

/** Assertions like */ 
S bug(S s) {
  return s.error(S::T);
}


S evaluate_list(S xs) { M(xs);
  return xs.null() ?  S::NIL: xs.car().eval().cons(evaluate_list(xs.cdr()));
}

S evaluate_cond(S test_forms) {
  D(test_forms);
  if (test_forms.null())
    return S::NIL;
  if (test_forms.car().atom())
    return test_forms.car().error(S::COND);
  if (test_forms.car().car().eval().t())
    return test_forms.car().cdr().car().eval();
  return evaluate_cond(test_forms.cdr());
}

S apply_unary_atomic(S atomic_function, S xs) {
  if (xs.null())
    return atomic_function.error(S::MISSING);
  if (xs.atom())
    return xs.error(S::INVALID);
  if (xs.cdr().t())
    return xs.error(REDUNDANT);
  const S first = xs.car();
  if (atomic_function.eq(S::EVAL))
    return first.car().eval();
  if (atomic_function.eq( S::CAR)) 
    return first.car();
  if (atomic_function.eq(S::CDR))
    return first.cdr();
  if (atomic_function.eq(S::NULL))
    return first.null() ? S::T : S::NIL;
  if (atomic_function.eq(S::ATOM))
    return first.atom() ? S::T : S::NIL;
  return bug(atomic_function);
}

S apply_binary_atomic(S atomic_function, S xs) {
  if (xs.null())
    return atomic_function.error(S::MISSING);
  if (xs.atom())
    return xs.error(S::INVALID);
  if (xs.cdr().null())
    return xs.error(S::MISSING);
  if (xs.cdr().atom())
    return xs.error(S::INVALID);
  if (xs.cdr().cdr().t())
    return xs.error(S::INVALID);

  const S first = xs.car();
  const S second = xs.cdr().car();;

  if (atomic_function.eq(S::CONS))
    return first.cons(second);
  if (atomic_function.eq(S::EQ))
    return first.eq(second) ? S::T : S::NIL;
  if (atomic_function.eq(S::SET))
    return set(first, second);
  return bug(atomic_function.cons(xs));
}

S apply_eager_atomic(S atomic_function, S actuals) {
  D(atomic_function, actuals);
  static const S unaries = list(S::CAR, S::CDR, S::ATOM, S::NULL, S::EVAL);
  if (exists(atomic_function, unaries)) 
    apply_unary_atomic(atomic_function, actuals);
  apply_binary_atomic(atomic_function, actuals);
}

S apply_atomic(S atomic_function, S actuals) {
  M(atomic_function, actuals);
  if (atomic_function.eq(S::COND)) 
    return evaluate_cond(actuals);
  if (atomic_function.eq(S::QUOTE)) 
    return evaluate_cond(actuals);
  return apply_eager_atomic(atomic_function, evaluate_list(actuals));
}

S evaluate_atomic(S s) { M(s);
  return apply_atomic(s.car(), s.cdr());
}

S apply(S s, S args) {
  return S::NIL;
}

S eval(S s) { M(s);
  if (s.atom()) return lookup(s);
  if (atomic(s.car())) return evaluate_atomic(s);
  return apply(eval(s.car()), s.cdr());
}

S defun(S name, S parameters, S body) {
  return set(name, list(S::LAMBDA, parameters, body));
}

S ndefun(S name, S parameters, S body) {
  return set(name, list(S::NLAMBDA, parameters, body));
}
