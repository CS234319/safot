#ifndef PAIR_H
#define PAIR_H
#include "chic.h"
#include "Sx.h"
#include "Word.h"
Type Pair: Sx {
  typedef Pair Self;
  Pair(Short);
  Pair(); 
  Selfer(car(Sx)); 
  Selfer(cdr(Sx)); 
  Property(Sx car);
  Property(Sx cdr);

  Property(Boolean x); // Change someday to nil
  Property(Boolean ok); // Consolidate variadic macro

  Property(Boolean foreign);

  Property(Boolean unseen);
  Property(Boolean seen);

  Selfer(visit()); // Consolidate variadic macro
  Selfer(leave()); 

  static Boolean ok(Word);
  protected:
    Property(Word& p);
    Property(Short& s1) Is(p().s1)
    Property(Short& s2) Is(p().s2)
};
#endif
