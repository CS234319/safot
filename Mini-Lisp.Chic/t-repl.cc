#include "test.h"
#undef function

#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include "repl.h"
#include "builtin.h"
#include "recorder.h"
#include "read.h"

static int REPL(const char *s) { inject(s); REPL(); }

TEST(REPL, Sanity0) { REPL("(cons 'x 'y)"); }
TEST(REPL, Sanity1) { EXPECT_TRUE(REPL("(cons 'x 'y)")); }
String output() { return Recorder::stdout.playback(); }
String error() { return Recorder::stderr.playback(); }
/**
 * Tests of REPL
 */

#define EXPECT_STDOUT(send,expected) { Recorder::stdout.reset(); REPL(send); EXPECT_STRCASEEQ(output(), expected); }
#define EXPECT_STDERR(send,expected) { Recorder::stderr.reset(); REPL(send); EXPECT_STRCASEEQ(error(), expected); }

TEST(test_REPL, EmptyList)   EXPECT_STDOUT("()", ">NIL\n>")
TEST(test_REPL, Nil0)        EXPECT_STDOUT("NIL" , ">NIL\n>")
TEST(test_REPL, Nil1)        EXPECT_STDOUT("T" , ">NIL\n>")
TEST(test_REPL, StdoutCar)   EXPECT_STDOUT("(CAR '(A B))", ">A\n");
TEST(test_REPL, StdoutCdr)   EXPECT_STDOUT("(CDR '(A B))", "(B)\n");
TEST(test_REPL, StdoutAtom)  EXPECT_STDOUT("(atom 'T)",  "T\n");
TEST(test_REPL, StdoutDefun) EXPECT_STDOUT("(defun f (xxx) (car 'x))","(LAMBDA (xxx) (CAR 'X))\n")
TEST(test_REPL, ZCar0)       EXPECT_STDOUT("(defun zcar(xxx) (cond ((atom x) x) (t (car x))))", "(LAMBDA (xxx) (CAR 'X))\n") 

TEST(test_REPL, StderrCar)   EXPECT_STDERR("(car 'a)", "Error CAR on A\n")
TEST(test_REPL, StderrCdr)   EXPECT_STDERR("(cdr 'a)", "Error CDR on A\n")
TEST(test_REPL, StderrDefun) EXPECT_STDERR("(defun fun x y z)", "Error REDUNDANT ARGUMENT(S) on (Z)\n")
TEST(test_REPL, StderrCons)  EXPECT_STDERR("(defun fun x y z)", "Error REDUNDANT ARGUMENT(S) on ('Z)\n")
TEST(test_REPL, StderrCons1) EXPECT_STDERR("x(cons 'x 'y 'z)", "Error: REDUNDANT ARGUMENT(S) on ('Z)\n")
TEST(test_REPL, StderrEval)  EXPECT_STDERR("(eval 'a 'a)", "Error REDUNDANT ARGUMENT(S) on ('A)\n")
TEST(test_REPL, StderrErr1)  EXPECT_STDERR("(eval 'a 'a)", "Error REDUNDANT ARGUMENT(S) on ('A)\n")
TEST(test_REPL, StderrErr2)  EXPECT_STDERR("(error 'msg)", "Error MISSING ARGUMENTS(S) on (..2)\n")

TEST(REPL, Deep) {
    S x("x");
    S y("y");
    S z("z");
    S a(UNIQUE);
    S b(UNIQUE);
    S c(UNIQUE);
    S f(__FUNCTION__);
    ndefun(f,list(a,b), list(a, b, list(CAR,a)));

    S l1 = list(CONS, x, list(f, T));
    l1 = list(CONS, l1, l1); 
    l1 = list(CONS, l1, l1); 

    S what = list(CONS, list(CONS,T,list(CONS,T,list(CONS,NIL,list(f,a,b)))));
    EXPECT_EXCEPTION(what.eval(), list(__2), MISSING_ARGUMENT);
}
