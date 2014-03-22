/*
 * AccountFileReader.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: Mitch
 */

#include <cstring>
#include <iostream>
#include "AccountFileReader.h"

namespace accounts {

AccountFileReader::AccountFileReader() {
	currentAccountLine = "";
	currentLineCount = 0;
	currentAccountNumberString = "";
}

AccountFileReader::~AccountFileReader() {
}

Accounts AccountFileReader::getAccounts() {
	return accounts;
}

std::string AccountFileReader::getCurrentAccountLine() {
	return currentAccountLine;
}

unsigned int AccountFileReader::getCurrentLineCount() {
	return currentLineCount;
}

std::string AccountFileReader::getCurrentAccountNumberString() {
	return currentAccountNumberString;
}

// Read in an account file given the name and a file stream to read from
FileReadReturnCode AccountFileReader::readFile(const char * inputFileName) {
	FileReadReturnCode retValue = FILE_READ_RETURN_SUCCESS;
	Account account;
	std::ifstream inFileStream;

	// Reset the line count and make sure the accounts are all emptied
	currentLineCount = 0;
	while (accounts.size() > 0) {
		accounts.pop_back();
	}

	// Check if the file name can be opened
	retValue = openFile(inputFileName, inFileStream);
	while (getline(inFileStream, currentAccountLine)
			&& FILE_READ_RETURN_SUCCESS == retValue) {
		retValue = checkLineGood(currentAccountLine);
		if (FILE_READ_RETURN_SUCCESS == retValue) {

			if (currentLineCount > 0) {
				currentAccountNumberString += currentAccountLine;
			} else {
				account.assignAccountNumber(currentAccountNumberString);
				accounts.push_back(account);
				currentAccountLine = "";
				currentAccountNumberString = "";
			}
		}
	}
	inFileStream.close();
	return retValue;
}

// Try to open the file and return status
FileReadReturnCode AccountFileReader::openFile(const char * fileName,
		std::ifstream& fileStream) {
	FileReadReturnCode retValue = FILE_READ_RETURN_SUCCESS;

	// Check if the file name can be opened
	fileStream.open(fileName);
	if (!fileStream.is_open()) {
		retValue = FILE_READ_RETURN_FILE_DOES_NOT_EXIST;
	}

	return retValue;
}

// Try to read one line of the file and return status
FileReadReturnCode AccountFileReader::checkLineGood(std::string & line) {
	FileReadReturnCode lineReadStatus = FILE_READ_RETURN_SUCCESS;

	// First check if the line is empty
	if (line.empty()) {
		lineReadStatus = FILE_READ_RETURN_LINE_EMPTY;
	} else {
		// Trim '\r' if exists
		if (line.find_last_of('\r') != std::string::npos) {
			line.erase(line.find_last_of('\r'));
		}
		if (line.length() != validLineLength) {
			lineReadStatus = FILE_READ_RETURN_INVALID_LINE_LENGTH;
		} else {
			// Line is initially good so increase the count
			++currentLineCount %= linesInAccountNumber;

			// Now check if it is the end of the account number
			if (currentLineCount == 0
					&& line.find_first_not_of(" ") != std::string::npos) {
				lineReadStatus = FILE_READ_RETURN_INVALID_END_OF_ACCOUNT_CHARS;
			} else if (line.find_first_not_of(" _|") != std::string::npos) {
				lineReadStatus = FILE_READ_RETURN_INVALID_LINE_CHARS;
			}
		}
	}

	return lineReadStatus;
}

std::string AccountFileReader::printAccount(const unsigned int index) {
	std::string retString = "";
	if (index < accounts.size()) {
		retString = accounts[index].printAccountNumber();
	}
	return retString;
}

std::string AccountFileReader::printAccounts() {
	std::string retString = "";
	for (unsigned int i = 0; i < accounts.size(); ++i) {
		retString += printAccount(i) + "\r\n";
	}
	return retString;
}

std::string AccountFileReader::printAccountsWithStatus() {
	std::string retString = "";
	for (unsigned int i = 0; i < accounts.size(); ++i) {
		retString += accounts[i].appendAccountNumberStatus(printAccount(i)) + "\r\n";
	}
	return retString;
}

} /* namespace accounts */
