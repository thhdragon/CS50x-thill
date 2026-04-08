#include "helpers.h"
#include <math.h>

// RGB_CHANNEL_COUNT = count of rgb channels aka 3. just to avoid magic number
const float RGB_CHANNEL_COUNT = 3.0;
#define red image[h][w].rgbtRed
#define blue image[h][w].rgbtBlue
#define green image[h][w].rgbtGreen

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  // iterate through pixels.
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      // calc the average rgb value from each pixel
      float average = (red + blue + green) / RGB_CHANNEL_COUNT;
      // round average
      average = roundf(average);
      // set each rgb entry to the average value
      red = blue = green = average;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  //
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  //
  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  //
  return;
}
