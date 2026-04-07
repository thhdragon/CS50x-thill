// ### Exercise 4A — Sort Integers Descending

// Implement selection sort (or bubble sort) to sort an integer array in **descending** order. Print
// the result.

#include <stdio.h>

void sort_descending(int arr[], int n) {
  // TODO: implement selection sort or bubble sort, descending
  for (int idx = 0; idx < n; idx++) {
    for (int jdx = idx + 1; jdx < n; jdx++) {
      if (arr[idx] < arr[jdx]) {
        int swap = arr[idx];
        arr[idx] = arr[jdx];
        arr[jdx] = swap;
      }
    }
  }
}

int main(void) {
  int scores[] = {3, 7, 1, 9, 4};
  sort_descending(scores, 5);
  for (int i = 0; i < 5; i++)
    printf("%d ", scores[i]);
  printf("\n");
  // Expected: 9 7 4 3 1
}
