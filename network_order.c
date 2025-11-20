#include <stdint.h>
#include <stdio.h>
/*
[Ox00,0x01,OxFE,0x6B,0x28,0x40,0x02,0x03]
0x00,0x03,OxFC,0xD6,0x50,0x80,0x04,0x06

0000 0000 0000 0001 1111 1110 0110 1011
1111 1110 0110 1011 0010 1000 0100 0000

1111 1111 0011 0101 1000 0000 0000 0000
1111 1110 0110 1011 0010 1000 0100 0000

11111111001101011000000000000000 (<< bit 14)
00000000000000000001010000000000 (<< bit 7) <- 14 - 8


11111111001101011001010000100000000000010000000110
11111110011010110010100001000000

* Take first four bytes in array
* Combine to a single 32-bit integer
* while the 31st bit is not set
*   left shift the integer by 1
*/

int findPattern(const uint32_t numBytes, const uint8_t data[])
{
  if (numBytes < 4)
    return -1;
  const uint32_t pattern = 0xFE6B2840u;
  const uint32_t totalBits = numBytes * 8u;

  for (uint32_t bitPos = 0; bitPos + 32u <= totalBits; ++bitPos)
  {
    uint32_t word = 0;
    for (int k = 0; k < 32; ++k)
    {
      uint32_t p = bitPos + (uint32_t)k;
      uint32_t byteIndex = p / 8u;
      uint32_t bitIndex = p % 8u;
      uint8_t bit = (data[byteIndex] >> (7 - bitIndex)) & 1u; // MSB-first within each byte
      word = (word << 1) | bit;
    }
    if (word == pattern)
      return (int)bitPos;
  }
  return -1;
}

int main()
{
  uint8_t data1[] = {0x00, 0x01, 0xFE, 0x6B, 0x28, 0x40, 0x02, 0x03};
  uint8_t data2[] = {0x00, 0x03, 0xFC, 0xD6, 0x50, 0x80, 0x04, 0x06};

  printf("ans: %d\n", findPattern(8, data1));
  printf("ans: %d\n", findPattern(8, data2));

  return 0;
}