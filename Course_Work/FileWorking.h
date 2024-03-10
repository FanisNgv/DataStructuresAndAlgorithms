#pragma warning (disable : 4996)
#include "Bank.h"
#include <fstream>
#include <iostream>

using namespace std;

inline bool isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
		return false;

	char* p;
	strtol(s.c_str(), &p, 10);
	return (*p == 0);
}

class File
{
private:
	string input_path;
	string output_path;
public:
	File(string in_path, string out_path) 
	{
		input_path = in_path;
		output_path = out_path;
	};
	bool Input(Bank* bank)
	{
		string text, Branch;
		int number = -1;
		char buffer[100];
		char* f;

		ifstream file(input_path);

		if (!file.is_open()) 
		{
			return false;
		}

		if (!file.eof()) 
		{
			file.getline(buffer, 100);
			text = buffer;
			bank->SetName(text);
		}
		else 
		{
			cout << "Файл пуст!\n";
			return false;
		}
		while (!file.eof()) 
		{
			file.getline(buffer, 100); 
			f = strtok(buffer, " ");
			if (f == NULL) 
			{
				continue;
			}
			if (f) 
			{
				Branch = f;
			}
			bank->AddSortedBranch(stoi(Branch));
			f = strtok(NULL, " ");
			while (f) 
			{
				if (f) 
				{
					text = f;
				}
				f = strtok(NULL, " ");
				if (!isInteger(f))
				{
					text += " ";
					text += f;
					f = strtok(NULL, " ");
				}
				if (f)
				{
					text += " ";
					text += f;
				}
				f = strtok(NULL, " ");
				if (f)
				{
					number = stoi(f);
				}
				else
				{
					return false;
				}
				bank->GetBranches()[bank->GetElementIndex(stoi(Branch))]->AddSortedCashMachine(number, text);
				f = strtok(NULL, " ");
			}
		}
		file.close();
		return true;
	}

	bool Output(Bank* bank) 
	{
		ofstream file(output_path);
		if (!file.is_open())
		{
			return false;
		}
		file << "___________" << bank->GetName() << "___________\n" << std::endl;
		for (int i = 0; i < bank->GetBranchesCount(); i++)
		{
			bank->GetBranches()[i]->GetNumber();
			CashMachine* Current = bank->GetBranches()[i]->GetHead();
			file << "Номер филиала: " << bank->GetBranches()[i]->GetNumber() << "\n";
			file << "___________________________________\n";
			file << "Номер банкомата\t|Адресс банкомата\n";
			while (Current != NULL)
			{
				file << Current->GetNumber() << "\t\t|";
				file << Current->GetAdress() << '\n';
				Current = Current->GetNext();
			}
			file << "___________________________________\n";
			file << std::endl;
		}
		file.close();
		return true;
	}
};
