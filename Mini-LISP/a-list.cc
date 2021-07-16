#include "a-list.h"
#include "basics.h"

S alist = NIL; 
static S saved_alist = alist;

static int count_sets = 0;
static int count_eval = 0;

void inc_eval_counter()      { count_eval++;   }
void dec_eval_counter()      { count_eval--;   }
int get_eval_counter()       { return count_eval; }
void reset_eval_counter()    { count_eval = 0; }
void reset_set_counter()     { count_sets = 0; }

void restore_alist() {
    /*
     * This function call from error.
     *
     * In case of an error, we want to free all the set
     * operations that occurred from the alist.
     *
     */
    // Clean alist from all the local sets:
    for (int i=0; i < count_sets; i++) {
        alist = alist.cdr();
    }

    // Reset count_sets:
    reset_set_counter();
    reset_eval_counter();
}

namespace {
  static const S x1(set(NIL, NIL));  // (set (quote nil) (quote nil))
  static const S x2(set(T, T));      // (set (quote t) (quote t))
}

S set(S name, S value) {
    count_sets++;
    return (alist = name.cons(value).cons(alist)), value;
}

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
