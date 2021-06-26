#ifndef PAIR_H
#define PAIR_H
#include "chic.h"
#include "Sx.h"
#include "Word.h"
Type Pair: Sx {
  typedef Pair Self;
  Pair(Short);
  Pair(): Pair(1) {} 
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
  Selfer(unvisit()); 

  static Boolean ok(Word);
  private: Property(Word& p);
};
#endif
