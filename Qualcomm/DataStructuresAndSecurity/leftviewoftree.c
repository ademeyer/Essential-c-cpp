/**
 * @file leftviewoftree.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-01-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for a binary tree node
struct TreeNode
{
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
};

// Structure to store result
struct Result
{
  int *arr;
  int size;
  int capacity;
};

/**
 * Recursive function to get left view
 * @param node: Current node
 * @param result: Result array
 * @param level: Current level
 * @param max_level: Pointer to maximum level reached so far
 */
void leftViewUtil(struct TreeNode *node, struct Result *result, int level, int *max_level)
{
  if (node == NULL)
    return;

  // If this is the first node at this level
  if (*max_level < level)
  {
    // Add node to result
    if (result->size >= result->capacity)
    {
      result->capacity *= 2;
      result->arr = realloc(result->arr, result->capacity * sizeof(int));
    }
    result->arr[result->size++] = node->data;
    *max_level = level;
  }

  // Recur for left subtree first (important for left view)
  leftViewUtil(node->left, result, level + 1, max_level);
  leftViewUtil(node->right, result, level + 1, max_level);
}

/**
 * Main function to get left view
 * @param root: Root of the binary tree
 * @param returnSize: Pointer to store size of result array
 * @return: Array containing left view nodes
 */
int *leftView(struct TreeNode *root, int *returnSize)
{
  // Initialize result structure
  struct Result result;
  result.size = 0;
  result.capacity = 10; // Initial capacity
  result.arr = malloc(result.capacity * sizeof(int));

  int max_level = 0; // Tracks maximum level reached

  // Get left view
  leftViewUtil(root, &result, 1, &max_level);

  // Set return size
  *returnSize = result.size;

  // Return the array
  return result.arr;
}