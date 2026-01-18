/**
 * @file longestsubstringwithoutRepeatingchar.c
 * @author your name (you@domain.com)
 * @brief Given a string s, find the length of
          the longest substring without
          duplicate characters.
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char *s)
{
  const int n = strlen(s);

  if (n == 0)
    return 0;

  int lastSeen[128];

  for (int i = 0; i < 128; ++i)
    lastSeen[i] = -1;

  int left = 0, maxLen = 0;
  for (int right = 0; right < n; ++right)
  {
    char c = s[right];
    if (lastSeen[c] >= left)
      left = lastSeen[c] + 1;

    lastSeen[c] = right;
    int curLen = right - left + 1;

    if (curLen > maxLen)
      maxLen = curLen;
  }

  return maxLen;
}

int main()
{
  {
    char *s = "abcabcbb";
    printf("Longest substring without repeating a char: %d\n", lengthOfLongestSubstring(s));
  }
  {
    char *s = "bbbbb";
    printf("Longest substring without repeating a char: %d\n", lengthOfLongestSubstring(s));
  }
  {
    char *s = "pwwkew";
    printf("Longest substring without repeating a char: %d\n", lengthOfLongestSubstring(s));
  }
  {
    char *s = "hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    printf("Longest substring without repeating a char: %d\n", lengthOfLongestSubstring(s));
  }
  return 0;
}