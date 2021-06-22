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
  Pristine();
  Pristine(Short h); 
  Pristine prev(Pristine); 
  Pristine next(Pristine); 
  Pristine prev() const;
  Pristine next() const; 
  Boolean ok() const;

  static Short count;
  static Boolean corrupted();
  static Boolean valid();
};

inline std::ostream& operator<<(std::ostream &os, Pristine p) {
  if (p.x())
    return  os << "Px";
  return os << "Pristine[" << p.prev().inner() << "." << p.next().inner()  << "]";
}

#endif


