/**
 * @file countingbits.c
 * @author your name (you@domain.com)
 * @brief Given an integer n, return an array
 *        ans of length n + 1 such that for
 *        each i (0 <= i <= n), ans[i] is the
 *        number of 1's in the binary representation of i.
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdlib.h>

// int* countBits(int n, int* returnSize){
//     *returnSize = n + 1;
//     int* ret = (int*) malloc(*returnSize * sizeof(int));
//     ret[0] = 0;
//     for (int i = 1; i < *returnSize; i++) {
//         ret[i] = (i & 1) + ret[i >> 1];
//     }
//     return ret;
// }

int *countBits(int n, int *returnSize)
{
  *returnSize = n + 1;
  int *res = (int *)malloc(*returnSize * sizeof(int));
  if (!res)
    return NULL;

  res[0] = 0;
  int offset = 1;
  for (int i = 1; i < *returnSize; ++i)
  {
    if (offset * 2 == i)
      offset = i;

    res[i] = 1 + res[i - offset];
  }
  return res;
}

int main()
{
  return 0;
}