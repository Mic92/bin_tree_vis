#include <stdio.h>
#include <stdlib.h>

#define EMPTY 1111			// Konstante, die für leere Elemente eingetragen wird; darf nicht als Element des Baumes verwendet werden
#define MAXCHAR "%2i" 		// als Zahl eintragen, wie viele Ziffern pro Element angezeit werden sollen
#define EMPTY_STRING "  "	// Zeichenkette wird für leere Zellen eingesetzt, sollte von der Länge zur Konstante MAXCHAR passen  

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
			printf("Element schon im Baum\n");
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
		printf("\nDeleting LEAF\n”");
		free(tree);
		tree = NULL;		
	}else if(tree->right == NULL || tree->left == NULL){
		printf("\nONE child\n”");
		Ptr neu;
		Ptr old = tree;
		if(tree->right == NULL)
			neu = tree->left;
		else
			neu = tree->right;
		tree = neu;
		free(old);	
	}else{
		printf("\ntwo children\n”");
		Ptr old = tree;
		tree = old->left;
		old->left->right = old->right;
		free(old);
	}
}


// tatsächliche(dargestellte) Breite des Baumes
int vis_width(int height){
	int i, w=1;
	for( i = 1; i<height; i++){
		w*=2;
	}
	
	return 2*w-2;
}

void print_element(Ptr tree, int **arr, int min, int max, int y){
	if(tree == NULL)
		return;	
		
	printf("printing element; element key: %i\n", tree->key);	
	printf("min: %i, max: %i, y: %i \n", min, max, y);
	
	int middle = min + (max-min+1)/2;
	
	printf("middle: %i \n\n", middle);

		
	arr[middle][y] = tree->key;
	
	print_element(tree->left , arr, middle +1, max,  y+1);
	print_element(tree->right, arr, min, middle -1, y+1);
}

int height(Ptr tree){	
	if(tree==NULL)
		return 0;
	return 1 + height(tree->right) + height(tree->left);
}
	
	

// stellt Baum von oben(Wurzel) nach unten dar
void print(Ptr tree){
	int h = height(tree);
	printf("calculated height:");
	printf("%i \n", h);
	
	int vis_w = vis_width(h);
	printf("calculated vis_width:");
	printf("%i \n", vis_w);
	
	// 2 dim. array
	int** arr = malloc( vis_w*sizeof(int**) ); 
    if ( !arr ){ 
        printf("error: out of memory"); return; 
    } 

	int i;
    for ( i=0; i<vis_w; i++ ) { 
        arr[i] = malloc( h*sizeof(int)); 
        if ( !arr[i]) break; 
    }
     if ( i<h ) { 
        printf("error: out of memory"); return; 
        int j;
        for ( j=0; j<=i; j++ ) free ( arr[j] ); 
        free( arr ); 
        return; 
    } 

      
	
	// array füllen:
	int x,y;
	for(y = 0; y< h; y++){
		for(x = 0; x<vis_w; x++){
			arr[x][y] = EMPTY;
		}
	}
	print_element(tree, arr, 0, vis_w, 0);
	
	
	// array anzeigen
	for(i = 0; i< h; i++){
		int k;
		for(k = 0; k<vis_w; k++){
			if(arr[k][i]== EMPTY)
				printf(EMPTY_STRING);
			else
				printf(MAXCHAR, arr[k][i]);
		}
		printf("\n");
	}
	
}


int main(){
	Ptr tree = (Ptr) malloc(sizeof(Node));
	tree->left = NULL;
	tree->right = NULL;
	tree->key = 0;
	
	
	
	int i;
	for(i = 1; i<3; i++){
		einfuegen(&tree, i);
		einfuegen(&tree, -2*i);

	}
	
		
	for(i = -10; i<10; i++){
		suche(tree, i);
	}
	
	//printf("\n\n Deleting 19 \n\n");
	//node_del(tree, 10);
	
	/*for(i = 0; i<3; i++){
		suche(tree, i);
	}*/
	
	
	printf("\n\n\n\n\n\n\n\n");
	print(tree);
	
	return 1;
}

