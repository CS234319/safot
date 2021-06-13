#ifndef A_LIST
#define A_LIST
#include "S.h"
extern S alist ;
extern S set(S name, S value);
extern S lookup(S id, S alist);
extern S lookup(S s) ;
extern S bind(S names, S values, S alist); 
#endif  // A_LIST
