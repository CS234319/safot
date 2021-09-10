#ifndef OUT_H
#define OUT_H
#include "S.h" 
/** Print an S expression */ extern int print(S);
/** Print an S expression with newline */ extern int println(S s);
/** Print the prompt */ extern int prompt(String);

/** Call before printing error messages */ extern int err();
/** Call before printing normal output */ extern int out();

#ifndef PRODUCTION // Testing adds overhead, which should not be part of production
namespace Printing { // Better name is Write, but we have to be consistent with REPLY
  extern void record(); /** Start recording into a new clean buffer, if buffer exists, clean it */
  extern String playback();  /** Return current contents of buffer */ 
};
namespace Erroring { // Name could (and probably would) change.
  extern void record(); /** Start recording into a new clean buffer, if buffer exists, clean it */
  extern String playback();  /** Return current contents of buffer */ 
};
#endif // PRODUCTION
#endif
