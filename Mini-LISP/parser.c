#include "parser.h"
#include "dump.h"

#define SILENT 1 
#if SILENT
#undef D
#define D(...) 0
#endif

namespace Parser {

extern enum Status status() {
  return ready;
}

extern void go(char *buffer) {
  Tokenizer::init(buffer);
}

extern void reset();
extern S result();
}
