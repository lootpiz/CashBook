#ifndef _OUTGO_H
#define _OUTGO_H

#include "Account.h"

class Outgo : public Account
{
public:
	Outgo();
	Outgo(Date& date, char (*contents), Currency amount, Currency bal_amount, char (*note));
	Outgo(const Outgo& source);
	virtual ~Outgo();
};

#endif