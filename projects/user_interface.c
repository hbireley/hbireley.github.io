/*****************************************************************
//
//  NAME:        Hayden Bireley
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 30, 2023
//
//  FILE:        user_interfase.c
//
//  DESCRIPTION: This file is the user interfase for a bank.
//
//  **************************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"
void getaddress(char[], int);
void getAccountNum(int *);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Prints out the menu and an intro message for the bank
//                 
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : succuss
//                 -1 : failed
//
****************************************************************/

int debugmode = 0;

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    char name[30];
    char address[50];
    int  accnum;
    char input[10];
    char cmd[10];
    char filename[] = "records.txt";
    char debug[] = "debug";
    int returnvalue = 0;
    int userloop = 1;
    int succuss;

    if (argc > 2)
    {
        printf("project: missing operand\n");
        returnvalue = -1;
    }

    else if (argc == 2)
    {
        if (strcmp (argv[1], debug) == 0)
            debugmode = 1;

        else
        {
            printf("project: missing operand\n");
            returnvalue = -1;
        }
    }

    if (returnvalue != -1)
    {
        readfile(&start, filename);

        printf("Welcome to Hayden's Bank it was founded by Hayden Bireley in 2023.\n");

        do
        {
            printf("\nType add: To add a record to the database.\n");
            printf("printall: To print all the records in the database.\n");
            printf("find: To find a record in the database based on account number.\n");
            printf("delete: To delete an existing record from the database based on account number.\n");
            printf("quit: To quit the program.");
            printf("\n");
            fgets(input, 10, stdin);

            if (input[0] == 'a')
            {
                strcpy(cmd, "add");

                if (strncmp(input, cmd, (strlen(input)-1)) != 0)
                {
                    printf("INVALID INPUT! ");
                    printf("Please enter one of the menu words or an abbreviated version.\n");
                }
                else
                {
                    printf("Enter your full name please.\n");
                    fgets(name, 30, stdin);

                    printf("Enter your address and enter @ when you are done entering.\n");
                    getaddress(address, 50);

                    printf("Enter your account number please.\n");
                    getAccountNum(&accnum);

                    succuss = addRecord(&start, accnum, name, address);
                    if (succuss == 0)
                    {
                        printf("Your record was succussfully added.\n");
                    }

                    else
                    {
                        printf("Your record was not added.\n");
                    }
                 }
            }

            else if (input[0] == 'p')
            {
                strcpy(cmd, "printall");

                if (strncmp(input, cmd, (strlen(input)-1)) != 0)
                {
                    printf("INVALID INPUT! ");
                    printf("Please enter one of the menu words or an abbreviated version.\n");
                }

                else
                    printAllRecords(start);
            }

            else if (input[0] == 'f')
            {
                strcpy(cmd, "find");

                if (strncmp(input, cmd, (strlen(input)-1)) != 0)
                {
                    printf("INVALID INPUT! ");
                    printf("Please enter one of the menu words or an abbreviated version.\n");
                }

                else
                {
                    printf("Enter the account number that you want to find please.\n");
                    getAccountNum(&accnum);

                    succuss = findRecord(start, accnum);
                    if (succuss == -1)
                    {
                        printf("The record was not found\n");
                    }
                }
            }

            else  if (input[0] == 'd')
            {
                strcpy(cmd, "delete");

                if (strncmp(input, cmd, (strlen(input)-1)) != 0)
                {
                    printf("INVALID INPUT! ");
                    printf("Please enter one of the menu words or an abbreviated version.\n");
                }

                else
                {
                    printf("Enter the account number that you want to delete please.\n");
                    getAccountNum(&accnum);

                    succuss = deleteRecord(&start, accnum);
                    if (succuss == 0)
                        printf("Your record was succussfully deleted.\n");

                    else
                        printf("Your record was not deleted.\n");
                }
             }

            else if (input[0] == 'q')
            {
                strcpy(cmd, "quit");

                if (strncmp(input, cmd, (strlen(input)-1)) != 0)
                {
                    printf("INVALID INPUT!");
                    printf("Please enter one of the menu words or an abbreviated version.\n");
                    userloop = 1;
                }

                else
                    userloop = 0;
            }

            else
            {
                printf("INVALID INPUT! ");
                printf("Please enter one of the menu words or an abbreviated version.\n");
            }
        }
        while (userloop);

        writefile(start, filename);
        cleanup(&start);
    }

    return returnvalue;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Get the address that the user inputs  
//                 
//                 
//
//  Parameters:    address (char[]) : pointer to the start of the array 
//                 size  (int) : size of the array they are passing 
//
//  Return values: void
//                 
//
****************************************************************/

void getaddress(char address[], int size)
{
    int count = 0;
    char trash[100];

    do
    {
        address[count] = fgetc(stdin);
        count = count + 1;
    }
    while (address[count - 1] != '@' && count < (size - 1));

    fgets(trash, 100, stdin);

    address[count] = '\0';
}

/*****************************************************************
//
//  Function name: getAccountNum
//
//  DESCRIPTION:   Gets the account number that the user inputs and chackes if it is positive  
//                 
//                 
//
//  Parameters:   accnum (int *) : pointer to the account number variable 
//                 
//
//  Return values: void
//                 
//
****************************************************************/

void getAccountNum(int *accnum)
{
    char trash[100];

    do
    {
        scanf("%d", accnum);
        fgets(trash, 100, stdin);

        if (*accnum < 0)
        {
            printf("INVALID INPUT! Please input a positive number.\n");
        }
    }
    while (*accnum < 0);
}
