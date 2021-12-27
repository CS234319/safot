#import "eval.h"
#import "a-list.h"
#import "builtin.h"
#import "basics.h"
#import "print.h"
#import "except.h"
#define PRODUCTION
#import "mode.h"

namespace Frame { 
  using namespace Engine;
  const struct Entry { 
    S key; Entry(S s): key(s) {}  
    S record(S value) const { return alist::push(key, value), value; }
  } NAME("\r //"),  ACTUALS("\r [...]"), LAMBDA("\r ..");
  S until(S s) {
    D(s);
    for (; ; s = s.cdr()) 
      if (s.null() ||  s.car().car().eq(NAME.key)) return s;
  }
}

extern const S DEFUN, LAMBDA, NDEFUN, NLAMBDA;

namespace Engine { 
  namespace { 
    bool normal(S tag) { return tag.eq(NDEFUN) or tag.eq(NLAMBDA); }
    bool native(S tag) { return tag.eq(NDEFUN) or tag.eq(DEFUN); }

    S identity(S s) { return s; }
    S evaluate(S s) { return s.eval(); }
    S check(S l, S e) { return l.null() ? l : l.atom() ? l.error(e) : check(l.cdr(), e); } 
    S map(S s, S (*f)(S)) { return s.null() ? s :  f(s.car()).cons(map(s.cdr(), f)); }

    S align(S s1, S s2, S e1, S e2) { return  
      s1.null()  &&  s2.null() ?  NIL0 : 
     !s1.null()  &&  s2.null() ? s1.error(e1) : 
      s1.null()  && !s2.null() ? s2.error(e2) : 
        align(s1.cdr(), s2.cdr(), e1, e2);  
    }
    void bind(S formals, S arguments) {
      if (formals.null() || arguments.null()) return; 
      alist::push(formals.car(), arguments.car());
      bind(formals.cdr(), arguments.cdr());
    }
  }

S apply(S f, S actuals) {
  Value lambda = f.eval(); 
  // Break lambda expression into its three components:  
                                                                        assert ( lambda.n3() or f.error(BAD_FUNCTION).t() );
    Value tag = lambda.$1$(); 
    Value formals = lambda.$1$(); 
    Value body = lambda.$1$(); 
  // Compute concrete arguments from actuals
                                                                        check(actuals, BAD_ARGUMENTS);
    Value arguments = map(actuals, normal(tag) ? identity : eval);

                  // Save the current alist
                  Value before = alist::current(); // Save the global a-list
    { // Bind formals to arguments 
      if (formals.atom()) {   // Variadic lambda or list-of-arguments-lambda? 
        alist::push(formals, arguments); // Variadic lambda: push a single entry into the a-list
      } else {                // It is a multiple argument function.
                                                                        check(formals, BAD_PARAMETERS);
                                                                        align(formals, actuals, MISSING_ARGUMENT, REDUNDANT_ARGUMENT);
        bind(formals, arguments);
      }
    }
    // Invoke eval recursively, or call an implementation of a native function. 
    Value result = (native(tag) ? Builtins::exec : eval)(body);
                    // Restore the alist
                    alist::restore(before);
    return result;
}

S eval(S s) { 
  return s.atom() ? alist::lookup(s) : apply(s.car(), s.cdr()); 
}
}
