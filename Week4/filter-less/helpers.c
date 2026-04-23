#include "helpers.h"
#include <math.h>

// RGB_CHANNEL_COUNT = count of rgb channels aka 3. just to avoid magic number
const float RGB_CHANNEL_COUNT = 3.0;
#define PIXEL image[h][w]
#define PIXEL_OPPOSITE image[h][width - w - 1]
#define CALC_SEPIA_RED .393 * PIXEL.rgbtRed + .769 * PIXEL.rgbtGreen + .189 * PIXEL.rgbtBlue
#define CALC_SEPIA_GREEN .349 * PIXEL.rgbtRed + .686 * PIXEL.rgbtGreen + .168 * PIXEL.rgbtBlue
#define CALC_SEPIA_BLUE .272 * PIXEL.rgbtRed + .534 * PIXEL.rgbtGreen + .131 * PIXEL.rgbtBlue

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  // Loop over all pixels
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      // Compute sepia values

      // red
      int sepia_red = roundf(CALC_SEPIA_RED);
      if (sepia_red > 255) {
        sepia_red = 255;
      }

      // green
      int sepia_green = roundf(CALC_SEPIA_GREEN);
      if (sepia_green > 255) {
        sepia_green = 255;
      }

      // blue
      int sepia_blue = roundf(CALC_SEPIA_BLUE);
      if (sepia_blue > 255) {
        sepia_blue = 255;
      }

      // Update pixel with sepia values

      // red
      PIXEL.rgbtRed = sepia_red;

      // green
      PIXEL.rgbtGreen = sepia_green;

      // blue
      PIXEL.rgbtBlue = sepia_blue;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  // swap PIXELs on horizontally opposite sides aka just width
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width / 2; w++) {
      RGBTRIPLE swap = PIXEL;
      // arrays go from 0 to size - 1
      PIXEL = PIXEL_OPPOSITE;
      PIXEL_OPPOSITE = swap;
    }
  }
  return;
}

// Blur image
void blur(int height, int width,
          RGBTRIPLE image[height][width]) { // iterate through the 2D pixel grid
  RGBTRIPLE blurred[height][width];
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      float average = 0.0;
      RGBTRIPLE current = PIXEL;
      int total_nearby_pixels = 0;
      int total_red = 0;
      int total_blue = 0;
      int total_green = 0;

      // for each pixel do another 2D iterative loop starting from (w,h)-1 to (w,h)+1
      // plus and minus 1 because we want to get the pixels within 1 row and 1 column of the current
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
      blurred[h][w].rgbtRed = roundf(average_red);
      blurred[h][w].rgbtBlue = roundf(average_blue);
      blurred[h][w].rgbtGreen = roundf(average_green);
    }
  }

  // put content of blurred into image
  for (int h = 0; h < height; h++) {
   for (int w = 0; w < width; w++) {
     PIXEL = blurred[h][w];
   }
  }
  return;
}
