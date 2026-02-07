/**
 * @file productofarrayexceptself.c
 * @author your name (you@domain.com)
 * @brief Given an integer array nums, return
          an array answer such that answer[i] is
          equal to the product of all the elements
          of nums except nums[i].

          The product of any prefix or suffix of
          nums is guaranteed to fit in a
          32-bit integer.

          You must write an algorithm that runs
          in O(n) time and without using
          the division operation.
 * @version 0.1
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdlib.h>

int *productExceptSelf(int *nums, int numsSize, int *returnSize)
{
  *returnSize = 0;
  if (numsSize == 0)
    return NULL;

  int *result = (int *)calloc(numsSize, sizeof(int));
  if (!result)
    return NULL;

  result[0] = 1;
  for (int i = 1; i < numsSize; ++i)
    result[i] = result[i - 1] * nums[i - 1];

  int rightProduct = 1;
  for (int i = numsSize - 1; i >= 0; --i)
  {
    result[i] *= rightProduct;
    rightProduct *= nums[i];
  }

  *returnSize = numsSize;
  return result;
}

int main()
{
  {
    int nums[] = {1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    int ret_size = 0;
    int *ret = productExceptSelf(nums, n, &ret_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
      printf("%d,", ret[i]);
    printf("]\n");
    if (ret)
      free(ret);
  }
  {
    int nums[] = {-1, 1, 0, -3, 3};
    int n = sizeof(nums) / sizeof(nums[0]);
    int ret_size = 0;
    int *ret = productExceptSelf(nums, n, &ret_size);
    printf("[");
    for (int i = 0; i < ret_size; ++i)
      printf("%d,", ret[i]);
    printf("]\n");
    if (ret)
      free(ret);
  }
  return 0;
}