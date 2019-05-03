#ifndef BST_H
#define BST_H

#include "privatebst.h"

#define INSERT(a, b, cmp) a.insert(&a, (void*)&b, sizeof(b), cmp);

typedef unsigned char bool;

typedef struct _bst {
	_BST_Node* root;
	int size;
	void (*insert)(struct _bst* T, void* key, size_t size, bool (*cmp)(void* a, void* b));
} BST;

BST new_BST();


#endif