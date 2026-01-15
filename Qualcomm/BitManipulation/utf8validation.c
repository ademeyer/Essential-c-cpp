/**
 * @file utf8validation.c
 * @author your name (you@domain.com)
 * @brief Given an integer array data representing the data,
          return whether it is a valid UTF-8 encoding (i.e. it
          translates to a sequence of valid UTF-8 encoded characters).

          A character in UTF8 can be from 1 to 4 bytes long,
          subjected to the following rules:

          For a 1-byte character, the first bit is a 0,
          followed by its Unicode code.
          For an n-bytes character, the first n bits are all
          one's, the n + 1 bit is 0, followed by n - 1 bytes with
          the most significant 2 bits being 10.
          This is how the UTF-8 encoding would work:

     Number of Bytes   |        UTF-8 Octet Sequence
                       |              (binary)
   --------------------+-----------------------------------------
            1          |   0xxxxxxx
            2          |   110xxxxx 10xxxxxx
            3          |   1110xxxx 10xxxxxx 10xxxxxx
            4          |   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
          x denotes a bit in the binary form of a byte that may
          be either 0 or 1.

          Note: The input is an array of integers. Only the
          least significant 8 bits of each integer is used to
          store the data. This means each integer represents only 1 byte of data.
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdbool.h>

bool validUtf8(int *data, int dataSize)
{
  int i = 0;
  while (i < dataSize)
  {
    unsigned char byte = data[i] & 0xFF;
    int nByte = 0;
    if ((byte & 0b10000000) == 0)
      nByte = 1;
    else if ((byte & 0b11100000) == 0b11000000)
      nByte = 2;
    else if ((byte & 0b11110000) == 0b11100000)
      nByte = 3;
    else if ((byte & 0b11111000) == 0b11110000)
      nByte = 4;
    else
      return false;

    // check if there is enough byte
    if (dataSize < i + nByte)
      return false;

    // check next byte 0b10xxxxxxx if needed
    for (int k = 1; k < nByte; ++k)
    {
      if (((data[i + k] & 0xFF) & 0b11000000) != 0b10000000)
        return false;
    }
    i += nByte;
  }
  return true;
}

int main()
{
  {
    int data[] = {197, 130, 1};
    const int n = sizeof(data) / sizeof(data[0]);
    printf("is valid UTF: %s\n", validUtf8(data, n) ? "True" : "False");
  }
  {
    int data[] = {235, 140, 4};
    const int n = sizeof(data) / sizeof(data[0]);
    printf("is valid UTF: %s\n", validUtf8(data, n) ? "True" : "False");
  }
  {
    int data[] = {115, 100, 102, 231, 154, 132, 13, 10};
    const int n = sizeof(data) / sizeof(data[0]);
    printf("is valid UTF: %s\n", validUtf8(data, n) ? "True" : "False");
  }
  return 0;
}