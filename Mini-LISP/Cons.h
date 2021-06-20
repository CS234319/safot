#ifndef CONS_H
#define CONS_H
#include "Word.h"
#include "Knob.h"

Type Cons: private Knob {
  using Knob::inner;
  static Short count; 
  static Short reuse; 
  static Short miss; 
  Cons(Short);
  Cons car(Short); 
  Cons cdr(Short); 
  Handle car() const;
  Handle cdr() const;
  bool ok() const;
  static bool ok(Word);
};
#endif


