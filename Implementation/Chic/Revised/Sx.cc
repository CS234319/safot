#import "Sx.h"

#import "text.h"
#import "heap.h"
#import "Pair.h"

// Property(Pair Sx::pair(Sx cdr)) Is(Sx(*this, cdr));
Property(Boolean Sx::atom) Is(handle() <= 0);
Property(Sx Sx::car)  Is(p().s1) 
Property(Sx Sx::cdr)  Is(p().s2) 
Sx::Sx(const Sx &s1, const Sx & s2) : Sx(request(s1, s2).handle()) {}
Sx::Sx(const Text t)       : Sx(request(t)) {}
// Property(Pair Sx::Pair)  Is(Pair(handle())) 

Pair Sx::Pair() const {
  return ::Pair(handle());
}
