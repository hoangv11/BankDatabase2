/**********************************************************
//
//  Name:        Victor Hoang
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        11/25/2023
//
//  FILE:        llist.h
//
//  DESCRIPTION: 
//
//
//
**********************************************************/

#include "record.h" 
class llist
{
    private: 
        record * start;
        char filename[20];
        int readfile();
        int writefile();
        void cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        int addRecord(int, char[], char[]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};
