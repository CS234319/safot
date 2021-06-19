#ifndef PRISTINE_H
#define PRISTINE_H 
#include "chic.h"
#include "Knob.h"

Type Pristine: private Knob {
  // Decomposition
  using Knob::inner;
  using Knob::x;
  // Statistics
  using Knob::Item, Knob::Cons;
  Pristine(Short h); 
  Pristine prev(Pristine); 
  Pristine next(Pristine); 
  Pristine prev() const;
  Pristine next() const; 
  bool ok() const;

  static Short count;
};
#endif


