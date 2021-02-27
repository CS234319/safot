#include <iostream>
#include <sstream>
#include "mini-lisp.h"
#include "parser.h"

extern std::ostream& operator<<(std::ostream &os, Pair p); 
extern std::ostream& operator<<(std::ostream &os, S s); 
extern std::ostream& operator<<(std::ostream &os, std::ostringstream o);
extern bool isRule(int i);
extern String stack();
extern String operator ~(Parser::Symbol s);
extern String operator ~(S s);
