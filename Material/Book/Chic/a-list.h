#import "S.h"

namespace Engine::globals {
  namespace globals {
    extern S current() ;
    extern S clear() ;
    extern S set(S k, S v) ;
  }
}

namespace Engine::alist {
  extern S current();
  extern S clear();
  extern S reset();
  extern S restore(S previous);
  extern S set(S k, S v) ;
}

namespace Engine::Dictionary {
  extern S lookup(S id); 
}


/* Get the alist */
namespace Engine::alist {
  extern S current();
  extern S push(S key, S value);
  extern S lookup(S);
  extern S lookup(S key, S alist);
  extern S clear(); 
  extern S reset(); // Reset globals and a-list

  inline S v1() { return current().car().cdr(); } 
  inline S v2() { return current().cdr().car().cdr(); } 
  inline S v3() { return current().cdr().cdr().car().cdr(); } 

  namespace globals {
    extern S current();
    extern S set(S key, S value);
    extern void clear(); 
  }
  extern void traceback();
}

namespace Dump {
  extern S globals(); 
   /** In case of error, dump the association-list with trace back: */
  extern void calls();
}

/* Stack trace */
