#include "avl_tree_algorithms.h"

int balance(Ptr node){
	if(node == NULL)
		return 0;
	
	return height(node->right) - height(node->left);
}

void avl_einfuegen(Ptr t, int x){
	
}

void avl_delete(Ptr *tree, int key){
}


