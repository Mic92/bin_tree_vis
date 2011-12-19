#include "bin_tree_vis.c"

/**
 * Gibt einen Elternknoten oder NULL zurück.
 * Je nach Baum kann der Knoten nicht eindeutig sein.
 */ 
Ptr getParent(Ptr tree, Ptr child){
	if(tree==NULL)
		return NULL;
		
	if( (tree->left==child) ||  (tree->right==child) )
		return tree;
		
	Ptr left = getParent(tree->left, child);
	Ptr right = getParent(tree->right, child);
	
	if(left!=NULL)
		return left;
	
	if(right!=NULL)
		return right;
	
	return left;
}

/**
 * Löscht einen Knoten mit angegebenen Key.
 * Je nach Baum kann der Knoten nicht eindeutig sein.
 */ 
int delete(Ptr *tree, int key){	
	Ptr node = *tree;
	
	// kein Baum vorhanden
	if(node == NULL)
		return 0;
	
	// Node hat nicht den key 
	if(node->key != key){
		return delete( &(node->right), key) + delete( &(node->left), key);
	}else{	// Node hat key
		
		// keine Kindknoten
		if( (node->right) == NULL && (node->left) == NULL){
			*tree = NULL;
			free(node);
		}else{ // genau zwei Kindknoten
			*tree = node->right;
			//(*tree)->right = node->right;
			//(*tree)->left = node->left; // froehliches umhaengen
			
			free(node);
		}
		
		return 1;
	}	
}

int main(){
	printf("Debugging is ");
	printf(DEBUG ? "enabled" : "disabled");
	printf("\n\n");
	
	// Baum initialisieren
	Ptr tree = (Ptr) malloc(sizeof(Node));
	tree->left = NULL;
	tree->right = NULL;
	tree->key = 10;	
	
	// Baum mit Daten füllen
	// (Reihenfolge ist wichtig, damit ein "schöner Baum" erzeugt wird,
	// da Baum unbalanciert ist
	
	// links
	einfuegen(tree, 5);
	einfuegen(tree, 3);
	einfuegen(tree, 7);
	einfuegen(tree, 2);
	einfuegen(tree, 6);
	einfuegen(tree, 8);
	einfuegen(tree, 4);
	
	// rechts
	einfuegen(tree, 15);
	einfuegen(tree, 13);
	einfuegen(tree, 17);
	einfuegen(tree, 12);
	einfuegen(tree, 16);
	einfuegen(tree, 18);
	einfuegen(tree, 14);


	printf("Ein einfacher Binärer Baum");
	print(tree);

	printf("Deleting 13");
	delete(&tree, 13);
	print(tree);
	
	return 1;
}
