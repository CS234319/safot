#include "parser.h"
#include "read.h"
#include "out.h"
#include "a-list.h"

using namespace Parser;

S eval() { /** Should only be called after the parser finished successfully */
  try {
    print("Parser: "); print(Parser::result()); print("\n");
    print("Eval: "); print(Parser::result().eval());
    return Parser::result().eval();
  } catch (Pair x) { 
    throw err(),err("Error: kind = "), err(x.car), err(" Where = "), err(x.cdr), err("\n"),out();
  }
}

int REPL() { /** Realizes the famous "Read, Evaluate, Print, Loop" of all 
               interpreters; Returns the number of expressions successfully read
               and evaluated. */
  int n = 0;
  try {
    Start:
      reset(), prompt("> ");
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
    Eval:
      try {
        save();          // Prepare for an evaluation error
        const S result = eval(); 
      Print:
        print(result), print("\n");
        ++n;
      } catch (...) { // Ignore evaluation error
        restore();    // But restore the a-list to release parameter binding
      }
    Loop:
      goto Start;
    } catch (...) {
      return n;
    }
}

int main(int argc, char **argv) {
  printf("Read, evaluated, and printed successfully %d expressions\n", REPL());
  printf("Good bye!\n");
  return 0;
}
