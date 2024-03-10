#pragma once
#include <iostream>
#include <string>

class CashMachine
{
public:
	CashMachine(int number, std::string adress)
	{
		this->number = number;
		this->adress = adress;
		//count++;
	}
	void SetAdress(std::string adress)
	{
		this->adress = adress;
	}
	std::string GetAdress()
	{
		return adress;
	}
	void SetNumber(int number)
	{
		this->number = number;
	}
	int GetNumber()
	{
		return number;
	}
	void SetNext(CashMachine* next)
	{
		this->next = next;
	}
	CashMachine* GetNext()
	{
		return next;
	}
	void SetPrevious(CashMachine* previous)
	{
		this->previous = previous;
	}
	CashMachine* GetPrevious()
	{
		return previous;
	}

	~CashMachine()
	{
		number = 0;
		adress = "";
		next = NULL;
		previous = NULL;
		//count--;
	}
private:
	//static int count;
	int number;
	std::string adress;
	CashMachine* next;
	CashMachine* previous;	
};



