///////////////////////////////////////////////////////////////////////////////////////////////
// -Program Summary:
//  This program will generate a user provided total of random values (1 - 100). 
//  Each value will be written to a file named "numbers.bin" 
//  A separate function will open the "numbers.bin" file and will read each value,	
//  pushing each value to the top of the stack.  
//  After the data is pushed, the stack will output all items, popping the most recent 
//  data off the stack, while returning each previous value.  
//  This continues until all items on the stack have been popped.   
//
//
//  Justin C. Shows
//  20201004

// ////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
using namespace std;

//	Node will be embedded privately in stack class to protect its data members
struct node
{
	int data;
	node* behind;
};

//  Stack class will implement the node as a private member 
class stack
{
 private: 
	 node* top;

 public:
	 stack();
	 ~stack();

//	Points at top, invokes getTop for each value until stack is empty

	void viewStack();

//	If value is at top, returns the value

	int peekTop();

//	Points ahead of current top, returns top's value, deletes current top & iterates to new top, returning each value	

	int getTop();

//	Provided a value, inserts value at top of stack 

	int pushToStack(int value);
};

//	On creation of stack object, inits top pointer member variable to null
stack::stack()
{
	top = NULL;
	cout << "Stack object created. " << endl << endl;
}

//  Destructor
stack::~stack()
{
	int count = 1;

//	Checks if object was destroyed, if not, deletes it: 
	while (top != NULL)
	{
		count = count + 1;
		cout << "Deleting: " << getTop() << endl;

//		Every 10 items, break output stream
		if (count % 10 == 0) { cout << endl; count = 1; }
	}

//	 If already empty, outputs to screen:
 	 if (top == NULL)
     {
	   cout << endl << "Destroyed stack object. " << endl << endl;
     }
}

//  Provided a value, pushes to top of stack, redirects pointers to accomodate new top
int stack::pushToStack(int value)
{
	struct node* newNode = new node;

	if (newNode == NULL) { cout << "Error creating new node to insert. "; return 1; }

//	Grab new data passed in function
	newNode->data = value;

//	New node points to current top
	newNode->behind = top;

//	Top now points to new location of top - newnode
	top = newNode;

	return 0;
}

//  Returns current top value - note it does not pop the top value:
int stack::peekTop()
{
//  If there's a valid top, return that top's value
	if (top != NULL)
	{
		return top->data;
	}

//	If stack is empty, returns null
	else
	{
		cout << "Nothing to peek. " << endl;
		return NULL;
	}
}

//	Returns value for current top, deletes that top, and iterates through until top is empty
int stack::getTop()
{
	if (top != NULL)
	{
//		Grab top value from stack
		int topValue = peekTop();
		struct node* temp = top;

//		Top points to new top
		top = temp->behind;

//		Delete old top
		delete temp;

//		Note this data is from old top
		return topValue;
	}

  return NULL;
}

//   Displays all items. While top is present, outputs each value, deletes current top & points to new top
void stack::viewStack()
{
//	Used to format output 
	int count = 1;
	cout << "Stack: " << endl;

//  Until no more stack values are present in linked data: 
	while (top != NULL)
	{
		cout << getTop() << "\t";

//	    Every 10 items, break this output stream: 
		if (count % 10 == 0)
		{
			cout << endl;
		}

//	    Track # times item is output: 
		count = count + 1;
	}

//	Display total size of stack:
	cout << endl << endl;
	cout << "Total items in stack: " << count - 1 << " " << endl;
}

//----------------------------END CLASS----------------------------------------------------------

//	If total #'s to generate is not passed in cmd line, grabs total from user  
int getTotal();

//	Writes random numbers into numbers.bin file 
int writeBinary(const int& totalValues);

//  Reads from previously written to numbers.bin file and pushes each value read from file to stack
int getData(stack& myStack);

int main(int argc, char *argv[]) 
{
//	Used later to seed random numbers in binary file

	srand((unsigned)time(NULL));

//	Total numbers to be generated from user:

	int totalValues = 0;

//	If user didn't pass total in cmd line, invokes function to get total from user:

	if (argc != 2) 
	{
		cout << "Please provide total # of data to generate: "<< endl;
		totalValues = getTotal();
	}

//	Provided valid value in command line, just stores it: 

	else if (argc == 2) { totalValues = stoi(argv[1]); }

//  Create stack object to reference start of given stack:

	stack myStack;

	if (totalValues != 0)
	{
//		Write random #'s (1-100) to binary file "numbers.bin"
		writeBinary(totalValues);

//		Read from "numbers.bin" & push each file value to top of stack: 
		getData(myStack);
	}
	else { cout << "Error getting total values. " << endl; exit(1); }
	cout << "\n\n\n";

//	View all items in stack, peeks at top, returns value, pops most recent top, points to new top:
	myStack.viewStack();

   return 0;
}

//  If user didn't give total #'s to generate in cmd line, this function returns their input for TTL: 
int getTotal()
{
	int total = 0;

//	Total must be between 1-1000:
	while (true)
	{
		cout << "Enter total amount of numbers to generate: (1-1000 only) " << endl << "-1 TO EXIT" << endl;
		cin >> total;
		if (total >= 1 && total <= 1000) { break; }
		if (total == -1) { cout << "Closing program..." << endl; exit(1); }
	}

	return total;
}

//	Creates numbers.bin file and writes random #'s in binary to this file 
int writeBinary(const int& total)
{
	ofstream writeBinary;
	writeBinary.open("numbers.bin", ios::out | ios::binary);

//  Closes if cannot reference file
	if (!writeBinary.is_open())
	{
		cout << "Error creating new file to write to. " << endl; exit(1);
	}

//	Output
	cout << "Data written to file: (" << total << ") item(s). " << endl;

	int count = 0;
	for (int i = 0; i < total; i++)
	{
//		Random value to write to file: 
		int fileValue = 0;
		fileValue = rand() % 100 + 1;

//		Writes new binary number to file each iteration: 
		writeBinary.write(reinterpret_cast<const char*>(&fileValue), sizeof(int));

//		Outputs each value written to file: 
		cout << fileValue << "\t";

		count = count + 1;

//	    Every 10 lines, break the output stream
		if (count % 10 == 0) { cout << endl; count = 0; }
	}

	writeBinary.close();

	return 0;
}

//  Create stack object, pushes each value read in to stack 
int getData(stack& myStack)
{
	ifstream readFile;
	readFile.open("numbers.bin", ios::in | ios::binary);

//	Closes if cannot reference the file: 
	if (readFile.is_open() == false)
	{
		cout << "Error reading from 'numbers.bin' file. Is file in current directory? " << endl;
		exit(1);
	}

//	Until reaching end of the file, pushes each value to stack: 
	while (readFile && !readFile.eof())
	{
		int value = 0;
		readFile.read((char*)&value, sizeof(int));

//		Provided valid value, pushes to stack 
		if (value != 0)
		{
			myStack.pushToStack(value);
		}
		else { continue; }
	}

//	Close input stream
	readFile.close();

	return 0;
}
