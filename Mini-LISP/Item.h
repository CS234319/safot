#ifndef ITEM_H
#define ITEM_H
#include "Knob.h"
Type Item: private Knob {
  using Knob::inner;
  using Knob::x;
  Item();
  Item(Short s);

  Property(Item rest);
  Property(Short head);
  Property(Boolean ok);
  Item head(Short s);
  Item rest(Short s);
  static Short count;
}; 
#endif
