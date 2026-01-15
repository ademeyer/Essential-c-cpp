/**
 * @file reversestring.c
 * @author your name (you@domain.com)
 * @brief Write a function that reverses a string. The input
 *        string is given as an array of characters s. You
 *        must do this by modifying the input array in-place
 *        with O(1) extra memory.
 * @version 0.1
 * @date 2026-01-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <string.h>

void reverseString(char *s, int sSize)
{
  if (!s || sSize <= 0)
    return;

  int i = 0, j = sSize - 1;
  while (i < j)
  {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    ++i;
    --j;
  }
}

int main()
{
  {
    char s[] = {'h', 'e', 'l', 'l', 'o'};
    const int n = strlen(s);
    reverseString(s, n);
    printf("reverse string: %s\n", s);
  }
  {
    char s[] = {'H', 'a', 'n', 'n', 'a', 'h'};
    const int n = strlen(s);
    reverseString(s, n);
    printf("reverse string: %s\n", s);
  }
  return 0;
}