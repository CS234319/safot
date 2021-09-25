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
/**Function REPL realizes its acronym---the famous ``\emph{\textbf Read,
\textbf Evaluate, \textbf Print, \textbf Loop}'' of all interpreters. It loops
until an end-of-file mark is entountered on its input stream. It also halts
when the evaluation engine fails due to some unrecoverable error, such as
memory exhaustion, or due to a bug in the engine's implementation.
\par
The function \emph{does not} terminate in an evaluation error, in which case,
the programmer is invited to feed new input.  Upon termination, this function
returns the total number of expressions successfully read and evaluated. */
Integer REPL() {   Var Integer n = 0;
  Start: try {            // Reading and evaluation may fail
    Read:  Let S expression = read();       // Read an S-expresson
    Eval:  Let S result = eval(expression); // Evaluate this expression 
    Print: println(result);                 // Print the evaluation result 
    Loop:  ++n;  goto Start;                // Loop
  } catch (S error) { goto Start; }         // Failed evaluation is ignored
    catch (...)     { return n; }           // Engine failure or EOF terminate REPL
}
/*{END}*/
