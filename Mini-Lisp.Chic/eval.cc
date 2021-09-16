#include "eval.h"
#include "a-list.h"
#include "builtin.h"
#include "basics.h"
#include "print.h"
#include "except.h"

#define xPRODUCTION
#include "mode.h"


#undef NULL
void bind(S formals, S arguments) {
  if (formals.null() || arguments.null()) return; 
  push(formals.car(), arguments.car());
  bind(formals.cdr(), arguments.cdr());
}

S iterate(S s, S (*f)(S)) {
  return s.null() ? s :  f(s.car()).cons(iterate(s.cdr(), f)); 
}

S check(S list, S report) {
  if (list.null()) return NIL;
  if (list.atom()) list.error(report);
  check(list.cdr(), report);
}

S align(S s1, S s2) {
  if (s1.null() && !s2.null()) return s2.error(REDUNDANT_ARGUMENT);
  if (!s1.null() && s2.null()) return s1.error(MISSING_ARGUMENT);
  if (s1.null()) return NIL; 
  return align(s1.cdr(), s2.cdr());
}

namespace {
  namespace {
    S identity(S s) { return s; }
    S evaluate(S s) { return s.eval(); }
    bool normal(S tag) { return tag.eq(NDEFUN) || tag.eq(NLAMBDA); }
    bool native(S tag) { return tag.eq(NDEFUN) || tag.eq(DEFUN); }
  }

  S apply(S tag, S formals, S body, S actuals) {
    M(">> Applying to", actuals, tag, formals, body); 
    check(actuals, BAD_ARGUMENTS);
    if (formals.atom())   M("Variadic binding of", formals, actuals), 
      push(formals, actuals);
    else { M("list of arguments"),
      check(formals, BAD_PARAMETERS);
      S arguments = iterate(actuals, normal(tag) ? identity : evaluate);
      align(formals, actuals);
      bind(formals, arguments);
    }
    const auto result = (native(tag) ? exec : evaluate)(body);
    M4("<< application", body, "/", actuals,  result); 
    return result;
  }
}

S apply(S f, S actuals) {
  S before = alist;
  push(S("*"), f.cons(actuals));
  S anonymous = f.eval(); 
  push(S(RECURSE), anonymous);
  anonymous.n3() || f.error(BAD_FUNCTION).t();
  S result = apply(anonymous.$1$(), anonymous.$2$(), anonymous.$3$(), actuals);
  alist = before;
  return result;
}

S eval(S s) {
    struct {
      S eval(S s) {
        M3(">> Evaluating [", s, "]");
        return s.atom() ? lookup(s) : apply(s.car(), s.cdr()); 
      }
    } inner; 
    const S result = inner.eval(s);
    M4("<< [", s, "] evaluated to " , result);
    return result;
}
