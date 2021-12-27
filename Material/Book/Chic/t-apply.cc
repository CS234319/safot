#import  <iostream>
#import  "gtest/gtest.h"
#import  "test.h"

#include "eval.h"

SUITE(Apply)

using Engine::apply;
static S a("A"), b("B"), c("C");
static S x("X"), y("Y"), z("Z");

TEST_F(Apply, Empty) {
    S f = list(LAMBDA, NIL, NIL);
    EXPECT_EQ(apply(f, NIL).eval(), NIL);
}

TEST_F(Apply, ReturnEmptyList) {
    S f = list(NLAMBDA, list(x, y), list());
    EXPECT_EQ(apply(f, list(a, b)), list());
}

TEST_F(Apply, ReturnSameAtom) {
    S f = list(NLAMBDA, list(x, y), z.q());
    EXPECT_EQ(apply(f, list(a, b)), z);
}

TEST_F(Apply, ReturnID) {
    S f = list(NLAMBDA, list(x), x);
    EXPECT_EQ(apply(f, list(a)), a);
}

TEST_F(Apply, Car3) {
    S f = list(NLAMBDA, list(x, y, z), x);
    EXPECT_EQ(apply(f, list(a, b, c)), a);
}

TEST_F(Apply, Rac3) {
    S f = list(NLAMBDA, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(a, b, c)), c);
}

TEST_F(Apply, CarFirst) {
    S f = list(NLAMBDA, list(x, y), list(CAR, x));
    EXPECT_EQ(apply(f, list(list(a,b), c)), a);
}

TEST_F(Apply, CarLast) {
    S f = list(NLAMBDA, list(x, y), list(CAR, y));
    EXPECT_EQ(apply(f, list(c, list(a,b))), a);
}

TEST_F(Apply, Swap) {
    S f = list(NLAMBDA, list(x, y), list(CONS, y, x));
    EXPECT_EQ(apply(f, list(a, b)), b.cons(a));
}

TEST_F(Apply, Set) {
    S f = list(NLAMBDA, list(x, y), list(SET, x, y));
    EXPECT_EQ(apply(f, list(a, b)), b);
}

TEST_F(Apply, SetAndCar) {
    S f = list(NLAMBDA, list(x, y), list(SET, x.q(), list(CAR, y)));
    EXPECT_EQ(apply(f, list(a, list(b, c))), b);
}


TEST_F(Apply, LambdaIdCar) {
    S f = list(LAMBDA, list(x), x);
    EXPECT_EQ(apply(f, list(CAR.cons(list(list(a,b).q())))), a);
}

TEST_F(Apply, LambdaRac3QuoteEval) {
    S f = list(LAMBDA, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(a.q(), b.q(), c.q())), c);
}

TEST_F(Apply, LambdaRac3CarFirstEval) {
    S f = list(LAMBDA, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(CAR.cons(list(list(a, NIL).q())), b.q(), c.q())), c);
}

TEST_F(Apply, LambdaRac3CarLastEval) {
    S f = list(LAMBDA, list(x, y, z), z);
    EXPECT_EQ(apply(f, list(a.q(), b.q(), CAR.cons(list(list(c, NIL).q())))), c);
}

TEST_F(Apply, Mirror) {
    S f = list(NLAMBDA, list(x), list(CONS, list(CDR, x), list(CAR, x)));
    EXPECT_EQ(apply(f, list(a.cons(b))), b.cons(a));
}
