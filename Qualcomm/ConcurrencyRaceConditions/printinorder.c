#include <semaphore.h>

typedef struct
{
  // User defined data may be declared here.
  sem_t sem_1;
  sem_t sem_2;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo *fooCreate()
{
  Foo *obj = (Foo *)malloc(sizeof(Foo));

  // Initialize user defined data here.
  sem_init(&obj->sem_1, 0, 0);
  sem_init(&obj->sem_2, 0, 0);

  return obj;
}

void first(Foo *obj)
{

  // printFirst() outputs "first". Do not change or remove this line.
  printFirst();
  sem_post(&obj->sem_1);
}

void second(Foo *obj)
{
  sem_wait(&obj->sem_1);
  // printSecond() outputs "second". Do not change or remove this line.
  printSecond();
  sem_post(&obj->sem_2);
}

void third(Foo *obj)
{
  sem_wait(&obj->sem_2);
  // printThird() outputs "third". Do not change or remove this line.
  printThird();
}

void fooFree(Foo *obj)
{
  // User defined data may be cleaned up here.
  if (obj)
  {
    sem_destroy(&obj->sem_1);
    sem_destroy(&obj->sem_2);
    free(obj);
  }
}

// typedef struct {
//     // User defined data may be declared here.
//     unsigned char sync_bit;
// } Foo;

// // Function Declaration, do not remove
// void printFirst();
// void printSecond();
// void printThird();

// Foo* fooCreate() {
//     Foo* obj = (Foo*)malloc(sizeof(Foo));

//     // Initialize user defined data here.
//     obj->sync_bit = 0;

//     return obj;
// }

// void first(Foo* obj) {

//     // printFirst() outputs "first". Do not change or remove this line.
//     printFirst();
//     obj->sync_bit |= 0b00000001; // mark first have ran
// }

// void second(Foo* obj) {
//     while (!(obj->sync_bit & 0x01))
//         ;
//     // printSecond() outputs "second". Do not change or remove this line.
//     printSecond();
//     obj->sync_bit |= 00000010; // 00000010
// }

// void third(Foo* obj) {
//     while ((obj->sync_bit & 00000011) != 00000011)
//         ; // needs 00000011 to run
//     // printThird() outputs "third". Do not change or remove this line.
//     printThird();
// }

// void fooFree(Foo* obj) {
//     // User defined data may be cleaned up here.
//     if (obj)
//         free(obj);
// }