#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Task {
	char title[100];
	int priority;
	struct Task* next;
	struct Task* prev;
}Task;

void addTask(Task** head, char* title, int priority) {
	Task* newTask = (Task*)malloc(sizeof(Task));
	if (newTask == NULL) {
		printf("Memory not Allocated.\n");
		return;
	}
	//Mapping
	strcpy(newTask->title, title);
	newTask->priority = priority;
	Task* next = NULL;
	Task* prev = NULL;

	//First Task
	if (*head == NULL || priority < (*head)->priority) {
		newTask->next = *head;
		if (*head != NULL) {
			(*head)->prev = newTask;
		}
		*head = newTask;
		printf("Task '%s' added at the top.\n", title);
		return;
	}
	//Finding location
	Task* current = *head;
	while (current->next != NULL && current->next->priority <= priority) {
		current = current->next;
	}
	//Insertion
	newTask->next = current->next;
	newTask->prev = current;

	if (current->next != NULL) {
		current->next->prev = newTask;	// Linking prev and next. EG if pri 4 new task is added when 1,2,3 and 5 are already present. Prevents an error
	}

	current->next = newTask;

	printf("Task '%s' added successfully.\n", title);
}

void viewTasks(Task* head) {
	if (head == NULL) {
		printf("No tasks in your to-do list.\n");
		return;
	}

	printf("Pending Tasks (Sorted by Priority):\n\n");

	Task* current = head;
	while (current != NULL) {
		printf("• Task   : %s\n", current->title);
		printf("  Priority: %d\n", current->priority);
		printf("----------------------\n");
		current = current->next;
	}
}

void markTaskAsDone(Task** head, const char* title) {
	if (*head == NULL) {
		printf("No Tasks to be deleted.\n");
		return;
	}
	Task* current = *head;
	while (current != NULL) {
		if (strcmp(current->title, title) == 0) {
			if (current == *head) {
				*head = current->next;
				if (*head != NULL) {
					(*head)->prev = NULL;
				}
			}
			else {
				current->prev->next = current->next;
				if (current != NULL) {
					current->next->prev = current->prev;
				}
			}
			printf("Task '%s' marked as done and removed.\n", title);
			free(current);
			return;
		}
		current = current->next;
	}
	printf("Task '%s' not found.\n", title);
}
	
void freeTasks(Task* head) {
	Task* temp;

	while (head != NULL) {
		temp = head;           // Save current node
		head = head->next;     // Move head to the next node
		free(temp);            // Free current node
	}

	printf("All tasks have been cleared from memory.\n");
}
int main() {
	Task* head = NULL;
	int choice;
	char title[100];
	int priority;

	while (1) {
		printf("\nTo-Do List Menu\n");
		printf("1. Add a new task\n");
		printf("2. View tasks\n");
		printf("3. Mark task as done\n");
		printf("4. Clear all tasks\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar(); // Clear newline from input buffer

		switch (choice) {
		case 1:
			printf("Enter task title: ");
			fgets(title, sizeof(title), stdin);
			title[strcspn(title, "\n")] = '\0';  // Remove newline

			printf("Enter priority (1 = highest): ");
			scanf("%d", &priority);
			getchar();

			addTask(&head, title, priority);
			break;

		case 2:
			viewTasks(head);
			break;

		case 3:
			printf("Enter task title to mark as done: ");
			fgets(title, sizeof(title), stdin);
			title[strcspn(title, "\n")] = '\0';
			markTaskAsDone(&head, title);
			break;

		case 4:
			freeTasks(head);
			head = NULL;
			break;

		case 5:
			freeTasks(head);
			printf("Exiting program. Goodbye!\n");
			return 0;

		default:
			printf("Invalid choice. Try again.\n");
		}
	}

	return 0;
}