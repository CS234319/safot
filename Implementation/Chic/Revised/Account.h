#import "chic.h"
#import "Clicker.h"
Type Account {
  Capsule(Clicker  p, m)
  Capsule(Clicker& plus = p, minus = m)
  Capsule(Account* const parent = 0);
  As(Integer) is(plus - minus) // Value
  Create(Account) from(nothing) by(p(), m())
  Create(Account) from(Clicker& p, Clicker& m) by(plus(p), minus(m))
  Account& operator ++() {  // Increment
    Keep((*this) >= 0)
    selfing(plus() | (not parent or do (++*parent))) 
  }
  Account& operator --()  {
    expecting((*this) > 0)
    Keep((*this) >= 0)
    selfing(minus() | (not parent or do (--*parent))) 
  }  
  Account& operator !() selfing(!plus | !minus) // Clear 
  ~Account() { !(*this); }
  Account kind() { return Account(0,*this); } 
  private: Account(int, Account& c): parent(&c) {}
};
