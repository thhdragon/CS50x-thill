// Exercise 5B — Add an Edge and Check
// `locked[i][j] == true` means there is a directed edge from candidate `i` to candidate `j` (i
// beats j and the edge is confirmed).

// Write `add_edge` and `is_source` to manipulate and query the graph programmatically.

#include <stdbool.h>
#include <stdio.h>

#define N 3
bool locked[N][N]; // all false initially

void add_edge(int from, int to) {
  // TODO: set locked[from][to] = true
  locked[from][to] = true;
}

// Returns true if no other candidate j has locked[j][candidate] == true
bool is_source(int candidate, int n) {
  for (int j = 0; j < n; j++) {
    // if locked[j][candidate] is true, return false
    if (locked[j][candidate]) {
      return false;
    }
  }
  return true;
}

int main(void) {
  add_edge(0, 1); // Alice → Bob
  add_edge(0, 2); // Alice → Charlie
  add_edge(2, 1); // Charlie → Bob

  for (int i = 0; i < N; i++)
    printf("Candidate %d is source: %s\n", i, is_source(i, N) ? "yes" : "no");
  // Expected:
  //   Candidate 0 (Alice)   is source: yes
  //   Candidate 1 (Bob)     is source: no
  //   Candidate 2 (Charlie) is source: no
}