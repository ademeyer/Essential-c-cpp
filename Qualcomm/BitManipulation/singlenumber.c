/**
 * @file singlenumber.c
 * @author your name (you@domain.com)
 * @brief Given a non-empty array of integers nums,
 *        every element appears twice except for one.
 *        Find that single one.
 *        You must implement a solution with a
 *        linear runtime complexity and use
 *        only constant extra space.
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>

int singleNumber(int *nums, int numsSize)
{
  int result = 0;
  for (int i = 0; i < numsSize; ++i)
    result ^= nums[i];

  return result;
}

int main()
{
  {
    int num[] = {2, 2, 1};
    const int n = sizeof(num) / sizeof(num[0]);
    printf("single number: %d\n", singleNumber(num, n));
  }
  {
    int num[] = {4, 1, 2, 1, 2};
    const int n = sizeof(num) / sizeof(num[0]);
    printf("single number: %d\n", singleNumber(num, n));
  }
  {
    int num[] = {1};
    const int n = sizeof(num) / sizeof(num[0]);
    printf("single number: %d\n", singleNumber(num, n));
  }
  return 0;
}