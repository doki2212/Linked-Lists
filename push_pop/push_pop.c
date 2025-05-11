#include <stdio.h>
#include <stdlib.h>

// Define the stack node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Push a value onto the stack
void push(Node** top, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = *top;   // Link new node to current top
    *top = newNode;         // Update top to new node
    printf("Pushed %d onto the stack.\n", value);
}

// Pop a value from the stack
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        return -1;  // Or other error signal
    }

    Node* temp = *top;
    int value = temp->data;
    *top = (*top)->next;  // Move top down
    free(temp);
    printf("Popped %d from the stack.\n", value);
    return value;
}

// Display the stack
void display(Node* top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack from top to bottom:\n");
    while (top != NULL) {
        printf("| %d |\n", top->data);
        top = top->next;
    }
    printf("-----\n");
}

// Main menu
int main() {
    Node* stack = NULL;
    int choice, value;

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(&stack, value);
            break;
        case 2:
            pop(&stack);
            break;
        case 3:
            display(stack);
            break;
        case 4:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
}
