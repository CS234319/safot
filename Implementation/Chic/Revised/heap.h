#import "chic.h"
#import "S.h"
#import "Item.h"
Module heap {
  extern Pair request(S, S); 
  extern Item fresh(Short, Short); 
  extern Unit free(Item); 

extern const Pristine& heap;
}
#import "Pristine.h"
#import "Pair.cc"
Module heap {
  extern Pristine reset();
  extern Unit gobble(Pair);
  Knob crude(); 
}
