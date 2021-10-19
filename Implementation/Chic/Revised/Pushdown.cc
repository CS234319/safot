#import "chic.h"
#import "Item.cc"

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

#if Implementation
Pushdown::~Pushdown() { clear(); }

#import "layout.h"
#import "Item.cc"
#import "heap.cc"


Property(Boolean Pushdown::empty) { 
  Keep(top.ok());
  return top.x(); 
} 

Short Pushdown::pop() {
  Expect(!empty());
  let $ = top.head();
  let old = top;
  top = top.rest();
  heap::free(old);
  --size;
  return $;
}


Pushdown& Pushdown::push(Short s) { 
  Expect(white(s));
  Keep(top.ok());
  Promise(!top.x());
  Promise(top.head() == s);
  ++size | do(top = fresh(s, top.handle())); 
  return *this; 
}

Pushdown& Pushdown::push(Short s1,Short s2) { return push(s2).push(s1); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3) { return push(s3).push(s1, s2); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4) { return push(s4).push(s1, s2, s3); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4, Short h5) { return push(h5).push(s1, s2, s3, s4); }

Pushdown& Pushdown::clear() {
  while (!empty()) 
    pop();
  return *this;
}

Short Pushdown::peep() const {
  Expect(!empty());
  return top.head();
}

Short Pushdown::peep(Short depth) const {
  Expect(!empty());
  Expect(depth <= size);
  Expect(depth >= 0);
  Expect(!top.x());
  for (auto i = top; ; i = i.rest(), --depth) {
    Expect(i.ok());
    Expect(!i.x());
    if (depth == 0)
      return i.head();
  }
}

void Pushdown::poke(Short depth, Short value) {
  Expect(!empty());
  Expect(depth < size);
  Expect(depth >= 0);
  for (auto i = top; ; i = i.rest(), --depth) {
    Expect(i.ok());
    Expect(!i.x());
    if (depth == 0) {
      i.head(value);
      return;
    }
  }
}
#endif
