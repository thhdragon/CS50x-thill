#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

// count letters, words, sentences in a string
void count_string(char *string, int *letters, int *words, int *sentences) {
  // in_word is used to track whether we are currently in a word or not
  int in_word = 0;
  // loop through each character in the string
  for (char *letter = string; *letter != '\0'; letter++) {
    // if the character is a letter, increment the letter count and set in_word
    // to true
    if (isalpha(*letter)) {
      // increment the letter count and set in_word to true
      (*letters)++;
      in_word = 1;
    } else if (*letter == '.' || *letter == '!' || *letter == '?') {
      // if the character is a sentence-ending punctuation mark, increment
      // sentence count and set in_word to true
      (*sentences)++;
      in_word = 1;
    } else if (isspace(*letter)) {
      // if the character is a space, check if we are currently in a word. If we
      // are, increment the word count and set in_word to false
      if (!in_word) {
        in_word = 1;
      } else {
        in_word = 0;
        (*words)++;
      }
    }
  }
  // if we end the string while still in a word, we need to increment the word
  // count one last time
  if (in_word) {
    (*words)++;
  }
}

// calculate the Coleman-Liau index
int coleman_liau(int wc, float lc, float sc) {
  // calculate the average number of letters and sentences per 100 words
  float l_per_100 = (lc / wc) * 100;
  float s_per_100 = (sc / wc) * 100;
  // calculate the Coleman-Liau index using the formula
  float index = 0.0588 * l_per_100 - 0.296 * s_per_100 - 15.8;

  // round the index to the nearest whole number and return it
  return roundf(index);
}

// main function
int main(void) {
  // prompt the user for a string and initialize letter, word, and sentence
  // counts
  char *prompt = get_string("Text: ");
  int letters = 0;
  int words = 0;
  int sentences = 0;

  // count the letters, words, and sentences in the prompt
  count_string(prompt, &letters, &words, &sentences);

  // calculate the Coleman-Liau index and print the appropriate grade level
  int index = coleman_liau(words, letters, sentences);

  // print the appropriate grade level based on the index
  if (index < 1) {
    puts("Before Grade 1.");
  } else if (index > 16) {
    puts("Grade 16+.");
  } else {
    printf("Grade %d\n", index);
  }
}