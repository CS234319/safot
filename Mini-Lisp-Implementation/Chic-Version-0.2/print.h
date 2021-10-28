#import "S.cc"
#import "Text.cc"
/** Print some text */ extern int print(String);
/** Print an S expression */ extern int print(S);
/** Print a newline */ inline int println() { print("\n"); }
/** Print a String with newline */ inline int println(Text t) is((print(t) then println()))
/** Print an S expression with newline */ inline int println(S s) is((print(s) then println()))
/** Print a prompt */ extern int prompt(Text);
/** Call before printing error messages */ extern int err();
/** Call before printing normal output */ extern int out();
extern void chatty();
extern void silent();
