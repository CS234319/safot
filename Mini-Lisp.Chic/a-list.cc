#include "a-list.h"
#include "basics.h"
#include "out.h"

/* Primitive functions */
static S nil() { static const S inner = S("NIL"); return inner; }
static S t()   { static const S inner = S("T"); return inner; }


/* Basic operations */
S set(S name, S value, S list) { return name.cons(value).cons(list); }
S push(S name, S value, S list) {
    return set(name, value, list);
}
S pop(S& list) {
    if (! list.n0()) {
        S top = list.car();
        list = list.cdr();
        return top;
    }
    return NIL;
}
bool in_alist(S id, S list) {
    // Same as look up, but return a boolean value
    if (list.null()) return false;
    if (list.car().car().eq(id)) return true;
    return in_alist(id, list.cdr());
}

/* alist */
S& alist() {
    static S inner = set(t(), t(), set(nil(), nil(), nil()));
    return inner;
}
S& tmp_alist() {
    static S tmp_inner = list();
    return tmp_inner;
}
static int count_sets = 0;
static int count_eval = 0;

/* alist operatorions */
S set(S name, S value) {
    count_sets++;
    return (alist() = set(name,value, alist())), value;
}
void push(S name, S value) {
    // prompt("DEBUG: Pushing - "); print(name); print("."); println(value);
    alist() = push(name, value, alist());
}
S pop() {
    return pop(alist());
}
bool in_alist(S id) {
    return in_alist(id, alist());
}
void remove_element(S name) {
    /*
     * Pseudo code:
     * ------------
     * init tmp_list
     * For each element in alist:
     *      if top.name == name:
     *          alist.pop()
     *          while tmp_list is not empty:
     *              alist += tmp_list.pop()
     *          break
     *      else:
     *          tmp_list.push(top)
     */
    // prompt("DEBUG: Removing - "); println(name);
    if (! in_alist(name)) return;
    while (! alist().n0()) {
        S top = pop();
        if (top.car().eq(name)) {
            while (! tmp_alist().n0()) {
                S restored_top = pop(tmp_alist());
                push(restored_top.car(), restored_top.cdr());
            }
            break;
        } else {
            tmp_alist() = push(top.car(), top.cdr(), tmp_alist());
        }
    }
}
void remove_elements(S names) {
    /*
     * Pseudo code:
     * ------------
     * For name in names:
     *      remove_element(name)
     */
    S elements = names;
    while (! elements.n0()) {
        S element = elements.car();
        remove_element(element);
        elements = elements.cdr();
    }
}

/* Complex Lisp operations */
S bind(S formals, S actuals, S list) { 
  if (!formals.null() && actuals.null()) return formals.error(MISSING);
  if (formals.null() && !actuals.null()) return actuals.error(REDUNDANT);
  if (formals.null()) return list;
  return formals.car().cons(actuals.car()).cons(bind(formals.cdr(), actuals.cdr(), list));
}
void remove_local_binding(S names) {
    /*
     * Remove all the local bindings,
     * avoiding recursions ambiguity.
     */
    remove_elements(names);
}
S lookup(S id, S list) { 
  return 
    list.null() ?  id.error(UNDEFINED): 
    list.car().car().eq(id) ?  list.car().cdr(): 
    lookup(id, list.cdr()); 
}
S lookup(S s) { return lookup(s, alist()); }


/* Error handling using counters */
void inc_eval_counter()      { count_eval++;      }
void dec_eval_counter()      { count_eval--;      }
int get_eval_counter()       { return count_eval; }
void reset_eval_counter()    { count_eval = 0;    }
void reset_set_counter()     { count_sets = 0;    }
void restore_alist() {
    /*
     * This function call from error.
     *
     * In case of an error, we want to free all the set
     * operations that occurred from the alist.
     *
     */
    // Clean alist from all the local sets:
    for (int i=0; i < count_sets; i++)
        pop();

    // Reset count_sets:
    reset_set_counter();
    reset_eval_counter();
}

S reverse(S alist) {
    S s = NIL;
    while (! alist.n0()) {
        S top = pop(alist);
        s = s.cons(top);
    }
    return s;
}

void stack_dump() {
    /*
     * In case of error, dump the a-list with trace back:
     */
    if (alist().n0() || ! in_alist(RESCUE) || ! in_alist(ARGUMENT)) return;

    // Reverse the alist, to print the most recent call last:
    S s = reverse(alist());

    // Print stack trace:
    println("Traceback:");
    bool open = false;
    for (bool comma = false; s.pair(); s = s.car()) { 
        auto top = s.cdr();
        if (top.car().eq(RESCUE)) {
            open ? println("\t ]]") : open = true;
            print("\t -> "), print(top.cdr()), println(" [[");
            comma = false; 
            remove_element(RESCUE);
        }
        if (top.car().eq(ARGUMENT)) {
            comma ? print(",") : comma = true;
            print("\t\t"),println(top.cdr()), 
            remove_element(ARGUMENT);
        }
    }
    open ? println("\t ]]") : open = false;
}
