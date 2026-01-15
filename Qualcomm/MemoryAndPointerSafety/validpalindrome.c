/**
 * @file validpalindrome.c
 * @author your name (you@domain.com)
 * @brief A phrase is a palindrome if, after
 *        converting all uppercase letters into
 *        lowercase letters and removing all non-alphanumeric
 *        characters, it reads the same forward and backward.
 *        Alphanumeric characters include letters and numbers.
 *        Given a string s, return true if it is a
 *        palindrome, or false otherwise.
 * @version 0.1
 * @date 2026-01-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isAlphaNumeric(char c)
{
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9');
}

char lower(char c)
{
  if (c >= 'A' && c <= 'Z')
    return c + 32;
  return c;
}

bool isPalindrome(char *s)
{
  if (!s)
    return true;

  const int n = strlen(s);
  char *left = s;
  char *right = s + n - 1;
  while (left < right)
  {
    while (left < right && !isAlphaNumeric(*left))
      ++left;
    while (left < right && !isAlphaNumeric(*right))
      --right;

    if (lower(*left) != lower(*right))
      return false;

    ++left;
    --right;
  }
  return true;
}

int main()
{
  {
    char *s = "A man, a plan, a canal: Panama";
    printf("%s\n", isPalindrome(s) ? "True" : "False");
  }

  {
    char *s = "race a car";
    printf("%s\n", isPalindrome(s) ? "True" : "False");
  }

  {
    char *s = " ";
    printf("%s\n", isPalindrome(s) ? "True" : "False");
  }

  {
    char *s = ".,";
    printf("%s\n", isPalindrome(s) ? "True" : "False");
  }
  return 0;
}