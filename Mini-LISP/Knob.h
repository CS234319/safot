#ifndef KNOB_H
#define KNOB_H
#include "chic.h"
#include "Handle.h"

Type Cons;
Type Item;
Type Pristine;

Type Knob: Handle { // An S-expression represented by its Knob
  typedef Handle Inner;
  // Composition
  Knob(Short);
  Knob(); 
  // Inspectors:
  Boolean   cons()     const;
  Boolean   item()     const;
  Boolean   pristine() const;
  Boolean   x()        const;
  Short  s1()       const;
  Short  s2()       const;
  // Convertors:
  Type Cons      Cons()      const;
  Type Item      Item()      const;
  Type Pristine  Pristine()  const;
  // Mutators:
  Knob s1(Short);
  Knob s2(Short);
};
  /*
    Short mark(Short h);
    Boolean marked(Short h);
  */
#endif
