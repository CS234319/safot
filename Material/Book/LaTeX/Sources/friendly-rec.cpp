class X {
  char f() { return g(); } // Definition of f()
  char g() { return f(); }  // Definition of g()
}
