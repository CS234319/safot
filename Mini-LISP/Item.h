#ifndef ITEM_H
#define ITEM_H
#include "Knob.h"

Type Item: private Knob {
  using Knob::inner;
  using Knob::x;
  Boolean ok() const;
  Item();
  Item(Short s);

  Item head(Short s);
  Item rest(Short s);
  Item rest() const;
  Short head() const;

  static Short count;
  static Boolean corrupted();
}; 
#endif
