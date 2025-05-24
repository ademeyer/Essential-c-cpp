#include <stdio.h>
#include <stdint.h>

typedef struct test
{
  int a;
  int b;
} test_t;

volatile uint32_t P = 45;

uint32_t *foo()
{

  static volatile uint32_t *M;
  M = &P;
  return M;
}

int main()
{
  const int a = 5;
  const int b = 6;
  int *pb = &b;
  const int *ptr = NULL;
  const int *const ptra = &a;

  test_t *t;
  t = &(test_t){
      .a = 4,
      .b = 1,
  };

  uint32_t *p = foo();
  *p = 8;
  printf("ptra address: %d, P value: %d, *p value: %d\n", ptra, P, *p);

  printf("ptra address: %d, ptra value: %d\n", ptra, *ptra);

  // ptra = &b;
  // printf("ptra address: %d, ptra value: %d\n", ptra, *ptra);

  ptr = &a;
  printf("ptr address: %d, ptr value: %d\n", ptr, *ptr);

  *pb = 25;
  ptr = &b;
  printf("ptr address: %d, ptr value: %d\n", ptr, *ptr);
  printf("a value: %d, b value: %d\n", a, b);
  return 0;
}