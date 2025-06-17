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
    char name[100];
    int votes;
    int eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
int vote(int voter, int rank, char name[]);
void tabulate(void);
int print_winner(void);
int find_min(void);
int is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[])
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
        strncpy(candidates[i].name, argv[i + 1], 100);
        candidates[i].votes = 0;
        candidates[i].eliminated = 0;
    }

    printf("Number of voters: ");
    scanf("%d", &voter_count); 
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
            char name[100];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);


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
    while (1)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        int won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        int tie = is_tie(min);

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
int vote(int voter, int rank, char name[])
{
    //get candidate index number
    int candidate_number = -1;
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
            candidate_number = i + 1;
        }
    }
    
    //vote doesn't match any candidates
    if (candidate_number <= 0) {
        printf("You must vote for a valid candidate.\n");
        return 0;
    }

    //check if already voted for by voter
    for (int i = 0;  i <= rank; i++) {
        if (preferences[voter][i] == candidate_number) {
            printf("You cannot vote for a single candidate 2 times.\n");
            return 0;
        }
    }

    //record vote
    preferences[voter][rank] = candidate_number;
    return 1;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //iterate through each voter
    for (int i = 0; i < voter_count; i++) {
        //find their first choice that has not yet been eliminated
        for (int j = 0; j < candidate_count; j++) {
            int candidate_number = preferences[i][j];
            if (!candidates[candidate_number - 1].eliminated) {
                candidates[candidate_number -  1].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
int print_winner(void)
{
    int threshold = voter_count / 2;
    //check all non eliminated candidates
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes > threshold) {
            printf("Winner: %s\n", candidates[i].name);
            return 1;
        }
    }
    return 0;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = 100;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && min > candidates[i].votes) {
            min = candidates[i].votes;
        }
    }    
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
int is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++) {
        if (min < candidates[i].votes) {
            return 0;
        }
    }    
    return 1;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min) {
            candidates[i].eliminated = 1;
        }
    }
    return;
}
