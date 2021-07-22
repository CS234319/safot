#include "Short.h"
#include "layout.h"

#include <iostream>
extern Short flip(Short s)    { return s + (1 << 15); } 
extern Boolean black(Short s) { return s < $X_f$ || s > $X_t$ + 1; } 
extern Boolean white(Short s) { return !black(s); } 

extern void stain(Short &s) {
  Promise(black(s));
  if (white(s)) s = flip(s);
}

extern void cleanse(Short &s) {
  Promise(white(s));
  if (black(s)) s = flip(s);
}
