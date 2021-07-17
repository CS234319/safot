#include "a-list.h"
#include "basics.h"

S bind(S formals, S actuals, S list) { 
  if (!formals.null() && actuals.null()) return formals.error(MISSING);
  if (formals.null() && !actuals.null()) return actuals.error(REDUNDANT);
  if (formals.null()) return list;
  return formals.car().cons(actuals.car()).cons(bind(formals.cdr(), actuals.cdr(), list));
}

S lookup(S id, S list) { 
  return 
    list.null() ?  id.error(UNDEFINED): 
    list.car().car().eq(id) ?  list.car().cdr(): 
    lookup(id, list.cdr()); 
}

S set(S name, S value, S list) { return name.cons(value).cons(list); }

static int count_sets = 0;
static int count_eval = 0;
void inc_eval_counter()      { count_eval++;   }
void dec_eval_counter()      { count_eval--;   }
int get_eval_counter()       { return count_eval; }
void reset_eval_counter()    { count_eval = 0; }
void reset_set_counter()     { count_sets = 0; }

S lookup(S s) { return lookup(s, alist()); }
S set(S name, S value) { count_sets++; return (alist() = set(name,value, alist())), value; }

static S nil() { static const S inner = S("NIL"); return inner; } 
static S t()   { static const S inner = S("T"); return inner; } 

S& alist() { 
  static S inner = set(t(), t(), set(nil(), nil(), nil()));
  return inner; 
}

static S saved_alist = alist();

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
        alist() = alist().cdr();
    }

    // Reset count_sets:
    reset_set_counter();
    reset_eval_counter();
}
