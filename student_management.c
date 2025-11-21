/*
 * Student Management System
 * A simple program to manage student records
 * By Kunal Tiwari
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "students.dat"

// Student information structure
struct Student {
    int rollNo;
    char name[50];
    int age;
    char department[30];
    float marks[5];
    float percentage;
    char grade;
};

// Global storage for students
struct Student students[MAX_STUDENTS];
int totalStudents = 0;

// Function declarations
void showMenu();
void addNewStudent();
void showAllStudents();
void findStudent();
void updateStudent();
void removeStudent();
void calculateResults(struct Student *s);
char getGrade(float percentage);
void saveData();
void loadData();
void clearBuffer();
int rollNumberExists(int roll);

int main() {
    // Load existing data when program starts
    loadData();
    
    printf("\n========================================\n");
    printf("  Student Management System\n");
    printf("  Welcome!\n");
    printf("========================================\n");
    
    showMenu();
    return 0;
}

void showMenu() {
    int choice;
    
    while(1) {
        printf("\n--- What would you like to do? ---\n");
        printf("1. Add a new student\n");
        printf("2. Show all students\n");
        printf("3. Search for a student\n");
        printf("4. Update student details\n");
        printf("5. Delete a student\n");
        printf("6. Save and exit\n");
        printf("\nYour choice: ");
        
        if(scanf("%d", &choice) != 1) {
            clearBuffer();
            printf("\nPlease enter a valid number!\n");
            continue;
        }
        clearBuffer();
        
        switch(choice) {
            case 1: addNewStudent(); break;
            case 2: showAllStudents(); break;
            case 3: findStudent(); break;
            case 4: updateStudent(); break;
            case 5: removeStudent(); break;
            case 6:
                saveData();
                printf("\nAll data saved successfully!\n");
                printf("Thanks for using the system. Goodbye!\n\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please pick 1-6.\n");
        }
    }
}

void addNewStudent() {
    if(totalStudents >= MAX_STUDENTS) {
        printf("\nSorry, the database is full! Can't add more students.\n");
        return;
    }
    
    struct Student newStudent;
    
    printf("\n--- Adding New Student ---\n");
    
    // Get roll number
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNo);
    clearBuffer();
    
    // Check if this roll number already exists
    if(rollNumberExists(newStudent.rollNo)) {
        printf("This roll number already exists! Please use a different one.\n");
        return;
    }
    
    // Get student name
    printf("Enter student name: ");
    fgets(newStudent.name, 50, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    
    // Get age
    printf("Enter age: ");
    scanf("%d", &newStudent.age);
    clearBuffer();
    
    // Get department
    printf("Enter department: ");
    fgets(newStudent.department, 30, stdin);
    newStudent.department[strcspn(newStudent.department, "\n")] = 0;
    
    // Get marks for 5 subjects
    printf("\nEnter marks for 5 subjects (0-100):\n");
    for(int i = 0; i < 5; i++) {
        do {
            printf("Subject %d marks: ", i + 1);
            scanf("%f", &newStudent.marks[i]);
            clearBuffer();
            
            if(newStudent.marks[i] < 0 || newStudent.marks[i] > 100) {
                printf("Invalid marks! Please enter between 0 and 100.\n");
            }
        } while(newStudent.marks[i] < 0 || newStudent.marks[i] > 100);
    }
    
    // Calculate percentage and grade
    calculateResults(&newStudent);
    
    // Add student to our database
    students[totalStudents] = newStudent;
    totalStudents++;
    
    printf("\nGreat! Student added successfully.\n");
    printf("Percentage: %.2f%%\n", newStudent.percentage);
    printf("Grade: %c\n", newStudent.grade);
}

void showAllStudents() {
    if(totalStudents == 0) {
        printf("\nNo students in the database yet.\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("All Students\n");
    printf("========================================\n");
    printf("%-8s %-20s %-5s %-15s %-10s %s\n", 
           "Roll", "Name", "Age", "Department", "Percentage", "Grade");
    printf("----------------------------------------\n");
    
    for(int i = 0; i < totalStudents; i++) {
        printf("%-8d %-20s %-5d %-15s %-10.2f %c\n",
               students[i].rollNo,
               students[i].name,
               students[i].age,
               students[i].department,
               students[i].percentage,
               students[i].grade);
    }
    
    printf("----------------------------------------\n");
    printf("Total: %d students\n", totalStudents);
}

void findStudent() {
    if(totalStudents == 0) {
        printf("\nNo students to search.\n");
        return;
    }
    
    int roll;
    printf("\n--- Search Student ---\n");
    printf("Enter roll number: ");
    scanf("%d", &roll);
    clearBuffer();
    
    int found = 0;
    for(int i = 0; i < totalStudents; i++) {
        if(students[i].rollNo == roll) {
            found = 1;
            printf("\nStudent Found!\n");
            printf("----------------------------------------\n");
            printf("Roll Number: %d\n", students[i].rollNo);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Department: %s\n", students[i].department);
            printf("\nMarks:\n");
            for(int j = 0; j < 5; j++) {
                printf("  Subject %d: %.2f\n", j + 1, students[i].marks[j]);
            }
            printf("\nPercentage: %.2f%%\n", students[i].percentage);
            printf("Grade: %c\n", students[i].grade);
            printf("----------------------------------------\n");
            break;
        }
    }
    
    if(!found) {
        printf("No student found with roll number %d.\n", roll);
    }
}

void updateStudent() {
    if(totalStudents == 0) {
        printf("\nNo students to update.\n");
        return;
    }
    
    int roll;
    printf("\n--- Update Student ---\n");
    printf("Enter roll number of student to update: ");
    scanf("%d", &roll);
    clearBuffer();
    
    int found = 0;
    for(int i = 0; i < totalStudents; i++) {
        if(students[i].rollNo == roll) {
            found = 1;
            
            printf("\nCurrent details of %s:\n", students[i].name);
            printf("Age: %d, Department: %s\n", students[i].age, students[i].department);
            
            printf("\n--- Enter new details ---\n");
            
            printf("New name: ");
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            
            printf("New age: ");
            scanf("%d", &students[i].age);
            clearBuffer();
            
            printf("New department: ");
            fgets(students[i].department, 30, stdin);
            students[i].department[strcspn(students[i].department, "\n")] = 0;
            
            printf("\nEnter new marks:\n");
            for(int j = 0; j < 5; j++) {
                do {
                    printf("Subject %d: ", j + 1);
                    scanf("%f", &students[i].marks[j]);
                    clearBuffer();
                    
                    if(students[i].marks[j] < 0 || students[i].marks[j] > 100) {
                        printf("Please enter marks between 0-100.\n");
                    }
                } while(students[i].marks[j] < 0 || students[i].marks[j] > 100);
            }
            
            calculateResults(&students[i]);
            
            printf("\nStudent record updated successfully!\n");
            printf("New percentage: %.2f%%\n", students[i].percentage);
            printf("New grade: %c\n", students[i].grade);
            break;
        }
    }
    
    if(!found) {
        printf("Student with roll number %d not found.\n", roll);
    }
}

void removeStudent() {
    if(totalStudents == 0) {
        printf("\nNo students to delete.\n");
        return;
    }
    
    int roll;
    char confirm;
    
    printf("\n--- Delete Student ---\n");
    printf("Enter roll number: ");
    scanf("%d", &roll);
    clearBuffer();
    
    int found = 0;
    for(int i = 0; i < totalStudents; i++) {
        if(students[i].rollNo == roll) {
            found = 1;
            
            printf("\nAre you sure you want to delete %s? (y/n): ", students[i].name);
            scanf("%c", &confirm);
            clearBuffer();
            
            if(confirm == 'y' || confirm == 'Y') {
                // Move all students after this one forward
                for(int j = i; j < totalStudents - 1; j++) {
                    students[j] = students[j + 1];
                }
                totalStudents--;
                printf("Student deleted successfully.\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            break;
        }
    }
    
    if(!found) {
        printf("Student with roll number %d not found.\n", roll);
    }
}

void calculateResults(struct Student *s) {
    float total = 0;
    
    // Add up all marks
    for(int i = 0; i < 5; i++) {
        total += s->marks[i];
    }
    
    // Calculate percentage
    s->percentage = (total / 500.0) * 100.0;
    
    // Assign grade
    s->grade = getGrade(s->percentage);
}

char getGrade(float percentage) {
    if(percentage >= 90) return 'A';
    if(percentage >= 80) return 'B';
    if(percentage >= 70) return 'C';
    if(percentage >= 60) return 'D';
    if(percentage >= 50) return 'E';
    return 'F';
}

int rollNumberExists(int roll) {
    for(int i = 0; i < totalStudents; i++) {
        if(students[i].rollNo == roll) {
            return 1;
        }
    }
    return 0;
}

void saveData() {
    FILE *file = fopen(FILENAME, "wb");
    
    if(file == NULL) {
        printf("Error: Couldn't save data to file!\n");
        return;
    }
    
    // Save total number of students first
    fwrite(&totalStudents, sizeof(int), 1, file);
    
    // Then save all student records
    fwrite(students, sizeof(struct Student), totalStudents, file);
    
    fclose(file);
}

void loadData() {
    FILE *file = fopen(FILENAME, "rb");
    
    if(file == NULL) {
        // File doesn't exist yet, that's okay
        return;
    }
    
    // Read total number of students
    fread(&totalStudents, sizeof(int), 1, file);
    
    // Read all student records
    fread(students, sizeof(struct Student), totalStudents, file);
    
    fclose(file);
    
    if(totalStudents > 0) {
        printf("\nLoaded %d student(s) from previous session.\n", totalStudents);
    }
}

void clearBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}