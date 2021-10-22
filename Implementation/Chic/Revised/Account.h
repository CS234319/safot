#import "chic.h"
#import "Clicker.h"
Type Account {
  Capsule(Clicker  p, m)
  Capsule(Clicker& plus = p, minus = m)
  Capsule(Account* const parent = 0);
  As(Integer) is(plus - minus) // Value
  Fill(Account) from(nothing) by(p(), m())
  Fill(Account) from(Clicker& p, Clicker& m) by(plus(p), minus(m))
  Account& operator ++() {  // Increment
    expecting((*this) >= 0)
    promising((*this) >= 0)
    maintaining((*this) >= 0)
    selfing(plus() | (not parent or do (++*parent))) 
  }
  Account& operator --()  {
    expecting((*this) > 0)
    promising((*this) >= 0)
    selfing(minus() | (not parent or do (--*parent))) 
  }  
  Account& operator !() selfing(!plus | !minus) // Clear 
  ~Account() { !(*this); }
  Account kind() { return Account(0,*this); } 
  private: Account(int, Account& c): parent(&c) {}
};
