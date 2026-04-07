// Exercise 3B — Collect Pairs from preferences[][]

// Write `add_pairs` using a nested loop over all `(i, j)` combinations where `i < j`.
// For each pair, compare `preferences[i][j]` with `preferences[j][i]` to decide who won,
// then add the appropriate struct.Ties(equal counts) are skipped — add no pair.

#include <stdio.h>

#define N 3

typedef struct {
  int winner;
  int loser;
  int margin;
} pair;

int preferences[N][N] = {
    {0, 3, 1},
    {2, 0, 5},
    {4, 0, 0},
};

pair pairs[N * N];
int pair_count = 0;

void add_pairs(int n) {
  for (int row = 0; row < N; row++) {
    for (int col = row + 1; col < N; col++) {
      // how to get winner index from
      int winner, loser, margin;
      int a = preferences[row][col];
      int b = preferences[col][row];
      if (a == b) {
        continue;
      } else if (a > b) {
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
      pairs[pair_count].margin = preferences[winner][loser];

      pair_count++;
    }
  }
}

int main(void) {
  add_pairs(N);
  for (int i = 0; i < pair_count; i++)
    printf("winner=%d loser=%d margin=%d\n", pairs[i].winner, pairs[i].loser, pairs[i].margin);
  // Expected (order may vary):
  //   winner=0 loser=1 margin=3
  //   winner=2 loser=0 margin=4
  //   winner=1 loser=2 margin=5
}