#ifndef PRINT_H
#define PRINT_H
#include "S.h"
/** Print a String */ extern int print(String);
/** Print an S expression */ extern int print(S);
/** Print a newline */ inline int println() { print("\n"); }
/** Print a String with newline */ inline int println(String s) { print(s), println(); }
/** Print an S expression with newline */ inline int println(S s) { print(s), println(); }
/** Print a prompt */ extern int prompt(String);
/** Call before printing error messages */ extern int err();
/** Call before printing normal output */ extern int out();
#endif
