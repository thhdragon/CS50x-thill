#include <stdio.h>
#include <string.h>

// Reuse find_candidate from 1A here.
int find_candidate(char *name, char *candidates[], int count) {
  // loop through candidates, return index on match, -1 if none
  // loop through as many times as there are candidates
  for (int idx = 0; idx < count; idx++) {
    // compare name to candidates[idx]
    if (strcmp(name, candidates[idx]) == 0) {
      return idx;
    }
  }
  return -1;
}

// Fill ranks[] from an array of name strings.
// Returns 1 on success, 0 if any name is invalid.
int populate_ranks(char *choices[], int ranks[], char *candidates[], int n) {
  for (int i = 0; i < n; i++) {
    // use find_candidate to look up choices[i]
    int found = find_candidate(choices[i], candidates, n);
    if (found == -1) {
      return 0;
    }
    ranks[i] = found;
    // If not found, print "Invalid\n" and return 0
    // Otherwise store the index in ranks[i]
  }
  return 1;
}

int main(void) {
  char *candidates[] = {"Alice", "Bob", "Charlie"};
  int ranks[3];

  // Voter ranks: Charlie first, then Alice, then Bob
  char *choices[] = {"Charlie", "Alice", "Bob"};

  if (populate_ranks(choices, ranks, candidates, 3)) {
    for (int i = 0; i < 3; i++)
      printf("ranks[%d] = %d\n", i, ranks[i]);
    // Expected:
    // ranks[0] = 2
    // ranks[1] = 0
    // ranks[2] = 1
  }

  // Test invalid name
  char *bad_choices[] = {"Charlie", "Dave", "Bob"};
  populate_ranks(bad_choices, ranks, candidates, 3); // expect "Invalid"
}
