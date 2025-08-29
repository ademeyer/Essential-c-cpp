#include <stdio.h>
#include <stdlib.h>

int solution(int A[], int N)
{
  if (N == 0)
    return 1;

  int *arr = (int *)malloc(sizeof(int) * N);
  if (!arr)
    return -1;
  /* Sort number in O(N) */
  for (int i = 0; i < N; ++i)
    arr[A[i] - 1] = A[i];

  int i = 0;
  for (i; i < N; ++i)
  {
    if (arr[i] != i + 1)
      break;
  }
  free(arr);
  return i + 1;
}

int main()
{
  {
    int A[] = {2, 3, 1, 5};
    int N = sizeof(A) / sizeof(A[0]);
    printf("missing integer: %d\n", solution(A, N));
  }
  {
    int A[] = {2};
    int N = sizeof(A) / sizeof(A[0]);
    printf("missing integer: %d\n", solution(A, N));
  }
  {
    int A[] = {1};
    int N = sizeof(A) / sizeof(A[0]);
    printf("missing integer: %d\n", solution(A, N));
  }
  {
    int A[] = {1};
    int N = sizeof(A) / sizeof(A[0]);
    printf("missing integer: %d\n", solution(A, 0));
  }
  return 0;
}