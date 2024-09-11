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
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   The interface for the user that t he user can use to access
//   bank database through commands.
//
****************************************************************/

#include <iostream>
#include <cstring>
#include <string>
#include "llist.h"

using namespace std;

void userMenu();
void getaddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Don't forget to describe what your main
//                 function does.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : some meaning
//                 -1 : some meaning
//
****************************************************************/

int main(int argc, char* argv[])
{
    llist mylist;
    int accountno;
    char name[30];
    char address[50];
    char userOption[20];
    int userMenuValid = 1;
    
    cout << "\nWelcome to the bank\n";

    while(userMenuValid)
    {
        userMenu();
        cin >> userOption;
   
        if(strlen(userOption) <= 3 && strncmp(userOption, "add", strlen(userOption)) == 0)
        {
            cout << "\nEnter your account number: ";
            cin >> accountno;
            cin.ignore();

            cout << "Enter your name: ";
            cin.getline(name, 30);
   
            cout << "Enter your address: "; 
            getaddress(address, 50);

            mylist.addRecord(accountno, name, address);
        }
        else if(strlen(userOption) <= 8 && strncmp(userOption, "printall", strlen(userOption)) == 0)
        {
            mylist.printAllRecords();
        }
        else if(strlen(userOption) <= 4 && strncmp(userOption, "find", strlen(userOption)) == 0)
        {
            cout << "Enter account number you would like to find: ";
            cin >> accountno;
            cin.ignore();
            mylist.findRecord(accountno);
        }
        else if(strlen(userOption) <= 6 && strncmp(userOption, "delete", strlen(userOption)) == 0)
        {
            cout << "Enter the account number you would like to delete: ";
            cin >> accountno;
            cin.ignore();
            mylist.deleteRecord(accountno);
        }
        else if(strlen(userOption) <= 4 && strncmp(userOption, "quit", strlen(userOption)) == 0)
        {    
            userMenuValid = 0;
        }
        else
        {
            cout << "Please enter a valid option\n";
        }
    }
}

/*****************************************************************
//
//  Function name: userMenu
//
//  DESCRIPTION:   This function displays the user menu which 
//                 the user can see to use the commands to accesss
//                 the database and its functions.
//                 
//                 
//
//  Parameters:    ...
//
//  Return values:  void
//                 
//
****************************************************************/

void userMenu()
{
    cout << "\nSelect and option to continue...\n";
    cout << "\nadd: add a new record into the system's database\n";
    cout << "print: prints all records currently stored within the database\n";
    cout << "find: find record of account number within the database\n";
    cout << "delete: delete an existing record with account number\n";
    cout << "quit: exit the program\n\n";
}

/******************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION: This function is used to obtain the address info
//               of the user who would like to add an account to 
//               the record
//
//  Parameters: char address[], int size
//
//  Return values: void
//
//
******************************************************************/

void getaddress(char address[], int size)
{
    int len = 0;
    int newLine = 0;
    int max = 0;
    char result;

    while(!newLine && !max) 
    {
        if(len < size - 1)
        {
            result = cin.get();
            if(result == '\n')
            {
                if(len > 0 && address[len - 1] == '\n')
                {
                    newLine = 1;
                    address[len - 1] = '\0';
                }
                else
                {
                    address[len++] = result;
                }
            }
            else
            {
                address[len++] = result;
            }
        }
        else
        {
            max = 1;
        }
    }
    
    if(!newLine && len > 0 && address[len - 1] == '\n')
    {
        address[len - 1] = '\0';
    }
}
