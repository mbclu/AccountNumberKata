/*
 * AccountNumberTest.h
 *
 *  Created on: Mar 16, 2014
 *      Author: Mitch
 */

#include "../contrib/gtest/gtest.h"
#include "Account.h"

#ifndef ACCOUNTTEST_H_
#define ACCOUNTTEST_H_

namespace accounts {

class AccountTest: public ::testing::Test {
protected:
	AccountTest() {
	}
	virtual ~AccountTest() {
	}
	virtual void SetUp() {
	}
	virtual void TearDown() {
	}

	AccountDigit ad;
	Account a0;

	void assertAccountDigitStringNotEmptyWhenSet(std::string value) {
		ad.setStringValue(value);
		ASSERT_FALSE(ad.getStringValue().empty());
	}

	void assertAccountDigitIsValid(std::string value) {
		assertAccountDigitStringNotEmptyWhenSet(value);
		ASSERT_TRUE(ad.isValid());
	}

	void assertAccountNumberInitialized() {
		ASSERT_FALSE(a0.getAccountNumber().empty());
	}

	void assertAccountNumberAdequateCapacity() {
		assertAccountNumberInitialized();
		ASSERT_GE(a0.getAccountNumber().max_size(), 9);
		ASSERT_GE(a0.getAccountNumber().capacity(), 9);
	}

	void assertAccountNumberSizeIsNine() {
		assertAccountNumberAdequateCapacity();
		ASSERT_EQ(9, a0.getAccountNumber().size());
	}

	void assertAllZeroIsValidAccountNumber() {
		std::string accountNumberString =
				std::string  (" _  _  _  _  _  _  _  _  _ ")
				+ std::string("| || || || || || || || || |")
				+ std::string("|_||_||_||_||_||_||_||_||_|");

		a0.assignAccountNumber(accountNumberString);
		assertAccountNumberSizeIsNine();
		for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
			EXPECT_GE(0, a0.getAccountNumberDigitValue(i, 0));
			EXPECT_LE(a0.getAccountNumberDigitValue(i, 0), 9);
		}
	}

};

} /* namespace accounts */

#endif /* ACCOUNTTEST_H_ */
