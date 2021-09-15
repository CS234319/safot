#include "recorder.h"
#include "test.h"
#undef function

#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include "repl.h"

TEST(REPL, Sanity) {
    REPL("(cons 'x 'y 'z)");
}

struct RecorderTest: ::testing::Test {
  Recorder recorder;
};

TEST_F(RecorderTest, Exists) {
  EXPECT_EQ(recorder.tape,(void *) 0);
  EXPECT_EQ(recorder.length,0);
}

TEST_F(RecorderTest, Start) {
  recorder.start();
  EXPECT_NE(recorder.tape,(void *)0);
  EXPECT_EQ(recorder.length,0);
}

TEST_F(RecorderTest, NoStartWrite) {
  recorder.record("A");
  EXPECT_EQ(recorder.tape,(void *)0);
  EXPECT_EQ(recorder.length,0);
}
TEST_F(RecorderTest, EmptyCheckContents) {
  recorder.record("Hello");
  EXPECT_EQ(0, recorder.playback());
  EXPECT_EQ(recorder.tape,(void *)0);
  EXPECT_EQ(recorder.length,0);
}

TEST_F(RecorderTest, CharacterWrite) {
  recorder.start();
  recorder.record("A");
  EXPECT_EQ(recorder.length,1);
  EXPECT_NE((void *)0, recorder.playback());
  EXPECT_STREQ(reinterpret_cast<char *>(recorder.tape),"A");
}

TEST_F(RecorderTest, HelloWrite) {
  recorder.start();
  recorder.record("Hello");
  EXPECT_EQ(recorder.length,5);
  EXPECT_NE((void *)0, recorder.playback());
  EXPECT_STREQ(reinterpret_cast<char *>(recorder.tape),"Hello");
}

TEST_F(RecorderTest, WriteContents1) {
  recorder.start();
  recorder.record("z");
  EXPECT_STREQ("z", recorder.playback());
}

TEST_F(RecorderTest, WriteContents2) {
  recorder.start();
  recorder.record("CAKE");
  EXPECT_STREQ("CAKE", recorder.playback());
}

TEST_F(RecorderTest, WriteTwice) {
  recorder.record("A B ");
  recorder.record("C D");
}

TEST_F(RecorderTest, StartWriteTwice) {
  recorder.start();
  recorder.record("A B ");
  recorder.record("C D");
}

TEST_F(RecorderTest, Concatenate) {
  recorder.start();
  recorder.record(" BABE");
  recorder.record(" CAFE");
  recorder.record(" DEAD");
  EXPECT_STREQ(" BABE CAFE DEAD", recorder.playback());
  EXPECT_EQ(recorder.length, strlen(" BABE CAFE DEAD"));
}

TEST_F(RecorderTest, CorrectStart) {
  recorder.record(" BABE");
  recorder.start();
  recorder.record(" CAFE");
  recorder.record(" DEAD");
  EXPECT_STREQ(" CAFE DEAD", recorder.playback());
}

/**
 * Tests of REPL
 */

using namespace std;

string output() {
    return testing::internal::GetCapturedStdout();
}

TEST(REPL, quick) {
    string expr = "()\n";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    EXPECT_EQ(output(), "> NIL\n");
}

// ****************************
// Tests: STDOUT

TEST(REPL, StdoutNil) {
    string expr = "()";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    EXPECT_EQ(
        output(),
        "> NIL\n"
    );
}

TEST(REPL, StdoutCar) {
    string expr = "(CAR '(A B))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    EXPECT_EQ(
            output(),
        "> A\n"
    );
}

TEST(REPL, StdoutCdr) {
    string expr = "(CDR '(A B))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    EXPECT_EQ(output(), "> (B)\n");
}

TEST(REPL, StdoutAtom) {
    string expr = "(atom 'T)";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    EXPECT_EQ(
            output(),
    "> T\n"
    );
}

TEST(REPL, StdoutDefun) {
    string expr = "(defun f (recorder) (car 'x))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    auto out = output(); 
    auto expected = "> (LAMBDA (RECORDER) (CAR 'X))\n";
    EXPECT_STRCASEEQ(expected,out.c_str());
}
TEST(REPL, ZCar0) {
    testing::internal::CaptureStdout();
    REPL(string("(defun zcar(recorder) (cond ((atom x) x) (t (car x))))").c_str());
    EXPECT_STRCASEEQ(output().c_str(), "> (lambda (recorder) (cond ((atom x) x) (t (car x))))\n");
}


TEST(REPL, ZCar1) {
    string expr = ("(defun zcar(recorder) (cond ((atom x) x) (t (car x))))");
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    EXPECT_STRCASEEQ(output().c_str(), "> (lambda (recorder) (cond ((atom x) x) (t (car x))))\n");
}

TEST(REPL, StdoutZcar) {
    testing::internal::CaptureStdout();
    string expr = "(defun zcar(recorder) (cond ((atom x) x) (t (car x))))";
    REPL(expr.c_str());
    const char *expected = "> (LAMBDA (RECORDER) (cond ((atom x) x) (t (car x))))\n";
    EXPECT_STRCASEEQ(output().c_str(), expected);
}


// ****************************
// Helper functions for stderr:
static int stdout_copy;
static int dev_null;

void close_stdout() {
    dev_null = open("/dev/null", O_WRONLY);
    stdout_copy = dup(STDOUT_FILENO);
    dup2(dev_null, STDOUT_FILENO);
}

void open_stdout() {
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdout_copy);
    close(dev_null);
}

// ****************************
// Tests: STDERR

TEST(REPL, StderrCar) {
    string expr = "(car 'a)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output,"Error CAR on A\n");
}

TEST(REPL, StderrCdr) {
    string expr = "(cdr 'a)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output,"Error CDR on A\n");
}

TEST(REPL, StderrDefun) {
    string expr = "(defun fun x y z)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output, "Error REDUNDANT ARGUMENT(S) on (Z)\n");
}

TEST(REPL, StderrCons) {
    // testing::internal::CaptureStderr(); close_stdout();
    REPL("(cons 'x 'y 'z)");
    // string output = testing::internal::GetCapturedStderr(); open_stdout();
    // EXPECT_EQ(output, "Error REDUNDANT ARGUMENT(S) on (Z)\n");
}

TEST(REPL, StderrCons1) {
  return;
    string expr = "x(cons 'x 'y 'z)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
//   string temp(testing::internal::GetCapturedStderr());
//    EXPECT_STREQ(temp.c_str(),"Error: REDUNDANT ARGUMENT(S) on ('Z)\n");
}

TEST(REPL, StderrEval) {
    string expr = "(eval 'a 'a)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr().c_str(); open_stdout();
   EXPECT_STRCASEEQ (output.c_str(),"Error: REDUNDANT ARGUMENT(S) on ('A)\n");
}

TEST(REPL, StderrError) {
    string expr = "(error 'msg)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    auto output = testing::internal::GetCapturedStderr().c_str(); open_stdout();
EXPECT_STRCASEEQ    (output,"Error: MISSING_ARGUMENT(S) on ( Y)\n");
}

extern S defun(S name, S parameters, S body);
extern S ndefun(S name, S parameters, S body);

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
    EXPECT_EQ(what,T);
    EXPECT_EXCEPTION(what.eval(), list(z), REDUNDANT_ARGUMENT);
}

