// Exercise 5C — Translate Pairs into Graph Edges
// Each pair struct already tells you exactly which two candidates are involved and who won:
// pairs[i].winner is the from node and pairs[i].loser is the to node.
// This exercise makes that connection explicit before you add the cycle-detection logic.
//
// Write a function lock_all that iterates over a sorted pairs[] array and calls add_edge
// for every pair — no cycle checking yet, just the translation.

#include <stdbool.h>
#include <stdio.h>

#define N 3

typedef struct {
  int winner;
  int loser;
  int margin;
} pair;

bool locked[N][N];

void add_edge(int from, int to) { locked[from][to] = true; }

// Lock every pair unconditionally (no cycle check — that comes in Concept 6).
void lock_all(pair pairs[], int pair_count) {
  for (int i = 0; i < pair_count; i++) {
    // TODO: call add_edge using the right fields from pairs[i].
    // Which field is the "from" node? Which is the "to" node?
    add_edge(pairs[i].winner, pairs[i].loser);
  }
}

int main(void) {
  // Sorted pairs (descending margin) from the earlier exercises:
  //   Bob beats Charlie  (margin 5)  → edge 1 → 2
  //   Charlie beats Alice (margin 4) → edge 2 → 0
  //   Alice beats Bob    (margin 3)  → edge 0 → 1
  pair pairs[] = {{1, 2, 5}, {2, 0, 4}, {0, 1, 3}};

  lock_all(pairs, 3);

  // Print every locked edge so you can verify the matrix matches the pairs.
  printf("Locked edges:\n");
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (locked[i][j])
        printf("  %d → %d\n", i, j);
  // Expected:
  //   1 → 2  (Bob → Charlie)
  //   2 → 0  (Charlie → Alice)
  //   0 → 1  (Alice → Bob)
  //
  // Notice: all three edges are locked because we skipped cycle checking.
  // This produces a cycle (0→1→2→0), which is exactly the problem
  // lock_pairs() must prevent. Concept 6 adds the guard.
}

// Checkpoint questions before moving on:

// After lock_all runs, which candidate is the source (no incoming edges)? Run is_source from 5B to
// check — you should find there is no source, because the cycle means everyone has an incoming
// edge.
//
// What single change to lock_all would fix this?