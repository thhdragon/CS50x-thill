// Modifies the volume of an audio file

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
#define HEADER_SIZE 44

int main(int argc, char *argv[]) {
  // Check command-line arguments
  if (argc != 4) {
    printf("Usage: ./volume input.wav output.wav factor\n");
    return 1;
  }

  // Open files and determine scaling factor
  FILE *input = fopen(argv[1], "rb");
  if (input == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  FILE *output = fopen(argv[2], "wb");
  if (output == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  float factor = atof(argv[3]);

  // TODO: Copy header from input file to output file
  // header is 44 bytes
  uint8_t header[HEADER_SIZE];
  // read the first 44 bytes and copy them into a new buffer
  fread(header, 1, HEADER_SIZE, input);
  fwrite(header, 1, HEADER_SIZE, output);
  // TODO: Read samples from input file and write updated data to output file
  // samples are 2 bytes. 16bit integer. can multiply to change volume
  size_t count = 0;
  int16_t samples[1024];
  while ((count = fread(samples, 2, 1024, input)) > 0) {
    // loop through samples and do something do them
    for (size_t idx = 0; idx < count; idx++) {
      samples[idx] *= factor;
    }
    // read samples buffer into output file
    fwrite(samples, 2, count, output);
  }

  // Close files
  fclose(input);
  fclose(output);
}
