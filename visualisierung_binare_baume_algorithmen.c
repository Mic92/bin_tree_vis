#include <stdio.h>
#include <stdlib.h>

#define EMPTY 1111			// Konstante, die für leere Elemente eingetragen wird; darf nicht als Element des Baumes verwendet werden
#define MAXchar 2			// Wie viele Ziffern pro Element angezeit werden sollen
#define MAXCHAR "%02i" 		// als Zahl MAXchar eintragen
#define EMPTY_STRING "  "	// Zeichenkette wird für leere Zellen eingesetzt, sollte von der Länge zur Konstante MAXchar passen  

#define DEBUG 0				// Debugging Modus einschalten/auschalten

typedef struct Nodeelem *Ptr;
typedef struct Nodeelem{
	int key;
	Ptr left, right;
	} Node;
	

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

void einfuegen(Ptr *t, int x){
	Ptr q;
	
	if(*t == NULL){
		q = (Ptr) malloc(sizeof(Node));
		q->key = x;
		q->left = NULL;
		q->right = NULL;
		*t = q;
	}else{
		if ( (*t)->key == x){
			if(DEBUG) printf("Element schon im Baum\n");
		}else{
			if( (*t)->key < x) einfuegen( &((*t)->right), x);
			else einfuegen( &((*t)->left), x);
		}
	}
}

void node_del(Ptr tree, int key){	
	if(tree == NULL)
		return;
	
	if(tree->key != key){
		if(tree->key<key){
			node_del(tree->right, key);
			return;
		}else{
			node_del(tree->left, key);
			return;
		}	
	}
	
	if(tree->left == NULL && tree->right == NULL){
		if(DEBUG) printf("\nDeleting leaf(no child), key: %i \n", key);
		free(tree);
		tree = NULL;		
	}else if(tree->right == NULL || tree->left == NULL){
		if(DEBUG) printf("\n Deleting Node with one child, key: %i \n", key);
		Ptr neu;
		Ptr old = tree;
		if(tree->right == NULL)
			neu = tree->left;
		else
			neu = tree->right;
		tree = neu;
		free(old);	
	}else{
		if(DEBUG) printf("\n Deleting Node with two children, key: %i \n", key);
		Ptr old = tree;
		tree = old->left;
		old->left->right = old->right;
		free(old);
	}
}


/**
 * Gibt tatsächliche(dargestellte Breite des Baumes zurück. 
 */ 
int vis_width(int height){
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
	print_element(tree->right , arr, middle +1, max,  y+1);
	print_element(tree->left, arr, min, middle -1, y+1);
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
	int vis_w = vis_width(h);
	
	// Debugging Infos
	if(DEBUG){
		printf("calculated height:");
		printf("%i \n", h);
		printf("calculated vis_width:");
		printf("%i \n", vis_w);
	}
	
	// 2 dimensionales Array dynamisch erzeugen
	int** arr = malloc( vis_w*sizeof(int**) ); 	// erst Reihen reservieren
    // Fehlerbehandlung
    if(!arr){ printf("error: out of memory"); return; } 

	// Jetzt Zeilen reservieren
	int i;
    for( i=0; i<vis_w; i++ ){ 
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
		for(x = 0; x<vis_w; x++){
			arr[x][y] = EMPTY;
		}
	}
	
	// Jetzt rekursiv Array mit tatsächlichen Daten füllen
	print_element(tree, arr, 0, vis_w, 0);
	
	// Array anzeigen
	printf("\n\n");		// Leerzeilen vor Baum
	for(i = 0; i< h; i++){
		int k;
		for(k = 0; k<vis_w; k++){
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
    for ( i=0; i<vis_w; i++ ){ 
        free(arr[i]); // Spalten freigeben 
    } 
    free(arr); // Zeilenzeiger freigeben 

}


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
		einfuegen(&tree, i);
		einfuegen(&tree, -i);
	}

	// Wieder etwas löschen
	//node_del(tree, 10);
	
	/*for(i = 0; i<3; i++){
		suche(tree, i);
	}*/
	
	print(tree);
	
	return 1;
}

