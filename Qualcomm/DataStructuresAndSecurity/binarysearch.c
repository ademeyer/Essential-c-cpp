/**
 * @file binarysearch.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-01-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>

int binarySearch(int arr[], int size, int k)
{
  int left = 0;
  int right = size - 1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2;

    if (arr[mid] == k)
    {
      // Check if this is the first occurrence
      if (mid == 0 || arr[mid - 1] != k)
      {
        return mid;
      }
      // Not the first occurrence, search left
      right = mid - 1;
    }
    else if (arr[mid] < k)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return -1;
}