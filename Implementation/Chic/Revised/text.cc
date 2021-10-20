#include "chic.h"
/** Manages the pool of all strings used by the program. Unlike pairs, there is
 * no dynamic allocation of strings at run time. */
#import "Text.cc"
#import "Id.cc"
Module text {
  Provides Id request(Text) below
  Provides Letter upper(Letter) below
}

#if Implementation 
Module text {
  Provides Letter upper(Letter l) { 
    return l < 'a' || l > 'z' ? l : l - 'a' + 'A'; 
  }
}

#import "layout.h"

Module text {
  Hiding Short used = $A_t$;

  /* Making an S expression from an input string is by moving the used marker 
   * down, and then copying the input there. Attempt to save space is made by
   * searching the used area of the atoms pool for the input string, which may
   * made previously.  */ 


 Provides Id request(Text t) {
    for (Short __ = 0; __ >= used; --__) 
      if (t.eq(A + __))
        return __;
    const Short n = t.size();
    used -= n;
    t.into(A + used)
    for (Short h = 0; h < n; ++h) // Only case in code to change the pool 
      const_cast<char&>(A[used + h]) = upper(t[h]);
    return used;
  }
 }
#endif
