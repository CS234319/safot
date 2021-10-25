#import  "read.h"

#import  <stdio.h>
#import  <stdlib.h>
#import  "mode.h"

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
#import  <string.h>
extern char *inject(String injection) {
  return ::injection = strdup(injection);
}
#endif
