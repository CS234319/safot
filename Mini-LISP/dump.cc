#include "dump.h"
bool dumping = false;

/*
#define VA_ARGS(...)  a,##__VA_ARGS__
#define G(_0,_1,_2, NAME,...) NAME 
#define F(_0,__VA_ARGS__, FE3, FE2) // FOR
#define Y(...)_0,_1, __VA_ARGS__, FE3, FE2) // GET
#define F(...) \
  G( _0,VA_ARGS(VA_ARGS(__VAR_ARGS__),F7, F6,F5,F4,F3,F2,F1,F0)\
    ( __VA_ARGS__)
#define X(...) Y(VA_ARGS(__VA_ARGS__)) 
#define C(...) [[__VA_ARGS__]]
#define Z(X) a #X 
*/

#if 0
int xmain() {
  D();
  D(1);
  D(1,2);
  D(1,2,3);
  D(1,2,3,4);
  D(1,2,3,4,5);
  D(1,2,3,4,5,6);
  D(1,2,3,4,5,6,7);
}
#endif

