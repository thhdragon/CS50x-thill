// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1599;

// Hash table
node *table[N];

// word count
int word_count = 0;

// return true if a word is located in the dictionary, otherwise false.
bool check(const char *word) {
  // Hash the word to obtain its hash value
  int bucket = hash(word);
  node *cursor = table[bucket];

  // compare word at table[bucket]->word and if not then move to next pointer
  // do this in a loop
  while (cursor != NULL) {
    if (strcasecmp(cursor->word, word) == 0) {
      return true;
    } else {
      // move cursor to next pointer
      // cursor become null if its the last pointer
      cursor = cursor->next;
    }
  }

  // Return false if no word is found
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  // TODO: Improve this hash function
  int hash_value = 0;
  int prev = 0;
  // walk through the word by char
  for (int idx = 0; word[idx] != '\0'; idx++) {

    // get the char as upper and get alphabet index
    int cursor = toupper(word[idx]) - 'A' + 1;

    // add cursor to hash value
    hash_value += cursor;

    // get the delta from the prev char
    int delta = cursor - prev;

    // do something with cursor and delta
    int context = cursor * delta;

    // add to hash value
    hash_value += context;

    // set prev to cursor
    prev = cursor;
  }
  hash_value %= N;
  return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  // Open the dictionary file
  FILE *source = fopen(dictionary, "r");
  if (source == NULL) {
    return false;
  }
  char buf[LENGTH];

  // Read each word in the file
  while (fscanf(source, "%s", buf) != EOF) {
    // Create space for a new hash table node
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
      return false;
    }

    // Copy the word into the new node
    strncpy(new_node->word, buf, LENGTH);

    // set ptr_node next to NULL
    new_node->next = NULL;

    // Hash the word to obtain its hash value
    int bucket = hash(buf);

    // Add each word to the hash table
    // Insert the new node into the hash table (using the index specified by its hash value)
    // set new_node next to table[bucket]
    new_node->next = table[bucket];
    table[bucket] = new_node;

    word_count++;
  }
  // Close the dictionary file
  fclose(source);

  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) { return word_count; }

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  // outer loop as many times as buckets
  for (int bucket = 0; bucket < N; bucket++) {
    node *cursor = table[bucket];
    // check if the bucket is null
    // if not null then
    while (cursor != NULL) {
      // create a pointer to point to the memory that cursor is pointing to?
      node *new_node = cursor;
      // point cursor to the next node
      cursor = cursor->next;
      // free the memory at the old pointer
      free(new_node);
    }
  }

  return true;
}
