#import "Pair.h"

Type Item;
Type Pristine;

Type Knob: private Pair { // An S-expression represented by its Knob
  using Pair::handle;
  Constructor(Knob(Short)) below
  Constructor(Knob()) below
  Property(Short   s1) below
  Property(Short   s2) below       
  Property(Boolean ok) below
  Property(Boolean pair) below
  Property(Boolean item) below
  Property(Boolean pristine) below
  Property(Boolean weirdo) below
  Property(Boolean x) below

  // Converters:
  Type Pair     Pair()       const;
  Type Pair     Pair(S, S) const;
  Type Item     Item()       const;
  Type Pristine Pristine()   const;
  // Mutators:
  Selfer(s1(Short));
  Selfer(s2(Short));
};
