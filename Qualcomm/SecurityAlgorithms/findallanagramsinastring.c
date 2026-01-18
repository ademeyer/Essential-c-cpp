/**
 * @file findallanagramsinastring.c
 * @author your name (you@domain.com)
 * @brief Given two strings s and p, return an
          array of all the start indices of p's
          anagrams in s. You may return the
          answer in any order.
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helper function to compare two char freq.
int comp_array(int *a, int *b)
{
  for (int i = 0; i < 26; ++i)
  {
    if (a[i] != b[i])
      return 0;
  }
  return 1;
}

int *findAnagrams(char *s, char *p, int *returnSize)
{
  *returnSize = 0;
  if (!s || !*p)
    return NULL;

  const int s_len = strlen(s), p_len = strlen(p);
  if (p_len > s_len)
    return NULL;

  int p_cnt[26] = {0}, s_window[26] = {0};

  // count frequency of char in p and window of s
  for (int i = 0; i < p_len; ++i)
  {
    p_cnt[p[i] - 'a']++;
    s_window[s[i] - 'a']++;
  }

  // dynamically allocate max_len result (s_len - p_len + 1)
  int res_len = s_len - p_len + 1;
  int *result = (int *)calloc(res_len, sizeof(int));
  if (!result)
    return NULL;

  int cnt = 0;

  // check first window
  if (comp_array(p_cnt, s_window))
    result[cnt++] = 0;

  // slide window
  for (int i = p_len; i < s_len; ++i)
  {
    // add new char to the window
    s_window[s[i] - 'a']++;
    // remove old char from the window
    s_window[s[i - p_len] - 'a']--;
    // check if current window matches p
    if (comp_array(p_cnt, s_window))
      result[cnt++] = i - p_len + 1;
  }

  *returnSize = cnt;
  return result;
}

int main()
{
  {
    char *s = "cbaebabacd", *p = "abc";
    int ret_size = 0;
    int *ret = findAnagrams(s, p, &ret_size);
    printf("ret_size: %d ->[", ret_size);
    for (int i = 0; i < ret_size; ++i)
      printf("%d, ", ret[i]);
    printf("]\n");
    if (ret)
      free(ret);
  }
  {
    char *s = "abab", *p = "ab";
    int ret_size = 0;
    int *ret = findAnagrams(s, p, &ret_size);
    printf("ret_size: %d ->[", ret_size);
    for (int i = 0; i < ret_size; ++i)
      printf("%d, ", ret[i]);
    printf("]\n");
    if (ret)
      free(ret);
  }
  return 0;
}