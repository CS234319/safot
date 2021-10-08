#import "S.h"

/* Get the alist */
namespace Engine {
  extern S globals;
  extern S alist;

/* Operations */
  extern S entry(S key, S value);
  extern S set(S key, S value);
  extern S lookup(S key, S alist);
  extern S lookup(S);
  extern void traceback();

  extern S reset(); // Reset globals and a-list
  extern void clear(); // Clears a-list only
}

namespace Dump {
  extern S globals(); 
   /** In case of error, dump the association-list with trace back: */
  extern void calls();
}

/* Stack trace */
