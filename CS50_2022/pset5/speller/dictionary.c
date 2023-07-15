// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Function Prototypes
void destroy(node *head);
node *create(const char *word);
node *insert(node *head, const char *word);
void print_list(node *head);
bool find(node *head, const char *word);

// Number of buckets in hash table
const unsigned int N = 52;

// Dictionary word counter
int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    return find(table[hash(word)], word);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function
    if ((toupper(word[1]) - 'A') < 13)
    {
        return ((toupper(word[0]) - 'A') * 2);
    }
    else
    {
        return (((toupper(word[0]) - 'A') * 2) + 1);
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Sets each hash table value to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    // Checks for errors in fopen
    if (file == NULL)
    {
        return false;
    }
    // Creates word buffer
    char buffer[LENGTH + 1];
    // Scans each word from the dictionary and puts it into the word buffer
    while (fscanf(file, "%s", buffer) != EOF)
    {
        if (table[hash(buffer)] == NULL)
        {
            table[hash(buffer)] = create(buffer);
            counter++;
        }
        else
        {
            table[hash(buffer)] = insert(table[hash(buffer)], buffer);
            counter++;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Goes through the hash table and frees each linked list
    for (int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }
    return true;
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

node *create(const char *word)
{
    // Dynamically allocate memory for a new node
    node *p = malloc(sizeof(node));
    // Check for malloc error
    if (p == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    // Initialize node's word value
    strcpy(p -> word, word);
    // Initialize node's next value
    p -> next = NULL;
    // Return a pointer to the newly created node
    return p;
}

node *insert(node *head, const char *word)
{
    // Create a new node using the create function
    node *new_head = create(word);
    // Set the next value of this new node to be the same as the current head of the linked list
    new_head -> next = head;
    // Returns the pointer of this new node to be the new head of the linked list
    return new_head;
}

void print_list(node *head)
{
    node *temp = head;
    while (temp != NULL)
    {
        printf("%s\n", temp -> word);
        temp = temp -> next;
    }
}

bool find(node *head, const char *word)
{
    // Traverses the linked list using the head pointer provided as the starting point
    node *temp = head;
    while (temp != NULL)
    {
        if (strcasecmp(word, temp -> word) == 0)
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