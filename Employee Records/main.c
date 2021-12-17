#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    int choice = -1;

    /*
        Open file for reading and writing
        in binary. If not made, then create
        it. File is name "EmployeeRecords.txt"
    */
    fp = fopen(FILENAME, "rb+");
    if(fp == NULL) {
        fp = fopen(FILENAME, "wb+");
        if(fp == NULL) {
            printf("Error creating file.\n");
            exit(-1);
        }
    }

    printf("WELCOME TO EMPLOYEE RECORDS\n\n");
    while(1) {
        printf(" [1] Add employee\n");
        printf(" [2] List employees\n");
        printf(" [3] Modify employee\n");
        printf(" [4] Delete employee\n");
        printf(" [5] Number of Employees registered\n");
        printf(" [6] Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        clearKeyboardBuffer();
        printf("\n");
        switch(choice){
            case 1:
                addEmployee();
                break;
            case 2:
                listEmployee();
                break;
            case 3:
                //modifyEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                //listEmployee();
                break;
            case 6:
                fclose(fp);
                printf("THANK YOU FOR USING OUR SYSTEM.\nGOODBYE\n\n");
                return 0;
        }
    }

    return 0;
}