#ifndef HANDLE_H
#define HANDLE_H
#include "chic.h"

Type Cons;
Type Id;

Type Handle { // An S-expression represented by its handle 
  // Composition
  Handle(Short s);
  // Decompositoin
  Short inner() const;
  // Access
  Cons $_p$() const; /// Interpreted as Knob of Cons, retrieves the Cons behind (mutable)  
  Id $_a$() const;   /// Interpreted as Id of an atom, retrieves its text representation 
  private: struct { Short capsule; }; 
};
#endif
