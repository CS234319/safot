#import "Knob.cc"
#import "Short.h"
Occasionally(Item, Knob, 
  Feature(ok) is(x() or white(s1()) and black(s2()))
  Feature(head) is(s1())
  Feature(rest) is(Item(flip(s2())))
  Fluent(head) taking(Short s) selfing(s1(s))
  Fluent(rest) taking(Short s) selfing(s2(flip(s)))
)
