#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define USE_THREAD 1

const char data[] = "\nWe need to make a statement before the end of the entire world, but just before then, try and print this long message to console. Hope this is long enough to eat CPU time. hahahahahahahahaahahahahahahahaha\n";
const int size_of_data = sizeof(data);

int pos = 0;

pthread_mutex_t posMtx = PTHREAD_MUTEX_INITIALIZER;

void *printc(void *args)
{
  // Get and print the thread ID
  // pthread_t thisThread = pthread_self();
  // printf("Thread: %lu is running task printc\n", (unsigned long)thisThread);
  while (pos < size_of_data)
  {
    fputc(data[pos], stdout);
    pthread_mutex_lock(&posMtx);
    ++pos;
    pthread_mutex_unlock(&posMtx);
  }
}

int main()
{

  clock_t startTime = clock(), endTime;
#if USE_THREAD
  // Create thread ID
  pthread_t threadID_1, threadID_2;

  // Create new thread
  pthread_create(&threadID_1, NULL, printc, NULL);
  pthread_create(&threadID_2, NULL, printc, NULL);

  // Wait for thread to finish
  pthread_join(threadID_1, NULL);
  pthread_join(threadID_2, NULL);

#else
  fputs(data, stdout);
#endif

  // Print time elapsed
  endTime = clock();
  printf("CPU Execution Time: %f microsec(s)\n", (double)(((endTime - startTime) * 1000000) / CLOCKS_PER_SEC));
  return 0;
}