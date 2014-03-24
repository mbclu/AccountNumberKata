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
	ASSERT_TRUE(ad.getRawStringValue().empty());
}

// Test that we can assign a value to an account digit
TEST_F(AccountTest, AccountNumberDigitStringAssignment) {
	assertAccountDigitStringNotEmptyWhenSet(" _  _ ");
}

// Test that account digits are of valid length
TEST_F(AccountTest, AccountNumberDigitStringLengthIsValid) {
	assertAccountDigitStringNotEmptyWhenSet(" _  _ ");
	EXPECT_NE(AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH,
			ad.getRawStringValue().length());
	ASSERT_FALSE(ad.isValid());

	assertAccountDigitStringNotEmptyWhenSet(" _  _  _ ");
	EXPECT_EQ(AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH,
			ad.getRawStringValue().length());
	ASSERT_TRUE(ad.isValid());
}

// Test that account digits are only valid characters
TEST_F(AccountTest, AccountNumberDigitStringCharactersAreValid) {
	assertAccountDigitStringNotEmptyWhenSet("123456789");
	EXPECT_NE(ad.getRawStringValue().find_first_not_of(" _|"), std::string::npos);
	ASSERT_FALSE(ad.isValid());

	assertAccountDigitStringNotEmptyWhenSet(" _     | ");
	EXPECT_EQ(ad.getRawStringValue().find_first_not_of(" _|"), std::string::npos);
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

// Test that invalid account numbers are indicated
TEST_F(AccountTest, AccountNumberBaseCaseInvalid) {
	// Tests that the base case returns something invalid for an invalid digit text
	assertAccountNumberSizeIsNine();
	a0.getAccountNumber()[0].setRawStringValue(" _  _  _ ");
	EXPECT_EQ(Digits::ACCOUNT_DIGIT_INVALID, a0.getAccountNumber()[0].getNumericValue());
}

// Test strings are decoded when assigned to digits using 0 through 9
TEST_F(AccountTest, AccountDigitDecodesValues) {
	// Test 0 - 9
	for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
		ad.setRawStringValue(Digits::DIGIT_STRINGS[i]);
		EXPECT_EQ(i, ad.getNumericValue());
	}
}

// Test that an entire account number can be parsed into the account number
TEST_F(AccountTest, AccountNumberAssignmentIsValid) {
	assertAllZeroIsValidAccountNumber();
}

// Test that we can get print expected account numbers
TEST_F(AccountTest, PrintAccount) {
	assertAllZeroIsValidAccountNumber();
	ASSERT_STREQ("000000000", a0.printAccountNumber(false).c_str());
	std::string accountNumberString =
			std::string  ("    _  _     _  _  _  _  _ ")
			+ std::string("  | _| _||_||_ |_   ||_||_|")
			+ std::string("  ||_  _|  | _||_|  ||_| _|");
	a0.assignRawAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	ASSERT_STREQ("123456789", a0.printAccountNumber(false).c_str());
}

// Test that a check sum is calculated correctly
TEST_F(AccountTest, ChecksumTest) {
	std::string accountNumberString =
			std::string  ("    _  _     _  _  _  _  _ ")
			+ std::string("  | _| _||_||_ |_   ||_||_|")
			+ std::string("  ||_  _|  | _||_|  ||_| _|");
	a0.assignRawAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	a0.calcAccountNumberChecksum();
	ASSERT_EQ(4, a0.checksum);
}

// Test an Illegible number
TEST_F(AccountTest, IllegibleNumberTest) {
	std::string accountNumberString =
			std::string  ("    _  _  _  _  _  _     _ ")
			+ std::string("|_||_|| || ||_   |  |  | _ ")
			+ std::string("  | _||_||_||_|  |  |  | _|");
	a0.assignRawAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	ASSERT_STREQ("49006771? ILL", a0.printAccountNumber(true).c_str());
}

// Test a checksum error when printing number
TEST_F(AccountTest, ChecksumPrintTestWithError) {
	std::string accountNumberString =
			std::string  (" _  _     _  _        _  _ ")
			+ std::string("|_ |_ |_| _|  |  ||_||_||_ ")
			+ std::string("|_||_|  | _|  |  |  | _| _|");
	a0.assignRawAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	EXPECT_STREQ("664371495 ERR", a0.printAccountNumber(true).c_str());

	accountNumberString =
				std::string  (" _  _  _  _  _  _  _  _    ") +
				std::string  ("| || || || || || || ||_   |") +
				std::string  ("|_||_||_||_||_||_||_| _|  |");
	a0.assignRawAccountNumber(accountNumberString);
	assertAccountNumberSizeIsNine();
	EXPECT_STREQ("000000051", a0.printAccountNumber(true).c_str());
}
} /* namespace accounts */
