/*
 * GtestFrameworkTest.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */

#include "../contrib/gtest/gtest.h"

TEST(FrameworkTest, BasicAsserts) {
	// Simple test to make sure the project and the google test framework are setup correctly
	// Test that the true and false assertions return the expected value.
	ASSERT_TRUE(true);
	ASSERT_FALSE(false);
}

TEST(FrameworkTest, BasicExpects) {
	// Simple test to make sure the project and the google test framework are setup correctly
	// Test that the true and false assertions return the expected value.
	EXPECT_TRUE(true);
	EXPECT_FALSE(false);
}

TEST(FrameworkTest, BinaryAsserts) {
	// Simple test to make sure the project and google test framework are setup and the
	// Binary assertions
	const int one = 1;
	const int two = 2;
	ASSERT_EQ(1, one);
	ASSERT_NE(one, two);
	ASSERT_LT(one, two);
	ASSERT_LE(one, two);
	ASSERT_LE(one, 1);
	ASSERT_GT(two, one);
	ASSERT_GE(two, one);
	ASSERT_GE(two, 2);
}

TEST(FrameworkTest, StringAsserts) {
	// Simple test to make sure the project and google test framework are setup and the
	const char empty[] = "";
	const char hello[] = "hello";
	const char goodbye[] = "goodbye";
	ASSERT_STREQ(hello, "hello");
	ASSERT_STRNE(NULL, empty);
	ASSERT_STRCASEEQ("HELLO", hello);
	ASSERT_STRCASENE(hello, goodbye);
}
