#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student {
    int roll_no;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();

int main() {
    int choice;
    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "a"); 
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter Roll No: ");
    scanf("%d", &s.roll_no);

    
    FILE *check_fp = fopen(FILE_NAME, "r");
    if (check_fp != NULL) {
        struct Student temp;
        while (fscanf(check_fp, "%d %s %f", &temp.roll_no, temp.name, &temp.marks) == 3) {
            if (temp.roll_no == s.roll_no) {
                printf("Error: Roll number already exists.\n");
                fclose(check_fp);
                fclose(fp);
                return;
            }
        }
        fclose(check_fp);
    }

    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name); 

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll_no, s.name, s.marks); 
    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "r"); 
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nStudent Records:\n");
    printf("Roll No  Name                Marks\n");
    printf("----------------------------------\n");

    while (fscanf(fp, "%d %s %f", &s.roll_no, s.name, &s.marks) == 3) {
        printf("%-8d %-20s %.2f\n", s.roll_no, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int roll_no, found = 0;
    FILE *fp = fopen(FILE_NAME, "r"); 
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter Roll No to search: ");
    scanf("%d", &roll_no);

    while (fscanf(fp, "%d %s %f", &s.roll_no, s.name, &s.marks) == 3) {
        if (s.roll_no == roll_no) {
            printf("\nStudent Found:\n");
            printf("Roll No: %d\nName: %s\nMarks: %.2f\n", s.roll_no, s.name, s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found) {
        printf("Student not found!\n");
    }
}

void deleteStudent() {
    struct Student s;
    int roll_no, found = 0;
    FILE *fp = fopen(FILE_NAME, "r"); 
    FILE *temp_fp = fopen("temp.dat", "w"); 

    if (!fp || !temp_fp) {
        perror("Error opening file");
        return;
    }

    printf("Enter Roll No to delete: ");
    scanf("%d", &roll_no);

    while (fscanf(fp, "%d %s %f", &s.roll_no, s.name, &s.marks) == 3) {
        if (s.roll_no == roll_no) {
            found = 1;
        } else {
            fprintf(temp_fp, "%d %s %.2f\n", s.roll_no, s.name, s.marks); 
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        if (remove(FILE_NAME) != 0) {
            perror("Error removing original file");
            return;
        }
        if (rename("temp.dat", FILE_NAME) != 0) {
            perror("Error renaming temporary file");
            return;
        }

        printf("Student deleted successfully!\n");
    } else {
        printf("Student not found!\n");
    }
}