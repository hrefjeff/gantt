#include <iostream>
#include <fstream>
#include <string>

#include <cctype>
#include <cmath>
#include <limits>
#include <vector>

#include "AbstractSchedStrat.h"

using namespace std;

#define NUM_OF_STRATS 2

void printMenu();
int getInputMethod();

int getInfo(string, int);
int check(int,int);

void loadDataFromFile(AbstractSchedStrat * stratArr[]);
void loadDataFromUser(AbstractSchedStrat * stratArr[]);

void readFile(string filename, Process * arr, int dataSize);

void makeCharts(AbstractSchedStrat * stratArr[]);

int main()
{

	int choice = 0;
		
	FirstComeFirstServe fcfs;
	RoundRobin rr;

	// ----------- Set Time Slice of Round Robin---------------
	rr.setTimeSlice(9);
	// --------------------------------------------------------

	AbstractSchedStrat * stratagyArray[NUM_OF_STRATS] = {&fcfs, &rr};

	printMenu();
	choice = getInputMethod();

	// If read from file
	if (choice == 1)
	{
		loadDataFromFile(stratagyArray);
	} 

	// If user input
	else 
	{
		loadDataFromUser(stratagyArray);
	}

	makeCharts(stratagyArray);

	return 0;
}


/*************************************************
  Name      : PrintMenu
  Writer(s) : Jeffrey Allen
  Purpose   : Prints a menu for the user
  Incoming  : N/A
  Outgoing  : N/A
  Return    : N/A (void)
*************************************************/
void printMenu()
{
	cout << endl;
	cout << "\t\t----------------------------------------" << endl;
	cout << "\t\t  Comparison of Scheduling Algorithms   " << endl;
	cout << "\t\t----------------------------------------" << endl;
	cout << endl << endl;

	cout << "Welcome to the job sechduling stategies program." << endl;
	cout << "******************Program Flow******************" << endl;
	cout << "\t A) Decide input method of information" << endl;
	cout << "\t B) Based on decision, either: " << endl;
	cout << "\t\t 1] You will put in your own data." << endl;
	cout << "\t\t 2] Data will be read from file." << endl;
	cout << "\t C) Results and analyzations will be written to ~/Results/ directory: " << endl;
	cout << "\t\t 1] gantt.html" << endl;
	cout << "\t\t 2] turnAround.html" << endl;
	cout << "\t\t 3] wait.html" << endl;
	cout << "\t\t 4] waitAvg.html\n" << endl;
}

/*************************************************
  Name      : getInputMethod
  Writer(s) : Jeffrey Allen
  Purpose   : Prompts a choice from the user.
  Incoming  : N/A
  Outgoing  : 1) read from file 2) build from user
  Return    : int
*************************************************/
int getInputMethod()
{
	int option = 0;

	cout << "\n" << endl;
	cout << "A) Which input method would you like to use?" << endl;
	cout << "\t1] Read from a file." << endl;
	cout << "\t2] Start from scratch and enter your own process?\n" << endl;

	cout << "Choice: ";
	cin >> option;

	while ((option <= 0) || (option >= 3)) {
		cout << "Please enter a valid choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> option;
	}

	return check(option,3);
}

int getInfo(string Item, int forNumber)
{
	int number = 0;

	cout << "Procces " << forNumber << " " << Item << " : ";
	cin >> number;

	return check(number,10);	
}

int check(int thingToCheck, int max)
{
	// While lesser than 0, or greater than max
	// KEEEEEEEP IT MOOOOVIN
	while ((0 >= thingToCheck) || (thingToCheck >= max))
	{
		cout << "Please enter a valid choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> thingToCheck;
	}

	return thingToCheck;
}

void loadDataFromFile(AbstractSchedStrat * stratArr[])
{

	fstream file;
	string fileName;
	bool badFile = true;

	do 
	{
		cout << "Input file name: ";
		cin >> fileName;

		file.open(fileName);
		badFile = file.fail();
		file.close();

	} while (badFile);

	int numOfProcesses = 0;

	do {

		cout << "Number of processes (max 20): ";
		cin >> numOfProcesses;

	} while (numOfProcesses <= 0);

	Process * tmpArray = new Process [numOfProcesses];

	readFile(fileName, tmpArray, numOfProcesses);

	for (int i = 0; i<NUM_OF_STRATS; i++)
	{
		for (int j = 0; j<numOfProcesses; j++)
		{
			stratArr[i]->addProcess(&tmpArray[j]);
		}
	}

	// for (int i = 0; i<numOfLinesToRead; i = i + 4)
	// 	cout << tmpArray[i] << " " << tmpArray[i+1] << " " << tmpArray[i+2] << " " << tmpArray[i+3] << endl;
}

void loadDataFromUser(AbstractSchedStrat * stratArr[])
{
	

	char pChoice = 'y';

	string name = "";
	int pNumber = 0;
	int pLevel = 0;
	int bTime = 0;


	do 
	{
		cout << "Process " << pNumber << " name: "; cin >> name;
		bTime = getInfo("burst time",pNumber);
		pLevel = getInfo("priority",pNumber);

		// implement when I get another strategy
		for (int i = 0; i < NUM_OF_STRATS; i++)
			stratArr[i]->addProcess(new Process(name,pNumber,bTime,pLevel));
		
		cout << "Enter another process? (y or n): "; cin >> pChoice;

		pNumber++;

	} while ((pChoice != 'n') && (pChoice != 'N'));

}

void readFile(string filename, Process * arr, int dataSize) { 

	// Insert each process into respective strategy array

	int i = 0;
	ifstream inFile;
	inFile.open(filename.c_str());

	string rName;
	int rNumber;
	int rBurstTime;
	int rPriority;

	if (!inFile.fail())
	{
		while ((!inFile.eof()) && (i < dataSize))
		{
			inFile >> rName;
			inFile >> rNumber;
			inFile >> rBurstTime;
			inFile >> rPriority;

			arr[i] = new Process(rName, rNumber, rBurstTime, rPriority);

			i++;
		}
	}

	inFile.close();
}

void makeCharts(AbstractSchedStrat * stratArr[])
{

	vector<Process *> statisticColumn;

	// *****implement when I get another strategy*********
	for (int i = 0; i < NUM_OF_STRATS; i++)
	{
		cout << "~~~~~~~~~~~~~~~~~~~~~~~STRATEGY " << i << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		stratArr[i]->printWaitQueue();
		stratArr[i]->makeGantt();
		stratArr[i]->makeColumnWait();

		// ~~~~~~~~~~~~~~~~~~~~~~Write charts out~~~~~~~~~~~~~~~~~~~~~~~~

		statisticColumn = stratArr[i]->getColumnWait();
		for (int k = 0; k < statisticColumn.size(); k++)
		{
			cout << "Process " << k << ", " << statisticColumn[k]->getName() << ", has wait time of " << statisticColumn[k]->getWaitTime() << "\t : ";
		 	for (int m = 0; m < statisticColumn[k]->getWaitTime(); m++)
		 	{
		 		cout << "|";
		 	}
			cout << endl;
		}
		statisticColumn.clear();

		stratArr[i]->makeColumnTurnAround();
		statisticColumn = stratArr[i]->getColumnTurnAround();
		
		cout << endl;
		cout << endl;

		for (int k = 0; k < statisticColumn.size(); k++)
		{
			cout << "Process " << k << ", " << statisticColumn[k]->getName() << ", has turn around time of " << statisticColumn[k]->getTurnAroundTime() << "\t : ";
		 	for (int m = 0; m < statisticColumn[k]->getTurnAroundTime(); m++)
		 	{
		 		cout << "|";
		 	}
			cout << endl;
		}

		cout << endl;
		statisticColumn.clear();
	}
}