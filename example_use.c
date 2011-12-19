#include "bin_tree_vis.c"
#include "bin_search_tree_algorithms.c"

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

	
	return 1;
}
