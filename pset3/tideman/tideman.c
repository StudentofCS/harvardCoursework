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
} pair;

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

// Function to use merge sort
void merge_sort(int first, int last);

// Function to merge arrays in the merge sort function
void merge_arrays(int first, int middle, int last);

// Function to check if an edge will create a cycle
bool check_cycle(int control, int pair_num);

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
    // TODO
    // Check if name is valid candidate
    for (int i = 0, j = candidate_count; i < j; i++)
    {
        // Update ranks to indicate voters rank preference
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
    // TODO
    // Loop through all the ranks
    for (int i = 0, j = candidate_count; i < j - 1; i++)
    {
        // Loop through all candidates making the first ranks preferred over the following ranks
        for (int k = 0; k < j; k++)
        {
            if (i < k)
            {
                preferences[ranks[i]][ranks[k]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Loop through all rows in 2d preferences array
    for (int i = 0, j = candidate_count; i < j; i++)
    {
        // Loop through all columns in 2d preferences array
        for (int k = 0; k < j; k++)
        {
            // Compare preferences between two candidates. Update pairs to show the winner
            if (preferences[i][k] > preferences[k][i] && i != k)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = k;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Find first and last elements of array to input into merge sort recursion
    int first = pair_count - pair_count;
    int last = pair_count;
    // Start merge sort recursion
    merge_sort(first, last);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // Loops through all sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        int control = i;
        // Lock the pair edge only if it will not create a cycle
        if (!check_cycle(control, i))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Loop through all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare each candidate to every other candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if anyone won against i candidate
            if (locked[j][i])
            {
                // If candidate i lost, go to next candidate
                break;
            }

            // If candidate i didn't lose and loop j went through all the candidates, print i as winner
            else if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
                return;
            }
        }
    }
    return;
}

// Use merge sort to sort the pairs
void merge_sort(int first, int last)
{
    int middle = first + (last - first) / 2;

    // Base case. If there's only one element, return.
    if (first == last)
    {
        return;
    }
    else
    {
        // Sort left half of pairs
        merge_sort(first, middle);

        // Sort right half of pairs
        merge_sort(middle + 1, last);

        // Merge and sorth the left and right pairs
        merge_arrays(first, middle, last);
    }
    return;
}

// Function to merge arrays in the merge sort function
void merge_arrays(int first, int middle, int last)
{
    // Create temporary arrays for left and right
    pair left_pair[middle - first + 1];
    pair right_pair[last - middle];

    // Temporary left pairs
    for (int i = 0, j = first; i + first <= middle; i++)
    {
        left_pair[i] = pairs[j];
        j++;
    }

    // Temporary right pairs
    for (int i = 0, j = middle + 1; i + j <= last; i++)
    {
        right_pair[i] = pairs[j];
        j++;
    }

    // Sort and merge the two halves
    for (int left = 0, right = 0, k = first, l = last; k <= l; k++)
    {
        // If left has elements and margin of vicotry is >= right margin of vicotry, add to pairs
        if ((left < (middle - first + 1) && preferences[left_pair[left].winner][left_pair[left].loser] >=
                                                preferences[right_pair[right].winner][right_pair[right].loser]) ||
            right == last - middle)
        {
            pairs[k] = left_pair[left];
            left++;
        }

        // If right pair > left pair OR there are no more left elements, place right pair element
        else
        {
            pairs[k] = right_pair[right];
            right++;
        }
    }
}

// Function to check if an edge will create a cycle
bool check_cycle(int control, int pair_num)
{
    // Base case
    if (pairs[control].winner == pairs[pair_num].loser)
    {
        // If input pair has a loser than is same as control winner, cycle has occurred.
        return true;
    }

    // Loops through locked pairs checking if input loser is a winner in another locked pair
    for (int i = 0; i < pair_count; i++)
    {
        // If loser is a winner in another locked pair, repeat check_cycle
        if (locked[pairs[i].winner][pairs[i].loser] && pairs[pair_num].loser == pairs[i].winner)
        {
            if (check_cycle(control, i))
            {
                return true;
            }

            // If locked pair is false, continue checking the following pairs
            else if (!check_cycle(control, i) && i < pair_count)
            {
                continue;
            }
        }
    }
    // If loser is not a winner in any other locked pair, return false.
    return false;
}