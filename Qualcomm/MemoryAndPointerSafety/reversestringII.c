/**
 * @file reversestring.c
 * @author your name (you@domain.com)
 * @brief Given a string s and an integer k, reverse
 *        the first k characters for every 2k characters
 *        counting from the start of the string. If there
 *        are fewer than k characters left, reverse all
 *        of them. If there are less than 2k but greater
 *        than or equal to k characters, then reverse the
 *        first k characters and leave the other as original.
 * @date 2026-01-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverseString(char *s, int k)
{
  if (!s)
    return NULL;

  const int n = strlen(s);
  char *new_str = (char *)malloc(sizeof(char) * (n + 1));
  if (!new_str)
    return NULL;

  memcpy(new_str, s, n);
  new_str[n] = '\0';

  if (k > n)
    k = n;

  if (n < k)
  {
    // If k >= n, reverse entire string
    int left = 0, right = n - 1;
    while (left < right)
    {
      char temp = new_str[left];
      new_str[left] = new_str[right];
      new_str[right] = temp;
      left++;
      right--;
    }
    return new_str;
  }

  for (int i = 0; i < n; i += 2 * k)
  {
    // Reverse first k characters in each 2k segment
    int left = i;
    int right = (i + k - 1 < n) ? (i + k - 1) : (n - 1); // Don't go beyond string end

    while (left < right)
    {
      char temp = new_str[left];
      new_str[left] = new_str[right];
      new_str[right] = temp;
      left++;
      right--;
    }
  }

  return new_str;
}

int main()
{
  {
    char *s = "a";
    int k = 2;
    printf("reverse string: %s\n", reverseString(s, k));
  }
  {
    char *s = "abcdefg";
    int k = 2;
    printf("reverse string: %s\n", reverseString(s, k));
  }
  {
    char *s = "abcdefg";
    int k = 8;
    printf("reverse string: %s\n", reverseString(s, k));
  }
  {
    char *s = "abcdefghijkl"; // bacdfeghjikl
    int k = 2;
    printf("reverse string: %s\n", reverseString(s, k));
  }
  {
    char *s = "abcd";
    int k = 2;
    printf("reverse string: %s\n", reverseString(s, k));
  }
  return 0;
}