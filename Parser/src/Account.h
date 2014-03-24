/*
 * AccountNumber.h
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */

#include <vector>
#include "AccountDigit.h"
#include "../contrib/gtest/gtest.h"

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

namespace accounts {

// Container for the entire account number
typedef std::vector<AccountDigit> AccountNumber;

class Account {
	friend class AccountTest;
	FRIEND_TEST(AccountTest, AccountNumberDecodesValues);
	FRIEND_TEST(AccountTest, ChecksumTest);

protected:
	AccountNumber accountNumberDigits;
	int checksum;

public:
	static const unsigned int ACCOUNT_LENGTH;

	Account();
	virtual ~Account();

	void assignRawAccountNumber(std::string accountString);
	AccountNumber getAccountNumber();
	std::string printAccountNumber(bool showStatus);

private:
	void calcAccountNumberChecksum();
};

} /* namespace accounts */

#endif /* ACCOUNT_H_ */
