#include "read.h"

#include <stdio.h>
#include <stdlib.h>
#include "mode.h"

static char *injection = (char *)0;

char *readln() {
  static size_t  length = 72;
  static char   *buffer = reinterpret_cast<char *>(malloc(length));
#ifndef PRODUCTION
  if (injection == buffer) return (char *)0; 
  if (injection != (char *)0) {
    auto result = injection;
    injection = buffer;
    return result;
  }
#endif
  extern int grunt(int);
  return grunt(getline(&buffer, &length, stdin)) ? (char *) 0: buffer;
}

#ifndef PRODUCTION
#include <string.h>
extern char *inject(String injection) {
  return ::injection = strdup(injection);
}
#endif
