#ifndef _DATE_H
#define _DATE_H

class Date
{
public:
	typedef unsigned short int UShort;
	enum Month {JAN =1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
	enum Weekday {SUN =1, MON, TUE, WEN, THU, FRI, SAT};

public:
	Date();
	Date(UShort year, Month month, UShort day = 1);
	Date(char (*date));
	Date(const Date& source);
	~Date();

	operator char*();
	int operator - (const Date& date);
	Date& operator = (const Date& source);
	Date operator - (UShort days) const;
	Date operator + (UShort days) const;

	Date& operator -- ();
	const Date operator -- (int);
	Date& operator ++ ();
	const Date operator++(int);

	bool operator == (const Date& other) const;
	bool operator != (const Date& other) const;
	bool operator > (const Date& other);
	bool operator < (const Date& other);
	bool operator >= (const Date& other);
	bool operator <= (const Date& other);
	Date& operator += (UShort days);
	Date& operator -= (UShort days);

	static Date GetCurrentDay();
	Date& SetToday();
	Date Previous(UShort days);
	Date Next(UShort days);
	Date Tomorrow();
	Date Yesterday();
	bool IsEqual(const Date& date);
	bool IsNotEqual(const Date& date);

	UShort GetYear() const;
	UShort GetMonth() const;
	UShort GetDay() const;
	Weekday GetWeekday() const;

	void SetWeekday();

private:
	UShort year;
	Month month;
	UShort day;
	Weekday weekday;
};

inline Date::UShort Date::GetYear() const
{
	return this->year;
}

inline Date::UShort Date::GetMonth() const
{
	return this->month;
}

inline Date::UShort Date::GetDay() const
{
	return this->day;
}

#endif
