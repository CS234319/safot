#include "mini-lisp.h"
/* Manages a singleton stack of handles, used
 * by the LL parsing algorithm.
 */
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
