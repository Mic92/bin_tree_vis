#include "avl_tree_algorithms.h"

int balance(Ptr node){
	if(node == NULL)
		return 0;
	
	return height(node->right) - height(node->left);
}

void avl_einfuegen(Ptr t, int new_val){
	einfuegen(t,new_val);
	// Vorgängerknoten des neuen Knoten bestimmen
	//Ptr n = predecessor(t, suche(t, new_val));
}

void avl_delete(Ptr *tree, int key){
}


