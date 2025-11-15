#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
  static const int a[] = {25, 2, 3, 5};

  int *ptr = (int*)a;
  
  // *ptr = 55;
  
  printf("address: 0x%lx, value: %d\n", (intptr_t)ptr, *ptr);
  
  return 0;
}
