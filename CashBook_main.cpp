#include <iostream>
#include <cstring>
#include <stdio.h>
#include "Cashbook.h"
#include "Account.h"
#include "Date.h"
using namespace std;

int main()
{	
	Cashbook cashbook;

	Date date;
	char contents[16];
	Account::Currency amount;
	Account::Currency bal_amount;
	Account* resultset;
	int count = 0;
	char note[12];
	
	strcpy(contents, "aaa");
	amount = 10000;
	bal_amount = 10000;
	strcpy(note, "bbb");
	
	date = date.SetToday();
	
	///////////////////////////////////////////////////Record
	cashbook.Record(date, contents, amount, note);
	///////////////////////////////////////////////////FindByContents
	cashbook.FindByContents(contents, &resultset, &count);
	cout << "################################FindByContents" << endl;
	cout << "count : " << count <<endl;

	//////////////////////////////////////////////////FindByDate
	count = 0;
	cashbook.FindByDate(date, &resultset, &count);
	cout << "################################FindByDate " << endl;
	cout << "count : " << count << endl;



	return 0;
}

