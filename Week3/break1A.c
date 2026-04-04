// Concept 1 — Searching an Array of Strings
// The skill: vote() must find a candidate's name in an array and store their
// index.

// Exercise 1A — Find a Name
// Write a function find_candidate that takes a name (string),
// an array of candidate names, and the count of candidates.
// Return the index of the matching name, or -1 if not found.
// Use strcmp for comparison.

#include <stdio.h>
#include <string.h>

int find_candidate(char *name, char *candidates[], int count) {
  // TODO: loop through candidates, return index on match, -1 if none
  // loop through as many times as there are candidates
  for (int idx = 0; idx < count; idx++) {
    // compare name to candidates[idx]
    if (strcmp(name, candidates[idx]) == 0) {
      return idx;
    }
  }
  return -1;
}


int main(void) {
  char *candidates[] = {"Alice", "Bob", "Charlie"};
  printf("%d\n", find_candidate("Bob", candidates, 3));     // expect 1
  printf("%d\n", find_candidate("Charlie", candidates, 3)); // expect 2
  printf("%d\n", find_candidate("Dave", candidates, 3));    // expect -1
}
