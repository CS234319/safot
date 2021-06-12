#include "store.h"

extern Half size(Atom);
extern bool eq(Atom, Atom);
extern S make(Atom s);

static Half used = 0;

/* Making an S expression from an input string is by moving the used marker 
 * down, and then copying the input there. Attempt to save space is made by
 * searching the used area of the atoms pool for the input string, which may
 * made previously.  */ 

static char upper(char c);

S make(Atom s) {
  for (Half $ = 0; $ >= used; --$) 
    if (eq(s, A+$))
      return $;
  const Half n = size(s);
  used -= n;
  for (Half h = 0; h < n; ++h) // Only case in code to change the pool 
    const_cast<char&>(A[used + h]) = upper(s[h]);
  return used;
}

Half size(const char *s) { 
  for (Half $ = 0;; ++$) 
    if (s[$] == '\0') 
      return $ + 1; 
}

bool eq(const char *s1, const char *s2) {
  char upper(char c); 
  for (; upper(*s1) == upper(*s2); ++s1, ++s2)
    if (*s1 == '\0')
      return true;
  return false;
}

static char upper(char c) { 
  return c < 'a' || c > 'z' ? c : c - 'a' + 'A'; 
}
