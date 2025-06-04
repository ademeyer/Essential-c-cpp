#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node* next;
};

int checkCircular(const struct Node* head)
{
  // null head is a circular list
  if(!head) return 1;
  
  struct Node* temp = NULL; 
  temp = (struct Node*) head->next;

  while(temp != NULL && temp != head)
  {
    temp = temp->next;
  }

  return temp == head;
}

struct Node* newNode(int data)
{
  struct Node* ptrNode = (struct Node*) malloc(sizeof(struct Node));
  if(!ptrNode)
    return NULL;
  ptrNode->data = data;
  ptrNode->next=NULL;
  return ptrNode;
}

int main()
{
  struct Node* head = NULL;
  int ret = checkCircular(head);
  printf("%s\n", (ret ? "is Circular" : "is Not Circular"));
  head = newNode(1);
  head->next = newNode(2);
  head->next->next = newNode(3);
  ret = checkCircular(head);
  printf("%s\n", (ret ? "is Circular" : "is Not Circular"));
  head->next->next->next = head;
  ret = checkCircular(head);
  printf("%s\n", (ret ? "is Circular" : "is Not Circular"));
  return 0;
}
