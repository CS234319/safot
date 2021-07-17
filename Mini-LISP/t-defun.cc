#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

/**
 * Tests of defun/ndefun
 */


static S a("a");
static S b("b");
static S c("b");
static S x("y");
static S y("y");
static S z("z");
static S a4("BAR");

extern S defun(S name, S parameters, S body);
extern S ndefun(S name, S parameters, S body);
extern S apply(S f, S args);

TEST(Defun, Empty) {
    S f = defun(a4, NIL, NIL);
    EXPECT_EQ(apply(f, NIL).eval(), NIL);
}

TEST(NDefun, ReturnEmptyList) {
    S f = ndefun(a4, list(x, y), list());
    EXPECT_EQ(apply(f, list(a, b)), list());
}

TEST(NDefun, ReturnSameAtom) {
    S f = ndefun(a4, list(x, y), z.q());
    EXPECT_EQ(apply(f, list(a, b)), z);
}

TEST(NDefun, ReturnID) {
    S f = ndefun(a4, list(x), x);
    EXPECT_EQ(apply(f, list(a)), a);
}

TEST(NDefun, Car3) {
    S f = ndefun(a4, list(x, y, z), x);
    EXPECT_EQ(apply(f, list(a, b, c)), a);
}

TEST(NDefun, Rac3) {
    S f = ndefun(a4, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(a, b, c)), c);
}

TEST(NDefun, CarFirst) {
    S f = ndefun(a4, list(x, y), list(CAR, x));
    EXPECT_EQ(apply(f, list(list(a,b), c)), a);
}

TEST(NDefun, CarLast) {
    S f = ndefun(a4, list(x, y), list(CAR, y));
    EXPECT_EQ(apply(f, list(c, list(a,b))), a);
}

TEST(NDefun, Swap) {
    S f = ndefun(a4, list(x, y), list(CONS, y, x));
    EXPECT_EQ(apply(f, list(a, b)), b.cons(a));
}

TEST(NDefun, Set) {
    S f = ndefun(a4, list(x, y), list(SET, x, y));
    EXPECT_EQ(apply(f, list(a, b)), b);
}

TEST(NDefun, SetAndCar) {
    S f = ndefun(a4, list(x, y), list(SET, x.q(), list(CAR, y)));
    EXPECT_EQ(apply(f, list(a, list(b, c))), b);
}

TEST(Defun, LambdaIdCar) {
    S f = defun(a4, list(x), x);
    EXPECT_EQ(apply(f, list(CAR.cons(list(list(a,b).q())))), a);
}

TEST(Defun, LambdaRac3QuoteEval) {
    S f = defun(a4, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(a.q(), b.q(), c.q())), c);
}

TEST(Defun, LambdaRac3CarFirstEval) {
    S f = defun(a4, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(CAR.cons(list(list(a, NIL).q())), b.q(), c.q())), c);
}

TEST(Defun, LambdaRac3CarLastEval) {
    S f = defun(a4, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(a.q(), b.q(), CAR.cons(list(list(c, NIL).q())))), c);
}

TEST(NDefun, Mirror) {
    S f = ndefun(a4, list(x), list(CONS, list(CDR, x), list(CAR, x)));
    EXPECT_EQ(apply(f, list(a.cons(b))), b.cons(a));
}
