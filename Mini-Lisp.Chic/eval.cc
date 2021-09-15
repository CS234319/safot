#include "eval.h"
#include "a-list.h"
#include "basics.h"
#include "print.h"
#include "except.h"

#define PRODUCTION
#include "mode.h"

S evaluate_cond(S s) {  
  return s.null() ?  s :
      s.car().atom() ? s.car().error(COND):
       s.car().car().eval().t() ? s.car().cdr().car().eval():
         evaluate_cond(s.cdr()) ;
}

static inline S t(S s) { return s.t() ? T : NIL; }  
S defun(S name, S parameters, S body) { return set(name, list(LAMBDA, parameters, body)); }
S ndefun(S name, S parameters, S body) { return set(name, list(NLAMBDA, parameters, body)); }

#undef NULL
namespace {
  namespace {
    inline S v1() { return alist.car().cdr(); } 
    inline S v2() { return alist.cdr().car().cdr(); } 
    inline S v3() { return alist.cdr().cdr().car().cdr(); } 
   // Elementary: 
    inline S atom() { return t(v1().atom()); }
    inline S car() { return v1().car(); }
    inline S cdr() { return v1().cdr(); }
    inline S cons() { return v2().cons(v1()); }
    inline S eq() { return t(v2().eq(v1())); }
    inline S cond() { return evaluate_cond(v1()); }
    // Auxiliary: 
    inline S eval() { return v1().eval(); }
    inline S error() {  return v2().error(v1()); }
    inline S set() { return ::set(v2(), v1()); }
    // Library I: 
    inline S null() { return t(v1().null()); } 
    inline S quote() {  return v1(); } 
    // Library II: 
    inline S lambda() { return list(LAMBDA, v2(), v1()); }
    inline S nlambda() {  return list(NLAMBDA, v2(), v1()); }
    inline S defun() { return ::defun(v3(), v2(), v1()); }
    inline S ndefun() { return ::ndefun(v3(), v2(), v1()); }
  }

  S builtin(S key) {
    static struct {
      S key;
      S (*f)();
    } builtins[] = {
    // 6 elementary functions:
      { ATOM,  atom },
      { CAR,   car  },
      { CDR,   cdr  },
      { COND,  cond },
      { CONS,  cons },
      { EQ,    eq   },
    // 3 auxiliary functions:
      { ERROR, error },
      { EVAL,  eval  },
      { SET,   set   },
    // 6 library functions 
      { NULL,    null },
      { QUOTE,   quote },
      { DEFUN,   defun },
      { NDEFUN,  ndefun },
      { LAMBDA,  lambda }, 
      { NLAMBDA, nlambda }, 
    // 1 end marker
      { NIL, 0}
    };

    for (H i = 0; builtins[i].f != 0; ++i) 
      if (key.handle == builtins[i].key.handle) 
        return (*(builtins[i].f))();  
    return key.error(list(v1(),v2(),v3()));
  }
}

void bind(S formals, S arguments) {
  if (formals.null() || arguments.null()) return; 
  push(formals.car(), arguments.car());
  bind(formals.cdr(), arguments.cdr());
}

S iterate(S s, S (*f)(S)) {
  return s.null() ? s :  f(s.car()).cons(iterate(s.cdr(), f)); 
}

S align(S s1, S s2) {
  if (!s1.null() && s2.null()) return s1.error(MISSING_ARGUMENT);
  if (s1.null() && !s2.null()) return s2.error(REDUNDANT_ARGUMENT);
  if (s1.null()) return s1; 
  if (s1.atom()) return s1.error(BAD_PARAMETERS);
  if (s2.atom()) return s2.error(BAD_ARGUMENTS);
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
    M4(">> Applying", body, "to", actuals); 
    align(formals, actuals);
    M("aligned");
    S arguments = iterate(actuals, normal(tag) ? identity : evaluate);
    D(arguments); 
    align(formals, actuals);
    bind(formals, arguments);
    const auto result = (native(tag) ? builtin : evaluate)(body);
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
    M4("<< [", s, "] evaluated to [" , result, "]");
    return result;
}
