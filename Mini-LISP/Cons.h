#ifndef CONS_H
#define CONS_H
#include "chic.h"
#include "Knob.h"
#include "Word.h"
Type Cons: private Knob {
  using Knob::inner;
  Cons(Short);
  Cons car(Short); 
  Cons cdr(Short); 
  Property(Handle car);
  Property(Handle cdr);
  Property(Boolean ok);
  static Boolean ok(Word);
  static Short count; 
  static Integer reuse; 
  static Integer miss; 
  static Boolean corrupted();
};
#endif


