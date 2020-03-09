#include <stdio.h>
#include <string.h>
#include "Cashbook.h"
#include "InCome.h"
#include "Outgo.h"

Cashbook::Cashbook()
{
	this->count = 0;
}

Cashbook::Cashbook(int capacity) : accounts(capacity)
{
	this->count  = 0;
}

Cashbook::Cashbook(const Cashbook& source) : accounts(source.accounts.GetCapacity())
{
	for(int i = 0; i< this->count; i++)
	{
		if(dynamic_cast<InCome*>( (const_cast<Cashbook&>(source)).accounts[i]) )
		{
			(this->accounts).Store(i, new InCome(
				*(reinterpret_cast<InCome*>((const_cast<Cashbook&>(source)).accounts[i]))));
		}

		else if(dynamic_cast<Outgo*>( (const_cast<Cashbook&>(source)).accounts[i]) )
		{
			(this->accounts).Store(i, new Outgo(
				*(reinterpret_cast<Outgo*>((const_cast<Cashbook&>(source)).accounts[i]))));
		}
	}

	this->count = source.count;
}

Cashbook::~Cashbook()
{
}

Cashbook& Cashbook::operator =(const Cashbook& source)
{
	for(int i = 0; i< this->count; i++)
	{
		if(dynamic_cast<InCome*>( (const_cast<Cashbook&>(source)).accounts[i]) )
		{
			(this->accounts).Store(i, new InCome(
				*(reinterpret_cast<InCome*>((const_cast<Cashbook&>(source)).accounts[i]))));
		}

		else if(dynamic_cast<Outgo*>( (const_cast<Cashbook&>(source)).accounts[i]) )
		{
			(this->accounts).Store(i, new Outgo(
				*(reinterpret_cast<Outgo*>((const_cast<Cashbook&>(source)).accounts[i]))));
		}
	}

	this->count = source.count;

	return (*this);
}

Account* Cashbook::operator [](int index)
{
	return this->accounts[index];
}

int Cashbook::Record(Date date, char (*contents), Account::Currency amount, char (*note))
{
	int index;
	Account* pAccount = 0;
	Account::Currency bal_amount;

	if(this->count == 0)
	{
		bal_amount = amount;
	}

	else
	{
		bal_amount = (this->accounts)[this->count-1]->GetBalanceAmount();
		bal_amount = bal_amount + amount;
	}

	if(amount > 0)
	{
		pAccount = new InCome(date, contents, amount, bal_amount, note);
	}

	else if(amount < 0)
	{
		pAccount = new Outgo(date, contents, amount * -1, bal_amount, note);
	}

	if(this->count < this->accounts.GetCapacity())
	{
		index = this->accounts.Store(this->count, pAccount);	
	}

	else
	{
		index = this->accounts.AppendFromRear(pAccount);
	}
		

	if(index > -1)
	{
		(this->count)++;
	}

	else
	{
		delete pAccount;
	}

	return index;
}

int CompareDate(void* one, void* other)
{
	int result;
	
	//if( *((Date*)one) == ( *((Account**)other))->GetDate() )
	//if( *((Date*)other) == ( *((Account**)one))->GetDate() )
	if((char*)other == ( *((Account**)one))->GetDate() )
	{
		result = 0;
	}

	return result;
}

int CompareContents(void* one, void* other)
{
	int result;
	//char* pContents = (char*)one;
	char* pContents = (char*)other;

	//Account* pAccount = *((Account**)other);
	Account*pAccount = *((Account**)one);

	if(strcmp(pContents, pAccount->GetContents()) == 0)
	{
		result = 0;
	}

	return result;
}

void Cashbook::FindByDate(Date date, Account* (*resultset), int *findcount)
{
	int* result = new int[this->count];

	this->accounts.LinearSearchByDuplicate(date, result, findcount, CompareDate);
	for(int i = 0; i < *findcount; i++)
	{
		resultset[i] = (this->accounts)[result[i]];
	}

	if(result != 0)
	{
		delete[] result;
	}
}

void Cashbook::FindByContents(char (*contents), Account* (*resultset), int *findcount)
{
	int* result = new int[this->count];

	this->accounts.LinearSearchByDuplicate(contents, result, findcount, CompareContents);
	for(int i = 0; i< *findcount; i++)
	{
		resultset[i] = (this->accounts)[result[i]];
	}

	if(result != 0)
	{
		delete[] result;
	}
}


int Cashbook::Modify(int index, Account::Currency amount, char (*note))
{
	Account* temp;
	Account* pAccount;
	
	if(index > -1 && index < this->accounts.GetLength())
	{
		pAccount = this->accounts[index];

		if(dynamic_cast<InCome*>(pAccount))
		{
			temp = new InCome(pAccount->GetDate(), pAccount->GetContents(), 
				amount, pAccount->GetBalanceAmount(), note);
		}

		else if(dynamic_cast<Outgo*>(pAccount))
		{
			temp = new Outgo(pAccount->GetDate(), pAccount->GetContents(),
				amount, pAccount->GetBalanceAmount(), note);
		}

		if(temp != 0)
		{
			(*pAccount) = (*temp);
			delete temp;
		}

		Account::Currency bal_amount = 0;

		for(int i = 0; i < this->count; i++)
		{
			Account* pAccount = this->accounts[i];
			if(dynamic_cast<InCome*>(pAccount))
			{
				bal_amount = bal_amount + pAccount->GetBalanceAmount();
				InCome temp(pAccount->GetDate(), pAccount->GetContents(),
					pAccount->GetAmount(), bal_amount, pAccount->GetNote());
				(*pAccount) = temp;
			}

			else if(dynamic_cast<InCome*>(pAccount))
			{
				bal_amount = bal_amount - pAccount->GetBalanceAmount();
				Outgo temp(pAccount->GetDate(), pAccount->GetContents(),
					pAccount->GetAmount(), bal_amount, pAccount->GetNote());
			}
		}
	}

	else
	{
		index = 1;
	}

	return index;
}

void Cashbook::Calculate(Date startDate, Date endDate, Account::Currency* incomeSum,
						 Account::Currency* outgoSum, Account::Currency* difference)
{
	Date currentDate;
	*incomeSum = 0;
	*outgoSum = 0;
	*difference = 0;

	Account* (*resultset) = new Account*[this->GetCount()];
	if(resultset != 0)
	{
		int count = 0;
		for(currentDate = startDate; currentDate <= endDate; currentDate++)
		{
			this->FindByDate(currentDate, resultset, &count);
			for(int i = 0; i < count; i++)
			{
				Account* pAccount = resultset[i];
				if(dynamic_cast<InCome*>(pAccount))
				{
					*incomeSum += pAccount->GetAmount();
				}
				else if(dynamic_cast<Outgo*>(pAccount))
				{
					*outgoSum += pAccount->GetAmount();
				}
			}
		}

		*difference = *incomeSum - *outgoSum;

		if(resultset != 0)
		{
			delete [] resultset;
		}
	}
}

void Cashbook::Load()
{
	Account temp;
	FILE* pfile;

	pfile = fopen("Account.dat", "rb");

	if(pfile != NULL)
	{
		while(!feof(pfile) && (fread(&temp, sizeof(Account), 1, pfile) > 0))
		{
			this->Record(temp.GetDate(), temp.GetContents(), temp.GetAmount(), temp.GetNote());
		}

		fclose(pfile);
	}
}

void Cashbook::Save()
{
	Account account;
	int i;

	FILE* pfile;

	pfile = fopen("Account.date", "wb");

	if(pfile != NULL)
	{
		for(i = 0; i < this->count; i++)
		{
			account = *(this->accounts[i]);
			fwrite(&account, sizeof(Account), 1, pfile);
		}
	}

	fclose(pfile);
}

