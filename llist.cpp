/*****************************************************************
//
//  NAME:        Ravi Narayan
//
//  HOMEWORK:    Project 2 
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 25, 2023
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   Holds functions that the will be implemented from selected
//   options of the user. 
//
****************************************************************/

#include "llist.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*****************************************************************
//
//  Function name: constructor
//
//  DESCRIPTION:   First thing that the program does when it starts
//                 in this case it initializes the linked list
//                 sets starts to 0 or NULL and then it
//                 reads the file
//
//  Parameters:    
//                 
//                              
//
//  Return values:  
//                 
//
****************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(filename, "data.txt");
    readfile();
}

llist::llist(char fname[])
{
    start = NULL;
    strcpy(filename, fname);
    readfile();
}

/*****************************************************************
//
//  Function name: destructor
//
//  DESCRIPTION:  Last thing the program does when exiting. This 
//                includes writefile where it copies current records
//                then it also cleans up by deallocating memory
//                
//                 
//
//  Parameters:  
//
//  Return values: 
//               
//
****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION: Function is used to add user information into a 
//               record
//
//
//
//  Parameters: int accountno, char name[], char address[]
//
//  Return values:  0 : function success
//                 -1 : function failure
//
*****************************************************************/

int llist::addRecord(int accountno, char name[], char address[])
{
    record *nextRecord = NULL;
    record *current = NULL;
    record *temp = NULL;

    #ifdef DEBUG

    cout << "\naddRecord debug: Account Number: " << accountno << ", Name: " << name << ", Address: " << address << endl;

    #endif 

    if(accountno < 0)
    {
 
       cout << "\nInvalid account number" << endl;
        return -1;
    }
   
    temp = start;
    
    while(temp != NULL)
    {
        if(temp->accountno == accountno)
        {
            cout << "\nA record with that account number already exists\n";
            return -1;
        }
        temp = temp->next;
    }

    nextRecord = new record;
    nextRecord->accountno = accountno;
    strcpy(nextRecord->name, name);
    strcpy(nextRecord->address, address);
    nextRecord->next = NULL;

    if(start == NULL || accountno > start->accountno)
    {
        nextRecord->next = start;
        start = nextRecord;
        cout << "\nYour record has been successfully added.\n";
        return 0;
    }

    current = start;
    
    while(current->next != NULL)
    {
        temp = current->next;
        if(accountno == temp->accountno)
        {
            delete nextRecord;
            return -1; 
        }
        if(accountno < temp->accountno)
        {
            nextRecord->next = temp;
            current->next = nextRecord;
            cout << "\nYour record has been successfully added.\n";
            return 0;
        }
        current = current->next;
    }

    current->next = nextRecord;
    cout << "\nYour record has been successfully added.\n";

    return 0;    
}

/******************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION: This function prints all the information that is 
//               currently stored in the record
//
//  Parameters: 
//
//  Return values: void
//
*****************************************************************/

void llist::printAllRecords()
{
    record *current = start;

    #ifdef DEBUG

    cout << "\nprintAllRecords debug: prints all existing records on file";

    #endif
    
    if(current == NULL)
    {
        cout << "\nThere are no files on record.\n";
    }
  
    while(current != NULL)
    {
        cout << "\nAccount Number: " << current->accountno << "\n";
        cout << "Name: " << current->name << "\n";
        cout << "Address: " << current->address << "\n";

        current = current->next;
    }
}

/*******************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION: This function finds and prionts the record of a 
//               specified account number
//
//  Parameters:  int account no
//
//  Return Values:  0 : successfully finds and prints record
//                 -1 : failed to find accountno on record
//
******************************************************************/

int llist::findRecord(int accountno)
{
    record *current = start;
    
    #ifdef DEBUG

    cout << "\nfindRecord debug: finds record with account number: " << accountno << endl;

    #endif
    
    while(current != NULL)
    {
        if(current->accountno == accountno)
        {
            cout << "\nAccount Number: " << current->accountno << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "Address: " << current->address << "\n";

            return 0;
        }

        current = current->next;
    }

    cout << "\nCouldn't find record with that account number\n";
    return -1;  
}

/******************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION: This function will delete a record with the
//               specific accoutno
//
//  Parameters: int accountno
//
//  Return values:  0 : successfully deletes record
//                 -1 : fails to find accoutno
//
******************************************************************/

int llist::deleteRecord(int accountno)
{
    record *current = start;
    record *previous = NULL;
    int recordDeleted = -1;
  
    #ifdef DEBUG

    cout << "\ndeleteRecord debug: deletes record with account number: " << accountno;

    #endif
  
    while(current != NULL && recordDeleted == -1)
    {
        if(current->accountno == accountno)
        {
            recordDeleted = 0;
         
            if(current == start)
            {
                start = current->next;
            }
            else
            {
                previous->next = current->next; 
            }
 
            delete current;
            cout << "\nRecord has been successfully deleted\n";
            return 0;
        }
        else
        {
            previous = current;
            current = current->next;
            cout << "\nRecord not found\n";
        }
    }

    return recordDeleted;
}

/******************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION: writes data stored in a record into a file that can
//               be later accessed
//
//  Parameters: 
//
//  Return values: 0 : success
//                -1 : failure
//
******************************************************************/

int llist::writefile()
{
    #ifdef DEBUG

    cout << "\nwritefile debug: writes existing files on record into data.txt";

    #endif

    record *current = start;
    ofstream wFile(filename, ofstream::out);

    if(wFile == NULL)
    {
        return -1;
    }
 
    while(current)
    {
        wFile << "Account Number: " << current->accountno << "\n";
        wFile << "Name: " << current->name << "\n";
        wFile << "Address: " << current->address << "\n\n";

        current = current->next;
    }

    wFile.close();
    
    return 0;
}

/******************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION: retrieves the recods from a saved file
//
//  Parameters: 
//
//  Return values: 0 : success
//                -1 : failure
//
******************************************************************/

int llist::readfile()
{
    #ifdef DEBUG 
  
    cout << "\nreadfile debug: copies from data.txt to linked list";

    #endif 

    ifstream rFile(filename, ifstream::in);
    record *current = NULL;
    record *newRecord = new record;
    int accountno;
    char name[30];
    char address[50];

    while(rFile >> accountno)
    {
        if(rFile >> accountno)
        {
            rFile.ignore();
            rFile.getline(name, 30);
            rFile.getline(address, 50);

            newRecord->next = NULL;
            if(start == NULL)
            {
                start = newRecord;
                current = start;
            }
            else
            {
                current->next = newRecord;
                current = current->next;
            }
        }
        else
        {
            delete(newRecord);
        }
    }
       
    rFile.close();

    return 0;  
}

/******************************************************************
//
//  Function name: cleanup 
//
//  DESCRIPTION: This function deallocates memory, sets the start
//               pointer to NULL
//
//  Parameters: 
//
//  Return values: void 
//
******************************************************************/

void llist::cleanup()
{

    #ifdef DEBUG

    cout << "\ncleanup debug: deallocating all memory on file on program termination\n";
   
    #endif 

    record *current = start;
    record *next = NULL;

    while(current != NULL)
    {
        next = current->next;
        delete(current);
        current = next;
    }

    start = NULL;       
}
    
