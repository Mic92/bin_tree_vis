#include "avl_tree_algorithms.h"
#include "bin_search_tree_algorithms.h"
#include "bin_tree.h"
#include "bin_tree_vis.h"
#include "config.h"

enum {LEFT, RIGHT, NEITHER};

void balance_all(Ptr root){
	if(root == NULL)
		return;
		
	root->balance = balance(root);
	balance_all(root->right);
	balance_all(root->left);	
}

int balance(Ptr node){
	if(node == NULL)
		return 0;

	return height(node->right) - height(node->left);
}

void rot_left(Ptr *n, Ptr *tree_root){

	printf("Rotating left \n");

	Ptr old_root = *n;
	*n = (*n)->right;
	printf("old_root: %i, new_root(n): %i \n", old_root->key, (*n)->key);

	old_root->right = (*n)->left;
	(*n)->left = old_root;
	
	if(old_root == *tree_root)
		tree_root = n;	
}

void rot_right(Ptr *n, Ptr *tree_root){

	printf("Rotating left \n");

	Ptr old_root = *n;
	*n = (*n)->left;
	printf("old_root: %i, new_root(n): %i \n", old_root->key, (*n)->key);

	old_root->left = (*n)->right;
	(*n)->right = old_root;
		
	if(old_root == *tree_root)
		tree_root = n;
}

/**
 * Returns the
 */ 
int sideOfTree(Ptr pre, Ptr child){
	if(pre == NULL)
		return NEITHER;
		
	if(pre->right == child){
		debug_print("Child is on right side \n");
		return RIGHT;
	}
	if(pre->left == child){
		debug_print("Child is on left side \n");
		return LEFT;
	}
	
	int l = sideOfTree(pre->left, child);
	return (l!=NEITHER) ? l : sideOfTree(pre->right, child) ;
	
}		

/**
 * Umsetzung des Algorithmuses im Script von Prof. Dr. Vogler auf Seite 123/124.
 * Nicht identisch mit der auf der auf den Folgeseiten abgedruckten Implementierung.
 */
void avl_einfuegen(Ptr *root, int new_val){
	Ptr t = *root;
	
	// Erstmal nur zur Sicherheit, wird später wieder entfernt!
	balance_all(t);
	
	// 1.: Knoten einfuegen
	einfuegen(t, new_val);

	Ptr new_node = suche(t, new_val);	// neuen Knoten finden
	new_node->balance = 0;

	// 2.: Vorgängerknoten des neuen Knoten bestimmen und dessen balance aktualisieren
	Ptr n = predecessor(t, new_node);

	while(n!= NULL){
		printf("while Schleife. Aktuelles Element: % i \n",n->key);
	
		// 2.a) new_val wurde im linken Unterbaum eingefügt
		if(sideOfTree(n, new_node) == LEFT){
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
			}else if(n->balance == -1){
				// iii)
				printf("iii \n");
				if(n->left->balance == -1)
					rot_right(&n, root);
				else if(n->left->balance ==	1){
					rot_left(&(n->left), root);
					rot_right(&n, root);
				}
				// ?
				n = predecessor(t, n);		
			}else{
				printf("this musn't happen!");
			}	
		}else if(sideOfTree(n, new_node) == RIGHT){ 
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
			}else if(n->balance == 1){
				// iii)
				printf("iii \n");
				if(n->right->balance == 1)
					rot_left(&n, root);
				else if(n->right->balance == -1){
					rot_right(&(n->right), root);
					rot_left(&n, root);
				}
				// ?
				n = predecessor(t, n);	
			}else{
				printf("this musn't happen!\n");
			}			
		}else{
			printf("this musn't happen!\n");
		}
	}		
	printf("end while\n");
}

void avl_delete(Ptr *tree, int key){
}


