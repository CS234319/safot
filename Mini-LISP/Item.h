#ifndef ITEM_H
#define ITEM_H
#include "Knob.h"

Type Item: private Knob {
  using Knob::inner;
  using Knob::x;
  static Short count;
  bool ok() const;
  Item();
  Item(Short s);

  Item head(Short s);
  Item rest(Short s);
  Item rest() const;
  Short head() const;
}; 
#endif
