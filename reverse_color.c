#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define R_MASK 0b1111100000000000
#define G_MASK 0b0000011111100000
#define B_MASK 0b0000000000011111

// Reverser uint16_t rgb (565) color 11011001
void reverse_color(void *color)
{
  if (!color)
    return;

  uint16_t mColor;
  // Need to handle misalign binary
  memcpy(&mColor, color, sizeof(uint16_t));
  // Get red value
  uint8_t red = ((mColor & R_MASK) >> 11);
  // Get green value
  uint8_t green = ((mColor & G_MASK) >> 5);
  // Get blue value
  uint8_t blue = (mColor & B_MASK) & 0xFF;
  // reverse color
  uint16_t bgr = (blue << 11) | (green << 5) | red;
  *((uint16_t *)color) = bgr;
}

int main()
{
  // 10000 111000 00111
  // 00111 111000 10000
  uint32_t color1 = 34567, color2 = 6792;
  printf("color1: %d, color2: %d\n", color1, color2);
  reverse_color(&color1);
  reverse_color(&color2);
  printf("color1: %d, color2: %d\n", color1, color2);
  return 0;
}

/*
1000011100000111
1111100000000000
= 1000000000000000 >> 11 = 10000

1000011100000111
0000011111100000
= 11100000000 >> 5 = 111000

1000011100000111
0000000000011111
= 111



1000000000000000
00000111000

*/