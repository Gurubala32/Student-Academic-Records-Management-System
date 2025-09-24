#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student {
    int id;
    char name[50];
    char dept[50];
    float gpa;
    struct Student *prev;
    struct Student *next;
} Student;

Student *head = NULL; 


void insertStudent(int id, char name[], char dept[], float gpa) {
    Student *newStudent = (Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    strcpy(newStudent->dept, dept);
    newStudent->gpa = gpa;
    newStudent->next = NULL;
    newStudent->prev = NULL;

    if (head == NULL) {
        head = newStudent;
    } else {
        Student *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
        newStudent->prev = temp;
    }
    printf("Student inserted successfully.\n");
}


void deleteStudent(int id) {
    Student *temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next; 
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Student with ID %d deleted successfully.\n", id);
}


void searchStudentByID(int id) {
    Student *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Found: %d | %s | %s | %.2f\n", temp->id, temp->name, temp->dept, temp->gpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}


void searchStudentByName(char name[]) {
    Student *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Found: %d | %s | %s | %.2f\n", temp->id, temp->name, temp->dept, temp->gpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student with name %s not found.\n", name);
}


void displayStudents() {
    Student *temp = head;
    if (temp == NULL) {
        printf("No student records found.\n");
        return;
    }
    printf("Student Records (Forward):\n");
    while (temp != NULL) {
        printf("%d | %s | %s | %.2f\n", temp->id, temp->name, temp->dept, temp->gpa);
        temp = temp->next;
    }
}


void displayStudentsReverse() {
    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }
    Student *temp = head;
    while (temp->next != NULL) {
        temp = temp->next; 
    }
    printf("Student Records (Reverse):\n");
    while (temp != NULL) {
        printf("%d | %s | %s | %.2f\n", temp->id, temp->name, temp->dept, temp->gpa);
        temp = temp->prev;
    }
}

Student* cloneList(Student *originalHead) {
    if (originalHead == NULL) return NULL;

    Student *cloneHead = NULL, *cloneTail = NULL;
    Student *temp = originalHead;

    while (temp != NULL) {
        Student *newNode = (Student*)malloc(sizeof(Student));
        *newNode = *temp; 
        newNode->next = NULL;
        newNode->prev = NULL;

        if (cloneHead == NULL) {
            cloneHead = newNode;
            cloneTail = newNode;
        } else {
            cloneTail->next = newNode;
            newNode->prev = cloneTail;
            cloneTail = newNode;
        }
        temp = temp->next;
    }
    return cloneHead;
}


void calculateAverageGPA() {
    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }
    Student *temp = head;
    int count = 0;
    float sum = 0;
    while (temp != NULL) {
        sum += temp->gpa;
        count++;
        temp = temp->next;
    }
    printf("Average GPA = %.2f\n", sum / count);
}


int main() {
    int choice, id;
    char name[50], dept[50];
    float gpa;

    while (1) {
        printf("\n--- Student Academic Record System ---\n");
        printf("1. Insert Student\n2. Delete Student\n3. Search by ID\n4. Search by Name\n5. Display Students\n6. Display Reverse\n7. Clone List\n8. Average GPA\n9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID, Name, Department, GPA: ");
                scanf("%d %s %s %f", &id, name, dept, &gpa);
                insertStudent(id, name, dept, gpa);
                break;
            case 2:
                printf("Enter Student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;
            case 3:
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                searchStudentByID(id);
                break;
            case 4:
                printf("Enter Student Name to search: ");
                scanf("%s", name);
                searchStudentByName(name);
                break;
            case 5:
                displayStudents();
                break;
            case 6:
                displayStudentsReverse();
                break;
            case 7: {
                Student *backup = cloneList(head);
                printf("Cloned list created successfully.\n");
                printf("Backup List:\n");
                Student *temp = backup;
                while (temp != NULL) {
                    printf("%d | %s | %s | %.2f\n", temp->id, temp->name, temp->dept, temp->gpa);
                    temp = temp->next;
                }
                break;
            }
            case 8:
                calculateAverageGPA();
                break;
            case 9:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
