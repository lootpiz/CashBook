#include "Account.h"
#include "InCome.h"
#include "Outgo.h"
#include <string.h>

Account::Account()
{
	strcpy(this->contents, "");
	this->amount = 0.0;
	this->bal_amount = 0.0;
	strcpy(this->note,"");
}

Account::Account(Date& date, char (*contents), Currency amount, Currency bal_amount, char (*note))
{
	this->date = date;
	strcpy(this->contents, contents);
	this->amount = amount;
	this->bal_amount = bal_amount;
	strcpy(this->note, note);
}

Account::Account(const Account& source)
{
	this->date = source.date;
	strcpy(this->contents, source.contents);
	this->amount = source.amount;
	this->bal_amount = source.bal_amount;
	strcpy(this->note, note);
}

Account::~Account()
{
}

Account& Account::operator = (const Account& source)
{
	this->date = source.date;
	strcpy(this->contents, source.contents);
	this->amount = source.amount;
	this->bal_amount = source.bal_amount;
	strcpy(this->note, note);

	return (*this);
}

Account& Account::operator + (Currency amount)
{
	this->amount += amount;
	return (*this);
}
	