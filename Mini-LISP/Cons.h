#ifndef CONS_H
#define CONS_H
#include "Word.h"
#include "Knob.h"

Type Cons: private Knob {
  using Knob::inner;
  Cons(Short);
  Cons car(Short); 
  Cons cdr(Short); 
  Handle car() const;
  Handle cdr() const;
  Boolean ok() const;
  static Boolean ok(Word);
  static Short count; 
  static Integer reuse; 
  static Integer miss; 
  static Boolean corrupted();
};
#endif


