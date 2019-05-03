#ifndef PRIVATE_BST_H
#define PRIVATE_BST_H

typedef struct _node {
	void* key;
	struct _node* left;
	struct _node* right;
	int height;
} _BST_Node;

#endif