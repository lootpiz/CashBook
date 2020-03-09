#ifndef _INCOME_H
#define _INCOME_H

#include "Account.h"

class InCome : public Account
{
public:
	InCome();
	InCome(Date& date, char (*contents), Currency amount, Currency bal_amount, char (*note));
	InCome(const InCome& source);
	virtual ~InCome();
};

#endif
