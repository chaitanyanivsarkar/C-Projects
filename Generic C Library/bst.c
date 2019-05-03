#include <stdlib.h>

#include "bst.h"
#include "privatebst.h"


#define max(a, b) a<b ? b : a;


/*
My Generic Implementation of an AVL Search Tree
Probably change the name from BST to AVLTree
*/

/*Utility Functions*/
int height(_BST_Node *node) {  
    if (node == NULL)  
        return 0;  
    return node->height;  
}

int get_balance(_BST_Node* node) {
	if (node == NULL) {
		return 0;
	}
	
	return height(node->left) - height(node->right);
}



/*_BST_Node Functions*/
_BST_Node* new__BST_Node(void* key, size_t size) {
	_BST_Node* node = (_BST_Node*)malloc(sizeof(_BST_Node));
	
	node->key = malloc(size);
	for (int i = 0; i < size; ++i) {
		*(char *)(node->key + i) = *(char *)(key + i);
	}
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	
	return node;
}

_BST_Node* right_rotate(_BST_Node* node1) {
	_BST_Node* node2 = node1->left;
	_BST_Node* temp = node2->right;
	
	node2->right = node1;
	node1->left = temp;
	
	node1->height = 1 + max(height(node1->left), height(node1->right));
	node2->height = 1 + max(height(node2->left), height(node2->right));
	
	return node2;
}

_BST_Node* left_rotate(_BST_Node *node1) {  
    _BST_Node *node2 = node1->right;  
    _BST_Node *temp = node2->left;  
  
    node2->left = node1;  
    node1->right = temp;  
  
    node1->height = 1 + max(height(node1->left), height(node1->right));  
    node2->height = 1 + max(height(node2->left), height(node2->right));  
  
    return node2;
}

_BST_Node* insert_node(_BST_Node* node, void* key, size_t size, bool (*cmp)(void* a, void* b)) {
	
	if (node == NULL) {
		return new__BST_Node(key, size);
	}
	
	// Less than
	if (cmp(key, node->key) == 0) {
		node->left = insert_node(node->left, key, size, cmp);
	}
	// Greater than
	else if (cmp(key, node->key) == 1) {
		node->right = insert_node(node->right, key, size, cmp);
	}
	// Equal not allowed
	else return node;
	
	node->height = 1 + max(height(node->left), height(node->right));
	
	/*
	Get the balance factor of this ancestor  
    node to check whether this node became  
    unbalanced
	*/
    int balance = get_balance(node);
	
	//Left Left case
	if (balance > 1 && cmp(key, node->left->key) == 0) {
        return right_rotate(node);
	}
	// Right Right Case  
    if (balance < -1 && cmp(key, node->right->key) == 1) {
        return left_rotate(node);
	}
    // Left Right Case  
    if (balance > 1 && cmp(key, node->left->key) == 1) {  
        node->left = left_rotate(node->left);  
        return right_rotate(node);  
    }  
    // Right Left Case  
    if (balance < -1 && cmp(key, node->right->key) == 0) {  
        node->right = right_rotate(node->right);  
        return left_rotate(node);  
    }  

    return node;
}



/*Tree Functions*/
void insert(BST* T, void* key, size_t size, bool (*cmp)(void* a, void* b)) {
	T->root = insert_node(T->root, key, size, cmp);
	T->size = T->size + 1;
}

BST new_BST() {
	BST T;
	T.root = NULL;
	T.size = 0;
	T.insert = insert;
	
	return T;
}

int main() {
	return 0;
}