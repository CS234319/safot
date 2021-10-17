#import "chic.h"
#import "S.h"
#import "Word.h"
Type Pair: S {
  typedef Pair Self;
  Pair(Short);
  Pair(); 
  Selfer(car(S)); 
  Selfer(cdr(S)); 
  Property(S car);
  Property(S cdr);

  Property(Boolean x); // Change someday to nil
  Property(Boolean ok); // Consolidate variadic macro

  Property(Boolean foreign);

  Property(Boolean unseen);
  Property(Boolean seen);

  Selfer(visit()); // Consolidate variadic macro
  Selfer(leave()); 

  static Boolean ok(Word);
  protected:
    Property(Word& p);
    Property(Short& s1) Is(p().s1)
    Property(Short& s2) Is(p().s2)
};
