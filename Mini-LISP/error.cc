#define STR(arg)  STR1(arg)
#define STR1(arg) STR2(arg)
#define STR2(arg) #arg

#define CAT(x, y)   CAT1(x, y)
#define CAT1(x, y)  CAT2(x, y)
#define CAT2(x, y)  x##_##y

#define FIELD(A, B, C)  char CAT(CAT(A,B),C) []= { STR(A) STR(B) STR(C) };

FIELD(CAR,OF,ATOM)
FIELD(CDR,OF,ATOM)

