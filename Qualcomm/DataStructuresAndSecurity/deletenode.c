/**
 * @file deletenode.c
 * @author your name (you@domain.com)
 * @brief Deleting a node in a cyclic node
 * @version 0.1
 * @date 2026-01-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdlib.h>

struct Node
{
  int val;
  struct Node *next;
};

void deleteANode(struct Node *head, int value)
{
  if (!head)
    return;

  // Edge case
  if (head->next == head && head->val == value)
  {
    free(head);
    return;
  }

  struct Node *node = head;
  struct Node *prev = NULL;

  do
  {
    if (node->val == value)
      break;

    prev = node;
    node = node->next;
  } while (node && node != head);

  // if not found
  if (node->val != value)
    return;

  // if we are deleting a head
  if (node == head)
  {
    struct Node *last = head;
    while (last->next != head)
      last = last->next;

    head = head->next;
    last->next = head;
    free(node);
    return;
  }

  struct Node *temp = node->next;
  node->val = temp->val;
  node->next = temp->next;
  free(temp);
}