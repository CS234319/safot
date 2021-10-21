#import "chic.h"

/* A very restricted integer, automatically initialized to  zero and can either
be incremented or cleared */

Type Clicker { 
  Capsule( Integer value = 0; Clicker *parent = 0)
  Create(Clicker) from(nothing) by(value(0))
  As(Integer) is(value)      // Value
  Clicker& operator()() selfing(++value | (not parent or do((*parent)())))
  Clicker& operator!() selfing(value = 0) // Clear
  Clicker kind() { return Clicker(0,*this); } 
  ~Clicker() { !(*this); }
  private: Create(Clicker) from(Integer valuePrime, Clicker& c) 
          by(parent(&c),value(valuePrime))
};
