// Exercise 3A — Define and Use a Struct

// The `margin` field stores `preferences[winner][loser]`
// this is the raw vote count for the winner against the loser
// (NOT THE DIFFERENCE BETWEEN THE TWO DIRECTIONS).
// This is the value used later when sorting by strength of victory.

#include <stdio.h>

typedef struct {
  int winner;
  int loser;
  int margin; // = preferences[winner][loser]
} pair;

#define N 3

int main(void) {
  char *candidates[] = {"Alice", "Bob", "Charlie"};
  // Given these final preference counts (3 candidates, 5 voters):
  // preferences[0][1] = 3, preferences[1][0] = 2  → Alice beats Bob   (margin 3)
  // preferences[2][0] = 4, preferences[0][2] = 1  → Charlie beats Alice (margin 4)
  // preferences[1][2] = 5, preferences[2][1] = 0  → Bob beats Charlie  (margin 5)
  int prefs[N][N] = {
      {0, 3, 1}, //
      {2, 0, 5}, //
      {4, 0, 0}, //
  };

  // declare pair pairs[3] and int pair_count = 0.
  pair pairs[N];
  int pair_count = 0;
  // For each matchup above, add a pair struct with the correct winner,
  // loser, and margin, then increment pair_count.

  for (int row = 0; row < N; row++) {
    for (int col = row + 1; col < N; col++) {
      // how to get winner index from
      int winner, loser, margin;
      int a = prefs[row][col];
      int b = prefs[col][row];
      if (a > b) {
        winner = row; // todo
        loser = col;  // todo
        margin = a;
      } else {
        winner = col; // todo
        loser = row;  // todo
        margin = b;
      }
      pairs[pair_count].winner = winner;
      pairs[pair_count].loser = loser;
      pairs[pair_count].margin = prefs[winner][loser];

      pair_count++;
    }
  }

  for (int i = 0; i < pair_count; i++)
    printf("idx %d beats idx %d with margin %d\n", pairs[i].winner, pairs[i].loser,
           pairs[i].margin);
  // Print each pair as: "Candidate X (idx W) beats Candidate Y (idx L) with
  // margin M"

  // Expected output:
  //   idx 0 beats idx 1 with margin 3
  //   idx 2 beats idx 0 with margin 4
  //   idx 1 beats idx 2 with margin 5
}
