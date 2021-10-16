#import "Sx.h"

#import "text.h"
#import "heap.h"
#import "Pair.h"

// Property(Pair Sx::pair(Sx cdr)) Is(Sx(*this, cdr));
Sx::Sx(Short s)      : Handle(s) {}
Sx::Sx(Handle h)     : Sx(h.handle()) {} 
Sx::Sx(Sx s1, Sx s2) : Sx(request(s1, s2).handle()) {}
Sx::Sx(Text t)       : Sx(request(t)) {}

Property(Boolean Sx::atom) Is(handle() <= 0);
Property(Sx Sx::car)  Is(p().s1) 
Property(Sx Sx::cdr)  Is(p().s2) 
// Property(Pair Sx::Pair)  Is(Pair(handle())) 

Pair Sx::Pair() const {
  return ::Pair(handle());
}
