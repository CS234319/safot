#include "a-list.h"
#include "basics.h"
S alist = NIL; 

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
  static const S x1(set(NIL, NIL));  // (set (quote nil) (quote nil))
  static const S x2(set(T, T));      // (set (quote t) (quote t))
}

S set(S name, S value) { return (alist = name.cons(value).cons(alist)), value; }

S lookup(S id, S alist) { 
  return 
    alist.null() ?  
      id.error(UNDEFINED): 
    alist.car().car().eq(id) ?  
      alist.car().cdr(): 
    lookup(id, alist.cdr()); 
}

S lookup(S s) { D(s,alist); return lookup(s, alist); }

S bind(S names, S values, S alist) {
  if (names.null()) 
    return values.null() ?  alist : values.error(REDUNDANT); 
  if (values.null()) 
    names.error(MISSING);
  return names.car().cons(values.car()).cons(bind(names.cdr(), values.cdr(), alist));
}
