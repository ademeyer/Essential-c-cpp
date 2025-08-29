#include <stdio.h>
#include <limits.h>

int get_min(int a, int b)
{
  return a < b ? a : b;
}

int get_abs(int a)
{
  return a < 0 ? -a : a;
}

int solution(int A[], int N)
{
  if (N == 0)
    return 0;
  if (N == 1)
    return A[0];

  int result = INT_MAX;
  long long left = 0, right = 0;

  for (int i = 0; i < N; ++i)
    right += A[i];

  for (int i = 0; i < N - 1; ++i)
  {
    left += A[i];
    right -= A[i];
    result = get_min(result, get_abs((left - right)));
  }
  // printf("left: %lld, right: %lld, result: %d\n", left, right, result);
  return result;
}

int main()
{
  {
    int A[] = {3, 1, 2, 4, 3};
    int N = sizeof(A) / sizeof(A[0]);

    printf("Tape Equilibrium: %d\n", solution(A, N));
  }
  {
    int A[] = {3};
    int N = sizeof(A) / sizeof(A[0]);

    printf("Tape Equilibrium: %d\n", solution(A, N));
  }
  {
    int A[] = {0};
    int N = sizeof(A) / sizeof(A[0]);

    printf("Tape Equilibrium: %d\n", solution(A, N));
  }

  {
    int A[] = {3, 1, 2, 4, 3, 234, 455, 63, 1, 2, 4, 8, 9, 100, 23, 78, 54, 345, 32, 759, 102};
    int N = sizeof(A) / sizeof(A[0]);

    printf("Tape Equilibrium: %d\n", solution(A, N));
  }
  return 0;
}