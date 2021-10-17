#import "Pair.h"

Type Item;
Type Pristine;

Type Knob: private Pair { // An S-expression represented by its Knob
  typedef Knob Self;
  typedef Pair Super;
  using Pair::handle;
  Constructor(Knob(Short));
  Constructor(Knob());
  Property(Short   s1);
  Property(Short   s2);       
  Property(Boolean ok);
  Property(Boolean pair);
  Property(Boolean item);
  Property(Boolean pristine);
  Property(Boolean weirdo);
  Property(Boolean x);

  // Converters:
  Type Pair     Pair()       const;
  Type Pair     Pair(S, S) const;
  Type Item     Item()       const;
  Type Pristine Pristine()   const;
  // Mutators:
  Selfer(s1(Short));
  Selfer(s2(Short));
};
