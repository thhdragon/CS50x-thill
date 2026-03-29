#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// encrypt a single character
char encrypt_char(char letter, char *key) {
  // check if the letter is uppercase
  if (isupper(letter)) {
    // subtract 'A'
    // get the index of the letter
    int alpha_idx = letter - 'A';
    // get the substitute character
    char sub = key[alpha_idx];
    // return the substitute character
    return toupper(sub);
  } else if (islower(letter)) {
    // subtract 'a'
    // get the index of the letter
    int alpha_idx = letter - 'a';
    // get the substitute character
    char sub = key[alpha_idx];
    // return the substitute character
    return tolower(sub);
  } else {
    // return the character unchanged
    return letter;
  }
}

// check if the key is alphabetic
bool isalpha_string(char *key) {
  // check if the key is empty
  if (*key == '\0') {
    return false;
  }

  // loop through the key
  while (*key != '\0') {
    // check if the character is alphabetic
    if (!isalpha(*key)) {
      return false;
    }
    // move to the next character
    key++;
  }
  // if it passes all checks
  return true;
}

// validate the key
bool validate_key(char *key) {
  // check if the key has 26 characters
  if (strlen(key) != 26) {
    return false;
  }
  // Check if every character in the key is alphabetic
  if (!isalpha_string(key)) {
    return false;
  }
  // if it passes all checks
  return true;
}

// main function
int main(int argc, string argv[]) {
  // check if the program was executed with exactly one command-line argument
  if (argc != 2) {
    puts("Usage: ./substitution key");
    return 1;
  }
  // get the plaintext from the user
  char *plain = get_string("Plaintext: ");
  // get the key from the command-line argument
  char *key = argv[1];
  // validate the key
  if (!validate_key(key)) {
    // If any validation fails, print an error message and return 1
    puts("Key must contain 26 characters.");
    return 1;
  }
  // print the ciphertext
  printf("ciphertext: ");
  // loop through the plaintext
  for (char *idx = plain; *idx != '\0'; idx++) {
    // encrypt the character
    char letter = encrypt_char(*idx, key);
    // print the encrypted character
    putchar(letter);
  }
  // print a newline
  putchar('\n');
}