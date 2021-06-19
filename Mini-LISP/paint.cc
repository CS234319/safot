static struct {
  auto clean(Short &h) {
    if (marked(h)) h = mark(h);
    return *this;
  }
  auto stain(Short &h){
    if (!marked(h)) h = mark(h);
    return *this;
  }
  inline auto cons(Short h) { 
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Is(h).cons());
    clean(P[h].s1).clean(P[h].s2);
    return Cons(h);
  } 
 inline auto Item(Short h) { 
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Is(h).item()) 
    clean(P[h].s1).stain(P[h].s2);
    return Item(h);
  } 
} paint; 

