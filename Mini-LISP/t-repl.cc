#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include "test.h"
#include "repl.h"

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
    string expr = "(defun f (x) (car 'x))";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
    "> F\n"
    );
}

TEST(REPL, StdoutNdefun) {
    string expr = "(ndefun f (x) x)";
    testing::internal::CaptureStdout();
    REPL(expr.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(
            output,
    "> F\n"
    );
}

TEST(REPL, StdoutZcar) {
    string expr = "(defun zcar(x) (cond ((atom x) x) (t (car x))))";
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
    EXPECT_EQ(output,"Error: kind = (MSG) Where = INVALID\n");
}
