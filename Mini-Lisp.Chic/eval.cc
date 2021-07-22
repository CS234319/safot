#include "eval.h"
#include "a-list.h"
#include "basics.h"

#define PRODUCTION
#include "mode.h"

#undef NULL

const auto ATOMIC_FUNCTIONS = list(
    CAR,  CDR,  CONS,
    ATOM,  NULL, EQ,  COND, 
    ERROR, SET,  EVAL, QUOTE,
    DEFUN, NDEFUN, NLAMBDA, LAMBDA);


bool atomic(S name) { return exists(name, ATOMIC_FUNCTIONS); }
S defun(S name, S parameters, S body) { return set(name, list(LAMBDA, parameters, body)); }
S ndefun(S name, S parameters, S body) { return set(name, list(NLAMBDA, parameters, body)); }

S apply_defined_function(S f, S args) { apply(f,args); }

/** Assertions like */ 
S bug(S s) { return s.error(BUG); }

#define FUN(Return, Name, ArgumentType) \
  Return Name(ArgumentType _) { \
    const auto $$ = Name; \
    M3("[",_,"]"); \
    Return __ =  

#define IS(X)    \
    X; \
    M2("-->", __); \
    return __; \
  } 


FUN(S, evaluate_list, S) IS(
 _.null() ? NIL : _.car().eval().cons($$(_.cdr()))
) 

FUN(S, evaluate_cond, S)  IS( 
    _.null() ?  NIL:
    _.car().atom() ? _.car().error(COND):
      _.car().car().eval().t() ? _.car().cdr().car().eval():
        $$(_.cdr()) ;
)

S only(S s) {
    s.pair() || die(s);
    s.cdr().cdr().t() && s.error(REDUNDANT).t();
    S a = evaluate_list(s.cdr());
    a.null() && s.error(MISSING).t();
    a.atom() && s.error(INVALID).t();
    return a.car();
}

void checkNumberOfArgs(S s) {
    S f = s.car();
    if (f.eq(QUOTE) || f.eq(CAR) || f.eq(CDR) || // 1 Args:
        f.eq(ATOM) || f.eq(NULL) || f.eq(EVAL)) {
        s.more2() && s.error(REDUNDANT).t();
        s.less2() && s.error(MISSING).t();
    }
    if (f.eq(CONS) || f.eq(SET) || f.eq(EQ) || f.eq(LAMBDA) || f.eq(NLAMBDA)) { // 2 Args:
        s.more3() && s.error(REDUNDANT).t();
        s.less3() && s.error(MISSING).t();
    }
    if (f.eq(NDEFUN) || f.eq(DEFUN)) { // 3 Args:
        s.more4() && s.error(REDUNDANT).t();
        s.less4() && s.error(MISSING).t();
    }
}

S evaluate_atomic_function(S s) { M(s);
  checkNumberOfArgs(s);
  const S f = s.car();
  // Atomic functions:
  if (f.eq(CAR))     return only(s).car();
  if (f.eq(CONS))    return s.$2$().eval().cons(s.$3$().eval());
  if (f.eq(SET))     return set(s.$2$().eval(),          s.$3$().eval());
  if (f.eq(EQ))      return s.$2$().eval().eq(s.$3$().eval()) ? T : NIL;
  if (f.eq(COND))    return evaluate_cond(s.cdr());
  if (f.eq(CDR))     return only(s).cdr();
  if (f.eq(ATOM))    return only(s).atom() ? T : NIL;
  if (f.eq(EVAL))    return only(s).eval();
  if (f.eq(ERROR))   return s.error(s.cdr().eval());
  if (f.eq(NULL))    return only(s).null() ? T : NIL;
  if (f.eq(QUOTE))   return s.cdr().car();
  if (f.eq(NLAMBDA)) return list(NLAMBDA, s.$2$(),  s.$3$());
  if (f.eq(LAMBDA))  return list(LAMBDA, s.$2$(), s.$3$());
  if (f.eq(NDEFUN)) { 
    ndefun(s.$2$(), s.$3$(), s.$4$());
    return  s.$2$();
  }
  if (f.eq(DEFUN)) { 
    defun(s.$2$(), s.$3$(), s.$4$());
    return  s.$2$();
  }
  return bug(s);
}

S apply(S f, S args) {
  D(f,args);
  f.n3() || f.cons(args).error(INVALID).t();
  D(f.$1$(),f.$2$(),f.$3$(),args,f.$1$().eq(NLAMBDA));
  const auto actuals = f.$1$().eq(NLAMBDA)? args : f.$1$().eq(LAMBDA) ? evaluate_list(args) : f.cons(args).error(INVALID);
  alist() = bind(f.$2$(), actuals, alist());

  const auto result = f.$3$().eval();
  return result;
}

S eval(S s) {
    D(s);
    inc_eval_counter();
    S res = NIL;
    D(s);
    if (s.atom()) {
       res = lookup(s);
       D(s, res);
    } else {
      D(s, s.car(), s.cdr());
      if (atomic(s.car())) {
       D(s.car());
       res = evaluate_atomic_function(s);
       D(s, res);
      } else {
       res = apply_defined_function(eval(s.car()), s.cdr());
       D(s, res);
      }
    }
    D(s,res);
    dec_eval_counter();
    if (get_eval_counter() == 0) reset_set_counter();
    return res;
}
