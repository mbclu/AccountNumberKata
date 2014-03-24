/*
 * AccountDigit.h
 *
 *  Created on: Mar 23, 2014
 *      Author: Mitch
 */
#include <string>

#ifndef ACCOUNTDIGIT_H_
#define ACCOUNTDIGIT_H_

namespace accounts {

// Structure that contains all of the digit strings
struct Digits {
	static const unsigned int TOTAL_DIGITS = 10;
	static const int ACCOUNT_DIGIT_INVALID;
	static const char * DIGIT_STRINGS[];
};

// Class for a single digit of the account number
class AccountDigit {
public:
	static const unsigned int ACCOUNT_DIGIT_STRING_LENGTH;

	AccountDigit();
	virtual ~AccountDigit();

	void resetPossibleDigits();
	bool isValid();
	std::string getRawStringValue();
	void setRawStringValue(std::string value);
	int getNumericValue();
	void setNumericValue(int number);

private:
	bool possibleDigits[Digits::TOTAL_DIGITS];
	std::string stringValue;
	int numericValue;

	int assignAccountNumberDigitValue(unsigned int charIndex);
};

} /* namespace accounts */

#endif /* ACCOUNTDIGIT_H_ */
