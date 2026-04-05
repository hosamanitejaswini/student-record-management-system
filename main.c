#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[50];
    float marks;
    char grade;
};

// Function to calculate grade
char calculateGrade(float marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 75) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 50) return 'D';
    else return 'F';
}

// Add student
void addStudent() {
    FILE *fp;
    struct student s;

    fp = fopen("students.txt", "a");

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    s.grade = calculateGrade(s.marks);

    fprintf(fp, "%d %s %.2f %c\n", s.roll, s.name, s.marks, s.grade);

    fclose(fp);

    printf("✅ Record Added Successfully!\n");
}

// Display all students
void displayStudents() {
    FILE *fp;
    struct student s;

    fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fscanf(fp, "%d %s %f %c", &s.roll, s.name, &s.marks, &s.grade) != EOF) {
        printf("Roll: %d | Name: %s | Marks: %.2f | Grade: %c\n",
               s.roll, s.name, s.marks, s.grade);
    }

    fclose(fp);
}

// Search student
void searchStudent() {
    FILE *fp;
    struct student s;
    int roll, found = 0;

    fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f %c", &s.roll, s.name, &s.marks, &s.grade) != EOF) {
        if (s.roll == roll) {
            printf("\n✅ Record Found!\n");
            printf("Name: %s | Marks: %.2f | Grade: %c\n",
                   s.name, s.marks, s.grade);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\n❌ Record Not Found!\n");

    fclose(fp);
}

// Delete student
void deleteStudent() {
    FILE *fp, *temp;
    struct student s;
    int roll, found = 0;

    fp = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f %c", &s.roll, s.name, &s.marks, &s.grade) != EOF) {
        if (s.roll != roll) {
            fprintf(temp, "%d %s %.2f %c\n", s.roll, s.name, s.marks, s.grade);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("\n✅ Record Deleted Successfully!\n");
    else
        printf("\n❌ Record Not Found!\n");
}

// Update student
void updateStudent() {
    FILE *fp, *temp;
    struct student s;
    int roll, found = 0;

    fp = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f %c", &s.roll, s.name, &s.marks, &s.grade) != EOF) {
        if (s.roll == roll) {
            printf("\nEnter New Name: ");
            scanf("%s", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            s.grade = calculateGrade(s.marks);
            found = 1;
        }
        fprintf(temp, "%d %s %.2f %c\n", s.roll, s.name, s.marks, s.grade);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("\n✅ Record Updated Successfully!\n");
    else
        printf("\n❌ Record Not Found!\n");
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n===== Student Record System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
