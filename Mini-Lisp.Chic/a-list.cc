#import  "a-list.h"
#import  "basics.h"
#import  "print.h"
#define PRODUCTION
#import  "mode.h"
#import  "except.h"
#import  "builtin.h"

  extern const S UNDEFINED_ATOM;
namespace Engine {
  extern S alist = NIL0;
  extern S globals = builtin(); 
  void reset() { alist = NIL0; globals = builtin(); }
  void clear() { alist = NIL0; }
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

int pr() {
  for (S s = alist; !s.null(); s = s.cdr()) {
    const S binding = s.car();
    const S key = binding.car();
    const S value = binding.cdr();
    print(key), print(" -> "), println(value);
  }
}

int pr(S from, S to) {
  for (S s = from; s.handle != to.handle; s = s.cdr()) {
    const S binding = s.car();
    const S key = binding.car();
    const S value = binding.cdr();
    print(key), print(" -> "), println(value);
  }
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
  print("       . "), print(key), print(" = "), println(value);
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
    print("  /"), print(value.car()), print("  :  "), println(value.cdr());
  }
  {
    const S binding = until.car();
    const S key = binding.car();
    const S value = binding.cdr();
    print("   + "), println(value);
  }
  arguments(s, until);
  return until.cdr();
}
/** In case of error, dump the association-list with trace back: */
void traceback() {
  int n = 0;
  D(n);
  M("ALIST"), D(alist, NIL0);
  M("FRAME"), D(alist, begin(alist));
  for (S s = alist; !s.null() && n < 5; ++n, s = frame(s)) {
     ; 
  }
}
}

