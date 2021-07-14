#include "S.h"
/* Manages a singleton stack of handles, used by the LL parsing algorithm. This
 * stack is implemented as a dynamically allocated singly linked list, where
 * each element is a pair of handles: One handle in the pair carries the data;
 * the other handle is a pointer identifying the next stack element. A zero
 * handle marks the bottom of the stack. 
 *
 * At the end of parsing the stack should be empty, and all pairs (used as
 * stack elements) should be returned to the pool.
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
  void clear(); // Clear the stack, returning all elements to the pool
  H &peep();    // Examine stack's, but without popping it.
  H &peep(H);   // Peep deeper into the stack.
}
