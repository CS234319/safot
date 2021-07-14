#include <iostream>
#include <sstream>
#include "S.h"
#include "parser.h"

/** Auxiliary file that should not be used by production code, only 
 * for debugging. 
 */
extern std::ostream& operator<<(std::ostream &, Pair); 
extern std::ostream& operator<<(std::ostream &, S); 
extern std::ostream& operator<<(std::ostream &, std::ostringstream);
extern bool isRule(int);
extern String stack();
extern String operator ~(Parser::Symbol);
extern String operator ~(S s);
