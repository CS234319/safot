#ifndef OUT_H
#define OUT_H
#include "S.h" 
/** Print an S expession */ extern int print(S);  // Forward declaration
/** Print the prompt */ extern int prompt(String  s);
/** Print a string error message */ extern int err(String   s);
/** Print an error message associated with a handle */  extern int err(H h);        
/** Call before printing error messages */ extern int err();
/** Call before printing to standard output */ extern int out();
#endif

