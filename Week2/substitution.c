#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Hardcode KEY for now
char *KEY = "NQXPOMAFTRHLZGECYJIUWSKDVB";
// Also hardcode Plaintext
char *TEXT_PLAIN = "Hello";

char encrypt_char(char letter) {
  if (isupper(letter)) {
    //   a. If the character is uppercase:
    //      - Determine its alphabetical index (0-25)
    // subtract 'A'
    int alpha_idx = letter - 'A';
    //      - Substitute it with the corresponding character from the key,
    //      preserving uppercase
    char sub = KEY[alpha_idx];
    return toupper(sub);
  } else if (islower(letter)) {
    //   b. If the character is lowercase:
    //      - Determine its alphabetical index (0-25)
    //      - Substitute it with the corresponding character from the key,
    //      preserving lowercase
    // subtract 'a'
    int alpha_idx = letter - 'a';

    char sub = KEY[alpha_idx];
    return tolower(sub);
  } else {
    //   c. If the character is non-alphabetic:
    //      - Output it unchanged
    return letter;
  }
}

bool isalpha_string(char *key) {
  if (*key == '0') {
    return false;
  }
  while (*key != '0') {
    if (!isalpha(*key)) {
      return false;
    }
    key++;
  }
  return true;
}

bool validate_key(char *key) {
  // Validate the Substitution Key

  // Check if the key contains each letter exactly once (no duplicates)
  // Check if the key has exactly 26 characters
  if (strlen(key) != 26) {
    return false;
  }
  // Check if every character in the key is alphabetic

  return true;
}

int main(int argc, string argv[]) {
  // Validate Command - Line Arguments
  // Check if the program was executed with exactly one argument
  // else print an error message and return 1
  if (argc != 2) {
    puts("Usage: ./substitution key");
    return 1;
  }

  char *key = argv[1];
  if (!validate_key(key)) {
    // If any validation fails, print an error message and return 1
    puts("Key must contain 26 characters.");
    return 1;
  }
  // 5. Encrypt and Output Ciphertext
  // Iterate through each character of the plaintext:
  printf("ciphertext: ");
  for (char *idx = TEXT_PLAIN; *idx != '\0'; idx++) {
    char letter = encrypt_char(*idx);
    putchar(letter);
  }
  // 6. Finalize Output
  // Print a newline character
  putchar('\n');
}