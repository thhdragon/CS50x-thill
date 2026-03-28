#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Program to compute the Coleman-Liau readability index for a given text.
//
// This program prompts the user for a block of text, counts the letters,
// words, and sentences, and then calculates the Coleman-Liau index to estimate
// the U.S. grade level required to understand the text.
//
// Coleman-Liau index:
//     index = 0.0588 * L - 0.296 * S - 15.8
// where:
//     L = average number of letters per 100 words
//     S = average number of sentences per 100 words
//
// Output rules:
//   - Round the computed index to the nearest integer.
//   - If the index is 16 or higher, print "Grade 16+."
//   - If the index is less than 1, print "Before Grade 1."
//   - Otherwise, print "Grade X" where X is the rounded index.

void count_string(char *string, int *letters, int *words, int *sentences) {
  int in_word = 0;
  for (char *letter = string; *letter != '\0'; letter++) {
    // Count letters, words, and sentences:
    // letters: alphabetic characters (A-Z and a-z)
    if (isalpha(*letter)) {
      (*letters)++;
      in_word = 1;
    } else if (*letter == '.' || *letter == '!' || *letter == '?') {
      // - sentences: occurrences of '.', '!', or '?'
      (*sentences)++;
      in_word = 1;
    } else if (isspace(*letter)) {
      // words: char(s) separated by spaces
      if (!in_word) {
        in_word = 1;
      } else {
        in_word = 0;
        (*words)++;
      }
    }
  }

  if (in_word) {
    (*words)++;
  }
}

int main(void) {
  // Prompt the user for input text.
  // hardcode grade 1 for now
  char *grade1 = "One fish. Two fish. Red fish. Blue fish.";
  int letters = 0;
  int words = 0;
  int sentences = 0;

  count_string(grade1, &letters, &words, &sentences);

  // DEBUGGING
  printf("%d\n", letters);
  printf("%d\n", sentences);
  printf("%d\n", words);

  // Compute the Coleman-Liau index using L and S per 100 words,
  // then round the result to the nearest integer.

  // Print the grade level according to the rules above.
}