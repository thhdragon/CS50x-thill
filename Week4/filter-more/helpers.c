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
//
// get average of rgb within one row and one column
// update the 1 single PIXEL with this average
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  // iterate through the 2D pixel grid
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      float average = 0.0;
      RGBTRIPLE current = PIXEL;
      int total_nearby_pixels = 0;
      int total_red = 0;
      int total_blue = 0;
      int total_green = 0;

      // for each pixel do another 2D iterative loop starting from w,h-1 to w,h+1
      // get pixels within 1 row and 1 column
      for (int inner_h = h - 1; inner_h <= h + 1; inner_h++) {
        for (int inner_w = w - 1; inner_w <= w + 1; inner_w++) {
          // check for negative or above the total height/width to continue
          if (inner_h < 0 || inner_h >= height || inner_w < 0 || inner_w >= width) {
            continue;
          }
          // accumulate totals
          total_red += image[inner_h][inner_w].rgbtRed;
          total_blue += image[inner_h][inner_w].rgbtBlue;
          total_green += image[inner_h][inner_w].rgbtGreen;
          // increment counter for average calc
          total_nearby_pixels++;
        }
      }
      // outside the inner 2D iteration loop get average from accumulated values
      float average_red = (float)total_red / total_nearby_pixels;
      float average_blue = (float)total_blue / total_nearby_pixels;
      float average_green = (float)total_green / total_nearby_pixels;

      // set the pixels RGB values to the new averages
      PIXEL.rgbtRed = average_red;
      PIXEL.rgbtBlue = average_blue;
      PIXEL.rgbtGreen = average_green;
    }
  }
  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  //
  return;
}
