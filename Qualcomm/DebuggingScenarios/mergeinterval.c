/**
 * @file mergeinterval.c
 * @author your name (you@domain.com)
 * @brief Given an array of intervals where
          intervals[i] = [starti, endi], merge
          all overlapping intervals, and return
          an array of the non-overlapping intervals
          that cover all the intervals in the input.
 * @version 0.1
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdlib.h>

int compareStartInterval(const void *a, const void *b)
{
  int *inter_1 = *(int **)a;
  int *inter_2 = *(int **)b;
  return inter_1[0] - inter_2[0];
}

int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize, int **returnColumnSizes)
{
  if (intervalsSize == 0)
  {
    *returnSize = 0;
    return NULL;
  }

  // sort intervals by start time
  qsort(intervals, intervalsSize, sizeof(int *), compareStartInterval);

  // allocate result array
  int **result = (int **)calloc(intervalsSize, sizeof(int *));
  *returnColumnSizes = (int *)calloc(intervalsSize, sizeof(int));

  // initialize with first interval
  result[0] = (int *)calloc(2, sizeof(int));
  result[0][0] = intervals[0][0];
  result[0][1] = intervals[0][1];
  (*returnColumnSizes)[0] = 2;
  int resultSize = 1;

  // merge intervals
  for (int i = 1; i < intervalsSize; ++i)
  {
    int *lastInterval = result[resultSize - 1];
    int *curInterval = intervals[i];

    // check for overlap: current start time and last end time
    if (curInterval[0] <= lastInterval[1])
    {
      // merge: update end time if current ends later
      if (curInterval[1] > lastInterval[1])
        lastInterval[1] = curInterval[1];
    }
    else // no overlap, add new interval to result
    {
      result[resultSize] = (int *)calloc(2, sizeof(int));
      result[resultSize][0] = curInterval[0];
      result[resultSize][1] = curInterval[1];
      (*returnColumnSizes)[resultSize] = 2;
      ++resultSize;
    }
  }
  *returnSize = resultSize;
  return result;
}

int main()
{
  {
    int *intervals[] = {(int[]){1, 3}, (int[]){2, 6}, (int[]){8, 10}, (int[]){15, 18}};
    int interval_size = 4;
    int interval_col_size[] = {2, 2, 2, 2};
    int ret_size = 0;
    int *ret_col_size;
    int **ret = merge(intervals, interval_size, interval_col_size, &ret_size, &ret_col_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
      printf("[%d, %d],", ret[i][0], ret[i][1]);
    printf("]\n");
    if (ret)
    {
      for (int i = 0; i < ret_size; ++i)
        free(ret[i]);
      free(ret);
    }
    if (ret_col_size)
      free(ret_col_size);
  }
  {
    int *intervals[] = {(int[]){1, 4}, (int[]){4, 5}};
    int interval_size = 2;
    int interval_col_size[] = {2, 2};
    int ret_size = 0;
    int *ret_col_size;
    int **ret = merge(intervals, interval_size, interval_col_size, &ret_size, &ret_col_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
      printf("[%d, %d],", ret[i][0], ret[i][1]);
    printf("]\n");
    if (ret)
    {
      for (int i = 0; i < ret_size; ++i)
        free(ret[i]);
      free(ret);
    }
    if (ret_col_size)
      free(ret_col_size);
  }
  {
    int *intervals[] = {(int[]){4, 7}, (int[]){1, 4}};
    int interval_size = 2;
    int interval_col_size[] = {2, 2};
    int ret_size = 0;
    int *ret_col_size;
    int **ret = merge(intervals, interval_size, interval_col_size, &ret_size, &ret_col_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
      printf("[%d, %d],", ret[i][0], ret[i][1]);
    printf("]\n");
    if (ret)
    {
      for (int i = 0; i < ret_size; ++i)
        free(ret[i]);
      free(ret);
    }
    if (ret_col_size)
      free(ret_col_size);
  }
  return 0;
}