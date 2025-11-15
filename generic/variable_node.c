#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Node
{
  void* data;
  struct Node* next;
};

struct Node* createNode(void* d)
{
  struct Node* node = (struct Node*) malloc(sizeof(struct Node));
  if(!node) return NULL;
  
  node->data = d;
  node->next = NULL;
  return node;
}

int main ()
{
  uint8_t v1 = 128; // head
  uint16_t v2 = 234;
  uint32_t v3 = 40000;

  struct Node* head = createNode((void*)&v1);
  head->next = createNode((void*)&v2);
  head->next->next = createNode((void*)&v3);


  uint8_t* r1 = (uint8_t*) head->data;
  uint16_t* r2 = (uint16_t*) head->next->data;
  uint32_t* r3 = (uint32_t*) head->next->next->data;

  printf("v1: %d, v2: %d, v3: %u\n", *r1, *r2, *r3);
  return 0;
}
