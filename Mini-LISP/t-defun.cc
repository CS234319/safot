#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

/**
 * Tests of defun/ndefun
 */

static S a("a");
static S b("b");
static S c("c");
static S j("j");
static S k("k");
static S m("m");
static S n("n");
static S p("p");
static S x("x");
static S y("y");
static S z("z");

static S a4("BAR");

extern S defun(S name, S parameters, S body);
extern S ndefun(S name, S parameters, S body);
extern S apply(S f, S args);

static S ndefun(S parameters, S body) { return ndefun(S("thingy"), parameters, body); }

TEST(Defun, Empty) { S f = defun(a4, NIL, NIL); EXPECT_EQ(apply(f, NIL).eval(), NIL); }
TEST(Defun, LambdaIdCar) { S f = defun(a4, list(x), x); EXPECT_EQ(apply(f, list(CAR.cons(list(list(a,b).q())))), a); }
TEST(Defun, LambdaRac3CarFirstEval) { S f = defun(a4, list(x, y, z), z); EXPECT_EQ(apply(f, list(CAR.cons(list(list(a, NIL).q())), b.q(), c.q())), c); }
TEST(Defun, LambdaRac3CarLastEval) { S f = defun(a4, list(x, y, z), z); EXPECT_EQ(apply(f, list(a.q(), b.q(), CAR.cons(list(list(c, NIL).q())))), c); }
TEST(Defun, LambdaRac3QuoteEval) { S f = defun(a4, list(x, y, z), z); EXPECT_EQ(apply(f, list(a.q(), b.q(), c.q())), c); }
TEST(NDefun, Car3) { S f = ndefun(list(x, y, z), x); EXPECT_EQ(apply(f, list(a, b, c)), a); }
TEST(NDefun, CarFirst) { S f = ndefun(list(x, y), list(CAR, x)); EXPECT_EQ(apply(f, list(list(a,b), c)), a); }
TEST(NDefun, CarLast1) { S f = ndefun(list(p, j), list(CAR, j)); EXPECT_EQ(apply(f, list(c, list(a,b))), a); }
TEST(NDefun, CarLast2) { S f = ndefun(list(x, y), list(CAR, y)); EXPECT_EQ(apply(f, list(c, list(a,b))), a); }
TEST(NDefun, Mirror) { S f = ndefun(list(x), list(CONS, list(CDR, x), list(CAR, x))); EXPECT_EQ(apply(f, list(a.cons(b))), b.cons(a)); }
TEST(NDefun, Rac3) { S f = ndefun(list(x, y, z), z); EXPECT_EQ(apply(f, list(a, b, c)), c); }
TEST(NDefun, ReturnEmptyList) { S f = ndefun(list(x, y), list()); EXPECT_EQ(apply(f, list(a, b)), list()); }
TEST(NDefun, ReturnID) { S f = ndefun(list(x), x); EXPECT_EQ(apply(f, list(a)), a); }
TEST(NDefun, ReturnSameAtom) { S f = ndefun(list(x, y), z.q()); EXPECT_EQ(apply(f, list(a, b)), z); }
TEST(NDefun, SetAndCar1) { S f = ndefun(list(m, n), list(SET, m.q(), list(CAR, n))); EXPECT_EQ(apply(f, list(a, list(b, c))), b); }
TEST(NDefun, SetAndCar2) { S f = ndefun(list(x, y), list(SET, x.q(), list(CAR, y))); EXPECT_EQ(apply(f, list(a, list(b, c))), b); }
TEST(NDefun, Set1) { S f = ndefun(list(p, y), list(SET, p, y)); EXPECT_EQ(apply(f, list(a, b)), b); }
TEST(NDefun, Set2) { S f = ndefun(list(x, y), list(SET, x, y)); EXPECT_EQ(apply(f, list(a, b)), b); }
TEST(NDefun, Swap1) { S f = ndefun(list(m, n), list(CONS, n, m)); EXPECT_EQ(apply(f, list(z, k)), k.cons(z)); }
TEST(NDefun, Swap2) { S f = ndefun(list(x, y), list(CONS, y, x)); EXPECT_EQ(apply(f, list(a, b)), b.cons(a)); }
