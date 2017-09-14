#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std; 

struct payRec
{
        int number;
        char code;
        double hrs;
};

payRec BuildRec(ifstream&);

void DisplayRec(payRec);

int main()
{ 
   payRec emp;
   ifstream inFile; 
   inFile.open("e:\\pay.dat");
     //insert code for file problem

    while(! inFile.eof())                 
    {
        emp = BuildRec(inFile);
        DisplayRec(emp);
    }

    inFile.close();

	system("pause");
    return 0;
 }

	payRec BuildRec(ifstream& inFile)
	{
		payRec temp;
		inFile >> temp.number >> temp.code >> temp.hrs;
		return temp;
	}
    void DisplayRec(payRec temp)
    {
        cout << temp.number << setw(4) << temp.hrs << endl;
    }

