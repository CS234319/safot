#include "test.h"
#undef function

#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include "recorder.h"


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
