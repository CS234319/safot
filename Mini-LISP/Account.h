#ifndef ACCOUNTER_H
#define ACCOUNTER_H
#include "chic.h"
#include "Clicker.h"
Type Account {
  Capsule(Clicker  p, m)
  Capsule(Clicker& plus = p, minus = m)
  Capsule(Account* const parent = 0);
  As(Integer) Is(plus - minus) // Value
  Account() {}
  Account(Clicker& p, Clicker& m): plus(p), minus(m) {}
  Account& operator ++() {  // Increment
    Keep((*this) >= 0)
    selfing(plus() | (not parent or do(++*parent))) 
  }
  Account& operator --()  {
    Expect((*this) > 0)
    Keep((*this) >= 0)
    selfing(minus() | (not parent or do(--*parent))) 
  }  
  Account& operator !() selfing(!plus | !minus) // Clear 
  ~Account() { !(*this); }
  Account kind() { return Account(0,*this); } 
  private: Account(int, Account& c): parent(&c) {}
};
#endif
