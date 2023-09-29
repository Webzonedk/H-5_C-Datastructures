#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining the Christmas Decoration struct
typedef struct ChristmasDecoration
{
    char description[256];
} ChristmasDecoration;

// Defining the Node struct
typedef struct Node
{
    ChristmasDecoration decoration;
    struct Node *next; // Pointer to the next node
} Node;

// Function to create a new node
Node *createNode(ChristmasDecoration decoration)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // Allocate memory for new node
    if (newNode == NULL)
    {
        printf("Error creating a new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->decoration = decoration; // Assign decoration to the new node
    newNode->next = NULL;             // Initialize next pointer to NULL
    return newNode;                   // Return the new node
}

// Function to insert a new node at the end of the list
void insert(Node **head, ChristmasDecoration decoration)
{
    Node *newNode = createNode(decoration); // Create a new node
    if (*head == NULL)
    {                    // If the list is empty
        *head = newNode; // Set the new node as the head
        return;
    }
    Node *currentNode = *head; // Start at the head
    while (currentNode->next != NULL)
    { // Traverse to the end of the list
        currentNode = currentNode->next;
    }
    currentNode->next = newNode; // Insert the new node at the end
}

// Function to delete a decoration
void deleteNode(Node **head, char *description)
{
    if (*head == NULL)
        return;                // If the list is empty, return
    Node *currentNode = *head; // Start at the head
    Node *previousNode = NULL; // Initialize previous node to NULL
    // Find the node to delete
    while (currentNode != NULL && strcmp(currentNode->decoration.description, description) != 0)
    {
        previousNode = currentNode;      // Keep track of the previous node
        currentNode = currentNode->next; // Move to the next node
        // Break if the list is circular and we're back at the head
        if (currentNode == *head)
            break;
    }
    if (currentNode == NULL || currentNode == *head)
        return; // Decoration not found or list is circular and we've looped around
    if (previousNode != NULL)
    {
        previousNode->next = currentNode->next; // Update the next pointer of the previous node
    }
    else
    {
        *head = currentNode->next; // If deleting the head, update the head pointer
    }
    free(currentNode); // Free the memory of the deleted node
}

// Function to search a decoration
Node *search(Node *head, char *description)
{
    Node *currentNode = head; // Start at the head
    while (currentNode != NULL && strcmp(currentNode->decoration.description, description) != 0)
    { // Traverse until found or end of list
        currentNode = currentNode->next;
    }
    return currentNode; // Return the found node or NULL if not found
}

// Function to print the list (non-circular)
void printList(Node *head)
{
    Node *currentNode = head; // Start at the head
    while (currentNode != NULL)
    { // Traverse and print each node
        printf("%s\n", currentNode->decoration.description);
        currentNode = currentNode->next;
    }
    printf("\n");
}


// Function to print the list (circular)
void printCircularList(Node *head)
{
    if (head == NULL)
        return;               // If the list is empty, return
    Node *currentNode = head; // Start at the head
    do
    {
        printf("%s\n", currentNode->decoration.description); // Print the decoration description
        currentNode = currentNode->next;                     // Move to the next node
    } while (currentNode != NULL && currentNode != head);    // Continue until the list loops back to the head or reaches a NULL pointer
    printf("\n");
}

// Make the list circular (last node points to the head)
void makeCircular(Node **head)
{
    if (*head == NULL || (*head)->next == *head)
    {
        return; // List is empty or already circular
    }
    Node *currentNode = *head; // Start at the head
    while (currentNode->next != NULL && currentNode->next != *head)
    { // Traverse to the end of the list
        currentNode = currentNode->next;
    }
    // Only make the list circular if it's not already circular
    if (currentNode->next != *head)
    {
        currentNode->next = *head; // Point the last node to the head, making the list circular
    }
}

// Clear the list
void ClearList(Node **head)
{
    if (*head == NULL)
        return;                // If the list is empty, return
    Node *currentNode = *head; // Start at the head
    Node *nextNode = NULL;     // Initialize next node to NULL
    do
    {
        nextNode = currentNode->next; // Store the next node
        free(currentNode);            // Free the current node
        currentNode = nextNode;       // Move to the next node
        // Break if the list is circular and we're back at the head
    } while (currentNode != NULL && currentNode != *head);
    *head = NULL; // Set the head pointer to NULL
}

void FillTheList(Node **head)
{
    // Inserting the decorations
    ChristmasDecoration decoration1;
    strcpy(decoration1.description, "Christmas tree");

    ChristmasDecoration decoration2;
    strcpy(decoration2.description, "Christmas lights");

    ChristmasDecoration decoration3;
    strcpy(decoration3.description, "Christmas balls");
    //---------------
    // Non-Circular Linked List operations (insert)
    insert(head, decoration1);
    insert(head, decoration2);
    insert(head, decoration3);
    // printf("\nNon-Circular Linked List:");
    // printList(head);
}

// Function to search and print a decoration
void SearchAndPrintDecoration(Node *head, char *description)
{
    Node *searchResult = search(head, description); // Call the search function
    if (searchResult != NULL)
    {
        printf("Search Result: %s", searchResult->decoration.description, "\n"); // Print the description if found
    }
    else
    {
        printf("Nothing found matching the search input\n"); // Print a message if not found
    }
}

// Function to print the list
int main()
{
    Node *head = NULL;
    FillTheList(&head);

    printf("\nNon-Circular Linked List:\n");
    printList(head);

    //  Search for a decoration
    SearchAndPrintDecoration(head, "Christmas lights");

    // Delete a decoration
    deleteNode(&head, "Christmas lights");
    printf("\n\nNon-Circular Linked List after deleting a decoration:\n");
    printList(head);

    // Making the list circular
    makeCircular(&head);

    // Clear the list
    ClearList(&head);

    // Circular Linked List operations (insert)
    FillTheList(&head);

    // Circular list operations
    printf("Circular Linked List:\n");
    printCircularList(head);

    //  Search for a decoration
    SearchAndPrintDecoration(head, "Christmas lights");

    // Delete a decoration
    deleteNode(&head, "Christmas balls");

    printf("\n\nAfter Deletion:\n");
    printCircularList(head);

    return 0;
}
