#include "avl_tree_algorithms.h"

int balance(Ptr node){
	if(node == NULL)
		return 0;
	
	return height(node->right) - height(node->left);
}

void rot_right(Ptr tree,Ptr node){
	printf("Not implemented yet.");
}


void rot_left(Ptr tree,Ptr node){
	printf("Not implemented yet.");
}

/**
 * Umsetzung des Algorithmuses im Script von Prof. Dr. Vogler auf Seite 123/124.
 */ 
void avl_einfuegen(Ptr t, int new_val){
	// 1.: Knoten einfuegen
	einfuegen(t,new_val);
	
	Ptr new_node = suche(t, new_val);
	new_node->balance = 0;	
	
	// 2.: Vorgängerknoten des neuen Knoten bestimmen und dessen balance aktualisieren
	Ptr n = predecessor(t, new_node);
	n->balance = balance(n);
	
	while(n!= NULL){
		// 2.a) new_val wurde im linken Unterbaum eingefügt
		if(n->right == new_node){
			if(n->balance == 1){
				// i)
				n->balance = 0;
				return;
			}else if(n->balance == 0){
				// ii)
				n->balance = -1;
				n = predecessor(t, n);
				break;
			}else if(n->balance == -1){
				// iii)
				if(n->left->balance == -1)
					rot_right(t, n);
				else if(n->left->balance ==	1){
					rot_left(t,n->left);
					rot_right(t,n);
				}	
			}else{
				printf("this musn't happen!");
			}	
		}else{ 
		// 2.b) new val wurde im rechten Unterbaum eingefügt
			printf("Noch nicht implementiert!");
		}
	}		
}

void avl_delete(Ptr *tree, int key){
}


