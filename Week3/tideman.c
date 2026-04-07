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
// if theres 3 candidates. i need the vote at index 0 which actually represents
// an index at what i think is called an adjacent array with the candidate
// names in it. and then i need to compare the vote at index 0 to the vote at
// index 1 and again 0 to index 2. then i need to get index 1 and check against
// index 2 basically like peeking
void record_preferences(int ranks[]) {
  // once for each voter means ranks[idx] will give 0-2
  for (int idx = 0; idx < candidate_count; idx++) {
    for (int jdx = idx + 1; jdx < candidate_count; jdx++) {
      int winner = ranks[idx];
      int loser = ranks[jdx];
      preferences[winner][loser]++;
    }
  }
  return;
}

// Record pairs of candidates where one is preferred over the other
//      A B C
//      _ _ _
// A || 0 2 2
// B || 1 0 2
// C || 1 1 0
// remember the number is an index for a candidate pointer
// the numbers in the table ARE CANDIDATES.
void add_pairs(void) {
  for (int row = 0; row < candidate_count; row++) {
    for (int col = row + 1; col < candidate_count; col++) {
      int a = preferences[row][col];
      int b = preferences[col][row];

      // dont over-complicate this.
      // a tie is simply [idx][jdx] vs [jdx][idx]
      if (a == b) {
        continue;
      } else if (a > b) {
        // use dot operator to access struct fields post init
        pairs[pair_count].winner = a;
        pairs[pair_count].loser = b;
      } else if (b > a) {
        pairs[pair_count].winner = b;
        pairs[pair_count].loser = a;
      }
      // increment pair count
      pair_count++;
    }
  }
  return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
  // TODO
  for (int idx = 0; idx < pair_count; idx++) {
    for (int jdx = idx + 1; jdx < pair_count; jdx++) {
      int current = 
    }
  }
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
