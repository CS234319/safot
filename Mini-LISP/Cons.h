#ifndef CONS_H
#define CONS_H
#include "chic.h"
#include "Knob.h"
#include "Word.h"
Type Sx;
Type Cons: private Knob {
  using Knob::inner, Knob::x;
  typedef Cons Self;
  Cons(Short);
  Selfer(car(Sx)); 
  Selfer(cdr(Sx)); 
  Property(Sx car);
  Property(Sx cdr);
  Property(Boolean ok);
  static Boolean ok(Word);
  static Short count; 
  static Integer reuse; 
  static Integer miss; 
};
#endif
