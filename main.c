#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

struct Student {
    int id;
    char name[50];
    int attendance;
};


void displayMenu();
void addStudent();
void viewRecords();
void takeAttendance();
void deleteRecord();

int main() {
    while (1) {
        displayMenu();

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                viewRecords();
                break;

            case 3:
                takeAttendance();
                break;

            case 4:
                deleteRecord();
                break;

            case 5:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\nAttendance Management System\n");
    printf("1. Add Student\n");
    printf("2. View Records\n");
    printf("3. Take Attendance\n");
    printf("4. Delete Record\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void addStudent() {
    FILE *file = fopen("students.txt", "a"); 
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Student newStudent;
    printf("Enter Student ID: ");
    scanf("%d", &newStudent.id);

    printf("Enter Student Name: ");
    scanf("%s", newStudent.name);

    newStudent.attendance = 0;

    fprintf(file, "%d %s %d\n", newStudent.id, newStudent.name, newStudent.attendance);

    fclose(file);

    printf("Student added successfully.\n");
}

void viewRecords() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    struct Student currentStudent;

    printf("\nStudent Records\n");
    printf("ID\tName\tAttendance\n");

    while (fscanf(file, "%d %s %d", &currentStudent.id, currentStudent.name, &currentStudent.attendance) == 3) {
        printf("%d\t%s\t%d\n", currentStudent.id, currentStudent.name, currentStudent.attendance);
    }

    fclose(file);
}

void takeAttendance() {
    FILE *file = fopen("students.txt", "r+");  
    if (file == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }

    int attendanceId;
    printf("Enter Student ID for Attendance: ");
    scanf("%d", &attendanceId);

    struct Student currentStudent;

    while (fscanf(file, "%d %s %d", &currentStudent.id, currentStudent.name, &currentStudent.attendance) == 3) {
        if (currentStudent.id == attendanceId) {
            currentStudent.attendance++;
            fseek(file, -1, SEEK_CUR);  
            fprintf(file, "%d %s %d", currentStudent.id, currentStudent.name, currentStudent.attendance);
            printf("Attendance recorded for %s.\n", currentStudent.name);
            break;
        }
    }

    fclose(file);
}

void deleteRecord() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char deleteName[50];
    printf("Enter Student Name to delete: ");
    scanf("%s", deleteName);

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    struct Student currentStudent;

    while (fscanf(file, "%d %s %d", &currentStudent.id, currentStudent.name, &currentStudent.attendance) == 3) {
        if (strcmp(currentStudent.name, deleteName) != 0) {
            fprintf(tempFile, "%d %s %d\n", currentStudent.id, currentStudent.name, currentStudent.attendance);
        } else {
            printf("Record with Name %s deleted.\n", deleteName);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    if (remove("students.txt") == 0) {
        if (rename("temp.txt", "students.txt") != 0) {
            printf("Error renaming temporary file.\n");
        }
    } else {
        printf("Error removing original file.\n");
    }
}