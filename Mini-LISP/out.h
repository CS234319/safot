#ifndef OUT_H
#define OUT_H
#include "S.h" 
/** Print an S expession */ extern int print(S);  
/** Print the prompt */ extern int prompt(String);
/** Print a string error message */ extern int err(String);
/** Print an error message associated with a handle */  extern int err(H);        
/** Call before printing error messages */ extern int err();
/** Call before printing normal output */ extern int out();
#endif
