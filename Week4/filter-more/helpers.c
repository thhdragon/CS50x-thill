#include "helpers.h"
#include <math.h>
#include <stdio.h>

// RGB_CHANNEL_COUNT = count of rgb channels aka 3. just to avoid magic number
const float RGB_CHANNEL_COUNT = 3.0;
#define PIXEL image[h][w]
#define PIXEL_OPPOSITE image[h][width - w - 1]

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  // iterate through PIXELs.
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      // calc the average rgb value from each PIXEL
      float average = (PIXEL.rgbtRed + PIXEL.rgbtBlue + PIXEL.rgbtGreen) / RGB_CHANNEL_COUNT;
      // round average
      average = roundf(average);
      // set each rgb entry to the average value
      PIXEL.rgbtRed = PIXEL.rgbtBlue = PIXEL.rgbtGreen = average;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  // swap PIXELs on horizontally opposite sides aka just width
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      RGBTRIPLE swap = PIXEL;
      // arrays go from 0 to size - 1
      PIXEL = PIXEL_OPPOSITE;
      PIXEL_OPPOSITE = swap;
    }
  }
  return;
}

// Blur image
// (0,0),(0,1),(0,2),(0,3),(0,4),
// (1,0),(1,1),(1,2),(1,3),(1,4),
// (2,0),(2,1),(2,2),(2,3),(2,4),
// (3,0),(3,1),(3,2),(3,3),(3,4),
// (4,0),(4,1),(4,2),(4,3),(4,4),
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  // get average of rgb within one row and one column
  // update the 1 single PIXEL with this average
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      float average = 0.0;
      RGBTRIPLE current = PIXEL;
      int count = 0;
      int red = 0;
      int blue = 0;
      int green = 0;

      // for each pixel do another 2D iterative loop starting from w,h-1 to w,h+1
      for (int inner_h = h - 1; inner_h < h + 1; inner_h++) {
        for (int inner_w = w - 1; inner_w < w + 1; inner_w++) {
          // check for negative or above the total height/width to continue
          if (inner_h < 0 || inner_h > height || inner_w < 0 || inner_w > width) {
            continue;
          }
          red += image[inner_h][inner_w].rgbtRed;
          blue += image[inner_h][inner_w].rgbtBlue;
          green += image[inner_h][inner_w].rgbtGreen;
        }
      }
    }
  }
  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  //
  return;
}
