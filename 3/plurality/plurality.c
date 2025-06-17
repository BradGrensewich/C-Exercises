#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define NAME_CHAR_MAX 100

// Candidates have name and vote count
typedef struct
{
    char name[NAME_CHAR_MAX];
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
int vote(char *name);
void print_winner(void);
void sort_candidates(void);
void swap_candidates(int index1, int index2);

int main(int argc, char **argv)
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
        strncpy(candidates[i].name, argv[i + 1], NAME_CHAR_MAX -1);
        candidates[i].name[NAME_CHAR_MAX - 1] = '\0';  // Ensure null-termination
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);
    getchar();  // Consume leftover newline

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        printf("Vote: ");
        char name[NAME_CHAR_MAX];
        scanf("%s", name);

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
int vote(char name[])
{
    for (int i =0; i < candidate_count; i ++) {        
        
        if (strcmp(name, candidates[i].name) == 0) {
            candidates[i].votes++;            
            return 1;
        }        
    }    
    return 0;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // could easily do without, but good practice
    sort_candidates();

    //print first candidate
    printf("Winner: %s with %d votes.\n", candidates[0].name, candidates[0].votes);
    return;
}

//bubble sort candidates in order by votes descending
void sort_candidates(void) {
    for (int i = 0; i < candidate_count - 1; i++) {
        int swaps = 0;
        for (int j = 0; j < candidate_count - i - 1; j++) {
            if(candidates[j].votes < candidates[j + 1].votes) {
                swap_candidates(j, j + 1);
                swaps++;
            }
        }
        if (swaps == 0) {
            return;
        }
    }
}

void swap_candidates(int index1, int index2) {    
    candidate temp;
    strncpy(temp.name, candidates[index1].name, NAME_CHAR_MAX -1);
    candidates[index1].name[NAME_CHAR_MAX - 1] = '\0';  // Ensure null-termination
    temp.votes = candidates[index1].votes;

    candidates[index1] = candidates[index2];
    candidates[index2] = temp; 
}