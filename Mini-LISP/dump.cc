#include "dump.h"
bool dumping = false;

#if 1
int f() {
  D(f());
  // M("A", 2); 
  // M("A", 2,3); 
  // D(2,f());
  // M("A", f(), f());
  // M("A", f());
  return 3;
}
#endif

