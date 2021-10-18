#import "S.h"

#import "text.h"
#import "heap.h"
#import "Pair.h"

Property(S S::car)  Is(p().s1) 
Property(S S::cdr)  Is(p().s2) 
S::S(const S &s1, const S & s2) : S(request(s1, s2).handle()) {}
S::S(const Text t)       : S(request(t)) {}
// Property(Pair S::Pair)  Is(Pair(handle())) 
// Property(Pair S::pair(S cdr)) Is(S(*this, cdr));

Pair S::Pair() const {
  return ::Pair(handle());
}
