#include "Date.h"
#include <cstdio>
#include <ctime>

Date::Date()
{
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
}

Date::Date(UShort year, Month month, UShort day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

Date::Date(char (*date))
{
	sscanf(date, "%4d%2d%2d", &year, &month, &day);
}

Date::Date(const Date& source)
{
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
}

Date::~Date()
{
}

Date& Date::operator = (const Date& source)
{
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
 
	return (*this);
}

Date Date::operator - (UShort days) const
{
	Date temp(*this);
	temp.day -= days;
	return temp;
}

Date Date::operator + (UShort days) const
{
	Date temp(*this);
	temp.day +=days;
	return temp;
}

Date& Date::operator -- ()
{
	this->day--;

	return *this;
}

const Date Date::operator -- (int)
{
	const Date temp(*this);
	this->operator --();
	return temp;
}

Date& Date::operator ++ ()
{
	this->day++;
	return *this;
}

const Date Date::operator ++ (int)
{
	const Date temp(*this);
	this->operator ++ ();
	return temp;
}

bool Date::operator == (const Date& other) const
{
	bool result = false;

	if(this->year == other.year)
	{
		if(this->month == other.month)
		{
			if(this->day == other.day)
			{
				result = true;
			}
		}
	}
	return result;
}

bool Date::operator != (const Date& other) const
{
	return !(this->operator == (other));
}

bool Date::operator > (const Date& other)
{
	int result = this->operator - (other);
	return (result > 0) ? true : false;
}

bool Date::operator < (const Date& other)
{
	int result = this->operator - (other);
	return (result < 0) ? true : false;
}

bool Date::operator >= (const Date& other)
{
	int result = this->operator - (other);
	return (result >= 0) ? true : false;
}

bool Date::operator <= (const Date& other)
{
	int result = this->operator - (other);
	return (result <= 0) ? true : false;
}

Date& Date::operator -= (UShort days)
{
	this->day -= days;
	return *this;
}

Date& Date::operator += (UShort days)
{
	this->day += days;
	return *this;
}

Date::operator char*()
{
	static char buffer[9];
	sprintf(buffer, "%4d%02d%02d", this->year, this->month, this->day);
	
	return buffer;
}

Date Date::GetCurrentDay()
{
	Date temp;
	struct tm *current = 0;
	time_t ltime;
	time(&ltime);
	current = localtime(&ltime);

	temp.year = current->tm_year + 1900;
	temp.month = static_cast<Month>(current->tm_mon + 1);
	temp.day = current->tm_mday;

	return temp;
}

Date& Date::SetToday()
{
	(*this) = Date::GetCurrentDay();
	return *this;
}

int Date::operator - (const Date& other)
{
	int difference;

	difference = this->year - other.year;
	if(difference == 0)
	{
		difference = this->month - other.month;
		if(difference == 0)
		{
			difference = this->day - other.day;
		}
	}
	return difference;
}

Date::Weekday Date::GetWeekday() const
{
	struct tm time= {0};
	time.tm_year = this->year - 1900;
	time.tm_mon = this->month;
	time.tm_mday = this->day;

	mktime(&time);

	return static_cast<Weekday>(time.tm_wday);
}

Date Date::Previous(UShort days)
{
	return (*this) - days;
}

Date Date::Next(UShort days)
{
	return (*this) + days;
}

Date Date::Tomorrow()
{
	return (*this) + static_cast<UShort>(1);
}

Date Date::Yesterday()
{
	return (*this) - static_cast<UShort>(1);
}

bool Date::IsEqual(const Date &date)
{
	return this->operator == (date);
}

bool Date::IsNotEqual(const Date& date)
{
	return this->operator !=(date);
}



