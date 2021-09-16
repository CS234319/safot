#include "repl.h"
#include "print.h"
#include "read.h"

#include "mode.h"

/** Internal function to evaluate of the parsed input; Should only be called
after the parser finished successfully */
static S eval(S s) { 
  try {
    return s.eval();
  } catch (Pair x) {
     return s;
  }
}

S read() {
  for (;;) 
    for (Parser::reset(), prompt("> ");; ) {
      String line = readln(); 
      if (line == (String)0) { throw 0; }
      Parser::supply(line);
      switch (Parser::status()) {
        case Parser::ready: prompt("- "); continue;     // More input must be waiting 
        case Parser::accept: return Parser::result();   // Return the parsed S expression
        case Parser::reject: prompt("?\n"); break;      // Admonish the client; continue
      }
    }
}

/** Realizes the famous "Read, Evaluate, Print, Loop" of all 
interpreters; Returns the number of expressions successfully read and
evaluated. */
int REPL() {   int n = 0;
  try {
    Read: const S expression = read();
    Eval: const S result = eval(expression); 
    Print: println(result); 
    Loop:  ++n;  goto Read;
  } catch (S s) {
      return n;
  } catch (...) {
      return n;
  }
}
