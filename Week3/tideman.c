#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// one name on each axis, follow the column `i` and row `j`
// cell contains true or false
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
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

int main(int argc, string argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: tideman [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i] = argv[i + 1];
  }

  // Clear graph of locked in pairs
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      locked[i][j] = false;
    }
  }

  pair_count = 0;
  int voter_count = get_int("Number of voters: ");

  // Query for votes
  for (int i = 0; i < voter_count; i++) {
    // ranks[i] is voter's ith preference
    int ranks[candidate_count] = {};

    // Query for each rank
    for (int j = 0; j < candidate_count; j++) {
      string name = get_string("Rank %i: ", j + 1);

      if (!vote(j, name, ranks)) {
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
bool vote(int rank, string name, int ranks[]) {
  // iterate through as many times as there are candidates
  for (int idx = 0; idx < candidate_count; idx++) {
    // use loop count to walk through candidates list and get a handle to it
    char *current_name = candidates[idx];
    // guard to make sure the name is on the ballet
    if (strcmp(name, current_name) == 0) {
      // idx is the candidate and rank holds its rank in the list of ranks
      ranks[rank] = idx;
      return true;
    }
  }
  putchar('\n');
  return false;
}

// Update preferences given one voter's ranks
// The function is called once for each voter, takes argument ranks[]
//     - (recall that ranks[i] is the voter’s ith preference,
//     - where ranks[0] is the first preference).
// The function should update the global preferences array
//     - add the current voter’s preferences.
//          - Recall that preferences[i][j] should represent
//          - the number of voters who prefer candidate i over candidate j.
//          - You may assume that every voter will rank each of the candidates.
void record_preferences(int ranks[]) {
  // once for each voter means ranks[idx] will give 0-2
  int candidate = 0;
  for (int idx = 0; idx < candidate_count; idx++) {
    candidate = ranks[idx];
    puts(candidates[candidate]);
  }
  // TODO
  return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
  // TODO
  return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
  // TODO
  return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
  // TODO
  return;
}

// Print the winner of the election
void print_winner(void) {
  // TODO
  return;
}
