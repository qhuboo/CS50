#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: "); 
	
    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // This function has as input a name, a rank, and the whole (as a reference) of the ranks array.
    // The function iterates through all the candidate names in the candidates array and when the input name matches one of the candidates on the list
    // the funtion changes the value of the ranks array at the value rank to i, the number of the candidate on the list and then returns true.
    // The true is then negated in the calling function so as to not go to the "invalid vote" branch.
    for (int i = 0; i < candidate_count; i++)
    {   
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }   
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{	
	// This function records the number of times when candidate i is prefered over candidate j = i + 1 (the subsequent candidate) in the ranks
	// array. The preferences array is a MAX x MAX array with 0 in every cell. So we just add 1 to every cell for position prefences[rank[i]][rank[j]].
	// Naturally we run through i from 0 to candidate_count - 1 so as to be able to use the last value in the ranks array. 
	// Example case: Say one of the voters chose his candidate preferences in the exact order of the candidates array for three candidates.
	// The ranks array would then be 0,1,2 signifying that the 0th candidate is prefered over the 1st candidate is prefered over the 2nd candidate.
	// Thus we would add 1 to the value at preferences[0][1], meaning 1 more voter prefers the 0th candidate over the 1st candidate,
	// then 1 to the value at preferences[1][2]. 
	for (int i = 0; i < candidate_count - 1; i++)
    {   
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }   
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // This function uses the prefernces array to find the differences of preferences between candidate i and the subsequent candidate j = i + 1. 
    // Naturally we iterate i through the second to last candidate, making j = i + 1 the last candidate compared. Of course, preferences[i][j] records the number of voters who prefered candidate i
    // over candidate j, and thus preferences[j][i] is the reverse. Subtracting these two values therefore results in the differences and hence the winner and the loser of the head to head between
    // candidate i and j. Since pair_count is initialized at 0 and array indexing starts at 0, we will imcrement pair_count by one *after* assigning the pairs[i].winner and pairs[i].loser. We will
    // end up with both the correct pair_count value and the right pairs array indexing.
    for (int i = 0; i < candidate_count - 1; i++)
    {   
        for (int j = i + 1; j < candidate_count; j++)
        {
            if ((preferences[i][j] - preferences[j][i]) != 0) // Checks for a tie, if a tie is present then the pair is not added to the pairs array.
            {
                if ((preferences[i][j] - preferences[j][i]) > 0) // If the statement is true then preferences[i][j] > preferences[j][i] and thus i is the winner and j the loser.
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else // Else preferences[j][i] > preferences[i][j] and thus j is the winner and i the loser.
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Calculates the size of victory for each pair in the pairs array and records it in the differences array
    int differences[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        differences[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    // Sort the differences array using selection sort
    int max, max_indx, temp;
    for (int i = 0; i < pair_count - 1; i++)
    {
        max = differences[i];
        max_indx = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (differences[j] < max)
            {
                max = differences[j];
                max_indx = j;
            }
        }
        // Swap values
        temp = max;
        differences[max_indx] = differences[i];
        differences[i] = temp;
    }

    // Sort pairs array according to the sorted differences array using selection sort
    // For the difference[i] value we iterate through the pairs array to find the same difference value. Once a match is found we swap the winners and losers value at index i with those at the index
    // we found the match in. This uses selection sort but since every pair has two values associated with it i.e., winner and loser we need a total of 6 swaps to totally change the values. We use
    // the i index to both go through the differences array and the pairs array but we only need to use the differences array to put the pairs array in the right order. The j index is used to go
    // through the pairs array. pairs[i].winner and pairs[i].loser contain candidate candidates thus we can find differences by using preferences[pairs.winner][pairs.loser] and the reverse
    // index to find the differnces.
    int temp_winner, temp_loser;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (differences[i] == preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner])
            {
                // Swap values
                temp_winner = pairs[i].winner;
                temp_loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = temp_winner;
                pairs[j].loser = temp_loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}
