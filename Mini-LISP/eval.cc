#include "eval.h"
#include "a-list.h"
#include "basics.h"

/** Assertions like */ 
S bug(S s) {
  s.error(S::T);
}


S evaluate_list(S xs) {
  if (xs.null())
    return S::NIL;
  return xs.car().eval().cons(evaluate_list(xs.cdr()));
}

S evaluate_cond(S test_forms) {
  if (test_forms.null())
    return S::NIL;
  if (test_forms.car().atom())
    return test_forms.car().error(S::COND);
  if (test_forms.car().car().eval().isTrue())
    return test_forms.car().cdr().car().eval();
  return evaluate_cond(test_forms.cdr());
}

S apply_trivial_atomic(S atomic_function, S first, S second) {
  if (atomic_function.eq(S::ATOM))
    return first.atom();
  if (atomic_function.eq( S::CAR)) 
    return first.car();
  if (atomic_function.eq(S::CDR))
    return first.cdr();
  if (atomic_function.eq(S::CONS))
    return first.cons(second);
  if (atomic_function.eq(S::EQ))
    return first.eq(second);
  if (atomic_function.eq(S::SET))
    return set(first, second);
  bug(list(atomic_function, first, second));
  return S::NIL;
}

S apply_eager_atomic(S atomic_function, S actuals) {
  if (atomic_function.eq(S::ERROR)) 
    return actuals.error(S::ERROR);
  if (atomic_function.eq(S::EVAL))
    return actuals.car().eval();
  return apply_trivial_atomic(atomic_function, actuals.car(), actuals.cdr().car());
}

S apply_atomic(S atomic_function, S actuals) {
  if (atomic_function.eq(S::COND)) 
    return evaluate_cond(actuals);
  return apply_eager_atomic(atomic_function, evaluate_list(actuals));
}

S evaluate_atomic(S s) {
  return apply_atomic(s.car(), s.cdr());
}

S apply(S s, S args) {
  return S::NIL;
}

S eval(S s) {
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
