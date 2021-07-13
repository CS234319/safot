#include "out.h"

#include "basics.h"
#include <errno.h>

static FILE *file = stdout;

int err() { return file = stderr, 0;  }
int out()   { return file = stdout, 0; }

bool grunt(int result)  {
  if (result >= 0) return false;
  if (errno != 0) perror("mini-lisp"); 
  throw errno; 
}

int print(S);             // Forward declaration
int put(String s)        { return grunt(fputs(s, file)); }  
int err(String   s)    { return put(s);  }
int err(H h)           { return print(S(h));  }
int print(String   line) { return put(line);       }
int prompt(String  s)    { return print(s);  }
int print(H h)           { return print(S(h)); }
int print(Pair p)        { return print("["), print(p.car), print("."), print(p.cdr), print("]"); }

/** Recursively print an S expression */
int print(S s) {
  if (s.null()) return print("NIL");
  if (s.atom()) return print(s.asAtom());
  if (!islist(s)) return print("("), print(s.car()), print("."), print(s.cdr()), print(")");
  print("(") ;
  for (;;) {
    print(S(s.car())); 
    if ((s = s.cdr()).null()) break;
    print(" ");
  }
  return print(")");
}


