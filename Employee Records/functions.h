#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define FILENAME "EmployeeRecords.bin"
//char* fileName = "EmployeeRecords.bin";
FILE* fp, *fTemp;
typedef struct employee {
    char name[40];
    int age;
    float salary;
    char id[12];
} Employee;

void addEmployee();
void listEmployee();
void modifyEmployee();
void deleteEmployee();
void numOfEmployees();

void clearKeyboardBuffer();
void omitNewLine(char* str);
int getWorkIdRegex();

#endif