#ifndef _CASHBOOK_H
#define _CASHBOOK_H

#include "Array.h"
#include "Account.h"

class Cashbook
{
public:
	Cashbook();
	Cashbook(int capacity);
	Cashbook(const Cashbook& source);
	~Cashbook();

	Cashbook& operator = (const Cashbook& soure);
	Account* operator [] (int index);

	int Record(Date date, char (*contents), Account::Currency amount, char (*note));
	void FindByDate(Date date, Account* (*resultset), int* count);
	void FindByContents(char (*contents), Account* (*resultset), int* count);
	int Modify(int index, Account::Currency amount, char (*note));
	void Calculate(Date startDate, Date endDate, Account::Currency* incomeSum, 
		Account::Currency* outgoSum, Account::Currency* difference);

	void Load();
	void Save();
	int GetCount() const;

private:
	Array<Account*> accounts;
	int count;
};

inline int Cashbook::GetCount() const
{
	return this->count;
}

#endif