#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 1000

// ================= STRUCT ===================
typedef struct StackNode {
    char* textSnapshot;
    struct StackNode* next;
} StackNode;

// ================= STACK FUNCTIONS ===================
void push(StackNode** stack, const char* text) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->textSnapshot = _strdup(text); // Copy current text
    newNode->next = *stack;
    *stack = newNode;
}

char* pop(StackNode** stack) {
    if (*stack == NULL) return NULL;

    StackNode* temp = *stack;
    *stack = (*stack)->next;

    char* text = temp->textSnapshot;
    free(temp);
    return text;
}

void clearStack(StackNode** stack) {
    while (*stack != NULL) {
        StackNode* temp = *stack;
        *stack = (*stack)->next;
        free(temp->textSnapshot);
        free(temp);
    }
}

// MAIN TEXT BUFFER 
char currentText[MAX_TEXT] = "";

// TYPE FUNCTION 
void typeText(StackNode** undoStack, StackNode** redoStack) {
    char input[MAX_TEXT];
    printf("Enter text to append: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline

    push(undoStack, currentText);       // Save current state
    clearStack(redoStack);              // Invalidate redo
    strcat(currentText, input);         // Append input
    printf(" Text added successfully.\n");
}

// UNDO / REDO 
void undo(StackNode** undoStack, StackNode** redoStack, char* currentText) {
    if (*undoStack == NULL) {
        printf("Nothing to undo.\n");
        return;
    }

    push(redoStack, currentText);           // Save current before undoing
    char* previous = pop(undoStack);        // Get last state
    strcpy(currentText, previous);          // Restore it
    free(previous);                         // Free snapshot
    printf("Undo completed.\n");
}

void redo(StackNode** undoStack, StackNode** redoStack, char* currentText) {
    if (*redoStack == NULL) {
        printf("Nothing to redo.\n");
        return;
    }

    push(undoStack, currentText);           // Save current before redo
    char* next = pop(redoStack);
    strcpy(currentText, next);
    free(next);
    printf("Redo completed.\n");
}

// DISPLAY 
void displayText(const char* currentText) {
    printf("\nCurrent Text: \"%s\"\n", currentText);
}

// MAIN MENU 
int main() {
    StackNode* undoStack = NULL;
    StackNode* redoStack = NULL;

    int choice;
    while (1) {
        printf("\n===========================\n");
        printf("Simple Text Editor Menu\n");
        printf("1. Type text\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Display current text\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
        case 1:
            typeText(&undoStack, &redoStack);
            break;
        case 2:
            undo(&undoStack, &redoStack, currentText);
            break;
        case 3:
            redo(&undoStack, &redoStack, currentText);
            break;
        case 4:
            displayText(currentText);
            break;
        case 5:
            clearStack(&undoStack);
            clearStack(&redoStack);
            printf(" Exiting... Goodbye!\n");
            return 0;
        default:
            printf(" Invalid choice. Try again.\n");
        }
    }
}
