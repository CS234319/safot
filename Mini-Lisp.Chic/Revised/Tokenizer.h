#import "chic.h"
namespace Tokenizer {
  enum { undefined = 128, $};
  extern void initialize(char *buffer);
  const char tokens[] = "()[].\'";
  // Retrieve the next token: if non-positive, this is an atom (including NIL)
  // else it is a character as per the table above
  extern Short next(); 
  extern Short get(); 
  extern Short unget(); 
  extern Short peep();
}
