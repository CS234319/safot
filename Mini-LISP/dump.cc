#include "dump.h"
bool dumping = false;

#if 1
/*
#undef BEFORE
#undef AFTER
#define BEFORE 
#define AFTER
*/
// #undef  __EXPRESSION
// #define __EXPRESSION(X) [[X]]
int xmain() {
  D(1);
  D(1,2);
  D(1,2,3);
  D(1,2,3,4);
  D(1,2,3,4,5);
  D(1,2,3,4,5,6);
  D(1,2,3,4,5,6,7);
  return D(1);
}
#endif
