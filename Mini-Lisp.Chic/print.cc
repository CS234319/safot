#include "print.h"

#include "basics.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static FILE *file = stdout;

int err() { return file = stderr, 0;  }
int out() { return file = stdout, 0; }

bool grunt(int result)  {
  if (result >= 0) return false;
  if (errno != 0) perror("mini-lisp"); 
  throw errno; 
}

static int put(String);
int print(String   line) { return put(line); }
int prompt(String  s)    { return print(s);  }
int print(H h)           { return print(S(h)); }


/** Recursively print an S expression */
int print(S s) {
  if (s.atom()) return print(s.asAtom());
  if (!islist(s)) return print("["), print(s.car()), print("."), print(s.cdr()), print("]");
  if (s.car().eq(QUOTE) && s.cdr().pair() && s.cdr().cdr().null())  return print("'"), print(s.cdr().car());
  for (print("(") ;; print(" ")) {
    print(S(s.car())); // First recursive call
    if ((s = s.cdr()).null()) return print(")");
  }
}

#ifndef PRODUCTION
#define TESTING(...) __VA_ARGS__ 
#endif 
TESTING( static void record(String s); )

static int put(String s)  { 
  TESTING(  record(s);  )
  return grunt(fputs(s, file)); 
}  

#import "recorder.h"

TESTING( static void record(String s) { (file == stdout ? Recorder::stdout : Recorder::stderr).record(s); } )
