/**
 * @file reverseinteger.c
 * @author your name (you@domain.com)
 * @brief Given a signed 32-bit integer x, return x with its digits reversed.
 *        If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
          !! Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
 * @version 0.1
 * @date 2026-01-12
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <limits.h>

int reverse(int x)
{
  if (x <= INT_MIN || x >= INT_MAX)
    return 0;
  /* Handle signedness */
  int sign = x < 0 ? -1 : 1;

  /* Get absolute value */
  x = x < 0 ? -x : x;
  int ret_x = 0;
  while (x)
  {
    int n = x % 10;

    if (ret_x > INT_MAX / 10 || (ret_x == INT_MAX / 10 && n > 7))
      return 0;

    ret_x = ret_x * 10 + n;
    x /= 10;
  }

  return (ret_x * sign);
}

int main()
{
  {
    printf("reverse int: %d\n", reverse(123));
  }
  {
    printf("reverse int: %d\n", reverse(-123));
  }
  {
    printf("reverse int: %d\n", reverse(120));
  }
  return 0;
}