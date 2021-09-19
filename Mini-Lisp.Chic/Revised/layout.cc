#import "layout.h"
#import "Word.h"

Let Long $m$ = $M_a$ + $M_p$ * sizeof (Word);

Service {
  Representation {
   char block[$m$];
   struct {
     char $A_0$[$M_a$ - LIMBO];
     char A[LIMBO] = { 'N', 'I', 'L', '\0' };
     Word P[$M_p$];
    };
  };
} memory; 

Let array(Word) P = memory.P - 1;
Let array(Word) $P_0$ = memory.P - 1;
Let array(Word) $P_1$ = memory.P + $M_p$;
Let array(char) A  = memory.A;
Let array(char) $A_0$  = memory.$A_0$;
Let array(char) $A_1$  = memory.A + $M_a$;

// Global:
Provides constant(Long) $m$;    /// how many bytes are used by the store 
// Atoms:
Provides constant(Short) $M_a$;  /// how many atoms are initially available 
Provides function Short $v_a$(); /// how many chars remain available for allocation 
Provides function Short $u_a$(); /// how many chars were allocated 
// Pairs
Provides constant(Short) $M_p$;  /// how many pairs are initially available 
Provides Short m$_p$;              /// how many are currently available 
Provides Short made$_p$;           /// how many pairs were made, reuses are counted
Provides Short free$n_p$;          /// how many pairs were freed 
Provides Short collected$n_p$;     /// how many pairs were garbage collected 


static_assert(A-$A_0$ >= $A_f$);
static_assert((Short) $M_a$ > 100);
static_assert((Short) $M_p$ > 100);
static_assert(0 == $m$ - sizeof memory.block);
static_assert(0 == P + 1 - memory.P);
static_assert(0 == sizeof memory.block - sizeof memory);
static_assert(0 == sizeof memory - sizeof memory.block);
static_assert($m$ - sizeof memory.block >= 0);
static_assert(P + 1 >= memory.P);
static_assert((Short) $M_p$ + 1 > 0);
static_assert(P + 1 <=memory.P);
static_assert(sizeof memory.block - $m$ <= 0);
static_assert($P_n$ < sizeof memory);
static_assert($P_n$ < sizeof memory.P);
static_assert((Short) - $M_a$ - 1 <  0);

static_assert($M_p$ == $P_t$);
static_assert($M_p$ ==sizeof memory.P / sizeof memory.P[0]);
static_assert($P_1$ - memory.P == $P_t$);
static_assert($P_n$ == $M_p$);
static_assert(A ==memory.A);
static_assert(P + 1 ==memory.P);
static_assert((Short) $M_a$ == $M_a$); 
static_assert((Short) $M_p$ == $M_p$); 
static_assert(sizeof memory.block == $m$);
static_assert(sizeof memory.block == sizeof memory);
static_assert((void *)(memory.A + sizeof memory.A) == (void *)memory.P); 

static_assert(memory.A + sizeof(memory.A) >= (void *)memory.P);
static_assert(memory.A + sizeof(memory.A) <= (void *)memory.P);
static_assert(memory.A + sizeof(memory.A) == (void *)memory.P);
