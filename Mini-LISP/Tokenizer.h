#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "chic.h"

extern Boolean inline exists(char c, Text s);


namespace Tokenizer {
  enum { undefined = 128, $};
  const char tokens[] = "()[].\'";
  extern void initialize(char *buffer);
  // Retrieve the next token: if non-positive, this is an atom (including NIL)
  // else it is a character as per the table above
  extern Short next(); 
  extern Short get(); 
  extern Short unget(); 
  extern Short peep();
}
extern Boolean exists(const char, const char *const); 
#endif

