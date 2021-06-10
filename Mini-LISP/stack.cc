#include "stack.h"

namespace Stack {
  H top = 0;
  bool empty() { return top == 0; } 
  void push(H data) { top = Pairs::allocate(data,top); }
  void push(H h1,H h2) { push(h2); push(h1); }
  void push(H h1,H h2, H h3) { push(h3); push(h1, h2); }
  void push(H h1,H h2, H h3, H h4) { push(h4); push(h1, h2, h3); }
  void push(H h1,H h2, H h3, H h4, H h5) { push(h5); push(h1, h2, h3, h4); }

  H pop() {
    !empty() || die(EMPTY); 
    auto free = top;
    auto p = S(top).asPair();
    auto $ = p.data;
    top = p.next;
    Pairs::free(free);
    return $;
  }

  void clear() {
    while (!Stack::empty())
      Stack::pop();
  }

  H& peep() {
    !empty() || die(EMPTY); 
    return Pairs::get(top).data;
  }

  H& peep(H offset) {
    for (H h = Stack::top, i = 0; ; i++) {
      if (i == offset)
        return Pairs::get(h).data;
      h = Pairs::get(h).next;
      h != 0 || die(EXHAUSTED);
    }
 }
}
