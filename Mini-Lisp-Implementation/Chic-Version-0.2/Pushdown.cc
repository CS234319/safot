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
  Alias(Pushdown) Self;
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
  maintaining(top.ok());
  return top.x(); 
} 

Short Pushdown::pop() {
  expecting(not empty());
  let $ = top.head();
  let old = top;
  top = top.rest();
  heap::free(old);
  --size;
  return $;
}


Pushdown& Pushdown::push(Short s) { 
  Perform(
    ++size | do(top = heap::fresh(s, top.handle())); 
    return *this; 
  , 
    expecting(white(s)) 
    maintaining(top.ok()) 
    promising(not top.x(),top.head() == s)
  )
}

Pushdown& Pushdown::push(Short s1,Short s2) { return push(s2).push(s1); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3) { return push(s3).push(s1, s2); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4) { return push(s4).push(s1, s2, s3); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4, Short h5) { return push(h5).push(s1, s2, s3, s4); }

Pushdown& Pushdown::clear() {
  while (not empty()) 
    pop();
  return *this;
}

Short Pushdown::peep() const Perform(is(top.head()), expecting(not empty()))

Short Pushdown::peep(Short depth) const 
  Perform(for (auto i = top; ; i = i.rest(), --depth) {
      expecting(i.ok(), not i.x());
      if (depth == 0)
        return i.head();
    }
    ,
    expecting(not empty(), depth <= size, depth >= 0, not top.x())
  ) 

void Pushdown::poke(Short depth, Short value) 
  Perform(
      for (auto i = top; ; i = i.rest(), --depth) {
        expecting(i.ok(), not i.x());
        if (depth == 0) {
          i.head(value);
          return;
        }
      }, expecting(not empty(), depth < size, depth >= 0)
  )
   
#endif
