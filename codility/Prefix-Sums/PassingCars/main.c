#include <stdio.h>

// int passing_cars(int A[], int N)
// {
//   if (N < 2)
//     return 0;

//   int i = 0, j = 1;
//   int cnt = 0;

//   while (i < N)
//   {
//     if (A[i] == 1)
//     {
//       ++i;
//       ++j;
//       continue;
//     }

//     if (j < N && A[i] == 0 && A[j] == 1)
//       ++cnt;

//     ++j;

//     if (j > N - 1)
//     {
//       ++i;
//       j = i + 1;
//     }
//   }
//   return cnt;
// }

int passing_cars(int A[], int N)
{
  long long pairs = 0, count_west = 0;
  for (int i = 0; i < N; ++i)
  {
    /* Count West bount cars */
    if (A[i] == 1)
      ++count_west;
  }

  /* Find Pairs */
  for (int i = 0; i < N; ++i)
  {
    /* Count East bount cars */
    if (A[i] == 0)
    {
      pairs += count_west;
      if (pairs > 1000000000)
        return -1;
    }
    else
      --count_west;
  }

  return (int)pairs;
}

int main()
{
  {
    int A[] = {0, 1, 0, 1, 1}; // 5
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  {
    int A[] = {1, 0, 0, 1, 1}; // 4
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  {
    int A[] = {0, 0, 0, 1, 1}; // 6
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  {
    int A[] = {0, 1, 1, 1, 1}; // 4
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  {
    int A[] = {1, 1, 1, 1, 1}; // 0
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  {
    int A[] = {1, 1, 0, 1, 0}; // 1
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  {
    int A[] = {1, 1, 0, 1, 0, 0}; // 1
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  {
    int A[] = {1, 1, 0, 1, 0, 1}; // 3
    int N = sizeof(A) / sizeof(A[0]);
    printf("pair of car passing: %d\n", passing_cars(A, N));
  }
  return 0;
}