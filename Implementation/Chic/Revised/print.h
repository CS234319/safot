#import "S.h"
/** Print some text */ extern int print(Text);
/** Print an S expression */ extern int print(S);
/** Print a newline */ inline int println() { print("\n"); }
/** Print a String with newline */ inline int println(Text t) Is(print(t), println())
/** Print an S expression with newline */ inline int println(S s) Is(print(s), println())
/** Print a prompt */ extern int prompt(Text);
/** Call before printing error messages */ extern int err();
/** Call before printing normal output */ extern int out();
extern void chatty();
extern void silent();
