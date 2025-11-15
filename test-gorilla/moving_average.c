#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void cal_mov_avg(int size, int vec[], int window_size, int* n, int** result)
{
  if(window_size > size) return;

  *n = 0;
  int cum = 0;
  for(int i = 0; i < size; ++i) // {1, 2, 3, 4, 5}
  {
    cum += vec[i];
    if((i + 1) >= window_size)
    {
      double g = cum / (double) window_size;
      (*result)[*n] = lround(g);
      ++*n;
      cum -= vec[i + 1 - window_size]; // remove the head;
    }
  }
}

int main()
{
  int* result = (int*)malloc(20 * sizeof(int));
  int n = 0;
  
  int arr[] = {1,2,3,4};
  int size = sizeof(arr) / sizeof(arr[0]);
  int window_size = 2;

  cal_mov_avg(size, arr, window_size, &n, &result);
  for(int i = 0; i < n; ++i)
    printf("%d, ", result[i]);
  printf("\n");

  free(result);

  return 0;
}
