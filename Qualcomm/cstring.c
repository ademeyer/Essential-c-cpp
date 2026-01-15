#include <stdio.h>
#include <string.h>

int main()
{
  char *s = "hello";
  const int t = strlen(s);
  char *d = s + t - 1;
  while (*d)
  {
    printf("%c", *d);
    --d;
  }
  char *r = s;
  printf("s addr: 0x%x, r addr: 0x%x\n", s, r);
  return 0;
}