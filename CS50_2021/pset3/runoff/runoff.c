#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // This tabulates all the vote counts per rank.
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < voter_count; j++)
        {
            int rank = i;
            while ((candidates[preferences[j][rank]].eliminated) == true)
            {
                rank++;
            }
            candidates[preferences[j][rank]].votes++;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // This initializes a results array for candidates votes total.
    int results[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        results[i] = candidates[i].votes;
    }

    //Now to find the max using selection sort
    int smallest;
    int min_index;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (results[j] < results[min_index])
            {
                min_index = j;
            }
        }
        smallest = results[min_index];
        results[min_index] = results[i];
        results[i] = smallest;
    }
    //Now to check whether that is more than half of the vote
    float percentage = (float) results[candidate_count - 1] / voter_count;
    if (percentage * 100 > (float)50)
    {
        //Now to look for the candidate that has that number of votes
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i]. votes == results[candidate_count - 1])
            {
                printf("%s", candidates[i].name);
            }
        }
        printf("\n");
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //Counts the number of candidates already eliminated
    int eliminated = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            eliminated++;
        }
    }
    int remaining_candidates = candidate_count - eliminated;
    // This initializes a results array for candidates votes total for those candidates not eliminated
    int results[remaining_candidates];
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            for (int j = 0; j < remaining_candidates; j++)
            {
                results[j] = candidates[i].votes;
            }
        }
    }
    //Now to find the min using selection sort
    int smallest;
    int min_index;
    for (int i = 0; i < remaining_candidates - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < remaining_candidates; j++)
        {
            if (results[j] < results[min_index])
            {
                min_index = j;
            }
        }
        smallest = results[min_index];
        results[min_index] = results[i];
        results[i] = smallest;
    }
    int min = results[0];
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int count = 0;
    int eliminated = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            count++;
        }
        else if (candidates[i].eliminated == true)
        {
            eliminated++;
        }
    }
    if (count == (candidate_count - eliminated))
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
