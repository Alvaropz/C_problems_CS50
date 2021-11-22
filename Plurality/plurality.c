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
int candWinnerVotes = 0; // Variable added by the new coder (Alvaro) to check the biggest amount of votes.

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
    for (int i = 0; i < candidate_count; i++) // We will check if the names given by the voters are in the array. 
    {
        if (strcmp(candidates[i].name, name) == 0) 
//  We will check the given name comparing the strings of the given name by the voter and the name of the i element that it's being checked. If they are the same, we will add one vote to that candidate.
        {
            candidates[i].votes = candidates[i].votes + 1; // So we will add one vote to the current i candidate.
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    for (int n = 0; n < candidate_count; n++) 
// We will go through the whole array of candidates to check which one has the biggest amount of votes.
    {
        if ((candidates[n].votes > candidates[n + 1].votes) && (candidates[n].votes > candWinnerVotes)) 
//If the current candidate has more votes than the next candidate in the array and his votes is bigger than the biggest amount of votes counted by then.
        {
            candWinnerVotes = candidates[n].votes; // We will set his votes as the biggest amount of votes counted so far.
        }
        if ((candidates[n].votes < candidates[n + 1].votes) && (candidates[n + 1].votes > candWinnerVotes)) 
//If the current candidate has fewer votes than the next candidate in the array and the votes of the next candidate are bigger than the biggest amount of votes counted by then.
        {
            candWinnerVotes = candidates[n + 1].votes; 
// We will set the votes of the next candidate as the biggest amount of votes counted so far.
        }
        if ((n == candidate_count) && (candidates[candidate_count].votes - 1 > candWinnerVotes)) 
//If the last candidate in the list has more votes than the biggest amount of votes counted so far.
        {
            candWinnerVotes = candidates[candidate_count].votes; 
// We will set the votes of the last candidate in the array as the biggest amount of votes counted so far.
        }
    }
    if (candWinnerVotes != 0) // Then, if any of them has at least one vote.
    {
        for (int i = 0; i < candidate_count; i++) // We will check who is the winner. We can also check if there is more than one winner.
        {
            if (candWinnerVotes == candidates[i].votes) // If the biggest amount of votes match with the votes of the current candidate check.
            {
                printf("%s\n", candidates[i].name); // We will print his name as one of the winners.
            }
        }
    }
    return;
}