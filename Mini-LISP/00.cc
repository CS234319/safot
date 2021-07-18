#include "parser.h"
#include "read.h"
#include "out.h"
#include "a-list.h"

using namespace Parser;

/** Internal function to evaluate of the parsed input; Should only be called
after the parser finished successfully */
static S eval() { 
  try {
    return Parser::result().eval();
  } catch (Pair x) { 
    throw err(),err("Error ["), err(x.cdr), err("] in "), err(x.cdr), err("\n"),out();
  }
}

/** Realizes the famous "Read, Evaluate, Print, Loop" of all 
interpreters; Returns the number of expressions successfully read and
evaluated. */
int REPL() {   int n = 0;
  try {
    Start:
      Parser::reset(), prompt("> ");
    Read:
      const String line = read(); 
      if (line == (char *)0) return n;
      supply(line);
      switch (status()) {
        case ready:      // More input must be waiting 
          prompt("- ");  // Prompt the user for more
          goto Read;     // Loop again 
        case accept:     // Proceed to evaluation
          break;
        case reject:     // Parsing error 
          prompt("?");   // Admonish the client; continue
          goto Start;
      }
    Eval: try {
        const S result = eval(); 
    Print:
        print(result), print("\n");
        print(Erroring::playback()), print("\n");
        print(Printing::playback()), print("\n");
        ++n;
    } catch (...) { /* Ignore evaluation error */ }
    Loop:
      goto Start;
  } catch (...) { return n; }
}

#include <stdio.h> 
int main(int argc, char **argv) {
  printf("Read, evaluated, and printed successfully %d expressions\n", REPL());
  printf("Good bye!\n");
  return 0;
}
