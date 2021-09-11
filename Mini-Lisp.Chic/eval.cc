#include "eval.h"
#include "a-list.h"
#include "basics.h"
#include "out.h"

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


FUN(S, materialize, S) IS(
 _.null() ? NIL : _.car().eval().cons($$(_.cdr()))
) 

FUN(S, evaluate_cond, S)  IS( 
    _.null() ?  NIL:
      _.car().atom() ? _.car().error(COND):
       _.car().car().eval().t() ? _.car().cdr().car().eval():
         $$(_.cdr()) ;
)

void checkNumberOfArgs(S s) {
    S f = s.car();
    push(ARGUMENT, s.cdr());
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
    remove_element(ARGUMENT);
}

S eval_argument(S arg) {
    // Eval 1 argument:
    push(ARGUMENT, arg);
    S res = arg.eval();
    remove_element(ARGUMENT);
    return res;
}

S eval_arguments(S arg1, S arg2) {
    // Eval 2 argument:
    push(ARGUMENT, arg1);
    push(ARGUMENT, arg2);
    S res1 = arg1.eval();
    S res2 = arg2.eval();
    remove_element(ARGUMENT);
    remove_element(ARGUMENT);
    return res1.cons(res2);
}

S evaluate_atomic_function(S s) { M(s);
  checkNumberOfArgs(s);
  const S f = s.car();
  S args_1 = NIL;
  S args_2 = NIL;
  S args_3 = NIL;
  S res = NIL;

  // Atomic functions:
  if (f.eq(CAR)) {
      args_1 = eval_argument(s.$2$());
      push(ARGUMENT, args_1);
      res = args_1.car();
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(CONS)) {
      S evaluated_args = eval_arguments(s.$2$(), s.$3$());
      args_1 = evaluated_args.car();
      args_2 = evaluated_args.cdr();
      push(ARGUMENT, args_1);
      push(ARGUMENT, args_2);
      res = args_1.cons(args_2);
      remove_element(ARGUMENT);
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(SET)) {
      S evaluated_args = eval_arguments(s.$2$(), s.$3$());
      args_1 = evaluated_args.car();
      args_2 = evaluated_args.cdr();
      push(ARGUMENT, args_1);
      push(ARGUMENT, args_2);
      res = set(args_1, args_2);
      remove_element(ARGUMENT);
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(EQ)) {
      S evaluated_args = eval_arguments(s.$2$(), s.$3$());
      args_1 = evaluated_args.car();
      args_2 = evaluated_args.cdr();
      push(ARGUMENT, args_1);
      res = args_1.eq(args_2) ? T : NIL;
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(COND)) {
      args_1 = s.cdr();
      push(ARGUMENT, args_1);
      res = evaluate_cond(args_1);
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(CDR)) {
      args_1 = eval_argument(s.$2$());
      push(ARGUMENT, args_1);
      res = args_1.cdr();
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(ATOM)) {
      args_1 = eval_argument(s.$2$());
      push(ARGUMENT, args_1);
      res = args_1.atom() ? T : NIL;
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(EVAL)) {
      args_1 = eval_argument(s.$2$());
      push(ARGUMENT, args_1);
      res = args_1.eval();
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(ERROR)) {
      if (! s.less2()) {
          args_1 = eval_argument(s.$2$());
      }
      push(ARGUMENT, args_1);
      return s.error(args_1); // throw
  }
  if (f.eq(NULL)) {
      args_1 = eval_argument(s.$2$());
      push(ARGUMENT, args_1);
      res = args_1.null() ? T : NIL;
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(QUOTE)) {
      args_1 = s.cdr();
      push(ARGUMENT, args_1);
      res = args_1.car();
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(NLAMBDA) || f.eq(LAMBDA)) {
      S f_type = f.eq(NLAMBDA) ? NLAMBDA : LAMBDA;
      args_1 = s.$2$();
      args_2 = s.$3$();
      push(ARGUMENT, args_1);
      push(ARGUMENT, args_2);
      res = list(f_type, s.$2$(), s.$3$());
      remove_element(ARGUMENT);
      remove_element(ARGUMENT);
      return res;
  }
  if (f.eq(NDEFUN) || f.eq(DEFUN)) {
      args_1 = s.$2$();
      args_2 = s.$3$();
      args_3 = s.$4$();
      push(ARGUMENT, args_1);
      push(ARGUMENT, args_2);
      push(ARGUMENT, args_3);
      if (f.eq(NDEFUN)) {
          ndefun(args_1, args_2, args_3);
      } else {
          defun(args_1, args_2, args_3);
      }
      remove_element(ARGUMENT);
      remove_element(ARGUMENT);
      remove_element(ARGUMENT);
      return args_1;
  }
  return bug(s);
}

S apply(S lambda, S body, S formals, S actuals) {
  push(ARGUMENT, actuals);
  const auto arguments =
    lambda.eq(NLAMBDA) ? actuals :
    lambda.eq(LAMBDA) ? materialize(actuals) :
    lambda.cons(actuals).error(INVALID)
  ;
  remove_element(ARGUMENT);
  alist() = bind(formals, arguments, alist());
  push(ARGUMENT, actuals);
  const auto result = body.eval();
  remove_element(ARGUMENT);
  remove_local_binding(formals);
  return result;
}

S apply(S lambda, S actuals) {
  lambda.n3() || lambda.cons(actuals).error(INVALID).t();
  return apply(lambda.$1$(), lambda.$3$(), lambda.$2$(), actuals);
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
       push(RESCUE, s.car());
       res = evaluate_atomic_function(s);
       remove_element(RESCUE);
       D(s, res);
      } else {
       S f_name = s.car();
       S f_body = s.car().eval();
       push(RESCUE, f_name);
       res = apply_defined_function(f_body, s.cdr());
       remove_element(RESCUE);
       D(s, res);
      }
    }
    D(s,res);
    dec_eval_counter();
    if (get_eval_counter() == 0) reset_set_counter();
    return res;
}
