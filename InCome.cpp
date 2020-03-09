#include "InCome.h"

InCome::InCome()
{
}

InCome::InCome(Date& date, char (*contents), Currency amount, Currency bal_amount, char(* note))
: Account(date, contents, amount, bal_amount, note)
{
}

InCome::InCome(const InCome& source)
{
}

InCome::~InCome()
{
}

