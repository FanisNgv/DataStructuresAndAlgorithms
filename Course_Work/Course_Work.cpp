#include <iostream>
#include <Windows.h>
#include <ctime>
#include "Bank.h"
#include "FileWorking.h"
#include "ExceptionInput.h"

using namespace std;

void Menu()
{
	std::cout <<
		"1) Добавить филиал\n" <<
		"2) Найти филиал\n" <<
		"3) Удалить филиал\n" <<
		"4) Добавить банкомат в соответствующий филиал\n" <<
		"5) Найти банкомат в соответствующем филиале\n" <<
		"6) Удалить банкомат в соответствующем филиале\n" <<
		"7) Завершить работу программы\n";
}
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	SetConsoleCP(1251);	
	SetConsoleOutputCP(1251); 

	char WhatToUse;
	std::cout <<
		"1) Использовать готовый шаблон частично заполненной структуры\n" <<
		"2) Использовать структуру с текстового доукмента\n" <<
		"3) Создать полностью новую структуру\n";
	WhatToUse = charinput();

	if (WhatToUse == '1')
	{
		bool working = true;
		char choice;
		string str;
		int n;
		int k;
		Bank* KaiBank = new Bank();

		while (working)
		{
			std::cout << "___________" << KaiBank->GetName() << "___________\n" << std::endl;
			KaiBank->ShowBank();
			Menu();
			choice = charinput();
			switch (choice)
			{
			case '1':
				std::cout << "Введите номер филиала: ";
				n = intinput();
				KaiBank->AddSortedBranch(n);
				break;
			case '2':
				std::cout << "Введите номер филиала для поиска: ";
				n = intinput();
				KaiBank->SearchElement(n);
				break;
			case '3':
				std::cout << "Введите номер филиала для удаления: ";
				n = intinput();
				KaiBank->DeleteBranch(n);
				break;
			case '4':
				std::cout << "Введите номер филиала для добавления банкомата: ";
				k = intinput();
				if (!KaiBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = KaiBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата: ";
				n = intinput();
				std::cout << "Введите адрес банкомата: ";
				std::cin.ignore();
				std::getline(std::cin, str);
				KaiBank->GetBranches()[k]->AddSortedCashMachine(n, str);
				break;
			case '5':
				std::cout << "Введите номер филиала для поиска банкомата: ";
				k = intinput();
				if (!KaiBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = KaiBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата для поиска: ";
				n = intinput();
				KaiBank->GetBranches()[k]->FindElement(n);
				break;
			case '6':
				std::cout << "Введите номер филиала, в котором нужно удалить банкомат: ";
				k = intinput();
				if (!KaiBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = KaiBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата для удаления: ";
				n = intinput();
				KaiBank->GetBranches()[k]->DeleteElement(n);
				break;
			case '7':
				std::cout << "Желаете ли сохранить данные в файл?(1): ";
				choice = charinput();
				if (choice == '1')
				{
					File file("DocBank.txt", "out.txt");
					file.Output(KaiBank);
				}
				delete KaiBank;
				return 0;
			default:
				break;
			}
		}
	}
	else if (WhatToUse == '2')
	{
		string name;
		Bank* DocBank = new Bank("");

		bool working = true;
		char choice;
		string str;
		int n;
		int k;

		File file("DocBank.txt", "out.txt");
		if (!file.Input(DocBank))
		{
			cout << "Не удалось взять структуру из файла!\n";
			cout << "Введите название вашего банка: ";
			cin >> name;
			DocBank->SetName(name);
		}
		while (working)
		{
			std::cout << "___________" << DocBank->GetName() << "___________\n" << std::endl;
			DocBank->ShowBank();
			Menu();
			choice = charinput();
			switch (choice)
			{
			case '1':
				std::cout << "Введите номер филиала: ";
				n = intinput();
				DocBank->AddSortedBranch(n);
				break;
			case '2':
				std::cout << "Введите номер филиала для поиска: ";
				n = intinput();
				DocBank->SearchElement(n);
				break;
			case '3':
				std::cout << "Введите номер филиала для удаления: ";
				n = intinput();
				DocBank->DeleteBranch(n);
				break;
			case '4':
				std::cout << "Введите номер филиала для добавления банкомата: ";
				k = intinput();
				if (!DocBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = DocBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата: ";
				n = intinput();
				std::cout << "Введите адрес банкомата: ";
				std::cin.ignore();
				std::getline(std::cin, str);
				DocBank->GetBranches()[k]->AddSortedCashMachine(n, str);
				break;
			case '5':
				std::cout << "Введите номер филиала для поиска банкомата: ";
				k = intinput();
				if (!DocBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = DocBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата для поиска: ";
				n = intinput();
				DocBank->GetBranches()[k]->FindElement(n);
				break;
			case '6':
				std::cout << "Введите номер филиала, в котором нужно удалить банкомат: ";
				k = intinput();
				if (!DocBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = DocBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата для удаления: ";
				n = intinput();
				DocBank->GetBranches()[k]->DeleteElement(n);
				break;
			case '7':
				std::cout << "Желаете ли сохранить данные в файл?(1): ";
				choice = charinput();
				if (choice == '1')
				{
					File file("DocBank.txt", "out.txt");
					file.Output(DocBank);
				}
				delete DocBank;
				return 0;
				break;
			default:
				break;
			}
		}
	}
	else if (WhatToUse == '3')
	{
		string name;
		Bank* EmptyBank = new Bank("");

		bool working = true;
		char choice;
		string str;
		int n;
		int k;

		std::cout << "Введите название вашего банка: ";
		cin >> str;
		EmptyBank->SetName(str);

		while (working)
		{
			std::cout << "___________" << EmptyBank->GetName() << "___________\n" << std::endl;
			EmptyBank->ShowBank();
			Menu();
			choice = charinput();
			switch (choice)
			{
			case '1':
				std::cout << "Введите номер филиала: ";
				n = intinput();
				EmptyBank->AddSortedBranch(n);
				break;
			case '2':
				std::cout << "Введите номер филиала для поиска: ";
				n = intinput();
				EmptyBank->SearchElement(n);
				break;
			case '3':
				std::cout << "Введите номер филиала для удаления: ";
				n = intinput();
				EmptyBank->DeleteBranch(n);
				break;
			case '4':
				std::cout << "Введите номер филиала для добавления банкомата: ";
				k = intinput();
				if (!EmptyBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = EmptyBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата: ";
				n = intinput();
				std::cout << "Введите адрес банкомата: ";
				std::cin.ignore();
				std::getline(std::cin, str);
				EmptyBank->GetBranches()[k]->AddSortedCashMachine(n, str);
				break;
			case '5':
				std::cout << "Введите номер филиала для поиска банкомата: ";
				k = intinput();
				if (!EmptyBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = EmptyBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата для поиска: ";
				n = intinput();
				EmptyBank->GetBranches()[k]->FindElement(n);
				break;
			case '6':
				std::cout << "Введите номер филиала, в котором нужно удалить банкомат: ";
				k = intinput();
				if (!EmptyBank->SearchElementAdditionall(k))
				{
					std::cout << "Филиал не найден!" << std::endl;
					break;
				}
				k = EmptyBank->GetElementIndex(k);
				std::cout << "Введите номер банкомата для удаления: ";
				n = intinput();
				EmptyBank->GetBranches()[k]->DeleteElement(n);
				break;
			case '7':
				std::cout << "Желаете ли сохранить данные в файл?(1): ";
				choice = charinput();
				if (choice == '1')
				{
					File file("DocBank.txt", "out.txt");
					file.Output(EmptyBank);
				}
				delete EmptyBank;
				return 0;
			default:
				break;
			}
		}
	}



    
	
	
	
	
}