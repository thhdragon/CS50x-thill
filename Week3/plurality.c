#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct {
  // name of candidate
  string name;
  // number of votes for candidate
  int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

// main function
int main(int argc, string argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: plurality [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates from amount of arguments passed
  // subtract program name
  candidate_count = argc - 1;
  // check if number of candidates is greater than max
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  // populate array of candidates
  for (int i = 0; i < candidate_count; i++) {
    // set name of candidate using command line arguments
    candidates[i].name = argv[i + 1];
    // set votes of candidate to 0
    candidates[i].votes = 0;
  }

  // get number of voters
  int voter_count = get_int("Number of voters: ");

  // Loop over all voters
  for (int i = 0; i < voter_count; i++) {
    // get vote from voter
    string name = get_string("Vote: ");

    // Check for invalid vote
    if (!vote(name)) {
      printf("Invalid vote.\n");
    }
  }

  // Display winner of election
  print_winner();
}

// Update vote totals given a new vote
bool vote(string name) {
  // iterate over each candidate
  for (int idx = 0; idx < candidate_count; idx++) {
    // get candidate name
    char *idx_name = candidates[idx].name;
    // compare candidate name to input name
    if (strcmp(name, idx_name) == 0) {
      // increment candidate votes
      candidates[idx].votes++;
      // return true
      return true;
    }
  }
  return false;
}

// Print the winner (or winners) of the election
void print_winner(void) {
  // set highest and current to 0
  int highest = 0;
  int current = 0;
  // iterate over each candidate
  for (int idx = 0; idx < candidate_count; idx++) {
    current = candidates[idx].votes;
    // if current is greater than highest, set highest to current
    if (current > highest) {
      highest = current;
    }
  }
  // iterate over each candidate
  for (int idx = 0; idx < candidate_count; idx++) {
    current = candidates[idx].votes;
    // if current is equal to highest, print candidate name
    if (current == highest) {
      puts(candidates[idx].name);
    }
  }
}