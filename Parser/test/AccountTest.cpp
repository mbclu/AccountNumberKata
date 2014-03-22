/*
 * AccountNumberTest.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */

#include "AccountTest.h"

namespace accounts {

// Test that new account digits strings are empty
TEST_F(AccountTest, AccountNumberDigitStringEmptyInitially) {
	ASSERT_TRUE(ad.getStringValue().empty());
}

// Test that we can assign a value to an account digit
TEST_F(AccountTest, AccountNumberDigitStringAssignment) {
	assertAccountDigitStringNotEmptyWhenSet(" _  _ ");
}

// Test that account digits are of valid length
TEST_F(AccountTest, AccountNumberDigitStringLengthIsValid) {
	assertAccountDigitStringNotEmptyWhenSet(" _  _ ");
	EXPECT_NE(AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH,
			ad.getStringValue().length());
	ASSERT_FALSE(ad.isValid());

	assertAccountDigitStringNotEmptyWhenSet(" _  _  _ ");
	EXPECT_EQ(AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH,
			ad.getStringValue().length());
	ASSERT_TRUE(ad.isValid());
}

// Test that account digits are only valid characters
TEST_F(AccountTest, AccountNumberDigitStringCharactersAreValid) {
	assertAccountDigitStringNotEmptyWhenSet("123456789");
	EXPECT_NE(ad.getStringValue().find_first_not_of(" _|"), std::string::npos);
	ASSERT_FALSE(ad.isValid());

	assertAccountDigitStringNotEmptyWhenSet(" _     | ");
	EXPECT_EQ(ad.getStringValue().find_first_not_of(" _|"), std::string::npos);
	ASSERT_TRUE(ad.isValid());
}

// Test that an account number is not initialized
TEST_F(AccountTest, AccountNumberIsInitialized) {
	assertAccountNumberInitialized();
}

// Test that the account number is capable of storing nine elements
TEST_F(AccountTest, AccountNumberCapacityIsNineOrGreater) {
	assertAccountNumberAdequateCapacity();
}

// Test that the account number has stored nine elements
TEST_F(AccountTest, AccountNumberSizeIsNine) {
	assertAccountNumberSizeIsNine();
}

// Test that only valid index positions can be accessed
TEST_F(AccountTest, AccountNumberAccessLimitedIndexing) {
	assertAccountNumberSizeIsNine();
	ASSERT_FALSE(a0.assignAccountNumberDigit(9, Digits::DIGIT_STRINGS[0]));
	ASSERT_TRUE(a0.assignAccountNumberDigit(0, Digits::DIGIT_STRINGS[0]));
	ASSERT_TRUE(a0.assignAccountNumberDigit(8, Digits::DIGIT_STRINGS[0]));
}

// Test that invalid account numbers are indicated
TEST_F(AccountTest, AccountNumberBaseCaseInvalid) {
	// Tests that the base case returns something invalid for an invalid digit text
	assertAccountNumberSizeIsNine();
	ASSERT_TRUE(a0.assignAccountNumberDigit(0, " _  _  _ "));
	EXPECT_EQ(Digits::ACCOUNT_DIGIT_INVALID,
			a0.getAccountNumberDigitValue(0, 0));
}

// Test that a zero string is decoded digits 0 through 9
TEST_F(AccountTest, AccountNumberDecodesValues) {
	assertAccountNumberSizeIsNine();
	// Test 0 - 9
	for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
		ASSERT_TRUE(a0.assignAccountNumberDigit(0, Digits::DIGIT_STRINGS[i]));
		EXPECT_EQ(i, a0.getAccountNumberDigitValue(0, 0));
		for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
			a0.possibleDigits[i] = true;
		}
	}
}

// Test that an entire account number can be parsed into the account number
TEST_F(AccountTest, AccountNumberAssignmentIsValid) {
	assertAllZeroIsValidAccountNumber();
}

// Test that we can get print expected account numbers
TEST_F(AccountTest, PrintAccount) {
	assertAllZeroIsValidAccountNumber();
	ASSERT_STREQ("000000000", a0.printAccountNumber().c_str());
	std::string accountNumberString =
			std::string  ("    _  _     _  _  _  _  _ ")
			+ std::string("  | _| _||_||_ |_   ||_||_|")
			+ std::string("  ||_  _|  | _||_|  ||_| _|");
	a0.assignAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	ASSERT_STREQ("123456789", a0.printAccountNumber().c_str());
}

// Test that a check sum is calculated correctly
TEST_F(AccountTest, ChecksumTest) {
	std::string accountNumberString =
			std::string  ("    _  _     _  _  _  _  _ ")
			+ std::string("  | _| _||_||_ |_   ||_||_|")
			+ std::string("  ||_  _|  | _||_|  ||_| _|");
	a0.assignAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	ASSERT_EQ(0, a0.calcAccountNumberChecksum());
}

// Test an Illegible number
TEST_F(AccountTest, IllegibleNumberTest) {
	std::string accountNumberString =
			std::string  ("    _  _  _  _  _  _     _ ")
			+ std::string("|_||_|| || ||_   |  |  | _ ")
			+ std::string("  | _||_||_||_|  |  |  | _|");
	a0.assignAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	ASSERT_STREQ("49006771? ILL", a0.appendAccountNumberStatus(a0.printAccountNumber()).c_str());
}

// Test an checksum error when printing number
TEST_F(AccountTest, ChecksumErrorNumberTest) {
	std::string accountNumberString =
			std::string  (" _  _     _  _        _  _ ")
			+ std::string("|_ |_ |_| _|  |  ||_||_||_ ")
			+ std::string("|_||_|  | _|  |  |  | _| _|");
	a0.assignAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	ASSERT_STREQ("664371495 ERR", a0.appendAccountNumberStatus(a0.printAccountNumber()).c_str());
}
} /* namespace accounts */

