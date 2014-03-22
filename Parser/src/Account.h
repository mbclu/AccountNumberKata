/*
 * AccountNumber.h
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */

#include <vector>
#include <string>
#include "../contrib/gtest/gtest.h"

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

namespace accounts {

// Structure that contains all of the digit strings
struct Digits {
	static const unsigned int TOTAL_DIGITS = 10;
	static const int ACCOUNT_DIGIT_INVALID;
	static const char * DIGIT_STRINGS[];
};

// Structure for a single digit of the account number
struct AccountDigit {
public:
	static const unsigned int ACCOUNT_DIGIT_STRING_LENGTH;

	bool isValid() {
		return (stringValue.length() == ACCOUNT_DIGIT_STRING_LENGTH
				&& stringValue.find_first_not_of(" _|") == std::string::npos);
	}
	std::string getStringValue() {
		return stringValue;
	}
	void setStringValue(std::string value) {
		stringValue = value;
	}

private:
	std::string stringValue;
};

// Container for the entire account number
typedef std::vector<AccountDigit> AccountNumber;

class Account {
	friend class AccountTest;
	FRIEND_TEST(AccountTest, AccountNumberDecodesValues);

protected:
	AccountNumber accountNumber;
	bool possibleDigits[Digits::TOTAL_DIGITS];

public:
	static const unsigned int ACCOUNT_LENGTH;

	Account();
	virtual ~Account();

	void resetPossibleDigits();
	AccountNumber getAccountNumber();
	void assignAccountNumber(std::string accountString);
	int getAccountNumberDigitValue(unsigned int digitIndex, unsigned int charIndex);
	bool assignAccountNumberDigit(unsigned int index, std::string digitString);
	std::string printAccountNumber();
	std::string appendAccountNumberStatus(std::string);
	int calcAccountNumberChecksum();
};

} /* namespace accounts */

#endif /* ACCOUNT_H_ */
