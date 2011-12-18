#include "bin_tree_vis.h"

#define EMPTY 1111			// Konstante, die für leere Elemente eingetragen wird; darf nicht als Element des Baumes verwendet werden
#define MAXchar 2			// Wie viele Ziffern pro Element angezeit werden sollen
#define MAXCHAR "%02i" 		// als Zahl MAXchar eintragen
#define EMPTY_STRING "  "	// Zeichenkette wird für leere Zellen eingesetzt, sollte von der Länge zur Konstante MAXchar passen  

#define DEBUG 0				// Debugging Modus einschalten/auschalten

/**
 * Binäre Suche. 
 * Einfach und effizient.
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
 * Achtung: Fügt nur an Knoten ohne Kindknoten ein, nicht für
 * AVL Bäume geeignet.
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
 * Gibt tatsächliche(dargestellte Breite des Baumes zurück. 
 */ 
int width(int height){
	int i, w=1;
	for( i = 1; i<height; i++){
		w*=2;
	}
	
	return (2*w-1)*MAXchar;
}

/**
 * Setzt rekursiv die einzelnen Werte des Binären Baumes in das übergebene
 * Array.
 */ 
void print_element(Ptr tree, int **arr, int min, int max, int y){
	// Rekursionsabbruch
	if(tree == NULL)
		return;	

	// Mitte vom (Teil)Baum ist Position des Wurzelelementes
	int middle = min + (max-min+1)/2;
	
	// Debugging Informationen
	if(DEBUG){		
		printf("printing element; element key: %i\n", tree->key);	
		printf("min: %i, max: %i, y: %i \n", min, max, y);
		printf("middle: %i \n\n", middle);
	}
	
	// Im Array Key von aktuellen Element eintragen
	arr[middle][y] = tree->key;
	
	// Unterbäume bearbeiten
	print_element(tree->left , arr, middle +1, max,  y+1);
	print_element(tree->right, arr, min, middle -1, y+1);
}

/**
 * Rekursive Berechnung der Höhe des Baumes
 */ 
int height(Ptr tree){
	// Rekursionsabbruch	
	if(tree==NULL)
		return 0;
	
	// Rückgabe von 1 + maximale Höhe von Kindern
	return 1 +  (   height(tree->right)>height(tree->left) ?  height(tree->right) :height(tree->left) ); 
}
	
	

/**
 * Stellt den übergebenen Binären Baum in der Konsole dar.
 */ 
void print(Ptr tree){
	
	// Höhe und Breite berechnen
	int h = height(tree);
	int w = width(h);
	
	// Debugging Infos
	if(DEBUG){
		printf("calculated height:");
		printf("%i \n", h);
		printf("calculated width:");
		printf("%i \n", w);
	}
	
	// 2 dimensionales Array dynamisch erzeugen
	int** arr = malloc( w*sizeof(int**) ); 	// erst Reihen reservieren
    // Fehlerbehandlung
    if(!arr){ printf("error: out of memory"); return; } 

	// Jetzt Zeilen reservieren
	int i;
    for( i=0; i<w; i++ ){ 
        arr[i] = malloc( h*sizeof(int)); 
        if ( !arr[i]) break; 
    }
    
    // Fehlerbehandlung
    if(i<h){ 
        printf("error: out of memory"); return; 
        int j;
        for ( j=0; j<=i; j++ ) free ( arr[j] ); 
        free( arr ); 
        return; 
    } 

      
	
	// Array mit leeren Daten füllen
	int x,y;
	for(y = 0; y< h; y++){
		for(x = 0; x<w; x++){
			arr[x][y] = EMPTY;
		}
	}
	
	// Jetzt rekursiv Array mit tatsächlichen Daten füllen
	print_element(tree, arr, 0, w, 0);
	
	// Array anzeigen
	printf("\n\n");		// Leerzeilen vor Baum
	for(i = 0; i< h; i++){
		int k;
		for(k = 0; k<w; k++){
			if(arr[k][i]== EMPTY)
				printf(EMPTY_STRING);
			else
				printf(MAXCHAR, arr[k][i]);
		}
		// Neue Zeile für jede neue Baumebene
			printf("\n");
	}
	printf("\n"); // Leerzeilen nach Baum

	
    // Memory Leak verhindern 
    for ( i=0; i<w; i++ ){ 
        free(arr[i]); // Spalten freigeben 
    } 
    free(arr); // Zeilenzeiger freigeben 

}
