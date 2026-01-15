#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define USE_THREAD 1

const char data[] = "\nWe need to make a statement before the end"
                    "of the entire world, but just before then, \ntry and print this long"
                    "message to console. \nHope this is long enough to eat CPU time, I am "
                    "guessing we must have exhausted system \nbuffer by now. "
                    "hahahahahahahahaahahahahahahahaha\n\n";

const int size_of_data = sizeof(data);
int pos = 0;

#if USE_THREAD

#define THREAD_NUM 1

pthread_mutex_t posMtx = PTHREAD_MUTEX_INITIALIZER;

void *printc(void *args)
{
  while (pos < size_of_data)
  {
    pthread_mutex_lock(&posMtx);
    fputc(data[pos], stdout);
    ++pos;
    pthread_mutex_unlock(&posMtx);
  }
}

// Create thread IDs
pthread_t threads[THREAD_NUM];

#endif

int main()
{
  clock_t startTime = clock(), endTime;

#if USE_THREAD
  const char *clause_print = " With Threads";

  for (int i = 0; i < THREAD_NUM; ++i)
    pthread_create(&threads[i], NULL, printc, NULL);

  // Wait for thread to finish
  for (int i = 0; i < THREAD_NUM; ++i)
    pthread_join(threads[i], NULL);

#else
  const char *clause_print = " With Using Threads";
  while (pos < size_of_data)
    fputc(data[pos++], stdout);
#endif

  // Print time elapsed
  endTime = clock();
  printf("CPU Execution Time%s: %f microsec(s)\n", clause_print, (double)(((endTime - startTime) * 1000000) / CLOCKS_PER_SEC));
  return 0;
}