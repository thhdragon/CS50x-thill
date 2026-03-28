#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// In the game of Scrabble, players create words to score points, and the number
// of points is the sum of the point values of each letter in the word.

// Point values for each letter:
// A=1  B=3  C=3  D=2  E=1  F=4  G=2  H=4  I=1  J=8  K=5  L=1
// M=3  N=1  O=1  P=3  Q=10 R=1  S=1  T=1  U=1  V=4  W=4  X=8
// Y=4  Z=10

// Example: "CODE" scores 3+1+2+1=7 points (C=3, O=1, D=2, E=1)

// TODO: Implement a Scrabble game where:
//   1. Prompt "Player 1" to input a word
//   2. Prompt "Player 2" to input a word
//   3. Calculate score for each player by summing letter values
//   4. Print the winner: "Player 1 wins!", "Player 2 wins!", or "Tie!"

// ---------------FIXES---------------
// ☹️ handles punctuation correctly
//   expected: "Tie!"
//   actual:   "Player 2 w..."

const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int char_to_index(char letter) {
  // take char as upper and minus 'A' to get alphabet index
  int idx = toupper(letter) - 'A';
  return idx;
}

int calculate_score(char *word) {
  int total = 0;
  // get length of word
  int length = strlen(word);

  // do this in a loop as many times as length of word
  for (int i = 0; i < length; i++) {
    // get letter from word
    char letter = word[i];

    // if letter is not A-Z then continue
    if (!isalpha(letter)) {
      continue;
    }
    // get alphabet index for letter
    int idx = char_to_index(letter);
    // use alphabet index to get points for letter
    int points = POINTS[idx];
    // add score to total score
    total += points;
  }
  return total;
}

int main(void) {

  // Prompt the user for two words
  string player1_word = get_string("Player 1: ");
  string player2_word = get_string("Player 2: ");

  // Compute the score of each word
  int player1_score = calculate_score(player1_word);
  int player2_score = calculate_score(player2_word);

  // Print the winner
  if (player1_score > player2_score) {
    // send player 1 to display_winner
    puts("Player 1 wins!");
  } else if (player1_score < player2_score) {
    // send player 2 to display_winner
    puts("Player 2 wins!");
  } else if (player1_score == player2_score) {
    puts("Tie!");
  }
}