/**
 * @file maximumproductofwordlengths.c
 * @author your name (you@domain.com)
 * @brief Given a string array words,
          return the maximum value of
          length(word[i]) * length(word[j])
          where the two words do not share
          common letters. If no such two
          words exist, return 0.
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProduct(char **words, int wordsSize)
{
  if (!words)
    return 0;

  int *masks = (int *)malloc(wordsSize * sizeof(int));
  if (!masks)
    return 0;

  int *lengths = (int *)malloc(wordsSize * sizeof(int));
  if (!lengths)
  {
    free(masks);
    return 0;
  }

  for (int i = 0; i < wordsSize; ++i)
  {
    int mask = 0;
    int len = strlen(words[i]);
    for (int j = 0; j < len; ++j)
    {
      int bit = words[i][j] - 'a'; // letter index in 26 chars
      mask |= (1 << bit);
    }

    masks[i] = mask;
    lengths[i] = len;
  }

  // Find the max product
  int max_product = 0;
  for (int i = 0; i < wordsSize; ++i)
  {
    for (int j = i + 1; j < wordsSize; ++j)
    {
      if ((masks[i] & masks[j]) == 0)
      {
        int product = lengths[i] * lengths[j];
        if (product > max_product)
          max_product = product;
      }
    }
  }

  free(masks);
  free(lengths);

  return max_product;
}

int main()
{
  {
    char *s[] = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    int num = 6;
    printf("max product of word lengths: %d\n", maxProduct(s, num));
  }
  {
    char *s[] = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
    int num = 7;
    printf("max product of word lengths: %d\n", maxProduct(s, num));
  }
  {
    char *s[] = {"a", "aa", "aaa", "aaaa"};
    int num = 4;
    printf("max product of word lengths: %d\n", maxProduct(s, num));
  }
  return 0;
}