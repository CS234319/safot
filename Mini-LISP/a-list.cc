#include "a-list.h"
#include "basics.h"

S alist = NIL; 
static S saved_alist = alist;

void save() { saved_alist = alist; }
void restore() { alist = saved_alist; }

namespace {
  static const S x1(set(NIL, NIL));  // (set (quote nil) (quote nil))
  static const S x2(set(T, T));      // (set (quote t) (quote t))
}

S set(S name, S value) { return (alist = name.cons(value).cons(alist)), value; }

S bind(S names, S values, S alist) { // TODO: there are four cases in this functions, but there should be only three.
  if (names.null() && !values.null()) names.error(MISSING);
  if (!names.null() && values.null()) values.error(MISSING);
  if (names.null())
    return values.null() ?  alist : values.error(REDUNDANT);
  return names.car().cons(values.car()).cons(bind(names.cdr(), values.cdr(), alist));
}

S lookup(S id, S alist) { 
  return 
    alist.null() ?  id.error(UNDEFINED): 
    alist.car().car().eq(id) ?  alist.car().cdr(): 
    lookup(id, alist.cdr()); 
}

S lookup(S s) { return lookup(s, alist); }
