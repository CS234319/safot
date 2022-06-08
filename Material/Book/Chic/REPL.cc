#include <assert.h>
#import  "REPL.h"
#import  "read.h"
#import  "print.h"
#import  "parser.h"
static S eval(S s) { try { return s.eval(); } catch (Pair $x$) { throw s; } }

#define forever    for (;;) 
#define whatever   ... 
#define relax      0
#define loop       goto

#define EOF ((char *)0)

struct panic{};

/*| Z |*/
/** Prompt for input and read it line by line, until a valid
S-expression is found and returned; panics on EOF. */
/*| W |*/
S read() { 
  Prompt:   collaterally( Parser::reset(), prompt(">") );
  Consume:  {
    Value line = readln(); 
    if (line == EOF) throw panic(); 
    Parser::supply(line); 
    switch (Parser::status()) {
      case Parser::ready: 
        prompt("-"); loop Consume;    // More input must be waiting 
      case Parser::accept: 
        return Parser::result();   
      default:                            assert(Parser::status() == Parser::reject);
        collaterally( prompt("?\n"), Parser::reset() );
        loop Consume;   // Admonish programmer; continue
    }
  }
}
/*| X |*/

/*| A |*/
/** REPL realizes its acronym---the famous 
``\emph{\textbf Evaluate, \textbf Print, \textbf Loop\/}" of all interpreters.
The function repeatedly consumes and processes input.  The cycle repeats ad
infinitum, but may stop before in case of \emph{panic} situations.
\begin{itemize}
  \item Panics include memory exhaustion, failed assertions, and the more
  common the case of \textbf Read encountering an end-of-file mark in its input
  stream, memory exhaustion, and, failed assertions. 
  \item In case of panic, REPL returns the number of S-expression
  that it successfully read and evaluated.
 \item Malformed input detected by \textbf Read and errors in \textbf Eval of
 correct input are no reason for REPL to panic: \textbf Read repeatedly 
 prompts the user until correct input is provide; errors are reported
 telegraphically, and REPL proceeds to trying to evaluate the next
 correct input.  
 \end{itemize} */
/*| B |*/
Integer REPL() {   
  Variable $n$ = 0;Start:                         try {           // Reading and evaluation may fail
    Read:  Value $x$ = read();                                    // Read an S-expression; may panic
    Eval:  Value $e$ = eval($x$);                                   // Evaluate this expression; may throw anything
    Print: println($e$);                                          // Print the evaluation result 
                        } catch (panic) { return $n$; }           // Engine failure or EOF terminating REPL
                          catch (whatever) { goto Start;      } // Evaluation error, retry in another cycle      
    Loop:  ++$n$;                                                 // Current cycle completed successfully
           goto Start;                                           // Proceed to next cycle 
}
/*| C |*/
