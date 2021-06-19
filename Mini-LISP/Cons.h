#ifndef CONS_H
#define CONS_H
#include "Word.h"
#include "Knob.h"

Type Cons: private Knob {
  using Knob::inner;
  Cons(Short h);
  Cons car(Short h); 
  Cons cdr(Short h); 
  Knob car() const;
  Knob cdr() const;
  bool ok() const;
  static bool ok(Word);
};
#endif


