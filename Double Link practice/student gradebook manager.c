#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student {
	char name[100];
	int roll;
	char subject[100];
	char grade;
	struct student* next;
	struct student* prev;
}student;

void addstudent(student** head) {
	student* newstudent = (student*)malloc(sizeof(student));
	if (newstudent == NULL) {
		printf("Memory not Allocated.\n");
		return;
	}
	printf("Enter Students Name.\n");
	fgets(newstudent->name, sizeof(newstudent->name), stdin);
	newstudent->name[strcspn(newstudent->name, "\n")] = '\0';

	printf("Enter Students Roll Number.\n");
	scanf("%d", &newstudent->roll);
	getchar();

	student* temp = *head;
	while (temp != NULL) {
		if (temp->roll == newstudent->roll) {
			printf("Duplicate Roll Number cannot be added.\n");
			free(newstudent);
			return;
		}
		temp = temp->next;
	}

	printf("Enter Subject.\n");
	fgets(newstudent->subject, sizeof(newstudent->subject), stdin);
	newstudent->subject[strcspn(newstudent->subject, "\n")] = '\0';

	printf("Enter Grade Obtained.\n");
	scanf(" %c", &newstudent->grade);
	getchar();

	newstudent->next = NULL;
	newstudent->prev = NULL;

	//Empty List

	if (*head == NULL) {
		*head = newstudent;
		printf("New Student has been successfully added.\n");
		return;
	}
	
	//Add at beginning

	if (newstudent->roll < (*head)->roll) {
		newstudent->next = *head;
		(*head)->prev = newstudent;
		*head = newstudent;
		printf("Student added successfully.\n");
		return;
	}

	//Add middle or end
	student* current = *head;
	while (current->next != NULL && current->next->roll < newstudent->roll) {
		current = current->next;
	}
	newstudent->next = current->next;
	newstudent->prev = current;

	if (current->next != NULL) {
		current->next->prev = newstudent; /// Linking in between
	}
	current->next = newstudent;
	printf("New Student added Successfully\n");
}

void viewallstudents(student *head) {
	if (head == NULL) {
		printf("No student record found.\n");
		return;
	}
	printf("\nList of Students:\n");
	printf("%-15s %-10s %-15s %-2s\n", "Name", "Roll No", "Subject", "Grade");
	printf("----------------------------------------------------------\n");

	student* current = head;
	while (current != NULL) {
		printf("%-15s %-10d %-15s %-2c\n", current->name, current->roll, current->subject, current->grade);
		current = current->next;
	}
}

void deletestudent(student **head, int roll) {
	if (*head == NULL) {
		printf("No Records to delete\n");
		return;
	}

	student* current = *head;
	while (current != NULL && current->roll != roll) {
		current = current->next;
	}
	if (current == NULL) {
		printf("Record for this student does not exist.\n");
		return;
	}
	if (current == *head) {
		*head = current->next;
		if (*head != NULL) {
			(*head)->prev = NULL;
		}
	}
	else {
		current->prev->next = current->next;
		if (current->next != NULL) {
			current->next->prev = current->prev;
		}
	}
	printf("Record Succesfully deleted.\n");
	free(current);
}

void upgrade(student* head, int roll) {
	if (head == NULL) {
		printf("Student record not found.\n");
		return;
	}
	student* current = head;
	while (current != NULL && current->roll != roll) {
		current = current->next;
	}
	if (current == NULL) {
		printf("Student Record not found.\n");
		return;
	}
	printf("Found Student: %s (Roll: %d, Subject: %s, Grade: %c)\n",
		current->name, current->roll, current->subject, current->grade);

	//New grade
	char ch;
	printf("Enter New Grade.\n");
	scanf(" %c", &ch);
	getchar();

	current->grade = ch;
	printf("Grade changed.\n");
}

void searchrollnumber(student* head, int roll) {
	if (head == NULL) {
		printf("Record does not exist.\n");
		return;
	}
	student* current = head;
	while (current != NULL && current->roll != roll) {
		current = current->next;
	}
	if (current == NULL) {
		printf("Student record not found.\n");
		return;
	}
	printf("Found Student: %s (Roll: %d, Subject: %s, Grade: %c)\n",
		current->name, current->roll, current->subject, current->grade);
}

void clearall(student* head) {
	student* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	printf("All Tasks have been cleared from memory.\n");
}
int main() {
	student* head = NULL;
	int choice;

	while (1) {
		printf("\n===== Student Management Menu =====\n");
		printf("1. Add Student\n");
		printf("2. View All Students\n");
		printf("3. Delete Student by Roll Number\n");
		printf("4. Update Grade by Roll Number\n");
		printf("5. Search Student by Roll Number\n");
		printf("6. Clear All Records\n");
		printf("7. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();  // Clear newline from input buffer

		if (choice == 1) {
			addstudent(&head);
		}
		else if (choice == 2) {
			viewallstudents(head);
		}
		else if (choice == 3) {
			int roll;
			printf("Enter roll number to delete: ");
			scanf("%d", &roll);
			getchar();
			deletestudent(&head, roll);
		}
		else if (choice == 4) {
			int roll;
			printf("Enter roll number to update grade: ");
			scanf("%d", &roll);
			getchar();
			upgrade(head, roll);
		}
		else if (choice == 5) {
			int roll;
			printf("Enter roll number to search: ");
			scanf("%d", &roll);
			getchar();
			searchrollnumber(head, roll);
		}
		else if (choice == 6) {
			clearall(head);
			head = NULL;
			printf("All records cleared.\n");
		}
		else if (choice == 7) {
			clearall(head);
			printf("Exiting program. Goodbye!\n");
			break;
		}
		else {
			printf("Invalid choice. Please try again.\n");
		}
	}

	return 0;
}

