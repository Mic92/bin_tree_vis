#include "bin_search_tree_algorithms.h"


/**
 * Binäre Suche. 
 */ 
Ptr suche(Ptr t, int x){
	if( t==NULL){
		printf("%i", x);
		printf(" - Nicht gefunden\n");
		return NULL;
	}else{
		if(t->key == x){
			return t;
		}else{
			if(t->key < x) 
				return suche(t->right, x);
			else 
				return suche(t->left, x);
		}	
	}
}

/**
 * Funktion zum Einfügen. 
 */ 
void einfuegen(Ptr t, int x){
	Ptr q;
	
	// Fall 1: Element schon im Baum
	if(t->key == x){
		if(DEBUG) printf("Element schon im Baum\n");
		return;
	}
	// Fall 2: Element muss left eingefügt werden
	if(t->key > x){
		// Fall 2a: kein Nachfolger, direktes Einfügen
		if(t->left != NULL){
			einfuegen(t->left, x);
		// Fall 2b: Nachfolger vorhanden, kein direktes Einfügen
		}else{
			q = (Ptr) malloc(sizeof(Node));
			q->key = x;
			q->left = NULL;
			q->right = NULL;
			t->left = q;
		}
	// Fall 3: Element muss right eingefügt werden	
	}else{
		// Fall 3a: kein Nachfolger, direktes Einfügen
		if(t->right != NULL){
			einfuegen(t->right, x);
		// Fall 3b: Nachfolger vorhanden, kein direktes Einfügen
		}else{
			q = (Ptr) malloc(sizeof(Node));
			q->key = x;
			q->left = NULL;
			q->right = NULL;
			t->right = q;
		}
	}
}

/**
 * Löscht einen Knoten mit angegebenen Key.
 */ 
void delete(Ptr *tree, int key){
	Ptr node = *tree;
	
	if(node == NULL)
		return;
	
	if(node->key == key){
		// Keine Kindknoten
		if(  (node->left==NULL) && (node->right==NULL)  ){
			*tree = NULL;
		}else if( (node->left!=NULL) && (node->right==NULL) ){// Nur links Kind
			*tree = (*tree)->left;		
		}else if( (node->left==NULL) && (node->right!=NULL) ){ // Nur rechtes Kind
			*tree = (*tree)->right;		
		}else{// Zwei Kindknoten
			Ptr rightside = node->right;			
			*tree = node->left;

			Ptr very_right = node->left;
			while(very_right->right!=NULL)
				very_right = very_right->right;
			very_right->right = rightside;	
		}
		free(node);
	}else{
		delete( &(node->left), key);
		delete( &(node->right), key);
	}
	
}

/**
 * Gibt größten Wert im Suchbaum zurück.
 */ 
int max(Ptr tree){
	return (tree->right != NULL) ? max(tree->right) : tree->key;
}

/**
 * Gibt kleinsten Wert im Suchbaum zurück.
 */ 
int min(Ptr tree){
	return (tree->left != NULL) ? min(tree->left) : tree->key;
}
