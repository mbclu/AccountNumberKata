/*
 * AccountNumber.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */

#include <iostream>
#include "Account.h"

namespace accounts {

// Constant member for account digit value length
const unsigned int AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH = 9;
const int Digits::ACCOUNT_DIGIT_INVALID = -1;
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

// Constant member for account length
const unsigned int Account::ACCOUNT_LENGTH = 9;

// Account Constructor
Account::Account() {
	accountNumber.reserve(Account::ACCOUNT_LENGTH);
	for (unsigned int i = 0; i < Account::ACCOUNT_LENGTH; ++i) {
		accountNumber.push_back(AccountDigit());
	}
	resetPossibleDigits();
}

void Account::resetPossibleDigits() {
	for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
		possibleDigits[i] = true;
	}
}

// Account Destructor
Account::~Account() {
}

// Account class method to get the entire account number
AccountNumber Account::getAccountNumber() {
	return accountNumber;
}

// Take the account number as it is expected from the file and create an account number
void Account::assignAccountNumber(std::string accountString) {
	for (unsigned int i = 0; i < Account::ACCOUNT_LENGTH; ++i) {
		accountNumber[i].setStringValue(
				accountString.substr(i * 3, 3) +
				accountString.substr((i * 3) + (Account::ACCOUNT_LENGTH * 3), 3) +
				accountString.substr((i * 3) + (Account::ACCOUNT_LENGTH * 6), 3));
	}
}

// Account class method to interpret the value of a number in the account
int Account::getAccountNumberDigitValue(unsigned int digitIndex, unsigned int charIndex) {
	int retValue = Digits::ACCOUNT_DIGIT_INVALID;	// Chose an invalid number to start

	if (digitIndex < ACCOUNT_LENGTH && charIndex < AccountDigit::ACCOUNT_DIGIT_STRING_LENGTH) {
		// Pre-Recursion
		// Check if the number is still a possibility and then validate this character
		for (unsigned int i = 0; i < Digits::TOTAL_DIGITS; ++i) {
			if (possibleDigits[i] != false) {
				if (accountNumber[digitIndex].getStringValue().c_str()[charIndex] != Digits::DIGIT_STRINGS[i][charIndex]) {
					possibleDigits[i] = false;
				}
			}
		}

		// Call this function recursively until we reach the end of the string
		while (getAccountNumberDigitValue(digitIndex, ++charIndex) > 0) {
		}

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

// Account class method to add a string value to the account digit at a given index
bool Account::assignAccountNumberDigit(unsigned int index,
		std::string digitString) {
	bool retValue = false;
	if (index < ACCOUNT_LENGTH) {
		accountNumber[index].setStringValue(digitString);
		retValue = accountNumber[index].isValid();
	}
	return retValue;
}

std::string Account::printAccountNumber() {
	int digit = -1;
	std::string retString = "";
	for (unsigned int i = 0; i < Account::ACCOUNT_LENGTH; ++i) {
		digit = getAccountNumberDigitValue(i, 0);
		resetPossibleDigits();
		if (-1 == digit) {
			retString += '?';
		} else {
			retString += ('0' + digit);
		}
	}
	return retString;
}

int Account::calcAccountNumberChecksum() {

}

} /* namespace accounts */
