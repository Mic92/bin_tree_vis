#include "avl_tree_algorithms.h"
#include "bin_search_tree_algorithms.h"
#include "bin_tree.h"
#include "bin_tree_vis.h"
#include "config.h"

enum {LEFT, RIGHT, NEITHER};

void update_all_parents(Ptr root){
	if(root == NULL)
		return;
		
	if(root->left != NULL)	
		root->left->parent = root;
	
	if(root->right != NULL)	
		root->right->parent = root;

	update_all_parents(root->right);
	update_all_parents(root->left);
}

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

void rot_left(Ptr *n){
	printf("Rotating left \n");

	Ptr old_root = *n;
	*n = (*n)->right;
	printf("old_root: %i, new_root(n): %i \n", old_root->key, (*n)->key);

	old_root->right = (*n)->left;
	(*n)->left = old_root;
		
	(*n)->parent = old_root->parent;

	old_root->parent = *n;
	
	if( (*n)->parent != NULL){
		printf("Updating child of %i\n", (*n)->parent->key);
		(*n)->parent->right = *n;
	}	
	
	printf("Finished rotating \n\n");	
}

void rot_right(Ptr *n){

	printf("Rotating right \n");

	Ptr old_root = *n;
	*n = (*n)->left;
	printf("old_root: %i, new_root(n): %i \n", old_root->key, (*n)->key);

	old_root->left = (*n)->right;
	(*n)->right = old_root;
	
	
	(*n)->parent = old_root->parent;

	old_root->parent = *n;	
			
	if( (*n)->parent != NULL){
		printf("Updating child of %i, new child is %i\n", (*n)->parent->key, (*n)->key);
		(*n)->parent->left = *n;
	}		
	
	printf("Finished rotating \n\n");		
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
	Ptr n = new_node->parent;

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
				n = n->parent;		
			}else if(n->balance == -1){
				// iii)
				printf("iii \n");
				if(n->left->balance == -1)
					rot_right(&n);
				else if(n->left->balance ==	1){
					rot_left(&(n->left));
					rot_right(&n);
				}
				return;
			}else{
				printf("this musn't happen 1!");
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
				n = n->parent;		
			}else if(n->balance == 1){
				// iii)
				printf("iii \n");
				if(n->right->balance == 1)
					rot_left(&n);
				else if(n->right->balance == -1){
					rot_right(&(n->right));
					rot_left(&n);
				}
				return;
			}else{
				printf("this musn't happen 2!\n");
			}			
		}else{
			printf("this musn't happen 3!\n");
			return;
		}
		printf("\n\n");
	}		
	printf("end while\n");
	
}

void avl_delete(Ptr *tree, int key){
}


