/*
 * AccountDigit.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: Mitch
 */
/* ACCOUNT DIGIT SECTION */
#include "AccountDigit.h"

namespace accounts {

// Constant member for account digit value length
const unsigned int AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH = 9;
// Constant Digits member indicating that an account number digit is invalid
const int Digits::ACCOUNT_DIGIT_INVALID = -1;
// Constant member for account digits string values
const char * Digits::DIGIT_STRINGS[] = {
		" _ "
		"| |"
		"|_|",
		"   "
		"  |"
		"  |",
		" _ "
		" _|"
		"|_ ",
		" _ "
		" _|"
		" _|",
		"   "
		"|_|"
		"  |",
		" _ "
		"|_ "
		" _|",
		" _ "
		"|_ "
		"|_|",
		" _ "
		"  |"
		"  |",
		" _ "
		"|_|"
		"|_|",
		" _ "
		"|_|"
		" _|" };

AccountDigit::AccountDigit() {
	stringValue = "";
	numericValue = -1;
	resetPossibleDigits();
}

AccountDigit::~AccountDigit() {
}

void AccountDigit::resetPossibleDigits() {
	for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
		possibleDigits[i] = true;
	}
}

std::string AccountDigit::getRawStringValue() {
	return stringValue;
}

void AccountDigit::setRawStringValue(std::string value) {
	stringValue = value;
	resetPossibleDigits();
	if (true == isValid()) {
		setNumericValue(assignAccountNumberDigitValue(0));
	}
}

int AccountDigit::getNumericValue() {
	return numericValue;
}

void AccountDigit::setNumericValue(int number) {
	numericValue = number;
}

bool AccountDigit::isValid() {
	return (stringValue.length() == ACCOUNT_DIGIT_STRING_LENGTH
			&& stringValue.find_first_not_of(" _|") == std::string::npos);
}

// AccountDigit method to interpret the value of a number in the account
int AccountDigit::assignAccountNumberDigitValue(unsigned int charIndex) {
	int retValue = Digits::ACCOUNT_DIGIT_INVALID;	// Chose an invalid number to start

	if (charIndex < AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH) {
		// Pre-Recursion
		// Check if the number is still a possibility and then validate this character
		for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
			if (possibleDigits[i] != false) {
				if (stringValue[charIndex] != Digits::DIGIT_STRINGS[i][charIndex]) {
					possibleDigits[i] = false;
				}
			}
		}

		// Call this function recursively until we reach the end of the string
		while (assignAccountNumberDigitValue(++charIndex) > 0);

		// Post-Recursion
		// Change the return value to the true one
		for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
			if (possibleDigits[i] == true) {
				retValue = i;
				break;
			}
		}
	}

	return retValue;
}

} /* namespace accounts */
