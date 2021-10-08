#import "chic.h"
#import "Word.h"
Provides array(char) A;
Provides array(Word) P;
Let Short $M_a$ = 1<<12; 
Let Short $M_p$ = (1<<15) - $M_a$ + 2; 
Let Short LIMBO = sizeof "NIL";
Let Short $A_f$ = LIMBO - $M_a$, $A_t$ = 0, $A_n$ = range($A_f$, $A_t$), $A_x$ = $A_f$ -1;
Let Short $P_f$ = 1, $P_t$ = $M_p$, $P_n$ = $M_p$, $P_x$ = 0;
Let Short $X_f$ = min($A_f$, $P_f$), $X_t$ = max($A_t$, $P_t$); 
Let Long $X_n$ = range($X_f$, $X_t$);
Let Short $X_x$ = $X_t$ + 1; 
