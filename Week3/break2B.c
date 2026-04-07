// Exercise 2B — Print a 2-D Array as a Table

// Practice reading a 2-D array by writing a function that pretty-prints
// `preferences` with row/column labels.
// Use the preferences values from Exercise 2A as test data.

#include <stdio.h>

#define N 3

void print_table(int prefs[N][N], char *candidates[], int n) {
  // print a header row of candidate names,
  for (int row = 0; row < n; row++) {
    printf("\t%s", candidates[row]);
  }
  putchar('\n');
  // then for each row print the candidate name followed by their preference
  // counts against each other.

  for (int row = 0; row < n; row++) {
    printf("%s\t", candidates[row]);
    for (int col = 0; col < n; col++) {
      printf("%d\t", prefs[row][col]);
    }
    putchar('\n');
  }
  putchar('\n');

  // Diagonal entries (prefs[i][i]) are always 0 and can be printed as-is.
}

int main(void) {
  char *candidates[] = {"Alice", "Bob", "Charlie"};
  // Sample data: 5 voters, all preferences tallied
  int prefs[N][N] = {
      {0, 3, 1}, // Alice over Bob: 3,  Alice over Charlie: 1
      {2, 0, 5}, // Bob over Alice: 2,  Bob over Charlie: 5
      {4, 0, 0}, // Charlie over Alice: 4, Charlie over Bob: 0
  };
  print_table(prefs, candidates, N);
}

// Expected output (spacing need not be exact):
//           Alice  Bob  Charlie
// Alice       0     3      1
// Bob         2     0      5
// Charlie     4     0      0
