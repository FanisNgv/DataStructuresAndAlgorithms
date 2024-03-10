#pragma once
#include <iostream>
#include <string>
#define MAX_SIZE 5

class CashMachine
{
public:
	CashMachine(int number, std::string adress)  // конструктор для создания объекта
	{
		this->number = number;
		this->adress = adress;
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
	}
private:
	int number;
	std::string adress;
	CashMachine* next;
	CashMachine* previous;
};
class Branch
{
public:
	Branch(int number)			// конструктор для создания объекта
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
	void AddSortedCashMachine(int number, std::string adress)
	{
		if (IsEmpty())	// Если динамический список пустой, то инициализируем Head
		{
			Head = new CashMachine(number, adress);
			Head->SetNext(NULL);
			countOfElements++;
		}
		else if (FindElementAdditionall(number))	// Проверка, есть ли уже такой элемент
		{
			std::cout << "Банкомат с таким номером уже существует!" << std::endl;
			return;
		}
		else
		{
			CashMachine* AddElem = new CashMachine(number, adress);
			CashMachine* Current = Head;
			while (number > Current->GetNumber())	// Пробегаемся по списку
			{
				if (Current->GetNext() == NULL) // Если не нашлось элемента больше добавляемого
				{
					AddElem->SetPrevious(Current);
					AddElem->SetNext(Current->GetNext());
					Current->SetNext(AddElem);
					countOfElements++;
					return;
				}
				Current = Current->GetNext();
			}
			if (Current == Head)			// Если уже Head больше, то переопределяем Head
			{				
				AddElem->SetPrevious(NULL);
				AddElem->SetNext(Head);
				Head->SetPrevious(AddElem);
				Head = AddElem;
				countOfElements++;											
			}
			else
			{							// Или же общий случай для добавления между двумя элементами
				AddElem->SetPrevious(Current->GetPrevious());
				AddElem->SetNext(Current);
				(AddElem->GetPrevious())->SetNext(AddElem);
				Current->SetPrevious(AddElem);
				countOfElements++;				
			}
		}
	}
	bool FindElement(int element)		// Поиск элемента
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
	bool FindElementAdditionall(int element)  // Вспомогательная функция поиска
	{
		bool WasFound = false;		
		CashMachine* Current = Head;
		while (Current != NULL)
		{
			if (Current->GetNumber() == element)
			{
				return true;
			}
			Current = Current->GetNext();
		}
		return false;
		
	}
	void DeleteElement(int element)		// Удаление элемента
	{
		bool ItsMax = false;
		if (IsEmpty())
		{
			std::cout << "Филиал пуст. Добавьте банкоматы" << std::endl;
			return;
		}
		else if (!FindElementAdditionall(element))
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
			if (Current == Head) // Если это Head, то переопределяем Head
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
		std::cout << "Номер филиала: " << number << "\n";
		std::cout << "___________________________________\n";
		std::cout << "Номер банкомата\t|Адресс банкомата\n";
		while (Current != NULL)
		{
			std::cout << Current->GetNumber() << "\t\t|";
			std::cout << Current->GetAdress() << '\n';
			Current = Current->GetNext();
		}
		std::cout << "___________________________________\n";
		std::cout << std::endl;
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
class Bank
{
public:
	Bank(std::string name)
	{
		this->name = name;
		BranchesCount = 0;
	}
	Bank()
	{
		this->name = "KaiBank";
		BranchesCount = 0;
		AddSortedBranch(1);
		AddSortedBranch(4);
		AddSortedBranch(10);

		Branches[GetElementIndex(1)]->AddSortedCashMachine(3, "Короленко 12");
		Branches[GetElementIndex(1)]->AddSortedCashMachine(4, "Батурина 33");
		Branches[GetElementIndex(1)]->AddSortedCashMachine(10, "Проспект Победы 31");

		Branches[GetElementIndex(4)]->AddSortedCashMachine(45, "Четаева 18");
		Branches[GetElementIndex(4)]->AddSortedCashMachine(10, "Гоголя 32");
		Branches[GetElementIndex(4)]->AddSortedCashMachine(1, "Гагарина 1");

		Branches[GetElementIndex(10)]->AddSortedCashMachine(13, "Фатыха Амирхана 88");
		Branches[GetElementIndex(10)]->AddSortedCashMachine(12, "Восстания 3");
		Branches[GetElementIndex(10)]->AddSortedCashMachine(3, "Маршала Чуйкова 32");
	}

	void SetName(std::string name)
	{
		this->name = name;
	}
	std::string GetName()
	{
		return this->name;
	}
	int GetBranchesCount()
	{
		return BranchesCount;
	}
	
	void SetBranch(Branch* Branches[])
	{
		for(int i = 0; i < MAX_SIZE; i++)
		{
			this->Branches[i] = Branches[i];
		}
	}
	
	Branch** GetBranches()
	{
		return Branches;
	}

	bool IsFull()
	{
		if (BranchesCount == MAX_SIZE)
		{
			std::cout << "Статический список филиалов заполнен!" << std::endl;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	bool IsEmpty()
	{
		if (BranchesCount == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	bool SearchElement(int BranchNumber)
	{
		for (int i = 0; i < BranchesCount; i++)
		{
			if (Branches[i]->GetNumber() == BranchNumber)
			{
				std::cout << "Филиал с таким номером найден под индексом " << i << std::endl;
				return 1;
			}
		}
		std::cout << "Филиал не найден!" << std::endl;
		return 0;
	}
	bool SearchElementAdditionall(int BranchNumber)
	{
		for (int i = 0; i < BranchesCount; i++)
		{
			if (Branches[i]->GetNumber() == BranchNumber)
			{
				return 1;
			}
		}
		return 0;
	}
	void AddSortedBranch(int BranchNumber)
	{
		if (IsEmpty())
		{
			Branches[0] = new Branch(BranchNumber);
			BranchesCount++;
			return;
		}
		else if (IsFull())
		{
			return;
		}
		else if (SearchElementAdditionall(BranchNumber))
		{
			std::cout << "Филиал с таким номером уже существует!" << std::endl;
			return;
		}
		for (int i = 0; i <= BranchesCount; i++)
		{
			if (i == BranchesCount)
			{
				Branches[BranchesCount] = new Branch(BranchNumber);
				BranchesCount++;
				break;
			}
			if (Branches[i]->GetNumber() > BranchNumber)
			{
				for (int j = BranchesCount; j > i; j--)
				{
					Branches[j] = Branches[j - 1];
				}
				Branches[i] = new Branch(BranchNumber);
				BranchesCount++;
				break;
			}			
		}
	}
	int GetElementIndex(int element)
	{
		for (int i = 0; i < BranchesCount; i++)
		{
			if (Branches[i]->GetNumber() == element)
			{
				return i;
			}
		}
		return -1;
	}
	void DeleteBranch(int BranchNumber)
	{
		if (IsEmpty())
		{
			std::cout << "Статический список филиалов пуст. Удалять нечего!" << std::endl;
			return;
		}
		for (int i = 0; i < BranchesCount; i++)
		{
			if (Branches[i]->GetNumber() == BranchNumber)
			{
				delete Branches[i];
				for (int j = i; j < BranchesCount-1; j++)
				{
					Branches[j] = Branches[j + 1];
				}
				BranchesCount--;
				return;
			}
		}
		std::cout << "Элемент не обнаружен в списке филиалов!\n";
	}	
	void ShowBank()
	{
		for (int i = 0; i < BranchesCount; i++)
		{
			Branches[i]->ShowBranch();
		}
	}
	~Bank()
	{
		this->name = "";
		for (size_t i = 0; i < BranchesCount; i++)
		{
			Branches[i]->~Branch();
		}
		BranchesCount = 0;
	}	

private:
	std::string name;
	int BranchesCount;	
	Branch* Branches[MAX_SIZE];
};



