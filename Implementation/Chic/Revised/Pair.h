#import "chic.h"
#import "S.h"
#import "Knob.h"

Type Pair: Handle {
  Constructor Pair(Short) below
  Constructor Pair() below 

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
