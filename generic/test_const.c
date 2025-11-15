#include <stdio.h>

int main()
{
  const int a = 56;
  printf("first a = %d", a);
  int* ptra = (int*)&a;
  *ptra = 45;
  printf(" , second a = %d\n", a);
  return 0;
}
