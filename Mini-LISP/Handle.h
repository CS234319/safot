#ifndef HANDLE_H
#define HANDLE_H
#include "chic.h"

Type Pair;
Type Id;

Type Handle { // An S-expression represented by its handle 
  Constructor(Handle(Short));
  Property(Boolean ok); 
  Property(Short inner); 
  Property(Pair $_p$); /// Interpreted as Knob of Pair, retrieves the Pair behind (mutable)  
  Property(Id $_a$);   /// Interpreted as Id of an atom, retrieves its text representation 
  private: struct { Short capsule; }; 
};
#endif
