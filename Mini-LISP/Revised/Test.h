#ifndef TEST_H
#define TEST_H

#define UNCHIC
#include "chic.h" 
#include <gtest/gtest.h>

#define ASSERT_ZZ(v)  ASSERT_EQ(v,0)
#define ASSERT_TT     ASSERT_TRUE
#define ASSERT_FF     ASSERT_FALSE
#define EXPECT_ZZ(v)  EXPECT_EQ(v,0)
#define EXPECT_TT     EXPECT_TRUE
#define EXPECT_FF     EXPECT_FALSE
#endif
