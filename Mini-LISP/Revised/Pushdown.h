#include "layout.h"
#include "Item.h"
#include "heap.h"
/* Manages a singleton stack of handles, used by the LL parsing algorithm. This
 * stack is implemented as a dynamically allocated singly linked list, where
 * each element is a pair of handles: One handle in the pair carries the data;
 * the other handle is a pointer identifying the next stack element. A zero
 * handle marks the bottom of the stack. 
 *
 * At the end of parsing the stack should be empty, and all pairs (used as
 * stack elements) should be returned to the pool.
 */

#define Fluenton(x) Self& x 
Type Pushdown {
  Short pop();
  typedef Pushdown Self;
  Property(Boolean empty);
  Property(Short peep);    // Examine stack's, but without popping it.
  Fluenton(clear());               // Clear the stack, returning all elements to the pool
  Fluenton(push(Short));
  Fluenton(push(Short,Short));
  Fluenton(push(Short,Short,Short));
  Fluenton(push(Short,Short,Short,Short));
  Fluenton(push(Short,Short,Short,Short,Short));
  Short peep(Short) const; // Peep deeper into the stack.
  void poke(Short v);    // Examine stack's, but without popping it.
  void poke(Short h, Short v);    // Change stack, without popping it. 
  Item top = Item();
  Short size = 0;
  ~Pushdown();
};
