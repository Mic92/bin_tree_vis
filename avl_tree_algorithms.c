#include "avl_tree_algorithms.h"
#include "bin_search_tree_algorithms.h"
#include "bin_tree.h"
#include "config.h"

int balance(Ptr node){
	if(node == NULL)
		return 0;

	return height(node->right) - height(node->left);
}

void rot_left(Ptr *n){

	printf("Rotating left \n");

	Ptr old_root = *n;
	*n = (*n)->right;
	printf("old_root: %i, new_root(n): %i \n", old_root->key, (*n)->key);

	old_root->right = (*n)->left;
	(*n)->left = old_root;
}

void rot_right(Ptr *n){

	printf("Rotating left \n");

	Ptr old_root = *n;
	*n = (*n)->left;
	printf("old_root: %i, new_root(n): %i \n", old_root->key, (*n)->key);

	old_root->left = (*n)->right;
	(*n)->right = old_root;
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

	while(n!= NULL){

		// 2.a) new_val wurde im linken Unterbaum eingefügt
		if(n->left == new_node){
			printf("2.a), n=%i, n->balance=%i \n", n->key, n->balance);
			if(n->balance == 1){
				// i)
				printf("i \n");
				n->balance = 0;
				return;
			}else if(n->balance == 0){
				// ii)
				printf("ii \n");
				n->balance = -1;
				n = predecessor(t, n);
				break;
			}else if(n->balance == -1){
				// iii)
				printf("iii \n");
				if(n->left->balance == -1)
					rot_right(&n);
				else if(n->left->balance ==	1){
					rot_left(&(n->left));
					rot_right(&n);
				}	
			}else{
				printf("this musn't happen!");
			}	
		}else{ 
		// 2.b) new val wurde im rechten Unterbaum eingefügt
			printf("2.b), n=%i, n->balance=%i \n", n->key, n->balance);
			if(n->balance == -1){
				// i)
				printf("i \n");
				n->balance = 0;
				return;
			}else if(n->balance == 0){
				// ii)
				printf("ii \n");
				n->balance = 1;
				n = predecessor(t, n);
				break;
			}else if(n->balance == 1){
				// iii)
				printf("iii \n");
				if(n->right->balance == 1)
					rot_left(&n);
				else if(n->right->balance == -1){
					rot_right(&(n->right));
					rot_left(&n);
				}	
			}else{
				printf("this musn't happen!");
			}			
		}
	}		
}

void avl_delete(Ptr *tree, int key){
}


