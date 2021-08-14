#include "a-list.h"
#include "basics.h"
#include "out.h"

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

S& ar_alist() {
    /*
     * Activation record a-list:
     */
    static S ar_inner = list();
    return ar_inner;
}

void push(S name, S value) {
    /*
     * Push an element to the AR a-list:
     */
    ar_alist() = set(name, value, ar_alist());
}

S pop() {
    /*
     * Pop the first element from the AR a-list:
     */
    if (! ar_alist().n0()) {
        S top = ar_alist().car();
        ar_alist() = ar_alist().cdr();
        return top;
    }
    return NIL;
}

void stack_dump() {
    /*
     * In case of error, dump the AR a-list with trace back:
     */
    if (ar_alist().n0()) return;

    // Reverse the ar_alist, to print the most recent call last:
    S s = NIL;
    while (! ar_alist().n0()) {
        S top = pop();
        s = s.cons(top);
    }

    // Print stack trace:
    prompt("Traceback (most recent call last):\n");
    while (! s.n0()) {
        S top = s.cdr();
        s = s.car();
        if (top.car().eq(RESCUE)) {
            prompt("\tFrom function "), print(top.cdr()), print(":\n");
        }
        if (top.car().eq(ARGUMENT)) {
            prompt("\t\tArgs: "), print(top.cdr()), print("\n");
        }
    }
}
