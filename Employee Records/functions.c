#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/**
 * @brief Appends an employee
 *  to the end of the file using
 *  fseek.
 * 
 */
void addEmployee() {
    // Move the cursor to the EOF
    fseek(fp, 0, SEEK_END);
    Employee temp;

    // Prompt user for Employee info
    printf("Name: ");
    scanf("%s", temp.name);
    printf("Age: ");
    scanf("%d", &temp.age);
    printf("Salary: ");
    scanf("%f", &temp.salary);
    printf("Work ID: ");
    scanf("%s", temp.id);

    if(fp == NULL) {
        printf("File isn't open.\n");
        exit(-2);
    }

    // Write to file
    fwrite(&temp, sizeof(temp), 1, fp);
    printf('\n');
}

/**
 * @brief List the employees from the open
 *  file.
 * 
 */
void listEmployee() {
    // Reset file pointer
    rewind(fp); 
    
    // If the file is empty,
    // don't print anything
    if(fp != NULL) {
        fseek(fp, 0, SEEK_END);
        if(ftell(fp) == 0) {
            printf("File is empty.\n\n");
            return;
        } 

    }

    // Reset file pointer
    rewind(fp);
    
    // While the File != EOF, keep printing
    while(!feof(fp)) {
        Employee temp;
        // fread returns the total # of elements reads
        if(fread(&temp, sizeof(Employee), 1, fp) > 0){
            printf("Name: \t%8s\n", temp.name);
            printf("Age: \t%8d\n", temp.age);
            printf("Salary: %8.2f\n", temp.salary);
            printf("Work ID:%8s\n\n", temp.id);
        }
    }
}

void deleteEmployee() {
    
}

void clearKeyboardBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}