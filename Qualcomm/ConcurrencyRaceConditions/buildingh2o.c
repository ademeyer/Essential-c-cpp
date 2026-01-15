#include <semaphore.h>

typedef struct
{
  // User defined data may be declared here.
  sem_t h_sem;
  sem_t o_sem;
  int h;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O *h2oCreate()
{
  H2O *obj = (H2O *)malloc(sizeof(H2O));

  // Initialize user defined data here.
  sem_init(&obj->h_sem, 0, 2);
  sem_init(&obj->o_sem, 0, 0);
  obj->h = 0;

  return obj;
}

void hydrogen(H2O *obj)
{
  sem_wait(&obj->h_sem);
  // releaseHydrogen() outputs "H". Do not change or remove this line.
  releaseHydrogen();
  ++obj->h;
  if (!(obj->h % 2))
    sem_post(&obj->o_sem);
}

void oxygen(H2O *obj)
{
  sem_wait(&obj->o_sem);
  // releaseOxygen() outputs "O". Do not change or remove this line.
  releaseOxygen();
  sem_post(&obj->h_sem);
  sem_post(&obj->h_sem);
}

void h2oFree(H2O *obj)
{
  // User defined data may be cleaned up here.
  if (obj)
  {
    sem_destroy(&obj->h_sem);
    sem_destroy(&obj->o_sem);
    free(obj);
  }
}