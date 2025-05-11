#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Job_Evaluation {
	int emp_id;
	char name[100];
	char rating;
	struct Job_Evaluation* next;
}eval;

void addemployee(eval** head);

void addemployee(eval** head) {
	eval* emp = (eval*)malloc(sizeof(eval));
	if (emp == NULL) {
		printf("Memory Allocation failed.\n");
		return;
	}
	printf("Enter Emplyee ID: ");
	scanf("%d", &emp->emp_id);
	printf("Enter Emplyee Name: ");
	scanf(" %[^\n]", &emp->name);
	printf("Enter Emplyee Rating: ");
	scanf(" %c", &emp->rating);

	//New Employee
	emp->next = NULL;
	if (*head == NULL) {
		*head = emp;
	}
	else {
		eval* current = *head;
		while (current->next != NULL) {
			current = current->next; ///It is a pointer to the next eval struct so it will chang the entire values present in current
		}
		current->next = emp;
	}
	printf("Employee rating uploaded.\n");
	return;

}

void viewemprating(eval* head) {
	if (head == NULL) {
		printf("No Employees present\n");
		return;
	}
	printf("List of Employees with their rating.\n");
	eval* current = head;
	while (current != NULL) {
		printf("Employee ID: %d\n", current->emp_id);
		printf("Employee name: %s\n", current->name);
		printf("Employee rating: %c\n", current->rating);
		current = current->next;
	}
}

void searchbyid(eval* head, int id) {
	if (head == NULL) {
		printf("No data available.\n");
		return;
	}
	eval* current = head;
	while (current != NULL) {
		if (current->emp_id == id) {
			printf("Employee name is: %s\n", current->name);
			printf("Employee Rating is: %c\n", current->rating);
			return;
		}
		current = current->next;
	}
	printf("No Employee found with this ID.\n");
	
}

void deletebyempID(eval** head, int id) {
	if (*head == NULL) {
		printf("Data not available.\n");
		return;
	}
	eval* temp = *head;
	eval* prev = NULL;
	if (temp != NULL && temp->emp_id == id) {
		*head = temp->next;
		free(temp);
		printf("Successfully Deleted.\n");
		return;
	}
	while (temp != NULL && temp->emp_id != id) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) {
		printf("No Employess found with this ID.\n");
		return;
	}
	prev->next = temp->next;
	free(temp);
	printf("Successfully Deleted.\n");
}

void freedata(eval* head) {
	eval* temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}

	printf("All employees records have been freed from memory.\n");
}

int main() {
	eval* head = NULL;
	int choice;

	while (1) {
		printf("\n=== Menu ===\n");
		printf("1. Add a new employee\n");
		printf("2. View Existing employees\n");
		printf("3. Search for an employee\n");
		printf("4. Delete a record\n");
		printf("5. Delete all records\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		if (choice == 1) {
			addemployee(&head);
		}
		else if (choice == 2) {
			viewemprating(head);
		}
		else if (choice == 3) {
			int idToSearch;
			printf("Enter ID to search: ");
			scanf("%d", &idToSearch);
			searchbyid(head, idToSearch);  // Case-sensitive function name
		}
		else if (choice == 4) {
			int idToDelete;
			printf("Enter ID to delete: ");
			scanf("%d", &idToDelete);
			deletebyempID(&head, idToDelete);  // Case-sensitive
			viewemprating(head);
		}
		else if (choice == 5) {
			freedata(head);
			head = NULL;
			printf("All records deleted.\n");
		}
		else if (choice == 6) {
			freedata(head);
			printf("Exiting program. Goodbye!\n");
			break;  // Exit the loop
		}
		else {
			printf("Invalid choice. Try again.\n");
		}

	}

}