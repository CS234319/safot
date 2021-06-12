#include <iostream>
#include <sstream>
#include "00.h"
#include "parser.h"

/** Auxiliary file that should not be used by production code, only 
 * for debugging. 
 */
extern std::ostream& operator<<(std::ostream &os, Pair p); 
extern std::ostream& operator<<(std::ostream &os, S s); 
extern std::ostream& operator<<(std::ostream &os, std::ostringstream o);
extern bool isRule(int i);
extern String stack();
extern String operator ~(Parser::Symbol s);
extern String operator ~(S s);
