#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ARRAY_SIZE 9999

/*
A non-empty array A consisting of N integers is given. The array contains an odd number of elements, and each element of the array can be paired with another element that has the same value, except for one element that is left unpaired.

For example, in array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9
the elements at indexes 0 and 2 have value 9,
the elements at indexes 1 and 3 have value 3,
the elements at indexes 4 and 6 have value 9,
the element at index 5 has value 7 and is unpaired.
Write a function:

int solution(int A[], int N);

that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the unpaired element.

For example, given array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9
the function should return 7, as explained in the example above.

Write an efficient algorithm for the following assumptions:

N is an odd integer within the range [1..1,000,000];
each element of array A is an integer within the range [1..1,000,000,000];
all but one of the values in A occur an even number of times.
*/

int get_max(int a, int b)
{
  return a > b ? a : b;
}

int solution(int A[], int N)
{
  if (N % 2 == 0 || N == 0)
    return -1;

  /* Find Max digits */
  int S = 0;
  for (int i = 0; i < N; ++i)
    S = get_max(S, A[i]);

  ++S;

  // There are 0 - A[i]max digits, allocate, zero out
  int *arr = (int *)malloc(sizeof(int) * S);
  for (int i = 0; i < S; ++i)
    arr[i] = 0;

  /* if allocation failed */
  if (!arr)
    return -1;

  for (int i = 0; i < N; ++i)
    arr[A[i]]++;

  int res = -1;
  for (int i = 0; i < S; ++i)
  {
    if (arr[i] != 0 && arr[i] % 2 != 0)
    {
      res = i;
      break;
    }
  }
  free(arr);
  return res;
}

// void generate_array(int *arr, int max)
// {
//   for (int i = 0; i < max; ++i)
//   {
//     int p = 0;
//     do
//     {
//       p = rand();
//     } while (p == 0);

//     arr[i] = p;
//   }
//   // make non odd occurrence
//   for (int i = 0; i < max; i += 2)
//     arr[i] = arr[i + 1];

//   // random position to make an odd element
//   int pos = (rand() % max) - 1;
//   arr[pos] = rand();
//   printf("arr[%d] = %d\n", pos, arr[pos]);
// }

int main()
{
  int A[] = {9, 3, 9, 3, 9, 7, 9};
  int size_a = sizeof(A) / sizeof(A[0]);
  printf("oddly paired element: %d\n", solution(A, size_a));
  // int *bigArr = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE);
  // if (!bigArr)
  //   return EXIT_FAILURE;
  // generate_array(bigArr, MAX_ARRAY_SIZE);
  // printf("oddly paired element: %d\n", solution(bigArr, MAX_ARRAY_SIZE));
  // free(bigArr);

  return 0;
}