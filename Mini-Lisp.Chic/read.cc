#include "read.h"

#include <stdio.h>
#include <stdlib.h>

extern int grunt(int);

String readln() {
  static char   *buffer = 0;
  static size_t  length = 72;
  if (buffer == (char *)0) buffer = reinterpret_cast<char *>(malloc(length));
  return grunt(getline(&buffer, &length, stdin)) ? (String) 0: buffer;
}
