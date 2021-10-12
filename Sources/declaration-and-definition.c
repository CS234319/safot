extern char f();          // Declaration of f()
char g() { return f(); }  // Definition of g()
char f() { return g(); }  // Definition of f()
