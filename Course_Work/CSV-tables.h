#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

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
        getline(file, text);
        bank->SetName(text);
        while (getline(file, text))
        {

        }
    }
};

int main()
{
    ifstream inputFile;
    inputFile.open("C:\\temp\\student-records.csv");
    string line = "";

    vector<StudentRecord> students;
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        //StudentId, Last Name, FirstName, Age, Phone Number, GPA
        string studentId;
        string lastName;
        string firstName;
        int age;
        string phone;
        double gpa;
        string tempString;

        getline(inputString, studentId, ',');
        getline(inputString, lastName, ',');
        getline(inputString, firstName, ',');
        getline(inputString, tempString, ',');
        age = atoi(tempString.c_str());
        getline(inputString, phone, ',');
        getline(inputString, tempString);
        gpa = atof(tempString.c_str());

        StudentRecord student(studentId, lastName,
            firstName, age, phone, gpa);
        students.push_back(student);
        line = "";
    }

    displayStudents(students);
}