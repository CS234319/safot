#ifndef ITEM_H
#define ITEM_H
#include "Knob.h"

Type Item: private Knob {
  using Knob::inner;
  using Knob::x;
  static Short count;
  Item(Short s);
  Item head(Short s);
  Item rest(Short s);
  Short head() const;
  Short rest() const;
}; 
#endif
