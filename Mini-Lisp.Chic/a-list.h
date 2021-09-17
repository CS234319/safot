#import "S.h"

/* Get the alist */
namespace Engine {
  extern S globals;
  extern S alist;

/* Operations */
  extern S push(S key, S value);
  extern S set(S key, S value);
  extern S lookup(S key, S alist);
  extern S lookup(S);
  extern void traceback();

  extern void reset(); // Reset globals and a-list
  extern void clear(); // Clears a-list only
}

/* Stack trace */
