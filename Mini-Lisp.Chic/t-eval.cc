#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

/**
 * Tests of eval function
 */

static S a("a");
static S b("b");
static S c("c");
static S x("x");
static S y("y");
static S z("z");

static S a4("BAR");

S expr("");
S f("fun");

extern S eval(S s);
extern S defun(S name, S parameters, S body);
extern S ndefun(S name, S parameters, S body);


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
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
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
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
}

static S identity() { static S _ = ndefun(f, list(x), x); return _; }


static S invoke(S f, S arguments) { return f.cons(arguments).eval(); }

TEST(Eval, Identity0) { EXPECT_EQ(invoke(identity(), list(a)), a); }
TEST(Eval, Identity1) { EXPECT_EQ(invoke(identity(), list(x.cons(y))), x.cons(y)); }
TEST(Eval, Identity2) { EXPECT_EQ(invoke(identity(), list(list(a,b,c))), list(a,b,c)); }
TEST(Eval, Identity3) { EXPECT_EQ(invoke(identity(), list(list(CAR, CDR))), list(CAR, CDR)); }
TEST(Eval, Identity4) { EXPECT_EXCEPTION(invoke(identity(), list(a, b)), list(b), REDUNDANT); }
TEST(Eval, Identity5) { EXPECT_EXCEPTION(invoke(identity(), list()), list(x), MISSING); }

TEST(Eval, Car3) {
    // Define the function: "(ndefun f (x y z) x)"
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
    EXPECT_EXCEPTION(expr.eval(), list(z), MISSING);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y, z), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
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
    EXPECT_EXCEPTION(expr.eval(), list(z), MISSING);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y, z), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
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
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
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
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
}

TEST(Eval, Swap) {
    // Define the function: "(ndefun f (x y) (cons y x))"
    ndefun(f, list(x, y), list(CONS, y, x));

    // Check different evaluations:
    expr = f.cons(list(list(a, b), c));
    EXPECT_EQ(expr.eval(), c.cons(list(a,b)));
    expr = f.cons(list(list(x, y), z));
    EXPECT_EQ(expr.eval(), z.cons(list(x, y)));
    expr = f.cons(list(list(CAR, CDR), a));
    EXPECT_EQ(expr.eval(), a.cons(list(CAR, CDR)));
    expr = f.cons(list(list(a, b, c, x, y, z), c));
    EXPECT_EQ(expr.eval(), c.cons(list(a, b, c, x, y, z)));

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y) , MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
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
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
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
    EXPECT_EXCEPTION(expr.eval(), list(c), REDUNDANT);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
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
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), c, UNDEFINED);
    expr = f.cons(list());
    EXPECT_EXCEPTION(expr.eval(),list(x) , MISSING);
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

    // Check evaluation errors:
    expr = f.cons(list(a,b,c));
    EXPECT_EXCEPTION(expr.eval(), c, UNDEFINED);
    expr = f.cons(list(a));
    EXPECT_EXCEPTION(expr.eval(), list(y, z), MISSING);
}

TEST(Eval, LambdaRac3CarFirstEval) {
    // Define the function: "(defun f (x y z) z)"
    defun(f, list(x, y, z), z);

    // Check evaluation errors:
    expr = f.cons(list(CAR.cons(list(list(a, NIL).q())), b.q(), c.q()));
    EXPECT_EQ(expr.eval(), c);
}

TEST(Eval, LambdaRac3CarLastEval) {
    // Define the function: "(defun f (x y z) z)"
    defun(f, list(x, y, z), z);

    // Check evaluation errors:
    expr = f.cons(list(a.q(), b.q(), CAR.cons(list(list(c, NIL).q()))));
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
    EXPECT_EXCEPTION(expr.eval(), list(b,c), REDUNDANT);
    expr = f.cons(list());
    EXPECT_EXCEPTION(expr.eval(), list(x), MISSING);
    expr = f.cons(f);
    EXPECT_EXCEPTION(expr.eval(), f, CAR);
}
