#import  "repl.h"
#import  "read.h"
#import  "print.h"
#import  "parser.h"

static S eval(S s) { try { return s.eval(); } catch (Pair x) { throw s; } }

S read() { // Loop until an S expression is read
  for (;;) 
    for (Parser::reset(), prompt(">");; ) {
      String line = readln(); 
      if (line == (String)0) { throw 0; }
      Parser::supply(line);
      switch (Parser::status()) {
        case Parser::ready:  continue;                  // More input must be waiting 
        case Parser::accept: return Parser::result();   // Return the parsed S expression
        case Parser::reject: prompt("?\n"); continue;   // Admonish programmer; continue
      }
    }
}

#define Let const 
/*{REPL}*/
/** Function REPL realizes the famous ``Read, Evaluate, Print, Loop''
of all interpreters. It loops forever (theoretically), terminating
with end-of-file mark found on its input stream, or if the evaluation
engine fails due to some unrecoverable error, such as memory
exhaustion, or even due to a bug in the engine's implementation.

The function \emph{does not} terminate in an evaluation error, in
which case, the programmer is invited to feed new input. 

Upon termination, this function returns the number of expressions
successfully read and evaluated.*/
Integer REPL() {   Var Integer n = 0;
  Start: try {
    Read:  Let S expression = read(); // function read 
    Eval:  Let S evaluted = eval(expression); 
    Print: println(evaluted); 
    Loop:  ++n;  goto Read;
  } catch (S error) { goto Start; }  // Failed evaluation
    catch (...)     { return n; }    // Engine failure
}
/*{END}*/
