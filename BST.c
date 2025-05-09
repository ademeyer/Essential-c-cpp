#include <stdlib.h>
#include <stdio.h>

typedef struct Node 
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

int contains(const Node *root, int value)
{
	if(!root) return 0;
	if(root->value == value) return 1;
	if(value < root->value)
		return contains(root->left, value);
	if(value > root->value)
		return contains(root->right, value);
	return 0;
}

#ifndef RunTests
int main()
{
    Node n1 = {.value=1, .left=NULL, .right=NULL};
    Node n3 = {.value=3, .left=NULL, .right=NULL};
    Node n2 = {.value=2, .left=&n1, .right=&n3};

    printf("%d", contains(&n2, 3));
}
#endif
