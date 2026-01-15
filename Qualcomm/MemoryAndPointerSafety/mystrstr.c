/**
 * @file mystrstr.c
 * @author your name (you@domain.com)
 * @brief Implement strStr() (LC #28) - Implement string
 *        searching with bounds checking
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <string.h>

int strStr(char *haystack, char *needle)
{
  if (!haystack || !needle)
    return -1;

  const int hay_len = strlen(haystack);
  const int needle_len = strlen(needle);
  if (needle_len > hay_len)
    return -1;

  int i = 0, j = 0, idx = -1;

  while (i < hay_len && j < needle_len)
  {
    if (haystack[i] == needle[j])
    {
      if (j == 0)
        idx = i;
      ++j;
    }
    else
    {
      idx = -1;
      j = 0;
    }

    ++i;
  }
  return idx;
}

int main()
{
  {
    printf("Index: %d\n", strStr("catherina", "cat"));
  }

  {
    printf("Index: %d\n", strStr("catherina", ""));
  }

  {
    printf("Index: %d\n", strStr("", "cat"));
  }

  {
    printf("Index: %d\n", strStr("sadbutsad", "sad"));
  }

  {
    printf("Index: %d\n", strStr("leetcode", "leeto"));
  }

  {
    printf("Index: %d\n", strStr("leetcode", "code"));
  }
  return 0;
}