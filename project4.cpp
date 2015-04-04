

/***************************************************************/

/* PROGRAM: Project 4                                                                   */

/*                                                                                      */

/* AUTHOR: Tim Muller                                                                   */

/*                                                                                      */

/* DATE: 2/25/15                                                                        */

/*                                                                                      */

/* REVISIONS: Lots of bugs.                                                             */

/*                                                                                      */

/* PURPOSE: Simulates a slot machine, and lets the user print it to screen, 
and print out a certain reel. Includes dynamic memory.          */

/*                                                                                      */

/**************************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "stringFunctions.h"

struct symbol
	{
		char* symbolName;
		int bonusValue;
		bool isBonusZero;
	};

struct reel
{
	symbol* arrayOfSymbols;
};

using namespace std;

//These are all my function prototypes.
symbol* copySymbolsToArray(symbol* ptrsymbolStructArray);
void showMenu();
void switchCaseMenu(symbol* ptrsymbolStructArray, reel* ptrslotMachineArray);
void repopulateSlotMachine(symbol* ptrsymbolStructArray, reel* ptrslotMachineArray);
void outputSlotMachineToScreen(reel* ptrslotMachineArray);
void displayReelValue(reel* ptrslotMachineArray);
symbol* symbolPointerIncrement(symbol* ptrsymbolStructArray, int randomNum);
reel* reelPointerIncrement(reel* ptrslotMachineArray, int randomNum);
reel* allocateMemory(reel* ptrslotMachineArray);
void deleteMemory(reel* ptrslotMachineArray);

int main()
{
	//Makes a pointer that will point to my struct array containing the symbols file.
	symbol* ptrsymbolStructArray = NULL;
	//Makes a pointer that will point the the struct simulating my slot machine.
	reel* ptrslotMachineArray = NULL;

	//Copies the symbols from the file to a struct array, delcares dynamic memory for it, and returns a pointer to the base address.
	ptrsymbolStructArray = copySymbolsToArray(ptrsymbolStructArray);

	//Populates the slot machine once so the user can select other options from the menu without printing out garbage, and also dynamically
		//allocates memory for the char array containing symbol names.
	ptrslotMachineArray = allocateMemory(ptrslotMachineArray);
	
	repopulateSlotMachine(ptrsymbolStructArray, ptrslotMachineArray);

	

	//Runs the switch case menu, which prints out the menu and waits for user input.
	switchCaseMenu(ptrsymbolStructArray, ptrslotMachineArray);

	deleteMemory(ptrslotMachineArray);
}

//Copies the symbols to an array by using a nested for loop.
symbol* copySymbolsToArray(symbol* ptrsymbolStructArray)
{
	char* fileNameTemp = new char[30];
	char* fileName;
	
	ifstream symbolsFile;
	
	cout << "Enter name for symbols file:";
	cin >> fileNameTemp;
	
	int fileNameLength = stringLength(fileNameTemp);
	fileName = new char[fileNameLength + 1];
	
	stringCopy(fileNameTemp, fileName);
	symbolsFile.open(fileName);

	ptrsymbolStructArray = new symbol[6];
	symbol* home = ptrsymbolStructArray;
	int nameLength = 0;
	char* nameTemp = new char[15];


	for(int j = 0; j < 6; j++)
	{
		
		symbolsFile >> nameTemp;

		nameLength = stringLength(nameTemp);
		(*ptrsymbolStructArray).symbolName = new char[nameLength + 1];
		stringCopy(nameTemp, (*ptrsymbolStructArray).symbolName);
		cout << (*ptrsymbolStructArray).symbolName << endl;
		symbolsFile >> (*ptrsymbolStructArray).bonusValue;
		ptrsymbolStructArray++;
	}

	//cout << ptrsymbolStructArray<< endl;
	delete[] fileNameTemp;
	delete[] fileName;
	delete[] nameTemp;
	symbolsFile.close();

	return home;
}

//Copies strings from the source string to the destination string.

void showMenu()
{	cout << endl;
	cout << "1: to randomize the slot machine state." << endl;
	cout << "2: to print the slot machine config to the screen." << endl;
	cout << "3: to print out a certain position on the slot machine." << endl;
	cout << "4: exit" << endl;
	cout << endl;
}
//Waits for the user to put a number between 1 and 5, and performs the function in that case.
void switchCaseMenu(symbol* ptrsymbolStructArray, reel* ptrslotMachineArray)
{
	char userSelectedOption = '0';
	bool exit = 0;
	while(exit == 0)
	{
		showMenu();
		cin >> userSelectedOption;
		switch(userSelectedOption)
		{
			case '1':
				//deleteMemory(ptrslotMachineArray);
				repopulateSlotMachine(ptrsymbolStructArray, ptrslotMachineArray);
				break;
			case '2':
				outputSlotMachineToScreen(ptrslotMachineArray);
				break;
			case '3':
				displayReelValue(ptrslotMachineArray);
				break;
			case '4':
				exit = 1;
				cout << "Goodbye." << endl;
				break;
			default:
				cout << "This is an invalid input." << endl;
				break;
		}
	}
}

void repopulateSlotMachine(symbol* ptrsymbolStructArray, reel* ptrslotMachineArray)
{
	//Makes the numbers from the random number generator more random.
	srand(time(NULL));
	int randomNum;
	//deleteMemory(ptrslotMachineArray);

	


	symbol* randomPtrsymbolStructArray;
	symbol* ptrsymbolReelArray;
	
	int nameLength = 0;
	char* nameTemp = new char[15];
	
	for(int i = 0; i < 3; i++)
	{
		ptrsymbolReelArray = (*ptrslotMachineArray).arrayOfSymbols;
		for(int j = 0; j < 10; j++)
		{

			//assigns a random number between 1 and 5 to randomNum.
			randomNum = rand() % 6;
			randomPtrsymbolStructArray = symbolPointerIncrement(ptrsymbolStructArray, randomNum);


			//Copies a random symbol from symbolsArray to a spot on the 'reel' on slotMachineArray.
			stringCopy((*randomPtrsymbolStructArray).symbolName, nameTemp);
			nameLength = stringLength(nameTemp);
			if((*ptrsymbolReelArray).symbolName != NULL)
			{
				delete[] (*ptrsymbolReelArray).symbolName;
			}

			(*ptrsymbolReelArray).symbolName = new char[nameLength + 1];
			stringCopy((*randomPtrsymbolStructArray).symbolName, (*ptrsymbolReelArray).symbolName);
			(*ptrsymbolReelArray).bonusValue = (*randomPtrsymbolStructArray).bonusValue;
			if((*ptrsymbolReelArray).bonusValue > 0)
			{
				(*ptrsymbolReelArray).isBonusZero = false;
			}else{
				(*ptrsymbolReelArray).isBonusZero = true;
			}
			ptrsymbolReelArray++;

		}

		ptrslotMachineArray++;
	}
	cout << "Slot machine randomized." << endl;
	delete[] nameTemp;

}

//Outputs the slot machine array to screen using a nested for loop.
void outputSlotMachineToScreen(reel* ptrslotMachineArray)
{
	symbol* ptrsymbolReelArray;
	reel* homeslotMachineArray = ptrslotMachineArray;
	ptrsymbolReelArray = (*ptrslotMachineArray).arrayOfSymbols;

	for(int i = 0; i < 10; i++)
	{	
		for(int j = 0; j < 3; j++)
		{
			
			
			ptrsymbolReelArray = (*ptrslotMachineArray).arrayOfSymbols;
			for (int k = 0; k < i; k++)
			{
				ptrsymbolReelArray++;
				
			}
			cout << (*ptrsymbolReelArray).symbolName << "\t";
			ptrslotMachineArray++;
		}
		cout << endl;
		ptrslotMachineArray = homeslotMachineArray;
	}
}


//Prompts the user for a reel and coloumn, and then prints the symbol and its bonus at that location.
void displayReelValue(reel* ptrslotMachineArray)
{
	int row;	
	int coloumn;
	reel* ptrColumReel;
	symbol* ptrRowsymbolStructArray;

	cout << "Enter a number between 1 and 3 for the coloumn" << endl;
	cin >> coloumn;

	cout << "Enter a number between 1 and 10 for the row" << endl;
	cin >> row;
	

	// Stringcompare returns an int, specifically the row in symbolsArray where it found the matching string.

	ptrColumReel = reelPointerIncrement(ptrslotMachineArray, coloumn - 1);
	symbol* ptrsymbolReelArray = (*ptrColumReel).arrayOfSymbols;
	ptrRowsymbolStructArray = symbolPointerIncrement(ptrsymbolReelArray, row - 1);
	

	

	cout << "The symbol is " << (*ptrRowsymbolStructArray).symbolName << endl;
	
	cout << "The bonus value is " << (*ptrRowsymbolStructArray).bonusValue << "." << endl;

	if ((*ptrRowsymbolStructArray).isBonusZero == true)
	{
		cout << "The isBonusZero bool is true." << endl;
	}

	if ((*ptrRowsymbolStructArray).isBonusZero == false)
	{
		cout << "The isBonusZero bool is false." << endl;
	}

	
}
//Compares 2 strings; the first one which is the symbol at a specific stop number. The second string is from the symbolsArray.

symbol* symbolPointerIncrement(symbol* ptrsymbolStructArray, int randomNum)
{
	for (int i = 0; i < randomNum; i++)
	{
		ptrsymbolStructArray++;
	}
	return ptrsymbolStructArray;

}


reel* reelPointerIncrement(reel* ptrslotMachineArray, int randomNum)
{
	for (int i = 0; i < randomNum; i++)
	{
		ptrslotMachineArray++;
	}

	return ptrslotMachineArray;
}

reel* allocateMemory(reel* ptrslotMachineArray)
{
	ptrslotMachineArray = new reel[3];
	reel* homeslotMachineArray = ptrslotMachineArray;
	symbol* ptrsymbolReelArray;
	
	for (int i = 0; i < 3; i++)
	{

		(*ptrslotMachineArray).arrayOfSymbols = new symbol[10];
		ptrsymbolReelArray = (*ptrslotMachineArray).arrayOfSymbols;
		for(int j = 0; j < 10; j++)
		{
			(*ptrsymbolReelArray).symbolName = NULL;
			ptrsymbolReelArray++;
		}
		ptrslotMachineArray++;
	}

	ptrslotMachineArray = homeslotMachineArray;

	return homeslotMachineArray;
}

void deleteMemory(reel* ptrslotMachineArray)
{
	if(ptrslotMachineArray != NULL)
	{
		reel* homeslotMachineArray = ptrslotMachineArray;
		symbol* ptrsymbolReelArray;

		ptrsymbolReelArray = (*ptrslotMachineArray).arrayOfSymbols;

		for (int i = 0; i < 3; i++)
		{
			ptrsymbolReelArray = (*ptrslotMachineArray).arrayOfSymbols;
			for (int j = 0; j < 10; j++)
			{

				if((*ptrsymbolReelArray).symbolName != NULL)
				{
					delete[] (*ptrsymbolReelArray).symbolName;
					(*ptrsymbolReelArray).symbolName = NULL;
				}

				ptrsymbolReelArray++;
			}

			if((*ptrslotMachineArray).arrayOfSymbols != NULL)
				{
					delete[] (*ptrslotMachineArray).arrayOfSymbols;
				}
			ptrslotMachineArray++;
		}
		
		homeslotMachineArray = ptrslotMachineArray;
		
		if(ptrslotMachineArray != NULL)
		{
			delete[] ptrslotMachineArray;
			ptrslotMachineArray = NULL;
		}
	}
}