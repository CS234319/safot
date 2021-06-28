#ifndef CLICKER_H
#define CLICKER_H
#include "chic.h"
Type Clicker {
  As(Integer) Is(i)      // Value
  Clicker& operator()() selfing(++i | (not parent or do((*parent)())))
  Clicker& operator!() selfing(i = 0) // Clear
  Capsule(Integer i = 0; Clicker *parent = 0)
  Clicker(): i(0){}
  Clicker kind() { return Clicker(0,*this); } 
  ~Clicker() { !(*this); }
  private: Clicker(int, Clicker& c): parent(&c) {}
};
#endif
