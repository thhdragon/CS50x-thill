#include <stdio.h>
#include <string.h>

// Exercise 1B — Populate a Ranks Array
// A voter ranks candidates by name. Given those names in order,
// fill a ranks[] array where ranks[i] = the candidate index of their i-th
// choice.
// Print "Invalid" and stop if a name is not found.
// Input:  candidates = {"Alice","Bob","Charlie"},
// voter enters "Charlie","Alice","Bob"
// Output: ranks = {2, 0, 1}

int find_candidate(char *name, char *candidates[], int count) {
  // loop through candidates, return index on match, -1 if none
  // loop through as many times as there are candidates
  for (int idx = 0; idx < count; idx++) {
    // compare name to candidates[idx]
    if (strcmp(name, candidates[idx]) == 0) {
      // return current position in index for the match
      return idx;
    }
  }
  return -1;
}

int main(void) {
  char *candidates[] = {"Alice", "Bob", "Charlie"};
  int candidate_count = 3;
  int ranks[3];

  // Simulate a voter entering their choices in order:
  char *voter_input[] = {"Charlie", "Alice", "Bob"};

  for (int i = 0; i < candidate_count; i++) {
    int index = find_candidate(voter_input[i], candidates, candidate_count);

    if (index == -1) {
      printf("Invalid vote.\n");
      return 1;
    }

    // store the result so that ranks[i] holds the candidate
    // index of the voter's i-th choice
    ranks[i] = index;
  }

  // Expected output:
  // ranks[0] = 2  (Charlie is 1st choice, index 2)
  // ranks[1] = 0  (Alice is 2nd choice,   index 0)
  // ranks[2] = 1  (Bob is 3rd choice,      index 1)
  for (int i = 0; i < candidate_count; i++)
    printf("ranks[%d] = %d\n", i, ranks[i]);
}