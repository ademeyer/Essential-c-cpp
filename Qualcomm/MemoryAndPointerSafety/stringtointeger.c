/**
 * @file stringtointeger.c
 * @author your name (you@domain.com)
 * @brief String to Integer (atoi) (LC #8) - Handle edge cases and overflow
 * @version 0.1
 * @date 2026-01-11
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

static bool isDigit(char c)
{
  return ((c >= '0') && (c <= '9'));
}

static int round_to_int(long long val)
{
  if (val < INT_MIN)
    return INT_MIN;
  if (val > INT_MAX)
    return INT_MAX;
  return (int)val;
}

static int myAtoi(char *s)
{
  /* Input validation */
  if (!s)
    return 0;

  int sign = 1;
  int i = 0;
  /* Whitespace: Ignore any leading whitespace (" "). */
  while (s[i] == ' ')
    ++i;

  /** Signedness: Determine the sign by checking if the next
   * character is '-' or '+', assuming positivity if neither present.*/
  if (s[i] == '-' || s[i] == '+')
  {
    sign = (s[i] == '-') ? -1 : 1;
    ++i;
  }

  /** Conversion: Read the integer by skipping leading zeros
   * until a non-digit character is encountered or the end of
   * the string is reached. If no digits were read, then the result is 0. */
  long long value = 0;
  while (isDigit(s[i]))
  {
    int num = s[i] - '0';
    value = value * 10 + num;

    if (sign == 1 && value > INT_MAX)
      return INT_MAX;
    if (sign == -1 && -value < INT_MIN)
      return INT_MIN;

    ++i;
  }

  /** Rounding: If the integer is out of the 32-bit signed integer
   * range [-2^31, 2^31 - 1], then round the integer to remain in the
   * range. Specifically, integers less than -2^31 should be rounded
   * to -2^31, and integers greater than 2^31 - 1 should be rounded to 2^31 - 1.
   */
  return round_to_int(sign * value);
}

int main()
{
  {
    printf("string to int: %d\n", myAtoi(""));
  }
  {
    printf("string to int: %d\n", myAtoi("+1"));
  }
  {
    printf("string to int: %d\n", myAtoi("+-12"));
  }
  {
    printf("string to int: %d\n", myAtoi(" -042"));
  }
  {
    printf("string to int: %d\n", myAtoi("1337c0d3"));
  }
  {
    printf("string to int: %d\n", myAtoi("4193 with words"));
  }
  {
    printf("string to int: %d\n", myAtoi("-91283472332"));
  }
  {
    printf("string to int: %d\n", myAtoi("0d31337"));
  }
  {
    printf("string to int: %d\n", myAtoi("0-1"));
  }
  return 0;
}