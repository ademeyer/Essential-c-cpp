/**
 * @file circularbuffer.c
 * @author your name (you@domain.com)
 * @brief Design your implementation of the circular queue.
          The circular queue is a linear data structure in
          which the operations are performed based on FIFO
          (First In First Out) principle, and the last
          position is connected back to the first position
          to make a circle. It is also called "Ring Buffer".

          One of the benefits of the circular queue is that
          we can make use of the spaces in front of the queue.
          In a normal queue, once the queue becomes full, we
          cannot insert the next element even if there is a
          space in front of the queue. But using the circular
          queue, we can use the space to store new values.

          Implement the MyCircularQueue class:

          MyCircularQueue(k) Initializes the object with
          the size of the queue to be k.
          int Front() Gets the front item from the queue.
          If the queue is empty, return -1.
          int Rear() Gets the last item from the queue.
          If the queue is empty, return -1.
          boolean enQueue(int value) Inserts an element into
          the circular queue. Return true if the operation is
          successful.
          boolean deQueue() Deletes an element from the circular
          queue. Return true if the operation is successful.
          boolean isEmpty() Checks whether the circular queue
          is empty or not.
          boolean isFull() Checks whether the circular queue
          is full or not.
          You must solve the problem without using the
          built-in queue data structure in your programming language.
 * @version 0.1
 * @date 2026-01-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
  int capacity;
  int head;
  int tail;
  int *buffer;

} MyCircularQueue;

MyCircularQueue *myCircularQueueCreate(int k)
{
  if (k <= 0)
    return NULL;

  MyCircularQueue *q = (MyCircularQueue *)calloc(1, sizeof(MyCircularQueue));
  if (!q)
    return NULL;

  q->capacity = k + 1;
  q->buffer = (int *)calloc(k, sizeof(int));
  if (!q->buffer)
  {
    free(q);
    return NULL;
  }

  q->head = 0;
  q->tail = 0;
  return q;
}

bool myCircularQueueIsEmpty(MyCircularQueue *obj)
{
  if (!obj)
    return false;

  return (obj->head == obj->tail);
}

bool myCircularQueueIsFull(MyCircularQueue *obj)
{
  if (!obj)
    return false;

  return (((obj->head + 1) % obj->capacity) == obj->tail);
}

bool myCircularQueueEnQueue(MyCircularQueue *obj, int value)
{
  if (myCircularQueueIsFull(obj))
    return false;

  obj->buffer[obj->head] = value;
  obj->head = (obj->head + 1) % obj->capacity;
  return true;
}

bool myCircularQueueDeQueue(MyCircularQueue *obj)
{
  if (myCircularQueueIsEmpty(obj))
    return false;

  obj->tail = (obj->tail + 1) % obj->capacity;
  return true;
}

int myCircularQueueFront(MyCircularQueue *obj)
{
  if (myCircularQueueIsEmpty(obj))
    return -1;

  return obj->buffer[obj->tail % obj->capacity];
}

int myCircularQueueRear(MyCircularQueue *obj)
{
  if (myCircularQueueIsEmpty(obj))
    return -1;

  return obj->buffer[(obj->head - 1 + obj->capacity) % obj->capacity];
}

void myCircularQueueFree(MyCircularQueue *obj)
{
  if (obj)
  {
    if (obj->buffer)
      free(obj->buffer);
    free(obj);
  }
}

int main()
{
  MyCircularQueue *q = myCircularQueueCreate(3);
  printf("Expect: True, Got: %s\n", myCircularQueueEnQueue(q, 1) ? "True" : "False");
  printf("Expect: True, Got: %s\n", myCircularQueueEnQueue(q, 2) ? "True" : "False");
  printf("Expect: True, Got: %s\n", myCircularQueueEnQueue(q, 3) ? "True" : "False");
  printf("Expect: False, Got: %s\n", myCircularQueueEnQueue(q, 4) ? "True" : "False");
  printf("Expect: 3, Got: %d\n", myCircularQueueRear(q));
  printf("Expect: True, Got: %s\n", myCircularQueueIsFull(q) ? "True" : "False");
  printf("Expect: True, Got: %s\n", myCircularQueueDeQueue(q) ? "True" : "False");
  printf("Expect: True, Got: %s\n", myCircularQueueEnQueue(q, 4) ? "True" : "False");
  printf("Expect: 4, Got: %d\n", myCircularQueueRear(q));

  return 0;
}