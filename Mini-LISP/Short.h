#ifndef SHORT_H
#define SHORT_H
#include "chic.h"
Short mark(Short h);
bool marked(Short h);
inline void stain(Short &s) {
  if (!marked(s)) s = marked(s);
}
#endif

