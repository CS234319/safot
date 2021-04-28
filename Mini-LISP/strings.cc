#include "mini-lisp.h"
#include "stack-trace.h"
#define SILENT 1 
#if SILENT
#undef D
#define D(...) 0
#endif
 
namespace Strings { // Atoms are never freed in mini-lisp
  define(M = 1024); // We use a total of M + sizeof("NIL") (typically 4) bytes
  static struct { // Falls in the data segment; should be just before Pairs::buffer
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

  /* Allocation of a input string is by moving the pool pointer down and then
   * copying the input there. A bit of optimization saves some space by refraining
   * from allocating the same string twice; moreover, there is also a minimal attempt
   * to allow one string to be realizes the suffix of a previously allocated string  
   */ 
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

// Planned global data layout.
static const bool active = true; 

static struct { // Falls in the data segment; should be just before Pairs::buffer
   // This is where strings go, negative handles.
   char pool1[active<<10] = "BOTTOM";
   // handle 0 should be exactly here.
   char nil[sizeof("NIL")] = "NIL";
   // positive (i.e., not - handles point here. be careful 2^15 is not a positive number 
   Pair pool2[(active << 15)-2]; // not sure about the 2 here; add test
} SometimeYossiGil;
 
