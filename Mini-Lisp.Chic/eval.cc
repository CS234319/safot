#import "eval.h"
#import "a-list.h"
#import "builtin.h"
#import "basics.h"
#import "print.h"
#import "except.h"
#define PRODUCTION
#import "mode.h"

 
extern const S DEFUN, LAMBDA, NDEFUN, NLAMBDA;
namespace Engine { 
  namespace Inner { 
    bool normal(S tag) { return tag.eq(NDEFUN) || tag.eq(NLAMBDA); }
    bool native(S tag) { return tag.eq(NDEFUN) || tag.eq(DEFUN); }

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
      push(formals.car(), arguments.car());
      bind(formals.cdr(), arguments.cdr());
    }
  }

  using namespace Inner;
  S apply(S tag, S formals, S body, S actuals) {
    D(tag, formals);
    D(actuals);
    D(body);
    check(actuals, BAD_ARGUMENTS);
    S arguments = INVOKE(map(actuals, normal(tag) ? identity : eval));
    if (formals.atom())   M("Variadic binding of", formals, actuals), 
      push(formals, arguments);
    else { M("list of arguments",actuals);
      check(formals, BAD_PARAMETERS);
      align(formals, actuals, MISSING_ARGUMENT, REDUNDANT_ARGUMENT);
      bind(formals, arguments);
    }
    return INVOKE( (native(tag) ? exec : eval)(body));
  }

  S apply(S f, S actuals) {
    S before = alist;
    S what = f.eval(); 
    push(S("*"), f.cons(actuals));
    push(RECURSE, what);
    what.n3() || f.error(BAD_FUNCTION).t();
    S result = INVOKE(apply(what.$1$(), what.$2$(), what.$3$(), actuals));
    alist = before;
    return result;
  }

  S eval(S s) { 
      ENTER(M(">>", s));
      const S result = INVOKE(s.atom() ? lookup(s) : apply(s.car(), s.cdr())); 
      EXIT(M("<<", result));
      return result;
  }
}
