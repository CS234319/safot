#include "layout.h"
#include "Item.h"
#include "heap.h"

// Provides function Item fresh(Short, Short);       /// Returns (handle of) newly allocated atom with given text; 
// Provides procedure free(Handle);                 /// Marks an S-expression previously returned by make as no longer in use 

/* Manages a singleton stack of handles, used by the LL parsing algorithm. This
 * stack is implemented as a dynamically allocated singly linked list, where
 * each element is a pair of handles: One handle in the pair carries the data;
 * the other handle is a pointer identifying the next stack element. A zero
 * handle marks the bottom of the stack. 
 *
 * At the end of parsing the stack should be empty, and all pairs (used as
 * stack elements) should be returned to the pool.
 */
Type Pushdown {
  Short pop();
  Pushdown& push(Short);
  Pushdown& push(Short,Short);
  Pushdown& push(Short,Short,Short);
  Pushdown& push(Short,Short,Short,Short);
  Pushdown& push(Short,Short,Short,Short,Short);
  Boolean empty() const;
  Pushdown& clear(); // Clear the stack, returning all elements to the pool
  Short peep() const;    // Examine stack's, but without popping it.
  Short peep(Short h) const; // Peep deeper into the stack.
  void poke(Short v);    // Examine stack's, but without popping it.
  void poke(Short h, Short v);    // Change stack, without popping it. 
  Item top = Item();
  Short size = 0;
  ~Pushdown();
};
