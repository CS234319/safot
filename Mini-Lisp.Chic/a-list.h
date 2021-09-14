#ifndef A_LIST
#define A_LIST
#include "S.h"

/* Get the alist */
extern S globals;
extern S alist;

/* Operations */
extern S push(S key, S value);
extern S set(S key, S value);
extern S lookup(S key, S alist);
extern S lookup(S);

/* Stack trace */
extern void stack_dump();

#endif  // A_LIST
