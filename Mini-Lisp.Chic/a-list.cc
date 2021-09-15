#include "a-list.h"
#include "basics.h"
#include "print.h"
#define PRODUCTION
#include "mode.h"
#include "except.h"

extern S lookup(S id, S list) { 
  return 
    list.null() ?  id.error(UNDEFINED_ATOM): 
    list.car().car().eq(id) ? list.car().cdr() : 
    lookup(id, list.cdr()); 
}

extern S lookup(S id) { 
  for (S s = alist; s.pair(); s = s.cdr())
      if (s.car().car().eq(id))
        return s.car().cdr(); 
  return lookup(id, globals); 
}

extern S set(S k, S v) { return globals = k.cons(v).cons(globals), v;  }
extern S push(S k, S v) { return alist = k.cons(v).cons(alist), v; }

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
const S _(RECURSE), _(ARGUMENT);

static S builtin();
extern S alist = NIL;
extern S globals = builtin(); 

/** An anonymous static singleton encapsulates initialization */
namespace {
  inline S entry(S tag, S name, S formals) {
    return name.cons(list(tag, formals, name));
  }
  inline S eager(S name, S formals) {
    return entry(DEFUN, name, formals); 
  }
  inline S normal(S name, S formals) {
   return entry(NDEFUN, name, formals);
  }
}

static S builtin() {
  static S inner = list(
    NIL.cons(NIL), 
    T.cons(T), 
    eager(ATOM,  list(" x")),  
    eager(CAR,   list(" x")), 
    eager(CDR,   list(" x")),
    normal(COND, list(" x")), 
    eager(CONS, list(" x", " y")), 
    eager(EQ, list(" x", " y")),
    eager(EVAL, list(" x")), 
    normal(ERROR, list(" x", " y")), 
    eager(SET, list(" x", " y")),
    eager(NULL, list(" x")), 
    normal(QUOTE, list(" x")), 
    normal(LAMBDA, list(" x", "y")), 
    normal(NLAMBDA, list(" x", " y")),
    normal(DEFUN, list(" x", " y", " z")), 
    normal(NDEFUN,list(" x", " y", " z")) 
  ); 
  return inner;
} 

static S begin(S s) {
  D(s);
  for (; ; s = s.cdr()) {
    if (s.null()) return s;
    const S binding = s.car();
    const S key = binding.car();
    if (key.eq(RECURSE)) return s;
  }
}

static void argument(S s) {
  D(s);
  const S binding = s.car();
  const S key = binding.car();
  const S value = binding.cdr();
  print(" Argument: "), print(key), print(" = "), println(value);
}

static void arguments(S s, S until) {
  D(s);
  if (s.null() || s.handle == until.handle) return;
  arguments(s.cdr(), until);
  argument(s);
}

/** Print the bottom most frame on the association list, and return the list
 * without this frame */

static S frame(S s) {
  D(s);
  if (s.null()) return s;
  D(s);
  S until = begin(s); 
  D(until);
  if (until.null()) return s;
  if (until.cdr().pair()) {
    const S binding = until.cdr().car();
    const S key = binding.car();
    const S value = binding.cdr();
    print("While applying "), print(value.car()), print(" to list "), println(value.cdr());
  }
  {
    const S binding = until.car();
    const S key = binding.car();
    const S value = binding.cdr();
    print(" Function body: "), println(value);
  }
  arguments(s, until);
  return until.cdr();
}

/** In case of error, dump the association-list with trace back: */
void stack_dump() {
  int n = 0;
  for (S s = alist; !s.null() && n < 5; ++n, s = frame(s)) {
    ; 
  }
  alist = NIL;
}

