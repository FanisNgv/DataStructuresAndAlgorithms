#pragma once

class Branch
{
public:
	Branch(int number)
	{
		this->number = number;
		this->Head = NULL;
		countOfElements = 0;
	}
	void SetNumber(int number)
	{
		this->number = number;
	}
	int GetNumber()
	{
		return this->number;
	}
	void SetHead(CashMachine* Head)
	{
		this->Head = Head;
	}
	CashMachine* GetHead()
	{
		return this->Head;
	}
	bool IsEmpty()
	{
		if (Head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void AddCashMachineBefore(int number, std::string adress, int element)
	{
		if (IsEmpty())
		{
			Head = new CashMachine(number, adress);
			Head->SetNext(NULL);
		}
		else if (FindElement(number))
		{
			std::cout << "Банкомат с таким номером уже существует" << std::endl;
			return;
		}
		else
		{
			CashMachine* AddElem  = new CashMachine(number, adress);
			CashMachine* Current = Head;
			while (Current->GetNumber() != element)
			{
				Current = Current->GetNext();
			}
			if (Current == Head)
			{
				AddElem->SetPrevious(NULL);
				AddElem->SetNext(Head);
				Head->SetPrevious(AddElem);
				Head = AddElem;
			}
			else
			{
				AddElem->SetPrevious(Current->GetPrevious());
				AddElem->SetNext(Current);
				(AddElem->GetPrevious())->SetNext(AddElem);
				Current->SetPrevious(AddElem);
			}			
		}
	}	
	void AddCashMachineAfter(int number, std::string adress, int element)
	{
		if (IsEmpty())
		{
			Head = new CashMachine(number, adress);
			Head->SetNext(NULL);
		}
		else if (FindElement(number))
		{
			std::cout << "Банкомат с таким номером уже существует" << std::endl;
			return;
		}
		else
		{
			CashMachine* AddElem = new CashMachine(number, adress);
			CashMachine* Current = Head;
			while (Current->GetNumber() != element)
			{
				Current = Current->GetNext();
			}
			AddElem->SetPrevious(Current);
			AddElem->SetNext(Current->GetNext());
			Current->SetNext(AddElem);
			if (AddElem->GetNext() != NULL)
			{
				(AddElem->GetNext())->SetPrevious(AddElem);
			}			
		}
	}

	void AddSortedCashMachine(int number, std::string adress)
	{
		if (IsEmpty())
		{
			Head = new CashMachine(number, adress);
			Head->SetNext(NULL);
			countOfElements++;
		}
		else if (FindElement(number))
		{
			std::cout << "Банкомат с таким номером уже существует" << std::endl;
			return;
		}
		else
		{
			CashMachine* AddElem = new CashMachine(number, adress);
			CashMachine* Current = Head;
			bool ItsMax = false;
			while (number > Current->GetNumber())
			{
				if (Current->GetNext() == NULL)
				{
					ItsMax = true;
					break;
				}
				Current = Current->GetNext();				
			}
			if (Current == Head)
			{
				AddElem->SetPrevious(NULL);
				AddElem->SetNext(Head);
				Head->SetPrevious(AddElem);
				Head = AddElem;
				countOfElements++;
			}
			else
			{
				if (ItsMax)
				{
					AddElem->SetPrevious(Current);
					AddElem->SetNext(Current->GetNext());
					Current->SetNext(AddElem);
					countOfElements++;
				}
				else
				{
					AddElem->SetPrevious(Current->GetPrevious());
					AddElem->SetNext(Current);
					(AddElem->GetPrevious())->SetNext(AddElem);
					Current->SetPrevious(AddElem);
					countOfElements++;
				}							
			}
		}
	}
	bool FindElement(int element)
	{
		bool WasFound = false;
		if (IsEmpty())
		{
			std::cout << "Филиал пуст. Добавьте банкоматы" << std::endl;
			return false;
		}		
		else
		{
			CashMachine* Current = Head;
			while (Current != NULL)
			{								
				if (Current->GetNumber() == element)
				{
					std::cout << "Банкомат под номером " << element << " найден!" << std::endl;
					return true;
				}
				Current = Current->GetNext();
			}
			std::cout << "Банкомат под номером " << element << " не найден!" << std::endl;
			return false;
		}
	}
	void DeleteElement(int element)
	{
		bool ItsMax = false;
		if (IsEmpty())
		{
			std::cout << "Филиал пуст. Добавьте банкоматы" << std::endl;
			return;
		}
		else if (!FindElement(element))
		{
			std::cout << "Элемент не обнаружен" << std::endl;
			return;
		}
		else
		{
			CashMachine* Current = Head;
			while (Current->GetNumber() != element)
			{
				Current = Current->GetNext();
				if (Current->GetNext() == NULL)
				{
					ItsMax = true;
					break;
				}				
			}
			if (Current == Head)
			{
				Head = Head->GetNext();
				countOfElements--;
				delete Current;
			}
			else
			{
				if (ItsMax)
				{
					(Current->GetPrevious())->SetNext(NULL);
					countOfElements--;
					delete Current;
				}
				else
				{
					(Current->GetNext())->SetPrevious(Current->GetPrevious());
					(Current->GetPrevious())->SetNext(Current->GetNext());
					countOfElements--;
					delete Current;
				}				
			}			
		}
	}
	void ShowBranch()
	{
		CashMachine* Current = Head;
		std::cout << "Номер банкомата\tАдресс банкомата\n";
		while (Current != NULL)
		{
			std::cout << Current->GetNumber() << '\t\t';
			std::cout << Current->GetAdress() << '\n';
			Current = Current->GetNext();
		}
	}
	~Branch()
	{
		this->number = 0;
		CashMachine* Current = Head;
		CashMachine* temp;
		while (Current != NULL)
		{
			temp = Current;
			Current = Current->GetNext();
			delete temp;
		}
	}
private:
	int number;
	int countOfElements;
	CashMachine* Head;
};
