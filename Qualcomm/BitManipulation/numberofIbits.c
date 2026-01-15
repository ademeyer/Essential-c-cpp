/**
 * @file numberofIbits.c
 * @author your name (you@domain.com)
 * @brief Given a positive integer n, write
 *        a function that returns the number
 *        of set bits in its binary
 *        representation (also known as
 *        the Hamming weight).
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>

int hammingWeight(int n)
{
  int cnt = 0;
  while (n)
  {
    if (n & 0x01)
      ++cnt;
    n >>= 1;
  }
  return cnt;
}

int main()
{
  return 0;
}