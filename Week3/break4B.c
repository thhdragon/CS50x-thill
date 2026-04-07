// Exercise 4B — Sort Structs by a Field

// Now sort an array of `pair` structs by the `margin` field in descending order.
// When swapping, swap the **entire struct** (not just the margin),
// so `winner` and `loser` stay matched to their margin.

#include <stdio.h>

typedef struct {
  int winner;
  int loser;
  int margin; // = preferences[winner][loser]
} pair;

void sort_pairs(pair pairs[], int n) {
  // TODO: adapt your sort from 4A — compare pairs[i].margin and pairs[j].margin,
  // swap whole pair structs (use a temporary pair variable)
}

int main(void) {
  pair pairs[] = {{0, 1, 3}, {2, 0, 4}, {1, 2, 5}};
  sort_pairs(pairs, 3);
  for (int i = 0; i < 3; i++)
    printf("winner=%d loser=%d margin=%d\n", pairs[i].winner, pairs[i].loser, pairs[i].margin);
  // Expected:
  //   winner=1 loser=2 margin=5
  //   winner=2 loser=0 margin=4
  //   winner=0 loser=1 margin=3
}