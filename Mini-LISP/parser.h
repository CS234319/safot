#ifndef PARSER_H
#define PARSER_H
#include "mini-lisp.h"

namespace Parser {
  extern S result();
  enum Status { ready, accept, reject};
  extern enum Status status();
  extern void supply(char *input);
  extern void reset();
}
#endif

