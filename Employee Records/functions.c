#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("\n");
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
/**
 * @brief Temporarily creates a file
 *  to hold the transferred content of 
 *  the main file. It goes over the file
 *  searching for the name that wants to 
 *  be deleted. Once done, it deletes that
 *  temp file and transfers content back
 *  to the main file.
 *  
 */
void deleteEmployee() {
    Employee temp;
    char deleted[100];
    int counter = 0, total = 0;
    
    // Temporarily create a file.
    fTemp = fopen("temp.bin", "wb+");
    if(fTemp == NULL) {
        printf("Temporary file failed to be made.\n");
        exit(-13);
    }

    // Prompt user which person to delete.
    printf("Which employee would you like to delete: ");
    scanf("%s", deleted);
    clearKeyboardBuffer();

    // Iterate through file to transfer contents.
    rewind(fp);
    while(!feof(fp)) {
        if(fread(&temp, sizeof(Employee), 1, fp) > 0){
            if(strcmp(temp.name, deleted) != 0) {
                fwrite(&temp, sizeof(temp), 1, fTemp);
                total++;
            }
            counter++;
        }
    }

    // If the number transferred is equal to the
    // total amount of employees, then no person
    // is found with that name.
    if(total == counter) {
        printf("No employee found.\n\n");
        if(remove("temp.bin") != 0) {
            printf("File not successfully removed.\n");
            exit(-5);
        }
        return;
    }

    // Re-open the main file and transfer the contents
    // from temp to the main file.
    fp = freopen(FILENAME, "wb+", fp);
    rewind(fTemp);
    while(!feof(fTemp)) {
        if(fread(&temp, sizeof(Employee), 1, fTemp) > 0){
            fwrite(&temp, sizeof(temp), 1, fp);
        }
    }    

    // Remove the temp.bin file.
    fclose(fTemp);
    if(remove("temp.bin") != 0) {
            printf("File not successfully removed.\n");
            exit(-5);
    }
    
    printf("Successfully deleted.\n");
}

void clearKeyboardBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}