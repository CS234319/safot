#include "Pushdown.h"
#include "Short.h"

Pushdown::~Pushdown() { clear(); }

Property(Boolean Pushdown::empty) { 
  Keep(top.ok());
  return top.x(); 
} 

Pushdown& Pushdown::push(Short s) { 
  Expect(white(s));
  Keep(top.ok());
  Promise(!top.x());
  Promise(top.head() == s);
  ++size, top = fresh(s, top.inner()); 
  return *this; 
}

Pushdown& Pushdown::push(Short s1,Short s2) { return push(s2).push(s1); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3) { return push(s3).push(s1, s2); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4) { return push(s4).push(s1, s2, s3); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4, Short h5) { return push(h5).push(s1, s2, s3, s4); }

Short Pushdown::pop() {
  Expect(!empty());
  let $ = top.head();
  let old = top;
  top = top.rest();
  free(old);
  --size;
  return $;
}

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
