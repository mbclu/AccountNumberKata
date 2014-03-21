/*
 * AccountFileReaderTest.h
 *
 *  Created on: Mar 16, 2014
 *      Author: Mitch
 */

#include "AccountFileReader.h"

#ifndef ACCOUNTFILEREADERTEST_H_
#define ACCOUNTFILEREADERTEST_H_

#define DEFAULT_TEST_FILE_PATH	"C:\\Users\\Mitch\\GitHub\\AccountNumberKata\\Parser\\test_files\\"

namespace accounts {

class AccountFileReaderTest: public ::testing::Test {
protected:
	AccountFileReaderTest() {
		strcpy(filePathAndName, "");
		line = "";
		returnCode = FILE_READ_RETURN_SUCCESS;
	}
	virtual ~AccountFileReaderTest() {
	}
	virtual void SetUp() {
	}
	virtual void TearDown() {
		accountFile.close();
		line = "";
	}

	AccountFileReader fr0;
	static const unsigned int maxPathLength = 255;
	char filePathAndName[maxPathLength];
	std::ifstream accountFile;
	std::string line;
	FileReadReturnCode returnCode;

	void assertAccountFileExists(const char * fileName) {
		strcpy(filePathAndName, DEFAULT_TEST_FILE_PATH);
		strcat(filePathAndName, fileName);
		ASSERT_NE(FILE_READ_RETURN_FILE_DOES_NOT_EXIST, fr0.openFile(filePathAndName, accountFile));
	}

	void assertLineIsEmpty() {
		ASSERT_TRUE(fr0.getCurrentAccountLine().empty());
		ASSERT_STREQ(fr0.getCurrentAccountLine().c_str(), "");
	}

	void assertAccountStringEmpty() {
		ASSERT_TRUE(fr0.getCurrentAccountNumberString().empty());
		ASSERT_STREQ(fr0.getCurrentAccountNumberString().c_str(), "");
	}

	void assertFileReadCompletesSuccessfully(const char * fileName) {
		assertAccountFileExists(fileName);
		std::getline(accountFile, line);
		returnCode = fr0.checkLineGood(line);
		ASSERT_EQ(FILE_READ_RETURN_SUCCESS, returnCode);
	}

	void assertLineLengthValid(const char * fileName) {
		assertFileReadCompletesSuccessfully(fileName);
		ASSERT_NE(FILE_READ_RETURN_INVALID_LINE_LENGTH, returnCode);
	}

	void assertLineCharactersValid(const char * fileName) {
		assertLineLengthValid(fileName);
		ASSERT_NE(FILE_READ_RETURN_INVALID_LINE_CHARS, returnCode);
	}

	void assertValidAccountNumber(const char * fileName) {
		assertAccountFileExists(fileName);
//		ASSERT_EQ(FILE_READ_RETURN_SUCCESS, fr0.readValidAccountNumber(accountFile, line));
	}

	void assertValidSingleAccountFileRead(const char * fileName) {
		// Test file with a single account number in it
		strcpy(filePathAndName, DEFAULT_TEST_FILE_PATH);
		strcat(filePathAndName, fileName);
		FileReadReturnCode ret = fr0.readFile(filePathAndName);
		ASSERT_NE(FILE_READ_RETURN_FILE_DOES_NOT_EXIST, ret);
		EXPECT_EQ(FILE_READ_RETURN_SUCCESS, ret);
	}
};

} /* namespace accounts */

#endif /* ACCOUNTFILEREADERTEST_H_ */
