#include "bin_search_tree_algorithms.h"


/**
 * Binäre Suche. 
 */ 
void suche(Ptr t, int x){
	if( t==NULL){
		printf("%i", x);
		printf(" - Nicht gefunden\n");
	}else{
		if(t->key == x){
			printf("%i", x);
			printf(" liegt im Baum\n");
		}else{
			if(t->key < x) suche(t->right, x);
			else suche(t->left, x);
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
	// Fall 2: Element muss rechts eingefügt werden
	if(t->key > x){
		// Fall 2a: kein Nachfolger, direktes Einfügen
		if(t->right != NULL){
			einfuegen(t->right, x);
		// Fall 2b: Nachfolger vorhanden, kein direktes Einfügen
		}else{
			q = (Ptr) malloc(sizeof(Node));
			q->key = x;
			q->left = NULL;
			q->right = NULL;
			t->right = q;
		}
	// Fall 3: Element muss links eingefügt werden	
	}else{
		// Fall 3a: kein Nachfolger, direktes Einfügen
		if(t->left != NULL){
			einfuegen(t->left, x);
		// Fall 3b: Nachfolger vorhanden, kein direktes Einfügen
		}else{
			q = (Ptr) malloc(sizeof(Node));
			q->key = x;
			q->left = NULL;
			q->right = NULL;
			t->left = q;
		}
	}
}

/**
 * Löscht einen Knoten mit angegebenen Key.
 */ 
void delete(Ptr *tree, int key){
	if(*tree == NULL)
		return;
	
	Ptr old = *tree;
	// Keine Kindknoten
	if(  ((*tree)->left==NULL) && ((*tree)->right==NULL)  ){
		if(DEBUG)
			printf("\n Deleting node, no children \n");
		
		*tree = NULL;
	}
	// Nur links Kind
	if( ((*tree)->left!=NULL) && ((*tree)->right==NULL) ){
		if(DEBUG)
			printf("\n Deleting node, left child \n");
		
		*tree = (*tree)->left;		
	}
	// Nur rechtes Kind
	if( ((*tree)->left==NULL) && ((*tree)->right!=NULL) ){
		if(DEBUG)
			printf("\n Deleting node, right child \n");
		
		*tree = (*tree)->right;		
	}// Zwei Kindknoten
	if( ((*tree)->left==NULL) && ((*tree)->right!=NULL) ){
		if(DEBUG)
			printf("\n Deleting node, two children \n");
		
		*tree = (*tree)->right;		
	}
	free(old);
}
