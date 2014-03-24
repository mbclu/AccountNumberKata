/*
 * AccountNumber.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */

#include <iostream>
#include "Account.h"

namespace accounts {

// Constant member for account length
const unsigned int Account::ACCOUNT_LENGTH = 9;

/* ACCOUNT SECTION */
// Account Constructor
Account::Account() {
	accountNumberDigits.reserve(Account::ACCOUNT_LENGTH);
	for (unsigned int i = 0; i < Account::ACCOUNT_LENGTH; ++i) {
		accountNumberDigits.push_back(AccountDigit());
	}
	checksum = -1;
}

// Account Destructor
Account::~Account() {
}

// Account class method to get the entire account number
AccountNumber Account::getAccountNumber() {
	return accountNumberDigits;
}

// Take the account number as it is expected from the file and create an account number
void Account::assignRawAccountNumber(std::string accountString) {
	for (unsigned int i = 0; i < Account::ACCOUNT_LENGTH; ++i) {
		accountNumberDigits[i].setRawStringValue (
				accountString.substr(i * 3, 3) +
				accountString.substr((i * 3) + (Account::ACCOUNT_LENGTH * 3), 3) +
				accountString.substr((i * 3) + (Account::ACCOUNT_LENGTH * 6), 3));
	}
	// Make sure to set the checksum value as well
	calcAccountNumberChecksum();
}

std::string Account::printAccountNumber(bool showStatus) {
	int digit = -1;
	std::string retString = "";
	for (unsigned int i = 0; i < Account::ACCOUNT_LENGTH; ++i) {
		digit = accountNumberDigits[i].getNumericValue();
		if (-1 == digit) {
			retString += '?';
		} else {
			retString += ('0' + digit);
		}
	}
	if (true == showStatus) {
		if (retString.find_first_of('?') != std::string::npos) {
			retString += " ILL";
		} else if (checksum != 0) {
			retString += " ERR";
		}
	}
	return retString;
}

// Calculates the account number checksum according to the formula
// (d1 + d2 * 2 + d3 * 3 + d4 * 4 + d5 * 5 + d6 *6 + d7 * 7 +d8 * 8 + d9 * 9) % 11 == 0
void Account::calcAccountNumberChecksum() {
	checksum = accountNumberDigits[Account::ACCOUNT_LENGTH - 1].getNumericValue();
	for (int i = Account::ACCOUNT_LENGTH - 2; i >= 0; --i) {
		checksum += (accountNumberDigits[i].getNumericValue() * 2);
	}
	checksum %= 11;
}

} /* namespace accounts */
