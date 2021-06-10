#include "a-list.h"
#include "basics.h"
S alist = S::NIL; 

#define BUGGY 0

#if !BUGGY
#undef D
#undef M
#define D(...) 0
#define M(...) 0
#else 
#include "dump.h"
#include "io.h"
#endif

namespace {
  static const S x1(set(S::NIL, S::NIL));  // (set (quote nil) (quote nil))
  static const S x2(set(S::T, S::T));      // (set (quote t) (quote t))
}

S set(S name, S value) { return (alist = name.cons(value).cons(alist)), value; }

S lookup(S id, S as) { 
  D(id, as, alist);
  return 
      as.null() ?  
         (M("DONE"), id.error(S::UNDEFINED)): 
      as.car().car().eq(id) ? 
          (M("FOUND"), as.car().cdr()): (M("RECURSE"), lookup(id, as.cdr())); 
}

S lookup(S s) { D(s,alist); return lookup(s, alist); }

S bind(S names, S values, S alist) {
  if (names.null()) 
    return values.null() ?  alist : values.error(S::REDUNDANT); 
  if (values.null()) 
    names.error(S::MISSING);
  return names.car().cons(values.car()).cons(bind(names.cdr(), values.cdr(), alist));
}

