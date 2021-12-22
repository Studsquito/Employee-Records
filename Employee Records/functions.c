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
    fgets(temp.name, sizeof(temp.name), stdin);
    printf("Age: ");
    scanf("%d", &temp.age);
    clearKeyboardBuffer();
    printf("Salary: ");
    scanf("%f", &temp.salary);
    clearKeyboardBuffer();
    printf("Work ID: ");
    fgets(temp.id, sizeof(temp.id), stdin);
    
    omitNewLine(temp.name);
    omitNewLine(temp.id);

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
            printf("Name: \t\t%s\n", temp.name);
            printf("Age: \t\t%d\n", temp.age);
            printf("Salary: \t%.2f\n", temp.salary);
            printf("Work ID: \t%s\n\n", temp.id);
        }
    }
}

void modifyEmployee() {
    Employee temp, temp2;
    char modified[100];
    int choice = -1, total = 0, counter = 0;

    if(fp != NULL) {
        fseek(fp, 0, SEEK_END);
        if(ftell(fp) == 0) {
            printf("File is empty.\n\n");
            return;
        }
    }

    fTemp = fopen("temp.bin", "wb+");
    if(fTemp == NULL) {
        printf("Temporary file failed to be made.\n");
        exit(-13);
    }

    printf("Which employee do you want to modify? ");
    fgets(modified, sizeof(modified), stdin);
    omitNewLine(modified);

    rewind(fp);
    while(!feof(fp)) {
        if(fread(&temp, sizeof(Employee), 1, fp)) {
            if(strcmp(temp.name, modified) == 0) {
                temp2 = temp;
            }
            else if(strcmp(temp.name, modified) != 0) {
                fwrite(&temp, sizeof(Employee), 1, fTemp);
                total++;
            }
            counter++;
        }
    }

    if(total == counter) {
        printf("No employee found.\n\n");
        if(remove("temp.bin") != 0) {
            printf("File not successfully removed.\n");
            exit(-5);
        }
        return;
    }

    printf("\nWhat do you want to change?\n");
    printf(" [1] Name\n");
    printf(" [2] Age\n");
    printf(" [3] Salary\n");
    printf(" [4] Work ID\n");
    printf(" [5] All of the above\n");
    printf(" [6] Cancel\n");
    printf("Choice: ");
    scanf("%d", &choice);
    clearKeyboardBuffer();

    switch(choice) {
        case 1:
            printf("\nName: ");
            fgets(temp2.name, sizeof(temp2.name), stdin);
            break;
        case 2:
            printf("\nAge: ");
            scanf("%d", &temp2.age);
            clearKeyboardBuffer();
            break;
        case 3:
            printf("\nSalary: ");
            scanf("%f", &temp2.salary);
            clearKeyboardBuffer();
            break;
        case 4:
            printf("\nWork ID: ");
            fgets(temp2.id, sizeof(temp2.id), stdin);
            break;
        case 5:
            printf("Name: ");
            fgets(temp2.name, sizeof(temp2.name ), stdin);
            printf("Age: ");
            scanf("%d", &temp2.age);
            clearKeyboardBuffer();
            printf("Salary: ");
            scanf("%f", &temp2.salary);
            clearKeyboardBuffer();
            printf("Work ID: ");
            fgets(temp2.name, sizeof(temp2.id), stdin);
            break;
        case 6:
            printf("Returning to main menu..\n");
            fclose(fTemp);
            if(remove("temp.bin") != 0) {
                printf("File not successfully removed.\n");
                exit(-5);
            }
            return;
        default:
            printf("Choice is incorrect.\n");
            printf("Returning to main menu..\n\n");
            fclose(fTemp);
            if(remove("temp.bin") != 0) {
                printf("File not successfully removed.\n");
                exit(-5);
            }
            return;
    }
    omitNewLine(temp2.name);
    omitNewLine(temp2.id);

    fseek(fTemp, 0, SEEK_END);
    fwrite(&temp2, sizeof(Employee), 1, fTemp);

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

    clearKeyboardBuffer();
    printf("Successfully modified.\n\n");
    return;
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
    // Re-opening clears the file
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

    printf("Successfully deleted.\n\n");
}

/**
 * @brief Prints out the number of
 *  employees by iterating through it.
 *
 */
void numOfEmployees() {
    Employee temp;
    int counter = 0;

    // Check to see if file is empty.
    rewind(fp);
    if(fp != NULL) {
        fseek(fp, 0, SEEK_END);
        if(ftell(fp) == 0) {
            printf("No employees registered.\n\n");
            return;
        }
    }

    // Iterate through file to count.
    rewind(fp);
    while(!feof(fp)) {
        if(fread(&temp, sizeof(Employee), 1, fp) > 0) {
            counter++;
        }
    }

    // Print out number of employees
    if(counter) {
        printf("The number of employees is: %d\n\n", counter);
    }

    return;
}

void clearKeyboardBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void omitNewLine(char* str) {
    int n = -1;
    if((n = strlen(str)) > 0 && str[n - 1] == '\n') {
        str[n - 1] = '\0';
    }
}