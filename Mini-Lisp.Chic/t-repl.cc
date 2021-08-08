#include "recorder.h"
#include "test.h"
#undef function

#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include "repl.h"

TEST(Empty, Empty) {
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

// ****************************
// Tests: STDOUT

TEST(REPL, StdoutNil) {
    string expr = "()";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
        output,
        "> NIL\n"
    );
}

TEST(REPL, StdoutCar) {
    string expr = "(CAR '(A B))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
        "> A\n"
    );
}

TEST(REPL, StdoutCdr) {
    string expr = "(CDR '(A B))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
    "> (B)\n"
    );
}

TEST(REPL, StdoutAtom) {
    string expr = "(atom 'T)";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
    "> T\n"
    );
}

TEST(REPL, StdoutDefun) {
    string expr = "(defun f (recorder) (car 'x))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
    "> F\n"
    );
}

TEST(REPL, StdoutNdefun) {
    string expr = "(ndefun f (recorder) x)";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
    "> F\n"
    );
}

TEST(REPL, StdoutZcar) {
    string expr = "(defun zcar(recorder) (cond ((atom x) x) (t (car x))))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
    "> ZCAR\n"
    );
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
    EXPECT_EQ(output,"Error: kind = A Where = CAR\n");
}

TEST(REPL, StderrCdr) {
    string expr = "(cdr 'a)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output,"Error: kind = A Where = CDR\n");
}

TEST(REPL, StderrDefun) {
    string expr = "(defun fun x y z)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output,"Error: kind = (DEFUN FUN X Y Z) Where = REDUNDANT\n");
}

TEST(REPL, StderrCons) {
    string expr = "(cons 'x 'y 'z)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output,"Error: kind = (CONS (QUOTE X) (QUOTE Y) (QUOTE Z)) Where = REDUNDANT\n");
}

TEST(REPL, StderrEval) {
    string expr = "(eval 'a 'a)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output,"Error: kind = (EVAL (QUOTE A) (QUOTE A)) Where = REDUNDANT\n");
}

TEST(REPL, StderrError) {
    string expr = "(error 'msg)";
    testing::internal::CaptureStderr(); close_stdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStderr(); open_stdout();
    EXPECT_EQ(output,"Error: kind = (ERROR (QUOTE MSG)) Where = MSG\n");
}
