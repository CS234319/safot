#import  <iostream>
#import  "gtest/gtest.h"
#import  "a-list.h"
#import  "builtin.h"
#import  "test.h"

/**
 * Tests of eval function
 */

static S a("a"), b("b"), c("c"), x("x"), y("y"), z("z");
S expr("");
S f("my-function");
S argument("argument");

using Engine::set;

TEST(Eval, Empty) {
    // Define the function: "(ndefun f (x y) ())"
    ndefun(f, list(x, y), list());
    // Check different evaluations:
    expr = f.cons(list(a, b));
    EXPECT_EQ(expr.eval(), list());
}

TEST(Eval, emptyList0) {
    // Define the function: "(ndefun f (x y) ())"
    ndefun(f, list(x, y), list());
    expr = list(f);
    EXPECT_EXCEPTION(expr.eval(), list(x,y), MISSING_ARGUMENT);
}

TEST(Eval, emptyList1) {
    // Define the function: "(ndefun f (x y) ())"
    ndefun(f, list(x, y), list());
    expr = list(f, f);
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING_ARGUMENT);
}

TEST(Eval, emptyList2) {
    // Define the function: "(ndefun f (x y) ())"
    ndefun(f, list(x, y), list());
    expr = list(f, f, f);
    EXPECT_NIL(expr.eval());
}


TEST(Eval, ReturnEmptyList) { 
    // Define the function: "(ndefun f (x y) ())"
    ndefun(f, list(x, y), list());

    // Check different evaluations:
    expr = f.cons(list(a, b));
    EXPECT_EQ(expr.eval(), list());
    expr = f.cons(list(x, y));
    EXPECT_EQ(expr.eval(), list());
    expr = f.cons(list(list(CAR, CDR), list(a,b)));
    EXPECT_EQ(expr.eval(), list());
    expr = f.cons(list(list(a, b, c), list(a, b, c)));
    EXPECT_EQ(expr.eval(), list());

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING_ARGUMENT);
}

TEST(Eval, Z) { 
  ndefun(f, list(x, y), z.q());
  expr = list(f, a, b);
  CAREFULLY_EXPECT(EQ, expr.eval(), z);
}


TEST(Eval, ReturnSameAtom) { 
    // Define the function: "(ndefun f (x y) 'z)"
    ndefun(f, list(x, y), z.q());

    // Check different evaluations:
    expr = f.cons(list(a, b));
    EXPECT_EQ(expr.eval(), z);
    expr = f.cons(list(x, y));
    EXPECT_EQ(expr.eval(), z);
    expr = f.cons(list(list(CAR, CDR), list(a,b)));
    EXPECT_EQ(expr.eval(), z);
    expr = f.cons(list(list(a, b, c), list(a, b, c)));
    EXPECT_EQ(expr.eval(), z);

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING_ARGUMENT);
}


static S identity() { static S inner = ndefun(S("id"), list(x), x), lookup("id"); return inner; } 
static S invoke(S f, S arguments) { return f.cons(arguments).eval(); }

TEST(Eval, Identity0a) { CAREFULLY_EXPECT(EQ,list(identity(),a).eval(), a); }
TEST(Eval, Identity0b) { CAREFULLY_EXPECT(EQ,invoke(identity(), list(a)), a); }

TEST(Eval, Identity1) {    EXPECT_EQ(invoke(identity(), list(x.cons(y))), x.cons(y)); }
TEST(Eval, Identity2) {     EXPECT_EQ(invoke(identity(), list(list(a,b,c))), list(a,b,c)); }
TEST(Eval, Identity3) {  EXPECT_EQ(invoke(identity(), list(list(CAR, CDR))), list(CAR, CDR)); }
TEST(Eval, Identity4) {   EXPECT_EXCEPTION(invoke(identity(), list(a, b)), list(b), REDUNDANT_ARGUMENT); }
TEST(Eval, Identity5) { EXPECT_EXCEPTION(invoke(identity(), list()), list(x), MISSING_ARGUMENT); }

TEST(Eval, FirstOfThree) { 
    ndefun(f, list(x, y, z), x);
    expr = f.cons(list(a, b, c));
    EXPECT_EQ(expr.eval(), a);
}

TEST(Eval, Car3Long) { 
    // Define the function: "(ndefun f (x y z) x)"
    ndefun(f, list(x, y, z), x);

    // Check different evaluations:
    expr = f.cons(list(a, b, c));
    EXPECT_EQ(expr.eval(), a);
    expr = f.cons(list(x, y, z));
    EXPECT_EQ(expr.eval(), x);
    expr = f.cons(list(list(CAR, CDR), list(a,b), list(x, y)));
    EXPECT_EQ(expr.eval(), list(CAR, CDR));
    expr = f.cons(list(list(a, b, c), list(a, b, c), a));
    EXPECT_EQ(expr.eval(), list(a, b, c));

    // Check evaluation errors:
    expr = f.cons(list(a,b));
    EXPECT_EXCEPTION(expr.eval(), list(z), MISSING_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y, z), MISSING_ARGUMENT);
}

TEST(Eval, Rac3) { 
    // Define the function: "(ndefun f (x y z) z)"
    ndefun(f, list(x, y, z), z);

    // Check different evaluations:
    expr = f.cons(list(a, b, c));
    EXPECT_EQ(expr.eval(), c);
    expr = f.cons(list(x, y, z));
    EXPECT_EQ(expr.eval(), z);
    expr = f.cons(list(list(CAR, CDR), list(a,b), list(x, y)));
    EXPECT_EQ(expr.eval(), list(x, y));
    expr = f.cons(list(list(a, b, c), list(a, b, c), a));
    EXPECT_EQ(expr.eval(), a);

    // Check evaluation errors:
    expr = f.cons(list(a,b));
    EXPECT_EXCEPTION(expr.eval(), list(z), MISSING_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y, z), MISSING_ARGUMENT);
}

TEST(Eval, CarFirst) { 
    // Define the function: "(ndefun f (x y) (car x))"
    ndefun(f, list(x, y), list(CAR, x));

    // Check different evaluations:
    expr = f.cons(list(list(a, b), c));
    EXPECT_EQ(expr.eval(), a);
    expr = f.cons(list(list(x, y), z));
    EXPECT_EQ(expr.eval(), x);
    expr = f.cons(list(list(CAR, CDR), list(a,b)));
    EXPECT_EQ(expr.eval(), CAR);
    expr = f.cons(list(list(a, b, c), list(c)));
    EXPECT_EQ(expr.eval(), a);

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING_ARGUMENT);
}

TEST(Eval, CarLast) { 
    // Define the function: "(ndefun f (x y) (car y))"
    ndefun(f, list(x, y), list(CAR, y));

    // Check different evaluations:
    expr = f.cons(list(c, list(a, b)));
    EXPECT_EQ(expr.eval(), a);
    expr = f.cons(list(z, list(x, y)));
    EXPECT_EQ(expr.eval(), x);
    expr = f.cons(list(list(a,b), list(CAR, CDR)));
    EXPECT_EQ(expr.eval(), CAR);
    expr = f.cons(list(list(c), list(a, b, c)));
    EXPECT_EQ(expr.eval(), a);

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING_ARGUMENT);
}

TEST(Eval, CONSp0) EVAL_EQ(list(CONS, x.q(), y.q()), x.cons(y))

FIXTURE(SetX, Test, "(set 'x 'bar)")
TEST_F(SetX, T0) { EVAL_EQ("x", "bar"); }
TEST_F(SetX, T1) { EVAL_XX("y", "y", UNDEFINED_ATOM); }

FIXTURE(SetY, Test, "(set 'y 'foo)")
TEST_F(SetY, T0) { EVAL_EQ("y", "foo"); }
TEST_F(SetY, T1) { EVAL_XX("x", "x", UNDEFINED_ATOM); }

FIXTURE(Swap, Test, "(ndefun swap(x y) (cons (eval y) (eval x)))")
TEST_F(Swap, T1) { set(x, "foo"); EVAL_EQ("x", "foo"); }
TEST_F(Swap, T2) { set(y, "bar"); EVAL_EQ("y", "bar"); }
TEST_F(Swap, T3) { set(x, "foo"); set(y, "bar"); EVAL_EQ("(swap x y)", "y.x"); }
TEST_F(Swap, T4) { set("u", "foo"); set("v", "bar"); EVAL_EQ("(swap u v)", "bar.foo"); }
TEST_F(Swap, T5) EVAL_XX("(swap a b c)", "(c)", REDUNDANT_ARGUMENT) 
TEST_F(Swap, T6) EVAL_XX("(swap a)", "(y)", MISSING_ARGUMENT) 
TEST_F(Swap, T7) EVAL_EQ("(swap '(a b) 'c)", "(c a b)")

TEST(Eval, Set0) {  
    S foo("foo"), bar("bar");
    set(x, foo );
    set(y, bar);
    EXPECT_EQ(x.eval(), foo);
    EXPECT_EQ(y.eval(), bar);
}

TEST(Eval, Set) { 
    // Define the function: "(ndefun f (x y) (set x y))"
    ndefun(f, list(x, y), list(SET, x, y));

    // Check different evaluations:
    expr = f.cons(list(list(a, b), c));
    EXPECT_EQ(expr.eval(), c);
    expr = f.cons(list(list(x, y), z));
    EXPECT_EQ(expr.eval(), z);
    expr = f.cons(list(z, list(a,b)));
    EXPECT_EQ(expr.eval(), list(a,b));
    expr = f.cons(list(a, list(c)));
    EXPECT_EQ(expr.eval(), list(c));

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING_ARGUMENT);
}

TEST(Eval, SetAndCar) { 
    // Define the function: "(ndefun f (x y) (set 'x (car y)))"
    ndefun(f, list(x, y), list(SET, x.q(), list(CAR, y)));

    // Check different evaluations:
    expr = f.cons(list(c, list(a, b)));
    EXPECT_EQ(expr.eval(), a);
    expr = f.cons(list(z, list(x, y)));
    EXPECT_EQ(expr.eval(), x);
    expr = f.cons(list(z, list(a,b)));
    EXPECT_EQ(expr.eval(), a);
    expr = f.cons(list(a, list(list(c), b)));
    EXPECT_EQ(expr.eval(), list(c));

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT_ARGUMENT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING_ARGUMENT);
}

TEST(Eval, evaluate_all_arguments_before_binding) { 
    // Define the function: "(defun f (x) x)"
    defun(f, list(x), x);
    expr = list(f, T,NIL, c);
    EXPECT_EXCEPTION(expr.eval(), c, UNDEFINED_ATOM);
}

TEST(Eval, LambdaIdCar) { 
    // Define the function: "(defun f (x) x)"
    defun(f, list(x), x);

    // Check evaluation errors:
    expr = f.cons(list(CAR.cons(list(list(a,b).q()))));
    EXPECT_EQ(expr.eval(), a);
    expr = f.cons(list(CAR.cons(list(list(x,y).q()))));
    EXPECT_EQ(expr.eval(), x);
    expr = f.cons(list(CAR.cons(list(list(a.cons(b)).q()))));
    EXPECT_EQ(expr.eval(), a.cons(b));

    // Check evaluation errors:
    expr = f.cons(list());
    EXPECT_EXCEPTION(expr.eval(),list(x) , MISSING_ARGUMENT);
}


TEST(Eval, LambdaRac3QuoteEval) { 
    // Define the function: "(defun f (x y z) z)"
    defun(f, list(x, y, z), z);

    // Check evaluation errors:
    expr = f.cons(list(a.q(), b.q(), c.q()));
    EXPECT_EQ(expr.eval(), c);
    expr = f.cons(list(x.q(), y.q(), z.q()));
    EXPECT_EQ(expr.eval(), z);
    expr = f.cons(list(x.q(), list(y.q(), z.q()).q(), a.q()));
    EXPECT_EQ(expr.eval(), a);
    expr = f.cons(list(list(x.q()).q(), list(y.q()).q(), list(a.q()).q()));
    EXPECT_EQ(expr.eval(), list(a.q()));
}

TEST(Eval, ArgumentEvaluationOrder) { 
    // Define the function: "(defun f (x y z) z)"
  reset();
  defun(f, list(x, y, z), z);
  EXPECT_EXCEPTION(a.eval(), a, UNDEFINED_ATOM);
  EXPECT_EXCEPTION(list(f, a,b,c).eval(), a, UNDEFINED_ATOM);
}


TEST(Eval, DefunMissing) { 
    defun(f, list(x, y, z), z);
    EXPECT_EXCEPTION(list(f,a).eval(), a, UNDEFINED_ATOM);
}

TEST(Eval, LambdaRac3CarFirstEval) { 
    // Define the function: "(defun f (x y z) z)"
    defun(f, list(x, y, z), z);

    // Check evaluation errors:
  S  expr = f.cons(list(CAR.cons(list(list(a, NIL).q())), b.q(), c.q()));
    EXPECT_EQ(expr.eval(), c);
}

TEST(Eval, LambdaRac3CarLastEval) { 
    // Define the function: "(defun f (x y z) z)"
    defun(f, list(x, y, z), z);

    // Check evaluation errors:
   S expr = f.cons(list(a.q(), b.q(), CAR.cons(list(list(c, NIL).q()))));
    EXPECT_EQ(expr.eval(), c);
}

TEST(Eval, Mirror) { 
    // Define the function: "(ndefun f (x) (cons (cdr x) (car x)))"
    ndefun(f, list(x), list(CONS, list(CDR, x), list(CAR, x)));

    // Check different evaluations:
    expr = f.cons(list(a.cons(b)));
    EXPECT_EQ(expr.eval(), b.cons(a));
    expr = f.cons(list(x.cons(y)));
    EXPECT_EQ(expr.eval(), y.cons(x));
    expr = f.cons(list(list(x, y)));
    EXPECT_EQ(expr.eval(), list(y).cons(x));

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(b,c), REDUNDANT_ARGUMENT);
  S  expr = f.cons(list());
    EXPECT_EXCEPTION(expr.eval(), list(x), MISSING_ARGUMENT);
}

TEST(Eval, Variadic) { 
  S f("my function"); 
  ndefun(f, x, list(CONS, y.q(), x)); 
  CAREFULLY_EXPECT(EQ, list(f, a, b, c).eval(), list(y, a, b, c));
}

TEST(EvalError, BAD_ARGUMENTS1) { 
    ndefun(f, list(x, y), list());
    EXPECT_EXCEPTION(list(f, argument).eval(), list(y), MISSING_ARGUMENT);
}

TEST(EvalError, BAD_ARGUMENTS2) { 
    ndefun(f, list(x, y, z), z);
    S  expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}

TEST(EvalError, BAD_ARGUMENTS3) { 
    ndefun(f, list(x, y), z.q());
    S expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}

TEST(EvalError, BAD_ARGUMENTS4) { 
    ndefun(f, list(x, y, z), x);
  S  expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}

TEST(EvalError, BAD_ARGUMENTS5) { 
    ndefun(f, list(x, y), list(CAR, x));
    S expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}

TEST(EvalError, BAD_ARGUMENTS6) { 
    ndefun(f, list(x, y), list(CAR, y));
    S expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}

TEST(EvalError, BAD_ARGUMENTS7) {  
    // Define the function: "(ndefun f (x y) (set x y))"
    ndefun(f, list(x, y), list(SET, x, y));
  S  expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}

TEST(EvalError, BAD_ARGUMENTS8) {  
    // Define the function: "(ndefun f (x y) (set x y))"
    ndefun(f, list(x, y), list(SET, x, y));
    S expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}

TEST(EvalError, BAD_ARGUMENTS9) { 
    // Define the function: "(ndefun f (x y) (set 'x (car y)))"
    ndefun(f, list(x, y), list(SET, x.q(), list(CAR, y)));
    S expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, BAD_ARGUMENTS);
}
