#ifndef HANDLE_H
#define HANDLE_H
#include "chic.h"

Type Cons;
Type Id;

Type Handle { // An S-expression represented by its handle 
  Constructor(Handle(Short));
  Property(Boolean ok); 
  Property(Short inner); 
  Property(Cons $_p$); /// Interpreted as Knob of Cons, retrieves the Cons behind (mutable)  
  Property(Id $_a$);   /// Interpreted as Id of an atom, retrieves its text representation 
  private: struct { Short capsule; }; 
};
#endif
