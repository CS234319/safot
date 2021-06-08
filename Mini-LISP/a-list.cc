#include "a-list.h"
#include "basics.h"
S alist = S::NIL; 
S set(S name, S value) { return (alist = S(S(name, value), alist)), value; }
S lookup(S id, S as) { return as.null()? S::NIL: as.car().car().eq(id)? as.car().cdr(): lookup(id, as.cdr()); }
S lookup(S s) { return lookup(s, alist); }
S bind(S names, S values, S alist) {
  if (names.null()) 
    return values.null() ?  alist : values.error(S::REDUNDANT); 
  if (values.null()) 
    names.error(S::MISSING);
  return names.car().cons(values.car()).cons(bind(names.cdr(), values.cdr(), alist));
}

// const S S::NIL(set(S::NIL, S()));  // (set (quote nil) (quote nil))
// const S S::T(set(S::T,S::T));     // (set (quote t) (quote t))
