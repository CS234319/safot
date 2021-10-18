/** Manages the pool of all strings used by the program. Unlike pairs, there is
 * no dynamic allocation of strings at run time. */
#import "chic.h"
#import "Id.h"
Module text {
  extern Id request(Text);
  extern Boolean exists(const char, Text); 
}
