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
// Here, we will check if the vote is valid by comparing the string given by the user and all candidates in our array.
{
    // TODO
    for (int candPos = 0; candPos < candidate_count; candPos++)
    {
        if (strcmp(candidates[candPos].name, name) == 0)
        {
            preferences[voter][rank] = candPos; 
// If we have that candidate in our candidate's array, we will add his associated number for its position in its array to the current rank for that voter.
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int Voters = 0; Voters < voter_count; Voters++) // We will check the whole voters' array.
    {
        for (int candPos = 0; candPos < candidate_count; candPos++) // We will check the whole candidate's array.
        {
            if (candidates[preferences[Voters][candPos]].eliminated == false) 
//If the current candidate for the current voter and voter's position is false. That will mean that the candidate still exists.
            {
                candidates[preferences[Voters][candPos]].votes =  candidates[preferences[Voters][candPos]].votes + 1; 
// So we will add one vote for the current voter for its current position to that candidate.
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int candPos = 0; candPos < candidate_count; candPos++) // We will check the whole candidate array.
    {
        if (candidates[candPos].votes > (voter_count / 2)) 
// If any of them has more votes than the half of all votes, it means that he/she automatically has won.
        {
            printf("%s\n", candidates[candPos].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = voter_count; // Here, we will set "min" of votes to the total amount of voters.
    for (int candPos = 0; candPos < candidate_count; candPos++) // We will check the whole candidate's array.
    {
        if ((candidates[candPos].votes < min) && (candidates[candPos].eliminated == false)) 
//If the current checked candidate has less votes than the current min amoun of votes and that candidate is still playing.
        {
            min = candidates[candPos].votes; // That will mean that he/she is the candidate with the fewer number of votes.
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // We will check the whole candidates' list.
    {
        if ((min != candidates[i].votes) && (candidates[i].eliminated == false)) 
// If the mininum variable is differente than the for the current's candidate votes and that candidate is still running for the election.
        {
            return false; // That will means that there is not a tied.
        }
    }
    return true; // If that condition is not right, then that will mean that there is a tied.
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // We will check the whole candidates' array.
    {
        if (min == candidates[i].votes) // If any of them has the minium amount of votes.
        {
            candidates[i].eliminated = true; 
// That will means that is the candidate with fewer votes and he/she is automatically out of the election.
        }
    }
    return;
}