/**
 * @file validanagram.c
 * @author your name (you@domain.com)
 * @brief Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isAnagram(char *s, char *t)
{
  if (!s || !t)
    return false;

  int s_len = strlen(s), t_len = strlen(t);
  if (s_len != t_len)
    return false;

  // a - z
  int s_char[26] = {0}, t_char[26] = {0};
  for (int i = 0; i < s_len; ++i)
  {
    s_char[s[i] - 'a']++;
    t_char[t[i] - 'a']++;
  }

  for (int i = 0; i < 26; ++i)
  {
    if (s_char[i] != t_char[i])
      return false;
  }
  return true;
}

int main()
{
  {
    char *s = "anagram", *t = "nagaram";
    printf("Is anagram: %s\n", isAnagram(s, t) ? "True" : "False");
  }
  {
    char *s = "rat", *t = "car";
    printf("Is anagram: %s\n", isAnagram(s, t) ? "True" : "False");
  }
  return 0;
}