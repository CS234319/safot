#import "Knob.h"
Type Item: private Knob {
  using Knob::x;
  Item();
  Item(Short);

  Property(Item rest);
  Property(Short head);
  Property(Boolean ok);
  Item head(Short s);
  Item rest(Short s);
}; 
