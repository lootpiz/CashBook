#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include "Date.h"

class Account
{
public:
	typedef double Currency;
public:
	Account();
	Account(Date& date, char (*contents), Currency amount, Currency bal_amount, char (*note));
	Account(const Account& source);
	virtual ~Account();

	Account& operator +(Currency amount);
	Account& operator =(const Account& source);

	Date& GetDate() const;
	char* GetContents() const;
	Currency GetAmount() const;
	Currency GetBalanceAmount() const;
	char* GetNote() const;

private:
	Date date;
	char contents[16];
	Currency amount;
	Currency bal_amount;
	char note[12];
};

inline Date& Account::GetDate() const
{
	return const_cast<Date&>(this->date);
}

inline char* Account::GetContents() const
{
	return const_cast<char*>(this->contents);
}

inline Account::Currency Account::GetAmount() const
{
	return this->amount;
}

inline Account::Currency Account::GetBalanceAmount() const
{
	return this->bal_amount;
}

inline char* Account::GetNote() const
{
	return const_cast<char*>(this->note);
}

#endif