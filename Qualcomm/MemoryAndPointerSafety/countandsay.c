/**
 * @file countandsay.c
 * @author your name (you@domain.com)
 * @brief The count-and-say sequence is a sequence of digit strings
 *        defined by the recursive formula:
 *        - countAndSay(1) = "1"
          - countAndSay(n) is the run-length encoding of countAndSay(n - 1).
          Run-length encoding (RLE) is a string compression method
          that works by replacing consecutive identical
          characters (repeated 2 or more times) with the concatenation
          of the character and the number marking the count of the
          characters (length of the run). For example, to compress
          the string "3322251" we replace "33" with "23", replace "222"
          with "32", replace "5" with "15" and replace "1" with "11".
          Thus the compressed string becomes "23321511".
          Given a positive integer n, return the nth element of the count-and-say sequence.
 * @version 0.1
 * @date 2026-01-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *countAndSay(int n)
{
  if (n == 1)
  {
    char *res = (char *)malloc(sizeof(char) * 2);
    res[0] = '1';
    res[1] = '\0';
    return res;
  }

  // recursively call to get previous term
  char *prev = countAndSay(n - 1);
  int len = strlen(prev);

  // count the run in previous term
  char *result = (char *)malloc(sizeof(char) * (2 * len + 1));
  if (!result)
  {
    free(prev);
    return NULL;
  }

  int idx = 0; // index for result string
  int i = 0;   // index to traverse prev string
  while (i < len)
  {
    char c = prev[i];
    int cnt = 0;
    // count consecutive identical chars
    while (i < len && prev[i] == c)
    {
      ++cnt;
      ++i;
    }
    // append to result string
    result[idx++] = cnt + '0'; // make string
    result[idx++] = c;
  }
  result[idx] = '\0';
  free(prev);
  return result;
}

int main()
{
  {
    char *r = countAndSay(4);
    printf("%s\n", r);
    free(r);
  }
  {
    char *r = countAndSay(1);
    printf("%s\n", r);
    free(r);
  }
  {
    char *r = countAndSay(10);
    printf("%s\n", r);
    free(r);
  }
  return 0;
}