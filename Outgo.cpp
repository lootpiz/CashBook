#include "Outgo.h"

Outgo::Outgo()
{
}

Outgo::Outgo(Date& date, char (*contents), Currency amount, Currency bal_amount, char (*note))
: Account(date, contents, amount, bal_amount, note)
{
}

Outgo::Outgo(const Outgo& source)
{
}

Outgo::~Outgo()
{
}

	 
