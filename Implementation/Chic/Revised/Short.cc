#import "chic.h"
Short flip(Short);
Boolean black(Short);
Boolean white(Short);

#if Implementation 
#import "layout.h"
extern Short flip(Short s)    { return s + (1 << 15); } 
extern Boolean black(Short s) { return s < $X_f$ || s > $X_t$ + 1; } 
extern Boolean white(Short s) { return !black(s); } 

extern void stainx(Short &s) {
  Promise(black(s));
  if (white(s)) s = flip(s);
}

extern void cleansex(Short &s) {
  Promise(white(s));
  if (black(s)) s = flip(s);
}
#endif
