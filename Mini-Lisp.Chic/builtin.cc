#include "builtin.h"
#include "a-list.h"
#include "basics.h"
#define PRODUCTION
#include "mode.h"

S defun(S name, S parameters, S body) { return set(name, list(LAMBDA, parameters, body)); }
S ndefun(S name, S parameters, S body) { return set(name, list(NLAMBDA, parameters, body)); }

S evaluate_cond(S s) {  
  D(s);
  return s.null() ?  s :
      s.car().atom() ? s.car().error(COND):
       s.car().car().eval().t() ? s.car().cdr().car().eval():
         evaluate_cond(s.cdr()) ;
}



#undef NULL
#define _(T) T(#T)
/* Primitives */
const S _(NIL), _(T); 
const S _(ATOM), _(CAR), _(CDR), _(COND);
const S _(CONS), _(EQ);   
/* Auxiliary */ 
const S  _(ERROR), _(EVAL), _(SET);
/* Library */
const S _(NDEFUN), _(DEFUN), _(NLAMBDA), _(LAMBDA), _(QUOTE), _(NULL);
// Stack trace:
const S _(RECURSE);

const S __0(".."), __1("..1"), __2("..2"), __3("..3"), __00(list(__0)), __12(list(__1,__2)), __123(list(__1,__2,__3));

/** An anonymous static singleton encapsulates initialization */
namespace {
  inline S entry(S tag, S name, S formals) {
    return list(name, tag, formals, name);
  }
  inline S eager(S name, S formals) {
    return entry(DEFUN, name, formals); 
  }
  inline S normal(S name, S formals) {
   return entry(NDEFUN, name, formals);
  }
  inline S variadic(S name, S formals) {
   return entry(NDEFUN, name, formals);
  }
}

extern S builtin() {
  static S inner = list(
    NIL.cons(NIL), 
    T.cons(T), 
    eager(ATOM,  __00),  
    eager(CAR,   __00), 
    eager(CDR,   __00),
    variadic(COND, __0),
    eager(CONS, __12), 
    eager(EQ, __12),
    eager(EVAL, __00), 
    variadic(ERROR, __0),
    eager(SET, __12),
    eager(NULL, __00), 
    normal(QUOTE, __00), 
    normal(LAMBDA, __12), 
    normal(NLAMBDA, __12),
    normal(DEFUN, __123), 
    normal(NDEFUN, __123) 
  ); 
  return inner;
} 

extern S alist;
extern S t(S s) { return s.t() ? T : NIL; }  
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
  inline S cond() { D(v1()); return evaluate_cond(v1()); }
  // Auxiliary: 
  inline S eval() { return v1().eval(); }
  inline S error() { 
    return 
        v1().atom() ? v1().error(ERROR) : /* Empty list, or not a list at all */  
        v1().cdr().error(v1().car()); 
  }
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

extern S exec(S key) {
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
