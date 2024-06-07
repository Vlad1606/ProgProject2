#include "pch.h"
#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int writeFile()
{
	ofstream myfile;
	myfile.open("example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();
	return 0;
}

int addToFile()
{
	ofstream myfile;
	myfile.open("example.txt", ios::ate | ios::app);
	myfile << "Adding to the file.\n";
	myfile.close();
	return 0;
}

int readFile()
{
	string line;
	ifstream myfile("example.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << "\n";
		}
		myfile.close();
	}
	else cout << "unable to open file";

	return 0;
}

