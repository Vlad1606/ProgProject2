#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

int openfile()
{
	ofstream fout;
	fout.open("out.txt");
	char str[30] = "Hello World!";

	fout << str;
	fout.close();

	return 0;
}

int readfile()
{
	ifstream fin;
	fin.open("out.txt");
	char ch;

	while (!fin.eof())
	{
		fin.get(ch);
		cout << ch;
	}

	fin.close();
	return 0;
}

int numOfLines()
{
	ifstream fin;
	fin.open("out.txt");

	int count = 0;
	char str[80];

	while (!fin.eof())
	{
		fin.getline(str, 80);
		count++;
	}
	return 0;
}

class Student
{
	int admno;
	char name[50];
public:
	void setData();
	void showData();
	int getAdmno();
};
void Student::setData()
{
	cout << "\nEnter admission number. ";
	cin >> admno;
	cout << "\nEnter name of student ";
	cin.getline(name, 50);
}
void Student::showData()
{
	cout << "\nAdmission no. : " << admno;
	cout << "\nStudent Name : " << name;
}
int Student::getAdmno()
{
	return admno;
}

void write_record()
{
	ofstream outFile;
	outFile.open("student.dat", ios::binary | ios::app);

	Student obj;
	obj.setData();
	outFile.write((char*)&obj, sizeof(obj));

	outFile.close();
}

void display()
{
	ifstream inFile;
	inFile.open("student.dat", ios::binary);

	Student obj;


	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		obj.showData();
	}
	inFile.close();
}

void search(int n)
{
	ifstream inFile;
	inFile.open("student.dat", ios::binary);

	Student obj;

	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		if (obj.getAdmno() == n)
		{
			obj.showData();
		}
	}

	inFile.close();
}

void delete_record(int n)
{
	Student obj;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);

	ofstream outFile;
	outFile.open("temp.dat", ios::out | ios::binary);

	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		if (obj.getAdmno() != n)
		{
			outFile.write((char*)&obj, sizeof(obj));
		}
	}

	inFile.close();
	outFile.close();

	remove("student.dat");
	rename("temp.dat", "student.dat");
}

void modify_record(int n)
{
	fstream file;
	file.open("student.dat", ios::in | ios::out);

	Student obj;

	while (file.read((char*)&obj, sizeof(obj)))
	{
		if (obj.getAdmno() == n)
		{
			cout << "\nEnter the new details of student";
			obj.setData();
			int pos = -1 * static_cast<int>(sizeof(obj));
			file.seekp(pos, ios::cur);

			file.write((char*)&obj, sizeof(obj));
		}
	}

	file.close();
}
