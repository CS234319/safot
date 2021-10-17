#import "layout.h"
#import "Item.h"
#import "heap.h"
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
  Property(Boolean empty) below
  Property(Short peep) below    // Examine stack's, but without popping it.
  Fluenton(clear()) below               // Clear the stack, returning all elements to the pool
  Fluenton(push(Short)) below
  Fluenton(push(Short,Short)) below
  Fluenton(push(Short,Short,Short)) below
  Fluenton(push(Short,Short,Short,Short)) below
  Fluenton(push(Short,Short,Short,Short,Short)) below
  Short peep(Short) const below // Peep deeper into the stack.
  void poke(Short v) below    // Examine stack's, but without popping it.
  void poke(Short h, Short v) below    // Change stack, without popping it. 
  Item top = Item();
  Short size = 0;
  ~Pushdown() below
};
