/**
 * @file clonegraph.c
 * @author your name (you@domain.com)
 * @brief Given a reference of a node in a connected undirected graph.

          Return a deep copy (clone) of the graph.

          Each node in the graph contains a value (int) and a list
          (List[Node]) of its neighbors.

          class Node {
              public int val;
              public List<Node> neighbors;
          }


          Test case format:

          For simplicity, each node's value is the same as the node's
          index (1-indexed). For example, the first node with val == 1,
          the second node with val == 2, and so on. The graph is
          represented in the test case using an adjacency list.

          An adjacency list is a collection of unordered lists used
          to represent a finite graph. Each list describes the set
          of neighbors of a node in the graph.

          The given node will always be the first node with val = 1.
          You must return the copy of the given node as a reference to the cloned graph.
 * @version 0.1
 * @date 2026-01-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 101

struct Node
{
  int val;
  int numNeighbors;
  struct Node **neighbors;
};

struct Node **visited; // hash map to hold visited array

struct Node *cloneGraph(struct Node *s)
{
  if (!s)
    return NULL;

  if (!s->numNeighbors)
  {
    struct Node *cloneNode = (struct Node *)calloc(1, sizeof(struct Node));
    cloneNode->val = s->val;
    return cloneNode;
  }
  // allocate visited hash if not allocated
  if (!visited)
    visited = (struct Node **)calloc(MAX_NODE, sizeof(struct Node *));

  // we have visited this before?
  if (visited[s->val] != NULL)
  {
    printf("Node[%d]: %d\n", s->val, visited[s->val]->val);
    return visited[s->val];
  }

  struct Node *cloneNode = (struct Node *)calloc(1, sizeof(struct Node));
  cloneNode->val = s->val;
  cloneNode->numNeighbors = s->numNeighbors;
  cloneNode->neighbors =
      (struct Node **)calloc(cloneNode->numNeighbors, sizeof(struct Node *));

  // updated visited
  visited[s->val] = cloneNode;

  // deep clone neighbours
  for (int i = 0; i < s->numNeighbors; ++i)
    cloneNode->neighbors[i] = cloneGraph(s->neighbors[i]);

  return cloneNode;
}