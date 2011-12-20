#include "bin_tree_vis.c"
#include "bin_search_tree_algorithms.c"
#include "avl_tree_algorithms.c"


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
	printf("Kleinster Wert im Baum: %i\n", min(tree));
	printf("Größter Wert im Baum: %i \n\n", max(tree));
	
	
	printf("Nun wird die 7 aus dem Baum gelöscht:");
	delete(&tree, 7);

	// Baum braucht genug Platz um angezeigt werden zu können
	print(tree);

	printf("Balance-Faktor der Wurzel ist %i\n", balance(tree));
	printf("Balance-Faktor vom Knoten mit Key 6 ist %i \n\n", balance(suche(tree, 6)));

	printf("Vorgänger von 5 ist %i \n", (predecessor(tree, suche(tree,5)))->key);
	printf("Vorgänger von 6 ist %i \n", (predecessor(tree, suche(tree,6)))->key);
	printf("Vorgänger von 8 ist %i \n\n", (predecessor(tree, suche(tree,8)))->key);

	
	
	printf("AVL-Baum: \n");
	
	// Wurzel erstellen
	Ptr avl_tree = (Ptr) malloc(sizeof(Node));
	avl_tree->key = 10;
	avl_tree->right = NULL;
	avl_tree->left = NULL;
	avl_tree->balance = 0;
	
	// Werte einfügen
	avl_einfuegen(avl_tree, 20);	
	printf("\n\n 30 einfügen \n\n");
		avl_einfuegen(avl_tree, 30);
	print(avl_tree);
	
	
	rot_left(&avl_tree);

	print(avl_tree);
	
	return 1;
}
