#include "a-list.h"
#include "basics.h"

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

S alist = NIL; 
static S saved_alist = alist;

void save() { saved_alist = alist; }
void restore() { alist = saved_alist; }

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
  if (names.null() && !values.null()) names.error(MISSING);
  if (!names.null() && values.null()) values.error(MISSING);
  if (names.null())
    return values.null() ?  alist : values.error(REDUNDANT);
  return names.car().cons(values.car()).cons(bind(names.cdr(), values.cdr(), alist));
}
