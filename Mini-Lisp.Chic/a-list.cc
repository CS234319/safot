#include "a-list.h"
#include "basics.h"
#include "print.h"
#define PRODUCTION
#include "mode.h"
#include "except.h"
#include "builtin.h"

extern S alist = NIL;
extern S globals = builtin(); 
void reset() { alist = NIL; globals = builtin(); }
extern S push(S k, S v) { return alist = k.cons(v).cons(alist), v; }
extern S set(S k, S v) { return globals = k.cons(v).cons(globals), v;  }

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
  print("           "), print(key), print(" = "), println(value);
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
    print("... While applying "), print(value.car()), print(" to list "), println(value.cdr());
  }
  {
    const S binding = until.car();
    const S key = binding.car();
    const S value = binding.cdr();
    print("      i.e., applying "), print(value), println(" with these bindings:");
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

