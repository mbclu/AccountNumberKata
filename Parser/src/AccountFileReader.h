/*
 * AccountFileReader.h
 *
 *  Created on: Mar 16, 2014
 *      Author: Mitch
 */

#include <fstream>
#include "Account.h"
#include "../contrib/gtest/gtest.h"

#ifndef ACCOUNTFILEREADER_H_
#define ACCOUNTFILEREADER_H_

namespace accounts {

// Enumeration for the different ways a file read can complete
enum FileReadReturnCode {
	FILE_READ_RETURN_SUCCESS = 0,
	FILE_READ_RETURN_FILE_DOES_NOT_EXIST,
	FILE_READ_RETURN_LINE_EMPTY,
	FILE_READ_RETURN_INVALID_LINE_LENGTH,
	FILE_READ_RETURN_INVALID_LINE_CHARS,
	FILE_READ_RETURN_INVALID_END_OF_ACCOUNT_CHARS
};

// Typedef vector for holding multiple accounts
typedef std::vector<Account> Accounts;

// Class to handle file input for reading the account numbers
class AccountFileReader {
	friend class AccountFileReaderTest;
	FRIEND_TEST(AccountFileReaderTest, ReadAccountFileReturnsStatus);
	FRIEND_TEST(AccountFileReaderTest, FileNotAtEOF);
	FRIEND_TEST(AccountFileReaderTest, LineLengthIsValid);
	FRIEND_TEST(AccountFileReaderTest, LineCharactersAreValid);
	FRIEND_TEST(AccountFileReaderTest, ReadValidEndOfAccountLine);
	FRIEND_TEST(AccountFileReaderTest, FourByTwentySevenAccountNumberIsValid);
	FRIEND_TEST(AccountFileReaderTest, PrintAccountNumberCanFail);

protected:
	static const size_t validLineLength = 27;
	static const unsigned int linesInAccountNumber = 4;
	Accounts accounts;
	std::string currentAccountLine;
	unsigned int currentLineCount;
	std::string currentAccountNumberString;

public:
	AccountFileReader();
	virtual ~AccountFileReader();

	FileReadReturnCode readFile(const char * inputFileName);
	Accounts getAccounts();
	std::string getCurrentAccountLine();
	unsigned int getCurrentLineCount();
	std::string getCurrentAccountNumberString();
	std::string printAccount(const unsigned int index);
	std::string printAccounts();
	std::string printAccountsWithStatus();

private:
	FileReadReturnCode openFile(const char * fileName,
			std::ifstream& fileStream);
	FileReadReturnCode checkLineGood(std::string& line);
};

} /* namespace accounts */

#endif /* ACCOUNTFILEREADER_H_ */
