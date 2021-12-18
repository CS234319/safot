#import  "a-list.h"
#import  "basics.h"
#import  "print.h"
#define PRODUCTION
#import  "mode.h"
#import  "except.h"
#import  "builtin.h"

namespace Frame { extern S until(S); }
namespace Dump {
  static S frame(S), bindings(S);
  static void argument(S s), arguments(S s, S until);
 
  static S bindings(S from); 

  S globals() { return bindings(Engine::alist::globals::current()); }

  void calls() {
    int n = 0;
    for (S s = Engine::alist::current(); !s.null() && n < 5; ++n, s = frame(s)) {
       ; 
    }
  }

  static S bindings(S from) {
    println("(");
    for (S s = from; !s.null(); s = s.cdr()) {
      Value binding = s.car();
      Value key = binding.car();
      Value value = binding.cdr();
      print("\t Argument "), print(key), print("\t.\t"), println(value);
    }
    println(")");
  }


  /** Print the bottom most frame on the association list, and return the list
   * without this frame */
  static S frame(S s) { 
    S until = Frame::until(s);
    arguments(s, until); 
    return until.null() ? until : until.cdr();
  }

  static void argument(S s) {
    D(s);
    Value binding = s.car();
    Value key = binding.car();
    Value value = binding.cdr();
    print(key), print("\t=\t"), println(value);
  }

  static void arguments(S s, S until) {
    D(s);
    if (s.null()) return;
    if (s.handle != until.handle) arguments(s.cdr(), until);
    argument(s);
  }
}

extern const S UNDEFINED_ATOM;

namespace Engine::globals {
  extern S top = Builtins::builtin(); 
  extern S clear() { return top = Builtins::builtin(); }
  extern S current() { return top; } 
  extern S set(S k, S v) { return top = k.cons(v).cons(top), v;  }
}

namespace Engine::alist {
  extern S top = NIL0;
  extern S clear() { return top = NIL0; }
  extern S restore(S previous){  return top = previous; }
  extern S push(S k, S v) { return top = k.cons(v).cons(top), v; }
}
namespace Engine {
  namespace Dictionary {
    extern S reset() { return alist::clear(), globals::clear(); }

    static S lookup(S id, S list) {
      return list.null()             ? id.error(UNDEFINED_ATOM) : 
             list.car().car().eq(id) ? list.car().cdr()         : 
                                       lookup(id, list.cdr())   ; 
    }

    extern S lookup(S id) { 
      for (S s = alist::top; s.pair(); s = s.cdr())
        if (s.car().car().eq(id))
          return s.car().cdr(); 
      return lookup(id, globals::top); 
    }
  }
}
