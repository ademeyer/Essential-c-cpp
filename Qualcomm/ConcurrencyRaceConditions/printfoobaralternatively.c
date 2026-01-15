#include <semaphore.h>

typedef struct
{
  sem_t foo_sem;
  sem_t bar_sem;
  int n;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar *fooBarCreate(int n)
{
  FooBar *obj = (FooBar *)malloc(sizeof(FooBar));
  obj->n = n;
  sem_init(&obj->foo_sem, 0, 1);
  sem_init(&obj->bar_sem, 0, 0);

  return obj;
}

void foo(FooBar *obj)
{

  for (int i = 0; i < obj->n; i++)
  {
    sem_wait(&obj->foo_sem);
    // printFoo() outputs "foo". Do not change or remove this line.
    printFoo();
    sem_post(&obj->bar_sem);
  }
}

void bar(FooBar *obj)
{

  for (int i = 0; i < obj->n; i++)
  {
    sem_wait(&obj->bar_sem);
    // printBar() outputs "bar". Do not change or remove this line.
    printBar();
    sem_post(&obj->foo_sem);
  }
}

void fooBarFree(FooBar *obj)
{
  if (obj)
  {
    sem_destroy(&obj->foo_sem);
    sem_destroy(&obj->bar_sem);
    free(obj);
  }
}