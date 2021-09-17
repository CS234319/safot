#import  "test.h"
#undef function

#import  <iostream>
#import  <fcntl.h>
#import  <stdio.h>
#import  "gtest/gtest.h"
#import  "repl.h"
#import  "builtin.h"
#import  "recorder.h"
#import  "read.h"

static bool go(const char *s) { inject(s); return REPL(); }
struct REPL: Test { };

TEST(REPL, Sanity0) { go("(cons 'x 'y)"); }
TEST(REPL, Sanity1) { EXPECT_TRUE(go("(cons 'x 'y)")); }
String output() { return Recorder::stdout.playback(); }
String error() { return Recorder::stderr.playback(); }
/**
 * Tests of REPL
 */

#define EXPECT_STDOUT(send,expected) { Recorder::stdout.reset(); go(send); EXPECT_STRCASEEQ(output(), expected); }
#define EXPECT_STDERR(send,expected) { Recorder::stderr.reset(); go(send); EXPECT_STRCASEEQ(error(), expected); }

TEST(REPL, EmptyList)   EXPECT_STDOUT("()", ">NIL\n>")
TEST(REPL, Nil0)        EXPECT_STDOUT("NIL",">NIL\n>")
TEST(REPL, Nil1)        EXPECT_STDOUT("T" , ">T\n>")
TEST(REPL, StdoutCar)   EXPECT_STDOUT("(CAR '(A B))", ">A\n>");
TEST(REPL, StdoutCdr)   EXPECT_STDOUT("(CDR '(A B))", ">(B)\n>");
TEST(REPL, StdoutAtom)  EXPECT_STDOUT("(atom 'T)",  ">T\n>");
TEST(REPL, StdoutDefun) EXPECT_STDOUT("(defun f (xxx) (car 'x))",">(LAMBDA (xxx) (CAR 'X))\n>")
TEST(REPL, ZCar0)       EXPECT_STDOUT("(defun zcar(xxx) (cond ((atom x) x) (t (car x))))", ">(LAMBDA (XXX) (COND ((ATOM X) X) (T (CAR X))))\n>")

TEST(REPL, StderrCar)   EXPECT_STDERR("(car 'a)", "Error CAR on A\n")
TEST(REPL, StderrCdr)   EXPECT_STDERR("(cdr 'a)", "Error CDR on A\n")
TEST(REPL, StderrDefun) EXPECT_STDERR("(defun fun x y z)", "Error REDUNDANT ARGUMENT(S) on (Z)\n")
TEST(REPL, StderrCons)  EXPECT_STDERR("(defun fun x y z)", "Error REDUNDANT ARGUMENT(S) on (Z)\n")
TEST(REPL, StderrCons1) EXPECT_STDERR("(cons 'x 'y 'z)", "Error REDUNDANT ARGUMENT(S) on ('Z)\n")
TEST(REPL, StderrErr1)  EXPECT_STDERR("(eval 'a 'a)", "Error REDUNDANT ARGUMENT(S) on ('A)\n")
TEST(REPL, StderrErr2)  EXPECT_STDERR("(error 'msg)", "Error MISSING ARGUMENTS(S) on (..2)\n")

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
