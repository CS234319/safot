#include <stdio.h>
#include <stdlib.h>
#include "basics.h"
#include "parser.h"

static inline auto prompt(String s) {
  fputs(s, stdout);
}

int print(String s) {
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
    return print("("), print( s.car()), print("."), print( s.cdr()), print(")");
  print("(") ;
  for (;;) {
    print(S(s.car())); 
    if ((s = s.cdr()).null())
      break;
    print(" ");
  }
  return print(")");
}

// Realizes the famous "Read, Evaluate, Print, Loop" of interpreters
static int REPL() {
  static size_t n = 0;
  static auto line = (char *) malloc (n + 1);
  using namespace Parser;

  Start:
    reset();
    prompt("> ");
  Read:
    if (getline(&line, &n, stdin) < 0) 
      return 0;
    supply((char*)line);
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
    const S s = result();
  Eval:
    try {
      const S e = s.eval();
    } catch (Pair error) {
      print("Error");
      print(error.car);
      print(error.cdr);
    }
  Print:
    print(s), print("\n");
  Loop:
    goto Start;
}

int main(int argc, char **argv) {
  return REPL();
}
