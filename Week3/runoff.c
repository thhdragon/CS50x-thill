#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct {
  string name;
  int votes;
  bool eliminated;
} candidate;

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

int main(int argc, string argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: runoff [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX_CANDIDATES) {
    printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
    candidates[i].eliminated = false;
  }

  voter_count = get_int("Number of voters: ");
  if (voter_count > MAX_VOTERS) {
    printf("Maximum number of voters is %i\n", MAX_VOTERS);
    return 3;
  }

  // Keep querying for votes
  for (int i = 0; i < voter_count; i++) {

    // Query for each rank
    for (int j = 0; j < candidate_count; j++) {
      string name = get_string("Rank %i: ", j + 1);

      // Record vote, unless it's invalid
      if (!vote(i, j, name)) {
        printf("Invalid vote.\n");
        return 4;
      }
    }

    printf("\n");
  }

  // Keep holding runoffs until winner exists
  while (true) {
    // Calculate votes given remaining candidates
    tabulate();

    // Check if election has been won
    bool won = print_winner();
    if (won) {
      break;
    }

    // Eliminate last-place candidates
    int min = find_min();
    bool tie = is_tie(min);

    // If tie, everyone wins
    if (tie) {
      for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated) {
          printf("%s\n", candidates[i].name);
        }
      }
      break;
    }

    // Eliminate anyone with minimum number of votes
    eliminate(min);

    // Reset vote counts back to zero
    for (int i = 0; i < candidate_count; i++) {
      candidates[i].votes = 0;
    }
  }
  return 0;
}

// Record preference if vote is valid
//  The array preferences[i] will represent all of the preferences for voter number i. The integer,
//  preferences[i][j], will store the index of the candidate, from the candidates array, who is the
//  jth preference for voter i.
bool vote(int voter, int rank, string name) {
  // iterate through as many times as there are candidates
  for (int idx = 0; idx < candidate_count; idx++) {
    // find the idx that matches the name given
    if (strcmp(name, candidates[idx].name) == 0) {
      // store the candidate idx
      preferences[voter][rank] = idx;
      return true;
    }
  }
  return false;
}

// Tabulate votes for non-eliminated candidates
// The function should update the number of votes each candidate has at this stage in the runoff.
//
// Recall that at each stage in the runoff, every voter effectively votes for their top-preferred
// candidate who has not already been eliminated.
void tabulate(void) {
  // first step is get votes and candidates
  for (int voter = 0; voter < voter_count; voter++) {
    for (int choice = 0; choice < candidate_count; choice++) {
      int candidate_idx = preferences[voter][choice];
      if (!candidates[candidate_idx].eliminated) {
        candidates[candidate_idx].votes++;
        break;
      }
    }
  }
  return;
}

// Print the winner of the election, if there is one
// If any candidate has more than half of the vote, their name should be printed and the function
// should return true.
// If nobody has won the election yet, the function should return false.

// Recall that voter_count stores the number of voters in the election. Given that, how would you
// express the number of votes needed to win the election?
bool print_winner(void) {
  for (int choice = 0; choice < candidate_count; choice++) {
    int votes = candidates[choice].votes;
    int half = (voter_count / 2);
    if (votes > half) {
      char *winner = candidates[choice].name;
      puts(winner);
      return true;
    }
  }
  return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void) {
  // TODO
  int candidate_idx = 0;
  // give this an initial value of the max amount of votes
  int min_votes = voter_count;
  printf("%d\n", min_votes);

  for (int voter = 0; voter < voter_count; voter++) {
    for (int choice = 0; choice < candidate_count; choice++) {
      candidate_idx = preferences[voter][choice];
      bool eliminated = candidates[candidate_idx].eliminated;
      if (eliminated) {
        continue;
      }
      int votes = candidates[candidate_idx].votes;
      if (votes < min_votes) {
        min_votes = votes;
      }
    }
  }

  printf("%d\n", min_votes);
  return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
//
// The function takes an argument min, which will be the minimum number of votes that anyone in the
// election currently has.
//
// The function should return true if every candidate remaining in the election has the same number
// of votes, and should return false otherwise.
bool is_tie(int min) {
  // TODO
  return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min) {
  // TODO
  return;
}
