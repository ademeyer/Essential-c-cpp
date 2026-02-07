/**
 * @file findtheduplicatenumber.c
 * @author your name (you@domain.com)
 * @brief Given an array of integers nums containing n + 1
          integers where each integer is in the range [1, n] inclusive.

          There is only one repeated number in nums, return this repeated number.

          You must solve the problem without modifying the array
          nums and using only constant extra space.
 * @version 0.1
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>

int findDuplicate(int *nums, int numsSize)
{
  int slow = nums[0];
  int fast = nums[0];

  do
  {
    slow = nums[slow];       // move 1 step
    fast = nums[nums[fast]]; // move 2 steps
  } while (slow != fast);

  // find the entrance to the cycle (duplicate)
  slow = nums[0];
  while (slow != fast)
  {
    slow = nums[slow];
    fast = nums[fast];
  }
  return slow;
}

int main()
{
  {
    int nums[] = {1, 3, 4, 2, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("Duplicate Number: %d\n", findDuplicate(nums, n));
  }
  {
    int nums[] = {3, 1, 3, 4, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("Duplicate Number: %d\n", findDuplicate(nums, n));
  }
  {
    int nums[] = {3, 3, 3, 3, 3};
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("Duplicate Number: %d\n", findDuplicate(nums, n));
  }
  return 0;
}