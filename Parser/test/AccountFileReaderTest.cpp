/*
 * AccountFileReaderTest.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: Mitch
 */

#include "../src/globals.h"
#include "../contrib/gtest/gtest.h"
#include "AccountFileReaderTest.h"

namespace accounts {

// Test that if given a file name and stream we can open the file
TEST_F(AccountFileReaderTest, ReadAccountFileReturnsStatus) {
	// Test the case where we know the file does not exist
	ASSERT_EQ(FILE_READ_RETURN_FILE_DOES_NOT_EXIST,
			fr0.openFile("", accountFile));

	// Test the case where we have an existing file
	assertAccountFileExists("000000000.txt");
}

// Test that lines are initialized to an empty string
TEST_F(AccountFileReaderTest, LineIsEmptyIntially) {
	assertLineIsEmpty();
}

// Test that the line count starts at zero
TEST_F(AccountFileReaderTest, LineCountIsZeroInitially) {
	ASSERT_EQ(0, fr0.currentLineCount);
	ASSERT_EQ(0, fr0.totalLineCountRead);
}

// Test that account strings are initialized to an empty string
TEST_F(AccountFileReaderTest, AccountStringIsEmptyIntially) {
	assertAccountStringEmpty();
}

// Test that we have not reached the end of the file
// Also Test that the overall line count is recorded at the first error
TEST_F(AccountFileReaderTest, FileNotAtEOF) {
	// Test an existing file that does not have any content
	assertAccountFileExists("EmptyFile.txt");
	std::getline(accountFile, line);
	ASSERT_EQ(FILE_READ_RETURN_LINE_EMPTY, fr0.checkLineGood(line));
	accountFile.close();

	// Test an existing file that does not have any content
	assertAccountFileExists("000000000.txt");
	std::getline(accountFile, line);
	ASSERT_EQ(FILE_READ_RETURN_SUCCESS, fr0.checkLineGood(line));
	line = "";
	std::getline(accountFile, line);
	ASSERT_EQ(FILE_READ_RETURN_SUCCESS, fr0.checkLineGood(line));
	line = "";
	std::getline(accountFile, line);
	ASSERT_EQ(FILE_READ_RETURN_SUCCESS, fr0.checkLineGood(line));
	line = "";
	std::getline(accountFile, line);
	ASSERT_EQ(FILE_READ_RETURN_SUCCESS, fr0.checkLineGood(line));
	line = "";
	ASSERT_EQ(FILE_READ_RETURN_LINE_EMPTY, fr0.checkLineGood(line));
	ASSERT_EQ(FILE_READ_RETURN_LINE_EMPTY, fr0.checkLineGood(line));
}

// Test that the line of the file is the correct length (27)
TEST_F(AccountFileReaderTest, LineLengthIsValid) {
	// Test reading one line from a file returning the incorrect line length
	assertAccountFileExists("LineLengthInvalid.txt");
	std::getline(accountFile, line);
	returnCode = fr0.checkLineGood(line);
	ASSERT_EQ(FILE_READ_RETURN_INVALID_LINE_LENGTH, returnCode);
}

// Test that the line count resets for new file read
TEST_F(AccountFileReaderTest, LineCountResets) {
	// Test with an empty file because even if it is not opened it should be reset
	ASSERT_EQ(FILE_READ_RETURN_FILE_DOES_NOT_EXIST, fr0.readFile(""));
	ASSERT_EQ(0, fr0.currentLineCount);
	ASSERT_EQ(0, fr0.totalLineCountRead);
}

// Test that the line count increments after good read
TEST_F(AccountFileReaderTest, LineCountIncrements) {
	// Test that we increment the count if a line of good length was read in
	assertLineLengthValid("SingleGoodLine.txt");
	ASSERT_EQ(1, fr0.currentLineCount);
}

// Test that all the characters in a line are correct, (' ', '_', '|')
TEST_F(AccountFileReaderTest, LineCharactersAreValid) {
	// Test the case where the line is of valid length but has invalid characters
	assertAccountFileExists("LineCharactersInvalid.txt");
	std::getline(accountFile, line);
	returnCode = fr0.checkLineGood(line);
	ASSERT_EQ(FILE_READ_RETURN_INVALID_LINE_CHARS, returnCode);
}

// Test that we can detect the end of account number line (blank line)
TEST_F(AccountFileReaderTest, ReadValidEndOfAccountLine) {
	// Test the default file where the first line of the account should fail this case
	assertLineCharactersValid("EndOfAccountLine.txt");
	ASSERT_EQ(FILE_READ_RETURN_SUCCESS, fr0.checkLineGood(line));
	ASSERT_EQ(FILE_READ_RETURN_SUCCESS, fr0.checkLineGood(line));
	ASSERT_EQ(FILE_READ_RETURN_INVALID_END_OF_ACCOUNT_CHARS, fr0.checkLineGood(line));
}

// Test that we can read an entire account number
TEST_F(AccountFileReaderTest, FourByTwentySevenAccountNumberIsValid) {
	// Test that we get success if the file is OK
	assertValidAccountNumber("000000000.txt");
	accountFile.close();
	assertValidAccountNumber("111111111.txt");
	accountFile.close();
	assertValidAccountNumber("222222222.txt");
	accountFile.close();
}

// Test that our accounts are empty initially
TEST_F(AccountFileReaderTest, AccountAreEmptyInitially) {
	Accounts accounts = fr0.getAccounts();
	ASSERT_TRUE(accounts.empty());
}

// Test we can add an account to our accounts
TEST_F(AccountFileReaderTest, AccountsCanBeAdded) {
	// Test file with a single account number in it
	assertValidSingleAccountFileRead("000000000.txt");
}

// Test that the printer will fail gracefully
TEST_F(AccountFileReaderTest, PrintAccountNumberCanFail) {
	assertValidSingleAccountFileRead("000000000.txt");
	ASSERT_STREQ("", fr0.printAccount(fr0.getAccounts().size() +1, false).c_str());
}

// Test that we can print
TEST_F(AccountFileReaderTest, PrintAccountNumber) {
	assertValidSingleAccountFileRead("000000000.txt");
	ASSERT_EQ(1, fr0.getAccounts().size());
	ASSERT_STREQ("000000000", fr0.printAccount(0, false).c_str());
}

// Test that we can print a bunch of account numbers
TEST_F(AccountFileReaderTest, PrintAccountNumbers) {
	assertValidSingleAccountFileRead("000000000.txt");
	EXPECT_STREQ("000000000\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("111111111.txt");
	EXPECT_STREQ("111111111\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("222222222.txt");
	EXPECT_STREQ("222222222\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("333333333.txt");
	EXPECT_STREQ("333333333\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("444444444.txt");
	EXPECT_STREQ("444444444\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("555555555.txt");
	EXPECT_STREQ("555555555\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("666666666.txt");
	EXPECT_STREQ("666666666\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("777777777.txt");
	EXPECT_STREQ("777777777\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("888888888.txt");
	EXPECT_STREQ("888888888\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("999999999.txt");
	EXPECT_STREQ("999999999\r\n", fr0.printAccounts(false).c_str());
	assertValidSingleAccountFileRead("123456789.txt");
	EXPECT_STREQ("123456789\r\n", fr0.printAccounts(false).c_str());
}

// Test that we can read and print in a larger file with multiple account numbers
TEST_F(AccountFileReaderTest, PrintAccountNumbersFromSingleFile) {
	std::string expected = "";
	strcpy(filePathAndName, DEFAULT_TEST_FILE_PATH);
	strcat(filePathAndName, "0through9.txt");

	FileReadReturnCode ret = fr0.readFile(filePathAndName);
	ASSERT_NE(FILE_READ_RETURN_FILE_DOES_NOT_EXIST, ret);
	EXPECT_EQ(FILE_READ_RETURN_SUCCESS, ret);
	EXPECT_EQ(10, fr0.getAccounts().size());
	expected = "000000000\r\n";
	expected += "111111111\r\n";
	expected += "222222222\r\n";
	expected += "333333333\r\n";
	expected += "444444444\r\n";
	expected += "555555555\r\n";
	expected += "666666666\r\n";
	expected += "777777777\r\n";
	expected += "888888888\r\n";
	expected += "999999999\r\n";
	EXPECT_STREQ(expected.c_str(), fr0.printAccounts(false).c_str());
}

} /* namespace accounts */
