#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

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
    // TODO
    // Loop through all the candidate names
    for (int i = 0, j = candidate_count; i < j; i++)
    {
        // If candidate name matches, increase the vote by 1 for that candidate
        if (strcasecmp(name, candidates[i].name) == 0)
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
    int highest_votes = -1;

    // TODO
    // Loop through all the candidate votes
    for (int i = 0, j = candidate_count; i < j; i++)
    {
        // If the candidate has more votes than current highest votes, make current candidate highest
        if (highest_votes < candidates[i].votes)
        {
            highest_votes = candidates[i].votes;
        }
    }
    // Print all names with the highest votes
    for (int k = 0, l = candidate_count; k < l; k++)
    {
        if (candidates[k].votes == highest_votes)
        {
            printf("%s\n", candidates[k].name);
        }
    }

    return;
}