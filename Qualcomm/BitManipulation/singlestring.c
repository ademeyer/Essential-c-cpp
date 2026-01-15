/**
 * @file singlestring.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *singlestring(char **strs, int strLen)
{
  if (!strs)
    return NULL;

  int *chksum = (int *)malloc(sizeof(int) * strLen);
  if (!chksum)
    return NULL;
  // calculate a checksum
  for (int k = 0; k < strLen; ++k)
  {
    char *now = strs[k];
    int res = 0;
    for (size_t i = 0; i < strlen(now); ++i)
      res += (now[i] << i);

    chksum[k] = res;
  }

  int diff = 0;
  for (int k = 0; k < strLen; ++k)
    diff ^= chksum[k];

  int idx = -1;
  for (int k = 0; k < strLen; ++k)
  {
    if (diff == chksum[k])
      idx = k;
  }
  return idx == -1 ? NULL : strs[idx];
}

int main()
{
  {
    char *s[] = {"cat", "dog", "cat", "lion", "lion"};
    int n = 5;
    printf("single string: %s\n", singlestring(s, n));
  }

  {
    char *s[] = {"ca", "ac", "ca"};
    int n = 3;
    printf("single string: %s\n", singlestring(s, n));
  }
  return 0;
}