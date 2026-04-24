#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

bool is_jpeg(uint8_t block[]) {
  if (block[0] != 0xff) {
    return false;
  }
  if (block[1] != 0xd8) {
    return false;
  }
  if (block[2] != 0xff) {
    return false;
  }
  if ((block[3] & 0xf0) != 0xe0) {
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  // Accept a single command-line argument
  if (argc != 2) {
    return 1;
  }
  // Open the memory card with read bytes
  FILE *file_in = fopen(argv[1], "rb");

  // While there's still data left to read from the memory card
  int bytes_read = 0;
  uint8_t block[BLOCK_SIZE] = {0};
  int count_jpeg = 0;
  char jpeg_name[100] = {0};

  bool in_file = false;
  FILE *file_out = NULL;
  // read one block into the block array as long as bytes read doesnt come back as 0 aka eof
  while ((fread(block, BLOCK_SIZE, 1, file_in)) > 0) {
    // if we hit a valid jpeg header create a new file
    if (is_jpeg(block)) {
      // need a special case for the first time

      // if we find a header and we are already in a file
      // we need behavior to close the last file and create a new one
      if (in_file) {
        // set in file to false
        in_file = false;
        fclose(file_out);
        // add one to the counter
        count_jpeg++;
      }
      // format filename string into buffer
      snprintf(jpeg_name, sizeof(jpeg_name), "%03i.jpg", count_jpeg);

      // create a new jpeg file and get a pointer to it
      file_out = fopen(jpeg_name, "wb");
      in_file = true;
    }
    if (in_file) {
      fwrite(block, BLOCK_SIZE, 1, file_out);
    }
  }
  fclose(file_out);
  fclose(file_in);
}