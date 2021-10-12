#import  "builtin.h"
#import  "a-list.h"
#import  "basics.h"
#define PRODUCTION
#import  "mode.h"

#import "atoms.h"

const S __00(list(__0)), __12(list(__1,__2)), __123(list(__1,__2,__3));

namespace Engine {
  namespace Inner {
    S evaluate_cond(S s) {  
    D(s);
    return s.null() ?  s :
        s.car().atom() ? s.car().error(COND):
         s.car().car().eval().t() ? s.car().cdr().car().eval():
           evaluate_cond(s.cdr()) ;
  }
}
using namespace Inner;

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
   return entry(DEFUN, name, formals);
  }
  inline S nvariadic(S name, S formals) {
   return entry(NDEFUN, name, formals);
  }
}


extern S builtin() {
  static S inner = list(
    NIL.cons(NIL), 
    T.cons(T), 
    eager(NULL, __00), 
    normal(QUOTE, __00), 
    normal(LAMBDA, __12), 
    normal(NLAMBDA, __12),
    normal(DEFUN, __123), 
    normal(NDEFUN, __123), 
    eager(ATOM,  __00),  
    eager(CAR,   __00), 
    eager(CDR,   __00),
    nvariadic(COND, __0),
    eager(CONS, __12), 
    eager(EQ, __12),
    eager(EVAL, __00), 
    eager(SET, __12),
    variadic(ERROR, __0),
    eager(GLOBALS, NIL), 
    eager(RESET, NIL) 
  ); 
  return inner;
} 

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
        v1().cdr().null() ? v1().car().error(ERROR) : /* Empty list, or not a list at all */  
        v1().cdr().error(v1().car()); 
  }
  inline S set() { return Engine::set(v2(), v1()); }
  // Library I: 
  inline S null() { return t(v1().null()); } 
  inline S quote() {  return v1(); } 
  // Library II: 
  inline S lambda() { return list(LAMBDA, v2(), v1()); }
  inline S nlambda() {  return list(NLAMBDA, v2(), v1()); }
  inline S defun() { return Engine::set(v3(), lambda()); }
  inline S ndefun() { return Engine::set(v3(), nlambda()); }
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
    // Backdoor functions
      { GLOBALS, Dump::globals },
      { RESET, Engine::reset },
    // 1 end marker
      { NIL, 0}
    };

    for (H i = 0; builtins[i].f != 0; ++i) 
      if (key.handle == builtins[i].key.handle) 
        return (*(builtins[i].f))();  
    return key.error(list(v1(),v2(),v3()));
  }
}
