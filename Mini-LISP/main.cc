#include <stdio.h>
#include <stdlib.h>
#include "mini-lisp.h"
#include "parser.h"

static inline auto prompt(const char *s) {
  fputs(s, stdout);
}

int  print(String s) {
  return fputs(s,stdout);
}

int print(S s);

auto print(H h) {
  return print(S(h));
}

auto print(Pair p) {
   return print("["), print( p.car), print("."), print( p.cdr), print("]");
}

int print(S s) {
  if (s.null())
    return print("NIL");
  if (s.atom())
    return print( s.asAtom());
  if (!islist(s)) 
    return print("("), print( car(s)), print("."), print( cdr(s)), print(")");
  print("(") ;
  for (;;) {
    print(S(s.car())); 
    if ((s = s.cdr()).null())
      break;
    print(" ");
  }
  return print(")");
}

static S REPL() {
  static size_t n = 0;
  static auto line = (char *) malloc (n + 1);
  using namespace Parser;
  Start:
    reset();
    prompt("> ");
  Read:
    if (getline(&line, &n, stdin) < 0) 
      throw;
    supply(line);
    switch (status()) {
      case ready:
        prompt("- ");
        goto Read;
      case accept:
        break; 
      case reject:
        prompt("?");
        goto Start;
    }
    S s = result();
  Eval:
    S e = eval(s);
  Print:
    print(s), print("\n");
  Loop:
    goto Start;
}

int main(int argc, char **argv) {
  try {
    REPL();
  } catch (int e) {

  }
	return 0;
}
