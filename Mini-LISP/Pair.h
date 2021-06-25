#ifndef PAIR_H
#define PAIR_H
#include "chic.h"
#include "Sx.h"
#include "Word.h"

Type Pair: Sx {
  typedef Pair Self;
  Pair(Short);
  Selfer(car(Sx)); 
  Selfer(cdr(Sx)); 
  Property(Sx car);
  Property(Sx cdr);
  Property(Boolean ok);
  Property(Boolean x);
  static Boolean ok(Word);
  static Short count; 
  static Integer reuse; 
  static Integer miss; 
  private: Property(Word& p);
};
#endif
