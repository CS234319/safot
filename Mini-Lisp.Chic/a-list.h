#ifndef A_LIST
#define A_LIST
#include "S.h"

/* Get the alist */
extern S* alist();

/* Basic operations */
extern void remove_element(S name);
extern void remove_elements(S names);
extern void push(S name, S value);
extern S pop();
extern bool in_alist(S id);

/* Lisp operations */
extern S set(S name, S value);
extern S lookup(S id, S alist);
extern S lookup(S);

/* Complex Lisp operations */
extern S bind(S names, S values, S alist);
extern void remove_local_binding(S names);

/* Stack trace */
extern void stack_dump();

/* Error handling using counters */
extern void restore_alist();
extern void inc_eval_counter();
extern void dec_eval_counter();
extern int get_eval_counter();
extern void reset_eval_counter();
extern void reset_set_counter();

#endif  // A_LIST
