#include "read.h"
#include "out.h"

extern int grunt(int);
String read() {
  static char  *buffer = 0;
  static size_t length = 72;
  if (buffer == (char *)0) buffer = reinterpret_cast<char *>(malloc(length));
  return grunt(getline(&buffer, &length, stdin)) ? (String) 0: buffer;
}
