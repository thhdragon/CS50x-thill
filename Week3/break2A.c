// Concept 2 — 2-D Arrays and Nested Loops
// The skill: record_preferences() and add_pairs() both read/write
// preferences[i][j].
//
// Exercise 2A — Build a Preference Table
// Given a ranks[] array for one voter, update preferences[i][j] (count of
// voters who prefer i over j).
// Rule: if candidate A appears before candidate B in ranks, then
// preferences[A][B]++.

// Exercise 2B — Print a 2-D Array as a Table
// Practice reading a 2-D array by writing a function that
// pretty-prints preferences with row/column labels.
//        Alice  Bob  Charlie
// Alice    0     3      2
// Bob      1     0      4
// Charlie  3     1      0

#include <stdio.h>

#define N 3
int preferences[N][N]; // global, zero-initialized

void pretty_print() {
  
}

void record_preferences(int ranks[], int n) {
  // TODO: for every pair (i, j) where ranks puts i before j,
  //       increment preferences[ranks[i]][ranks[j]]
  for (int idx = 0; idx < n; idx++) {
    for (int jdx = idx + 1; jdx < n; jdx++) {
      int winner = ranks[idx];
      int loser = ranks[jdx];
      preferences[winner][loser]++;
    }
  }
}

int main(void) {
  // One voter: ranks = {2, 0, 1}  (Charlie > Alice > Bob)
  int ranks[] = {2, 0, 1};
  record_preferences(ranks, 3);

  // Expected preferences:
  // [2][0]++ → Charlie preferred over Alice
  // [2][1]++ → Charlie preferred over Bob
  // [0][1]++ → Alice preferred over Bob
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      printf("preferences[%d][%d] = %d\n", i, j, preferences[i][j]);
}
