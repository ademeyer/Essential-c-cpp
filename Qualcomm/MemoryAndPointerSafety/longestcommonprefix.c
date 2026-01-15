/**
 * @file longestcommonprefix.c
 * @author your name (you@domain.com)
 * @brief Write a function to find the longest common
 *        prefix string amongst an array of strings.
 *        If there is no common prefix, return an empty string ""
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *longestCommonPrefix(char **strs, int strsSize)
{
  if (!strs)
    return "";
  if (strsSize == 1)
    return strs[0];

  bool match = true;
  int match_cnt = 0;
  size_t nxt = 0;

  while (match)
  {
    char ch = strs[0][nxt];
    for (int i = 1; (i < strsSize && match); ++i)
      match &= ((ch == strs[i][nxt]) && (strlen(strs[i]) > nxt));

    if (match)
      ++nxt;
  }

  char *res = (char *)malloc(sizeof(char) * (nxt + 1));
  if (!res)
    return NULL;

  memcpy(res, strs[0], nxt);
  res[nxt] = '\0';

  return res;
}

int main()
{
  {
    char *s[] = {"flower", "flow", "flight"};
    const int ssize = 3;
    char *r = longestCommonPrefix(s, ssize);
    printf("match: %s\n", r);
    if (r)
      free(r);
  }
  {
    char *s[] = {"dog", "racecar", "car"};
    const int ssize = 3;
    char *r = longestCommonPrefix(s, ssize);
    printf("match: %s\n", r);
    if (r)
      free(r);
  }

  return 0;
}