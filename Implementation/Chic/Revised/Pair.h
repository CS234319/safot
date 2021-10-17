#import "CHIC"
#import "S.h"
#import "Handle.cc"

Type Pair: Handle {
  Constructor(Pair) from(Short) below
  Constructor(Pair) from(nothing) below

  Property(S car) below
  Property(S cdr) below
  Selfer(car(S)) below 
  Selfer(cdr(S)) below 

  Property(Boolean x) below // Change someday to nil
  Property(Boolean ok) below // Consolidate variadic macro

  Property(Boolean foreign) below

  Property(Boolean unseen) below
  Property(Boolean seen) below

  Selfer(visit()) below // Consolidate variadic macro
  Selfer(leave()) below 

  static Boolean ok(Word) below
  protected:
    property(s1) is(p().s1)
    property(s2) is(p().s2)
    Property(Word& p) below
};
