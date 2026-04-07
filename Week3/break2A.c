// Exercise 2A — Build a Preference Table

// Given a `ranks[]` array for one voter, update `preferences[i][j]` (count of
// voters who prefer candidate `i` over candidate `j`).

// Rule: if candidate A appears **before** candidate B in `ranks[]`, then
// `preferences[A][B]++`.

// Note: `ranks[i]` is a candidate *index*, not a position. To say "A is ranked
// before B", you need to find A's position and B's position in the `ranks[]`
// array, or equivalently loop over all rank positions `i < j` and increment
// `preferences[ranks[i]][ranks[j]]`.

#include <stdio.h>

#define N 3
int preferences[N][N]; // global, zero-initialized

void record_preferences(int ranks[], int n) {
  // use two nested loops over rank positions i and j (where i < j).
  // For each such pair, ranks[i] is preferred over ranks[j], so:
  for (int row = 0; row < n; row++) {
    for (int col = row + 1; col < n; col++) {
      //     preferences[ranks[i]][ranks[j]]++
      int winner = ranks[row];
      int loser = ranks[col];
      preferences[winner][loser]++;
    }
  }
}

int main(void) {
  // One voter: ranks = {2, 0, 1}  means 1st choice=Charlie, 2nd=Alice, 3rd=Bob
  int ranks[] = {2, 0, 1};
  record_preferences(ranks, 3);

  // Expected increments:
  //   i=0,j=1 → preferences[2][0]++  (Charlie preferred over Alice)
  //   i=0,j=2 → preferences[2][1]++  (Charlie preferred over Bob)
  //   i=1,j=2 → preferences[0][1]++  (Alice preferred over Bob)
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      printf("preferences[%d][%d] = %d\n", i, j, preferences[i][j]);
  // All other entries should remain 0.
}