/**
 * @file validatebinarysearchtree.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-01-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Definition for a binary tree node.
 *
 */
struct TreeNode
{
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

bool validate(struct TreeNode *node, long long min, long long max)
{
  if (!node)
    return true;

  if (node->val <= min || node->val >= max)
    return false;

  return validate(node->left, min, node->val) && validate(node->right, node->val, max);
}

bool isValidBST(struct TreeNode *root)
{
  return validate(root, LONG_MIN, LONG_MAX);
}
