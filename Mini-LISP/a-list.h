#ifndef A_LIST
#define A_LIST
#include "S.h"
extern S alist ;
extern S set(S name, S value);
extern S lookup(S id, S alist);
extern S lookup(S) ;
extern S bind(S names, S values, S alist); 
extern void save();
extern void restore_alist();
extern void inc_eval_counter();
extern void dec_eval_counter();
extern int get_eval_counter();
extern void reset_eval_counter();
extern void reset_set_counter();
#endif  // A_LIST
