/**
 * @file groupanagram.c
 * @author your name (you@domain.com)
 * @brief Given an array of strings strs, group the anagrams together. You can return the answer in any order.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
  int chksum[26];
  int pos;
  int size;
} anagram;

int compare_anagram(const void *a, const void *b)
{
  const anagram *ana_a = (const anagram *)a;
  const anagram *ana_b = (const anagram *)b;

  for (int i = 0; i < 26; ++i)
  {
    if (ana_a->chksum[i] != ana_b->chksum[i])
      return ana_a->chksum[i] - ana_b->chksum[i];
  }

  return 0;
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
  if (!strs)
  {
    *returnSize = 0;
    *returnColumnSizes = NULL;
    return NULL;
  }

  *returnSize = 0;
  anagram *word = (anagram *)calloc(strsSize, sizeof(anagram));
  int n = 0;

  for (int i = 0; i < strsSize; ++i)
  {
    n = strlen(strs[i]);
    word[i].pos = i;
    word[i].size = n;
    memset(word[i].chksum, 0, sizeof(word[i].chksum));
    for (int k = 0; k < n; ++k)
      word[i].chksum[strs[i][k] - 'a']++; // all char are lowercase
  }

  qsort(word, strsSize, sizeof(anagram), compare_anagram);

  ++(*returnSize);
  for (int i = 1; i < strsSize; ++i)
  {
    if (compare_anagram(&word[i], &word[i - 1]) != 0)
      ++(*returnSize);
  }

  *returnColumnSizes = (int *)calloc(*returnSize, sizeof(int));
  char ***result = (char ***)calloc(*returnSize, sizeof(char **));

  for (int i = 0; i < *returnSize; i++)
    (*returnColumnSizes)[i] = 0;

  int p = 0;
  (*returnColumnSizes)[p]++;
  for (int i = 1; i < strsSize; ++i)
  {
    if (compare_anagram(&word[i], &word[i - 1]) != 0)
      p++;
    (*returnColumnSizes)[p]++;
  }

  p = 0;
  int groupNo = 0;
  for (int i = 0; i < *returnSize; ++i)
  {
    groupNo = (*returnColumnSizes)[i];
    result[i] = (char **)calloc(groupNo, sizeof(char *));
    for (int k = 0; k < groupNo; ++k)
    {
      result[i][k] = (char *)calloc((word[p].size + 1), sizeof(char));
      memcpy(result[i][k], strs[word[p].pos], word[p].size);
      ++p;
    }
  }

  // deallocate memory
  if (word)
    free(word);

  return result;
}

int main()
{
  {
    char *s[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    const int i = 6;
    int ret_size = 0;
    int *ret_col_size = NULL;
    char ***ret = groupAnagrams(s, i, &ret_size, &ret_col_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
    {
      printf("[");
      int groupNo = ret_col_size[i];
      for (int k = 0; k < groupNo; ++k)
        printf("%s,", ret[i][k]);
      printf("],");
    }
    printf("]\n");

    if (ret)
      free(ret);
    if (ret_col_size)
      free(ret_col_size);
  }
  {
    char *s[] = {""};
    const int i = 1;
    int ret_size = 0;
    int *ret_col_size = NULL;
    char ***ret = groupAnagrams(s, i, &ret_size, &ret_col_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
    {
      printf("[");
      int groupNo = ret_col_size[i];
      for (int k = 0; k < groupNo; ++k)
        printf("%s,", ret[i][k]);
      printf("],");
    }
    printf("]\n");

    if (ret)
      free(ret);
    if (ret_col_size)
      free(ret_col_size);
  }
  {
    char *s[] = {"a"};
    const int i = 1;
    int ret_size = 0;
    int *ret_col_size = NULL;
    char ***ret = groupAnagrams(s, i, &ret_size, &ret_col_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
    {
      printf("[");
      int groupNo = ret_col_size[i];
      for (int k = 0; k < groupNo; ++k)
        printf("%s,", ret[i][k]);
      printf("],");
    }
    printf("]\n");

    if (ret)
      free(ret);
    if (ret_col_size)
      free(ret_col_size);
  }
  return 0;
}