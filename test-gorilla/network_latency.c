#include <stdio.h>
#include <stdbool.h>

#define MAX_NODE 100
#define MAX_CHILDREN 10

typedef struct
{
  int key;
  int children[MAX_CHILDREN];
  int childCount;
} Node;

Node network[MAX_NODE];
int nSize = 0;

void addEdges(int parent, int child)
{
  for (int i = 0; i < nSize; ++i)
  {
    if (parent == network[i].key)
    {
      Node *node = &network[i];
      node->children[node->childCount] = child;
      ++node->childCount;
      return;
    }
  }
  // Add new edges
  if (nSize < MAX_NODE)
  {
    Node node;
    node.key = parent;
    node.children[0] = child;
    node.childCount = 1;
    network[nSize] = node;
    ++nSize;
  }
}

void printNetwork()
{
  for (int i = 0; i < nSize; ++i)
  {
    printf("parent key: %d - childrent: ", network[i].key);
    for (int j = 0; j < network[i].childCount; ++j)
    {
      printf("%d, ", network[i].children[j]);
    }
    printf("\n");
  }
  printf("\n");
}

Node *findNode(int parentKey)
{
  for (int i = 0; i < nSize; ++i)
  {
    if (network[i].key == parentKey)
      return &network[i];
  }
  return NULL;
}

bool verify_network_node(int parentKey)
{
  Node *parentNode = findNode(parentKey);

  if (parentNode == NULL)
    return true;

  for (int i = 0; i < parentNode->childCount; ++i)
  {
    int childKey = parentNode->children[i];

    if (childKey < parentKey)
      return false;
    if (!verify_network_node(childKey))
      return false;
  }

  return true;
}

int main()
{
  int heap[5][2] = {{1, 3}, {1, 2}, {3, 6}, {3, 7}, {2, 8}};
  for (int i = 0; i < 5; ++i)
  {
    addEdges(heap[i][0], heap[i][1]);
  }
  printNetwork();
  printf("%s\n", (verify_network_node(network[0].key) ? "True" : "False"));
  return 0;
}
