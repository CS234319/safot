Type Cons: Is {
  Cons(Short h): Is(h) {}
  auto car(Short h) const { s1() = h; return *this; }
  auto cdr(Short h) const { s2() = h; return *this; }
  auto car() const { return s1(); }
  auto cdr() const { return s2(); } 
};
