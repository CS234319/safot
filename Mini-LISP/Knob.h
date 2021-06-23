#ifndef KNOB_H
#define KNOB_H
#include "Handle.h"

Type Cons;
Type Item;
Type Pristine;

Type Knob: Handle { // An S-expression represented by its Knob
  typedef Knob Self;
  typedef Handle Inner;
  // Composition
  Constructor(Knob(Short));
  Constructor(Knob());
  // Properties:
  Property(Short   s1);
  Property(Short   s2);       
  Property(Boolean ok);
  Property(Boolean cons);
  Property(Boolean item);
  Property(Boolean pristine);
  Property(Boolean weirdo);
  Property(Boolean x);

  // Converters:
  Type Cons     Cons()     const;
  Type Item     Item()     const;
  Type Pristine Pristine() const;
  // Mutators:
  Selfer(s1(Short));
  Selfer(s2(Short));
};
#endif
