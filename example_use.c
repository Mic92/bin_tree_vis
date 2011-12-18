#include "bin_tree_vis.c"

int main(){
	printf("Debugging is ");
	printf(DEBUG ? "enabled" : "disabled");
	printf("\n\n");
	
	// Baum initialisieren
	Ptr tree = (Ptr) malloc(sizeof(Node));
	tree->left = NULL;
	tree->right = NULL;
	tree->key = 0;	
	
	// Baum mit Daten füllen
	int i;
	for(i = 0; i<5; i++){
		einfuegen(tree, i);
		einfuegen(tree, -i);
	}
	einfuegen(tree, 3);

	print(tree);
	
	return 1;
}
