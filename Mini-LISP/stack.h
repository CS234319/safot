#include "mini-lisp.h"
namespace Stack {
  H pop();
  void push(H);
  void push(H,H);
  void push(H,H,H);
  void push(H,H,H,H);
  void push(H,H,H,H,H);
  extern H top;
  bool empty();
  void clear();
  H &peep();
  H &peep(H h);
}
