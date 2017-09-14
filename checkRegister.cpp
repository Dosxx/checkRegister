
// Author        : Kekeli D Akouete		
// Source file   : checkRegister.cpp	
// Description   : Check Register that read data from a File	
// Compiler used : NetBeans IDE 8.1

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std; 

// Structure declaration
struct custTrans
{
    int transCode;
    double transAmt;
};
struct totals
{
    double credits;
    double debits;
    double servChrge;
    int transCount;
};

// Function Prototypes
        totals buildTotal(ofstream&);
        void displayTotals(totals);
	void displayTitle();
	double getBegBal(ifstream&);
	void displayBal(double);
	custTrans getData(ifstream&);
	double processCheck(double, double);
	double processDeposit(double, double);
	double processATM(double, double);
	double processSvcChg(double);


//Global Constants
const double	CHARGE = 10,
				ATMFEE =  2;


int main()
{
	//Variable Declarations
	double balance;
        
        custTrans checkIn; 
        totals report;
        
        ifstream inFile;
        ofstream outFile;
        // Initialization        
        report = buildTotal(outFile);
        
        inFile.open("C:\\Users\\kekelidos\\checkIn.dat");   //file location path
	
        if (inFile.fail())
        {
            cout << " Input file open failed.\n";
            exit(1);
        }
        // Formating The output
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
        
        displayTitle();
	balance = getBegBal(inFile);
        while(!inFile.eof())
        {
                checkIn = getData(inFile);
                
		switch(checkIn.transCode)
		{
			case 1: balance = processCheck(balance, checkIn.transAmt);
                                report.debits += checkIn.transAmt;  break;
			case 2: balance = processDeposit(balance, checkIn.transAmt);
                                report.credits +=  checkIn.transAmt ;  break;
			case 3: balance = processATM(balance, checkIn.transAmt);
                                report.debits += checkIn.transAmt;  break;
		}
		displayBal(balance);
		if(balance < 0)
                {
			balance = processSvcChg(balance);
                        report.servChrge = (ATMFEE + CHARGE );
                }

                report.transCount++;
        }
        inFile.close();
        // initializing the output stream
        outFile.open("C:\\Users\\kekelidos\\checkOut.dat"); // file location path
        
        if (outFile.fail())
       {
           cout << " Output file open failed.\n";
           exit(1);
       }
        // output to a file formating 
        outFile.setf(ios::fixed);
	outFile.setf(ios::showpoint);
	outFile.precision(2);
        
        outFile << balance;
        
        outFile << setw(8)  << report.credits
                        << setw(8)  << report.debits
                          << setw(6) << report.servChrge
                             << setw(2) << report.transCount;

       outFile.close();
       cout << endl << endl;
       displayTotals(report);
 
return 0;
}	

	void displayTitle()
	{
		cout << "\n       Check Register\n\n";
	}

	double getBegBal(ifstream& inFile)
	{
		double bal;
                inFile >> bal;
		return bal;
	}

	void displayBal(double bal)
	{
		cout << "\t\tBalance = $" << setw(10) << bal;
	}

	custTrans getData(ifstream& inFile)
	{
                custTrans data;
                inFile >> data.transCode >> data.transAmt ;
                return data;
	}

	double processCheck(double bal, double amt)
	{
		cout << "\n  Check =    " << setw(10) << amt;
		return (bal - amt);
	}

	double processDeposit(double bal, double amt)
	{
		cout << "\n  Deposit =  " << setw(10) << amt;
		return (bal + amt);
	}
	double processATM(double bal, double amt)
	{
		cout << "\n  ATM     =  " << setw(10) << amt;
		bal = bal - amt;
		displayBal(bal);
		bal = bal - ATMFEE;
		cout << "\n  ATM Fee =  " << setw(10) << ATMFEE;
		return (bal);
	}
	double processSvcChg(double bal)
	{
		cout << "\n  Service chg =" << setw(8) << CHARGE;
		bal = bal - CHARGE;
		displayBal(bal);
		return (bal);
	}
       
        totals buildTotal(ofstream& outFile)
        {
            
            totals data;
            outFile  << data.credits << data.debits 
                    << data.servChrge << data.transCount;                        
            return data;
        }
        
        void displayTotals(totals data)
        {
          cout <<"\n Total Credit          = $" << setw(8) << data.credits << endl
               <<" Total Debit           = $" << setw(8) << data.debits << endl
               <<" Total Service Charges = $"  << setw(8) << data.servChrge << endl  
               <<" Total Transaction     =  "<< setw(5) << data.transCount  << endl;
        }
        
        
