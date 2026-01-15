/**
 * @file arraytolinkedlist.c
 * @author your name (you@domain.com)
 * @brief Write code to turn an array into a linked list with the same data.
 * @version 0.1
 * @date 2026-01-11
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int value;
  struct Node *next;
};

static struct Node *ArrayToLinkedList(const int *arr, int nSize)
{
  if (nSize == 0 || !arr)
    return NULL;

  struct Node *head = NULL;
  struct Node *cur = NULL;

  for (int i = 0; i < nSize; ++i)
  {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
      break;

    newNode->value = arr[i];
    newNode->next = NULL;

    if (!head) // create new node
    {
      head = newNode;
      cur = head;
    }
    else // link new to cur
    {
      cur->next = newNode;
      cur = cur->next;
    }
  }

  return head;
}

static void printnode(struct Node *root)
{
  struct Node *cur = root;
  while (cur)
  {
    printf("value: %d\n", cur->value);
    cur = cur->next;
  }
}

int main()
{
  {
    int arr[] = {1, 2, 3, 4, 5, 6};
    const int s = sizeof(arr) / sizeof(arr[0]);
    struct Node *node = ArrayToLinkedList(arr, s);
    printnode(node);
  }

  {
    int arr[] = {100, 300, 500, 200, 400};
    const int s = sizeof(arr) / sizeof(arr[0]);
    struct Node *node = ArrayToLinkedList(arr, s);
    printnode(node);
  }
  return 0;
}