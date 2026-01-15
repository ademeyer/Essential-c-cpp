/**
 * @file romantointeger.c
 * @author your name (you@domain.com)
 * @brief Roman numerals are represented by seven different
          symbols: I, V, X, L, C, D and M.

          Symbol       Value
          I             1
          V             5
          X             10
          L             50
          C             100
          D             500
          M             1000
          For example, 2 is written as II in Roman numeral,
          just two ones added together. 12 is written as XII,
          which is simply X + II. The number 27 is written as
          XXVII, which is XX + V + II.

        Roman numerals are usually written largest to smallest
        from left to right. However, the numeral for four is not
        IIII. Instead, the number four is written as IV. Because
        the one is before the five we subtract it making four.
        The same principle applies to the number nine, which is
        written as IX. There are six instances where subtraction is used:

        I can be placed before V (5) and X (10) to make 4 and 9.
        X can be placed before L (50) and C (100) to make 40 and 90.
        C can be placed before D (500) and M (1000) to make 400 and 900.
        Given a roman numeral, convert it to an integer.
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>

int symbolToValue(char symbol)
{
  switch (symbol)
  {
  case 'I':
    return 1;
  case 'V':
    return 5;
  case 'X':
    return 10;
  case 'L':
    return 50;
  case 'C':
    return 100;
  case 'D':
    return 500;
  case 'M':
    return 1000;
  }
  return 0;
}

int romanToInt(char *s)
{
  if (!s)
    return 0;

  int total = 0;

  while (*s)
  {
    int val = symbolToValue(*s);
    if (*s && *(s + 1))
    {
      if (val < symbolToValue(*(s + 1)))
        val *= -1;
    }
    total += val;
    ++s;
  }
  return total;
}

int main()
{
  {
    printf("Integer: %d\n", romanToInt("III"));
  }
  {
    printf("Integer: %d\n", romanToInt("LVIII"));
  }
  {
    printf("Integer: %d\n", romanToInt("MCMXCIV"));
  }
  return 0;
}