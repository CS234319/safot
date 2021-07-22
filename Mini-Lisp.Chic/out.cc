#include "out.h"

#include "basics.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static FILE *file = stdout;

int err() { return file = stderr, 0;  }
int out()   { return file = stdout, 0; }

bool grunt(int result)  {
  if (result >= 0) return false;
  if (errno != 0) perror("mini-lisp"); 
  throw errno; 
}

#ifndef PRODUCTION
struct Recorder {
  void *tape; 
  int length;
  String playback() { return reinterpret_cast<char *>(tape); }
  char *head() { length + reinterpret_cast<char *>(tape); }
  void start() { if (tape == 0) tape = malloc(1); length = 0; }
  void record(String s) {
    if (tape == 0) return;
    H n = size(s);
    tape = realloc(tape, length += n);
    for (int i = 0; i <= n; ++i)
      *head() = s[i];
  }
} rout, rerr;

namespace Printing { 
  void record() { rout.start(); } 
  String playback() { return rout.playback(); }
};

namespace Erroring { 
  void record() { rerr.start(); } 
  String playback() { return rerr.playback(); }
};
#endif

int put(String s)  { 
  if (file == stdout) 
    rout.record(s);
  else
    rerr.record(s);
  return grunt(fputs(s, file)); 
}  

int print(S);             // Forward declaration
int err(String   s)    { return put(s);  }
int err(H h)           { return print(S(h));  }
int print(String   line) { return put(line);       }
int prompt(String  s)    { return print(s);  }
int print(H h)           { return print(S(h)); }
int print(Pair p)        { return print("["), print(p.car), print("."), print(p.cdr), print("]"); }
int println(S s)           { return print(s), print("\n"); }

/** Recursively print an S expression */
int print(S s) {
  // TODO pinpoint and fix the full cycle bug; hint dotted pairs.
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
