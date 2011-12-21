#include "bin_tree_vis.h"

#define EMPTY 1111			// Konstante, die für leere Elemente eingetragen wird; darf nicht als Element des Baumes verwendet werden
#define MAXchar 2			// Wie viele Ziffern pro Element angezeit werden sollen
#define MAXCHAR "%02i" 		// als Zahl MAXchar eintragen
#define EMPTY_STRING "  "	// Zeichenkette wird für leere Zellen eingesetzt, sollte von der Länge zur Konstante MAXchar passen

// Debugging Modus einschalten/auschalten
#ifndef DEBUG
#define DEBUG_BIN_TREE_VIS 0
#else
#define DEBUG_BIN_TREE_VIS 1
#endif

// Gibt Text auf der Konsole aus, wenn DEBUG definiert ist. Benutzung siehe printf
#define debug_print(...) \
        do { if (DEBUG_BIN_TREE_VIS) fprintf(stderr, __VA_ARGS__); } while (0)

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
        debug_print("printing element; element key: %i\n"
                    "min: %i, max: %i, y: %i\n"
                    "middle: %i\n\n", tree->key, min, max, y, middle);

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
	int w = width(h);

        debug_print("calculated height: %i\n"
                    "calculated width:  %i\n",
                    h, w);

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
                printf("error: out of memory");
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
			printf("\n\n");
	}
	printf("\n"); // Leerzeilen nach Baum


    // Memory Leak verhindern
    for ( i=0; i<w; i++ ){
        free(arr[i]); // Spalten freigeben
    }
    free(arr); // Zeilenzeiger freigeben

}
