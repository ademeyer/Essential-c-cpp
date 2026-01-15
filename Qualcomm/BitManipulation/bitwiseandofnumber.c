/**
 * @file bitwiseandofnumber.c
 * @author your name (you@domain.com)
 * @brief Given two integers left and right that
          represent the range [left, right], return
          the bitwise AND of all numbers in this
          range, inclusive.
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>

int rangeBitwiseAnd(int left, int right)
{
  int shift = 0;
  while (left < right)
  {
    left >>= 1;
    right >>= 1;
    ++shift;
  }
  return left << shift;
}

int main()
{
  {
    printf("range AND: %d\n", rangeBitwiseAnd(5, 7));
  }
  {
    printf("range AND: %d\n", rangeBitwiseAnd(0, 0));
  }
  {
    printf("range AND: %d\n", rangeBitwiseAnd(1, 2147483647));
  }
  return 0;
}