// This program contains the implementation of the 5 basic operations 
// with singly linked lists enumerated in the singly linked list short.
// 1. Create a linked list when it doesn't already exist
// 2. Search through a linked list to find an element
// 3. Insert a new node into the linked list
// 4. Delete a single element from a linked list
// 5. Delete an entire linked list

// I have run out of time and will not be attempting the 4th operation until and unkown later date

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

// Function Prototypes
node* create(int n);
node* insert(node *head, int n);
void print_list(node *head);
bool find(node *head, int n);
void destroy(node *head);

int main(void)
{
    srand(time(NULL));
    int p = rand() % 20;
    node *head_pointer = NULL;

    for (int i = 0; i < 11; i++)
    {
        head_pointer = insert(head_pointer, rand() % 20);
    }

    print_list(head_pointer);
    int to_find = rand() % 20;
    bool exists = find(head_pointer, to_find);
    if (exists == true)
    {    
        printf("The number %i exists in this linked list\n", to_find);
    }
    else
    {
        printf("The number %i does not exist in this linked list\n", to_find);
    }
    destroy(head_pointer);
}

node* create(int n)
{
    // Dynamically allocate space for a new node
    node *p = malloc(sizeof(node));
    // Check to make sure we didn't run out of memory
    if (p == NULL)
    {
        printf("Creation of node has failed.\n");
        return NULL;
    }
    // Initialize the node's value (number in this case) field
    p-> number = n;
    // Initialize the node's next field
    p-> next = NULL;
    // Return a pointer to the newly created node
    return p;
}

node* insert(node *head, int n)
{
    // Creates a new node using the create function
    node *new_head = create(n);
    // Sets the next field of this new node to be the same as the head of the linked list
    new_head -> next = head;
    // Returns the pointer to this new node to become the new head of the linked list
    return new_head;
}

void print_list(node *head)
{
    printf("Head: %p\n", head);
    node *temp = head;
    int node_counter = 0;
    while (temp != NULL)
    {
        printf("Node %i: Number: %i Next: %p\n", node_counter, temp -> number, temp -> next);
        temp = temp -> next;
        node_counter++;
    }
    printf("\n");
}

bool find(node *head, int n)
{
    node *temp = head;
    while (temp != NULL)
    {
        if (temp -> number == n)
        {
            return true;
        }
        else
        {
            temp = temp -> next;
        }
    }
    return false;
}

void destroy(node *head)
{
    node *temp = head;
    if (temp == NULL)
    {
        return;
    }
    destroy(temp -> next);
    free(temp);
}
