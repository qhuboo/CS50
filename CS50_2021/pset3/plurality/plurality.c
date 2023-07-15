#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //This transfers the vote counts to another array (called array) that is easier to manipulate
    int array[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        array[i] = candidates[i].votes;
    }
    //This will sort the new array from smallest to largest
    int smallest;
    int min_index;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (array[j] < array[min_index])
            {
                min_index = j;
            }
        }
        smallest = array[min_index];
        array[min_index] = array[i];
        array[i] = smallest;
    }
    //This will then look for the candidates that votes as the largest number in our sorted array
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == array[candidate_count - 1])
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

