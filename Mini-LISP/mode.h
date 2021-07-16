#ifdef PRODUCTION 
  #undef D
  #undef M
  #undef M2
  #undef M3
  #define D(...) 0
  #define M(...) 0
  #define M2(...) 0
  #define M3(...) 0
#else
  #include <sstream>
  #include <iostream>
  #include <cstring>
  #include "dump.h"
  #include "io.h"
#endif
