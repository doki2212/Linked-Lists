#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct Student_records {             // typedef is an alias for the structure 'struct Student_records'. From henceforth whenever
	int id;									//you callStudent, you will be invoking the structure 'struct Student_records'. Its important for
	char name[100];							//linked lists
	float GPA;
	struct Student_records *next;			//Read this from the right. Defined a pointer called next which stores the next struct data
} Student;

void addStudent(Student **head); //Pointing to the location of head. An address will be passed here, the address will be recv from the main code
//Values are not passed from function to function, changed values remain in the function where they were changed. Hence we are passing via reference
//The **head == I am passing the address of the address of where the value is so that you can change it and return it.
void addStudent(Student** head) {
	Student* newstudent = (Student*)malloc(sizeof(Student));//malloc returns a null pointer, that pointer we redirect to Student*. Take this void 
	//pointer and store it as student struct. The pointer *newstudent just says that a pointer called newstudent whose type is Student has it's memory
	//stored in the memalloc space. ""malloc=Take this generic memory block and treat it as a pointer to a Student struct."
	if (newstudent == NULL) {			// Basic check for memory
		printf("Memory Allocation Failed.\n");
		return;
	}

	//Taking Input from user
	printf("Enter Student ID: ");
	scanf("%d", &newstudent->id);

	printf("Enter Student Name: ");
	scanf(" %[^\n]", newstudent->name);

	printf("Enter Student GPA: ");
	scanf("%f", &newstudent->GPA);

	//Adding next studen

	newstudent->next = NULL; //This checks if the linked list is currently empty.*head == NULL means the list has no nodes yet.
	if (*head == NULL) {		// If so, make this new node the head (first node) of the list.
		*head = newstudent;	//*head = newstudent; → Now the head of the list points to this first student.
	}
	else {
		Student* current = *head;			//keep going until i reach the next as null. This is to add a node at the end of the list
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newstudent;
	}
	printf("Student Added Successfully.\n");
	return;
}

void viewStudents(Student* head) {
	if (head == NULL) {
		printf("No Students Available.\n");
		return;
	}
	printf("List of Students.\n");

	Student* current = head;
	while (current != NULL) {
		printf("ID: %d\n", current->id);
		printf("Name: %s\n", current->name);
		printf("GPA: %.2f\n\n", current->GPA);
		current = current->next;
	}

}


void searchStudentByID(Student* head, int id) {
	if (head == NULL) {
		printf("Student ID not present.\n");
		return;
	}
	Student* current = head;
	while (current != NULL) {
		if (current->id == id) {
			printf("\nStudent Found:\n");
			printf("ID   : %d\n", current->id);
			printf("Name : %s\n", current->name);
			printf("GPA  : %.2f\n", current->GPA);
			return;
		}
		current = current->next;
	}
	printf("Student with ID %d not found.\n", id);
}
void deleteStudentByID(Student **head, int id) {
	if (*head == NULL) {
		printf("Student ID is not present.\n");
		return;
	}
	Student* temp = *head;
	Student* prev = NULL;
	if (temp != NULL && temp->id == id) {
		*head = temp->next;
		free(temp);
		printf("Student with ID %d deleted successfully.\n", id);
		return;
	}
	while (temp != NULL && temp->id != id) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("Student with ID %d not found.\n", id);
		return;
	}
	prev->next = temp->next;
	free(temp);
	printf("Student with ID %d deleted successfully.\n", id);
}

void freeStudentList(Student* head) {
	Student* temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}

	printf("All student records have been freed from memory.\n");
}
int main() {
	Student* head = NULL;
	int choice;

	while (1) {
		printf("\n=== Student Records Menu ===\n");
		printf("1. Add a new student\n");
		printf("2. View Existing students\n");
		printf("3. Search for a Student\n");
		printf("4. Delete a record\n");
		printf("5. Delete all records\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		if (choice == 1) {
			addStudent(&head);
		}
		else if (choice == 2) {
			viewStudents(head);
		}
		else if (choice == 3) {
			int idToSearch;
			printf("Enter ID to search: ");
			scanf("%d", &idToSearch);
			searchStudentByID(head, idToSearch);  // Case-sensitive function name
		}
		else if (choice == 4) {
			int idToDelete;
			printf("Enter ID to delete: ");
			scanf("%d", &idToDelete);
			deleteStudentByID(&head, idToDelete);  // Case-sensitive
			viewStudents(head);
		}
		else if (choice == 5) {
			freeStudentList(head);
			head = NULL;
			printf("All records deleted.\n");
		}
		else if (choice == 6) {
			freeStudentList(head);
			printf("Exiting program. Goodbye!\n");
			break;  // Exit the loop
		}
		else {
			printf("Invalid choice. Try again.\n");
		}
	}

	return 0;
}