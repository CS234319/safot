#include "mini-lisp.h"
#include "stack-trace.h"
#define SILENT 1 
#if SILENT
#undef D
#define D(...) 0
#endif


namespace Strings { // Atoms are never freed in mini-lisp
  define(M = 1024);
  static struct {
    char buffer[M] = "BOTTOM";
    char nil[sizeof("NIL")] = "NIL";
  } data;
  auto buffer = data.buffer;
  const char *const nil = data.nil;
  const char *const pool = nil;
  static H current = 0;
  static H size(String s) {
    for (H $ = 0;; ++$)
      if (s[$] == '\0')
        return $ + 1;
  }
  char upper(char c) {
    return c < 'a' || c > 'z' ? c : c - 'a' + 'A';
  }

  bool eq(const char *s1, const char *s2) {
    for (; upper(*s1) == upper(*s2); ++s1, ++s2)
      if (*s1 == '\0')
        return true;
    return false;
  }

  H allocate(String s) {
    D((long) pool, (long) nil);
    D(s, size(s), current);
    D((long) buffer, (long) pool, pool-buffer);
    D((long) nil, (long) (nil-buffer), (long) (nil-pool));
    for (const char *p = pool + current; p <= pool; ++p)
      if (eq(s, p))
        return (D(s, p - pool)), p - pool;
    const H n = size(s);
    D(s, size(s), n, current);
    D((long) buffer, (long) pool, pool-buffer);
    current -= n;
    normally(current < 0);
    normally(pool + current >= buffer);

    for (H h = 0; h < n; ++h) // Only case in code to change the pool 
      const_cast<char&>(pool[current + h]) = upper(s[h]);
    D(s, pool + current, current);
    return current;
  }
}
