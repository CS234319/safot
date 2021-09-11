#ifndef READ_H
#define READ_H
#include "S.h"
extern String readln();     // Only function in production mode

#ifndef PRODUCTION             // Testing adds overhead, which should not be part of production
  namespace Reading {          // For readability; Read::from("(car x)") is better than reader_set_source
    extern void from(String);  // Once called, you cannot go back to stdin, but you can set another source if you like 
  }
#endif // PRODUCTION
#endif // READ_H
