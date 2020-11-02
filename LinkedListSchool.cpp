//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                              
//   -Program Summary: 
// 
//    This program will write random #'s into a binary file called "numbers.bin." After 
//    writing to file, program will read from file & insert each value into a doubly linked list.
//    The insertion will update the ->next & ->previous ptrs 
//    After creating doubly-linked list with all read-in file data, program will check list 
//    for any nodes w/ even values. Any even value nodes will be removed and their respective pointers
//    re-incorporated into the adjusted linked list. 
//    After removing all even nodes, program will print the updated linked list w/ even values removed.
//   
//    Justin C. Shows
//    20201021
// 
// //////////////////////////////////////////////////////////////////////////////////////////// */
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

//  Definition of a node - contains value, ->next & ->prev pointers  
struct node
{
    int value;
    node* nextAddress;
    node* previous;
};

//  Grabs total #'s to generate from user:
int getTotal(int&);

//   Outputs values of a given linked list 
void twoWayPrint(node*);

//  Writes binary numbers randomly between 0 and 99
int writeData(const string&, int);

//    Reads each value in binary file & inserts into list:
node* readData(ifstream&, node*);
 
//    Provided reference to head & new value, inserts new node in list w/ value:
node* insertNodes(node*, int);

//    Points ahead of next while iterating & deletes current head 
node* removeEvenItems(node* head);      

//    Given ptr to head & node to delete, removes it & updates pointers
node* deleteNode(node* head, node* deleteNode);

//    Deletes every node in given list:
node* deleteAllNodes(node* head);

const int ERROR = 1;
const string filename = "numbers.bin";

//  Main:
int main(int argc, char* argv[])
{
       srand((unsigned)time(NULL));

       int totalValues = 0;
 
//     If user didn't pass in total, prompts user for total: 
       if (argc != 2)
       {
           cout << "Total not passed in. Enter total #'s to generate: " 
                   << endl << "-1 TO EXIT" << endl;
          getTotal(totalValues);
       }
       else
       totalValues = atoi(argv[1]);

//     If total passed in doesn't meet constraints, prompt user:
       if (totalValues < 20 || totalValues > 100) { getTotal(totalValues); }

//        Head is reference to starting address of new list
          struct node* head;

//        Allocate new head and check if it fails to 

          if ((head = new(node)) == NULL)
          {
             cout << "Memory error. " << endl;
             return ERROR;
          }

//        Set head->next & ->prev To null since head's currently start & end of list 

          head->nextAddress = NULL;
          head->previous = NULL;

//        Writes random #'s to new/existing file for total value passed by 

          writeData(filename, totalValues);
        
//        Will read from newly created binary file here

          ifstream binaryFile;
          binaryFile.open(filename, ios::in | ios::binary);

          if (!binaryFile.is_open()) { cout << "Error opening file. " << endl; return ERROR; }

//        Reads from file & inserts ea. value into list, catches any reading 

          head = readData(binaryFile, head);

//        Ensure stream buffer is closed

          binaryFile.close();

//        Output doubly linked list before modifying even nodes:

          twoWayPrint(head);
        
//        Remove even nodes in list:

          head = removeEvenItems(head);
          
//        After deleting even nodes, print updated list:

          cout << endl << "[After Deleting Nodes W/ Even Value] " << endl;
          twoWayPrint(head);

//        Now delete all nodes:

          head = deleteAllNodes(head);
          
//        Final print: 
          cout << "[After deleting] " << endl << endl;
          twoWayPrint(head);

          return 0;
}

//  Gets total #'s to create from user, called if not passed in command line: 
int getTotal(int& totalValues)
{
    while (totalValues < 20 || totalValues > 100)
    {
        cout << "Value must be between 20 - 100 " << endl;
        cout << "Enter total amount of data: " << endl;

        cin >> totalValues;

//     -1 to close program:
        if (totalValues == -1) { cout << "Exiting Program... " << endl; exit(1); }
    }

    return totalValues;
}

//    Opens binary file "numbers.bin" & reads each value & inserts as new node into list: 
node* readData(ifstream& binaryFile, node* head)
{
//  Until reaching end, store ea. bin value as int
    while (!binaryFile.eof())
    {
        int fileValue = 0;
        binaryFile.read((char*)&fileValue, sizeof(int));

//      If valid data is found, insert into list:
        if (fileValue != 0)
        {
              head = insertNodes(head, fileValue);
        }
    }

//  Head changed so return:  
    return head;
}

//    Deletes all nodes in a given linked list provided list's head: 
node* deleteAllNodes(node* head)
{
     struct node* traversal;

 //  Iterate through list, peeking ahead while deleting head's current node:
     while (head != NULL)
     {
          traversal = head->nextAddress;
          delete(head);
          head = traversal;
     }

//   Head changed so return: 
     return head;
}

//    Inserts nodes into doubly linked list, updates ->next and ->prev pointers for new insertions
node* insertNodes(node* head, int valueOther)
{
    struct node* current = head;
    struct node* newnode = new node;

    if (newnode == NULL) { cout << "Error creating new node. " << endl; return NULL; }

//  If there's a valid node ahead, we can assign previous ptr to it, otherwise not:
    if (current->nextAddress) { current->nextAddress->previous = newnode; }

//  Initialize pointers:
    newnode->nextAddress = NULL;
    newnode->previous = NULL;

//  Grab value for new node to be inserted: 
    newnode->value = valueOther;
    
//  Point to where current is: 
    newnode->previous = current;

//  Trade pointers with current
    newnode->nextAddress = current->nextAddress;

//  Link new node to main list: 
    current->nextAddress = newnode;

    head = current;
    return head;
}

//    Iterates through list and deletes any nodes with even values 
node* removeEvenItems(node* head)
{
    struct node* temp = head;
    struct node* peek;

//  Use peek pointer to look ahead, if node ahead is even, will delete:
    while (temp != NULL)
    { 
          peek = temp->nextAddress;
      
//        If node's value is even, pass node to deletion function: 
          if (temp->value % 2 == 0)
          head = deleteNode(head, temp);
        
          temp = peek;
     }
        
//  Since head changed, return:
    return head;
}

//    Deletes a given node with appropriate logic to update pointers:
node* deleteNode(node* head, node* deleteNode)
{
//  Base Case: 
    if (head == NULL || deleteNode == NULL)
         return NULL;

//  If node to be deleted is head node 
    if (head == deleteNode)
    {
        head = deleteNode->nextAddress;
    }

//  Makes sure the next->prev is not the end of the list:
    if (deleteNode->nextAddress != NULL)
    {
        deleteNode->nextAddress->previous = deleteNode->previous;
    }
        
//  Modifies previous only if there's valid previous node:
    if (deleteNode->previous != NULL)
    {
        deleteNode->previous->nextAddress = deleteNode->nextAddress;
    } 

//  Removes node from list by freeing node from memory 
    free(deleteNode);

//  Since head changed, return:
    return head;
}

//   Print head to tail, then print tail to head
void twoWayPrint(node* head)
{
     if (head == NULL){ cout << "List has been deleted. " << endl; exit(1); }

     struct node* current;
     current = head;
        
     int count = 1;
     cout << endl << "[Original Order] " << endl;

//   Print head to tail:

     while (current->nextAddress != NULL)
     {
//        Move to next node
          current = current->nextAddress;
          cout << current->value << "\t";

//        Every 10 outputs, break 
          if (count % 10 == 0) { cout << endl; }
          count = count + 1;
     }

//   Reset output counter for formatting reversed output below: 
     count = 1;

//   Print tail to head:

     cout << endl << endl << endl << "[Reversed Order]: " << endl;

     while (current->previous != NULL)
     {
         cout << current->value << "\t";
         current = current->previous;

//       Every 10 outputs, break lines
         if (count % 10 == 0) { cout << endl; }

         count = count + 1;
     }
     cout << endl << endl;
}

//  Writes random values between 0 and 99 into binary file "numbers.bin"
int writeData(const string& filename, int totalValues)
{
    ofstream writeBinary;
    writeBinary.open(filename, ios::out | ios::binary);

    if (writeBinary.is_open() == false) { cout << "Error writing file. "; return 3; }

//  Write Numbers into binary file to be read from later for inserting nodes:
    for (int i = 0; i < totalValues; i++)
    {
        int value = 0;
        value = (rand() * rand()) % 100 + 1;

//      For all 1's, randomize from [0 to 20 (+ 2)] )
        if (value == 1) {value = rand() % 20 + 2; }

//      Write random #'s into binary file "numbers.bin":
        writeBinary.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }
    cout << endl;

//  Critical to Close Buffer
    writeBinary.close();
    return 0;
}
