#include "repl.h"

using namespace Parser;

S eval() { /** Should only be called after the parser finished successfully */
    try {
//        prompt("Parser : "); println(Parser::result());
//        prompt("Eval   : "); println(Parser::result().eval());
        return Parser::result().eval();
    } catch (Pair x) {
        err(), print("Error: kind = "), print(S(x.car)), print(" Where = "), print(S(x.cdr)), print("\n"),out();
        throw;
    }
}

/** Realizes the famous "Read, Evaluate, Print, Loop" of all
interpreters; Returns the number of expressions successfully read
and evaluated. */

int REPL(const char* input) {
    int n = 0;
    try {
    Start:
        reset(), prompt("> ");
    Read:
        const String line = (input != ((char *)0)) ? input : read();
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
            const S result = eval();
        Print:
            println(result);
            ++n;
        } catch (...) {
        }
   Loop:
        if(input != (char *)0) return n;
        goto Start;
    } catch (...) {
        return n;
    }
}





