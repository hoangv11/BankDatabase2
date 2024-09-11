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
//  DATE:        September 3, 2112
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   Holds a struct record file 
//
****************************************************************/

struct record
{
    int accountno;
    char name[30];
    char address[50];
    struct record* next;
};
