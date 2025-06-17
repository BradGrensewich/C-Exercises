#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
int locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
char candidates[100][MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
int vote(int rank, char name[100], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void swap_pairs(int first, int next);
void lock_pairs(void);
int creates_cycle(int starting_node, int curr);
void print_winner(void);

int main(int argc, char *argv[])
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
        strncpy(candidates[i], argv[i + 1], 100);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[100];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

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
int vote(int rank, char name[100], int ranks[])
{
    int candidate_index;
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return 1;
        }
    }    
    return 0;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++) {
        int winner = ranks[i];
        for (int j = (i + 1); j < candidate_count; j++) {
            int loser = ranks[j];
            preferences[winner][loser]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (i == j) {
                continue;
            }
            if (preferences[i][j] > preferences[j][i]) {
                pair p;
                p.winner = i;
                p.loser = j;
                pairs[pair_count] = p;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i ++) {
        for (int curr = 0; curr < pair_count - 1; curr++) {
            int curr_strength = preferences[pairs[curr].winner][pairs[curr].loser];
            int next_strength = preferences[pairs[curr + 1].winner][pairs[curr + 1].loser];
            if (curr_strength < next_strength) {
                // printf("Before: %s is at index %d\n", candidates[pairs[curr].winner], curr);
                // printf("Before: %s is the loser\n", candidates[pairs[curr].loser]);
                swap_pairs(curr, curr + 1);
                // printf("After: %s is at index %d\n", candidates[pairs[curr].winner], curr);
                // printf("After: %s is the loser\n", candidates[pairs[curr].loser]);
            }
        }
    }    
    return;
}

void swap_pairs(int first, int next) {
    pair temp;
    temp.winner = pairs[first].winner;
    temp.loser = pairs[first].loser;
    pairs[first].winner = pairs[next].winner;
    pairs[first].loser = pairs[next].loser;
    pairs[next] = temp;


}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //each potental edge by strength
    for (int i = 0; i < pair_count; i++) {        
        pair curr = pairs[i];
        if (!creates_cycle(curr.winner, curr.loser)) {
            //lock
            locked[curr.winner][curr.loser] = 1;
        }
    }    
    
    return;
}

int creates_cycle(int starting_node, int curr) {
    if (starting_node == curr) {
        return 1;
    }
    for (int i = 0; i < candidate_count; i++) {
        if (locked[curr][i]) {
            if (creates_cycle(starting_node, i)) {
                return 1;
            }    
        }        
    }
    return 0;

}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        int has_lost = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                has_lost++;
                break;
            }
        }
        if (has_lost == 0) {
            printf("The winner is %s\n", candidates[i]);
        }
    }
    return;
}
