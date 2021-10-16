#import "text.h"
#import "layout.h"

extern Boolean exists(char c, Text s) {
  for (auto i = 0; s[i] != '\0'; ++i)
    if (c == s[i])
      return true;
  return false;
}

static Short used = $A_t$;

/* Making an S expression from an input string is by moving the used marker 
 * down, and then copying the input there. Attempt to save space is made by
 * searching the used area of the atoms pool for the input string, which may
 * made previously.  */ 

static char upper(char c);
static Short size(Text t); 

Boolean eq(const char *s1, const char *s2) {
  for (; upper(*s1) == upper(*s2); ++s1, ++s2)
    if (*s1 == '\0')
      return true;
  return false;
}

Id request(Text t) {
  for (Short __ = 0; __ >= used; --__) 
    if (eq(t, A + __))
      return __;
  const Short n = size(t);
  used -= n;
  for (Short h = 0; h < n; ++h) // Only case in code to change the pool 
    const_cast<char&>(A[used + h]) = upper(t[h]);
  return used;
}

static Short size(Text t) { 
  for (Short __ = 0;; ++__) 
    if (t[__] == '\0') 
      return __ + 1; 
}

static char upper(char c) { 
  return c < 'a' || c > 'z' ? c : c - 'a' + 'A'; 
}

#undef min
#undef max
#undef data
#undef function
#undef Type

#import "gtest/gtest.h"

inline auto operator ==(const Id s1, const Id s2) Is (s1.handle() == s2.handle())
