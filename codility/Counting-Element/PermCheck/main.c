#include <stdio.h>
#include <stdlib.h>
/*
A non-empty array A consisting of N integers is given.

A permutation is a sequence containing each element from 1 to N once, and only once.

For example, array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
    A[3] = 2
is a permutation, but array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
is not a permutation, because value 2 is missing.

The goal is to check whether array A is a permutation.

Write a function:

int solution(int A[], int N);

that, given an array A, returns 1 if array A is a permutation and 0 if it is not.

For example, given array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
    A[3] = 2
the function should return 1.

Given array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
the function should return 0.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [1..1,000,000,000].
*/

#include <limits.h>

int get_max(int a, int b)
{
  return a > b ? a : b;
}

int solution(int A[], int N)
{
  if (N == 0)
    return 1;

  int max = INT_MIN;
  for (int i = 0; i < N; ++i)
    max = get_max(max, A[i]);

  /* Ensure it's sequential */
  if (max != N)
    return 0;

  int *arr = (int *)malloc(sizeof(int) * max);
  if (!arr)
    return -1;

  for (int i = 0; i < max; ++i)
    arr[i] = 0;

  /* Ensure N occurs only once */
  int occured_once = 1;
  for (int i = 0; i < N; ++i)
  {
    int p = A[i] - 1;
    arr[p]++;
    if (arr[p] > 1)
    {
      occured_once = 0;
      break;
    }
  }
  free(arr);
  return occured_once;
}

int main()
{
  {
    int A[] = {4, 1, 3, 2};
    int N = sizeof(A) / sizeof(A[0]);
    printf("Perm Check: %s\n", (solution(A, N) ? "true" : "false"));
  }

  {
    int A[] = {4, 1, 3};
    int N = sizeof(A) / sizeof(A[0]);
    printf("Perm Check: %s\n", (solution(A, N) ? "true" : "false"));
  }
  return 0;
}