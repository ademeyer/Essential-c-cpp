/**
 * @file sumoftwointegers.c
 * @author your name (you@domain.com)
 * @brief Given two integers a and b, return
          the sum of the two integers without
          using the operators + and -.
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>

int getSum(int a, int b)
{
  while (b != 0)
  {
    int carry = a & b;
    a = a ^ b;
    b = (unsigned int)carry << 1;
  }
  return a;
}

int main()
{
  return 0;
}