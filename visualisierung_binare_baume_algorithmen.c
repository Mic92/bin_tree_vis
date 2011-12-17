#include <stdio.h>
#include <stdlib.h>

typedef struct Nodeelem *Ptr;
typedef struct Nodeelem{
	int key;
	Ptr left, right;
	} Node;
	
Ptr p;

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

// Breite des Baumes
int width(int height){
	if(height == 1)
		return 1;
	return 2*(height-1);
}

// tatsächliche(dargestellte) Breite des Baumes
int vis_width(int heigth){
	
	int i, w=0;
	for( i = 1; i<=heigth; i++){
		w+=width(i);
	}

	return w;
}

void print_element(Ptr tree, int height, int **arr, int x, int y){
	if(tree == NULL)
		return;	
		
	printf("printing element; element key: %i\n", tree->key);	
	printf("x: %i, y: %i\n\n", x, y);
		
	arr[x][y] = tree->key;
	
	print_element(tree->left, height, arr, x - (height-y) +1, y+1);
	print_element(tree->right, height, arr, x + (height-y) +1, y+1);
}

int heigth(Ptr tree){	
	if(tree==NULL)
		return 0;
	return 1 + heigth(tree->right) + heigth(tree->left);
}
	
	

// stellt Baum von oben(Wurzel) nach unten dar
void print(Ptr tree){
	int h = heigth(tree);
	printf("calculated height:");
	printf("%i \n", h);
	
	int w = width(h);
	int vis_w = vis_width(h);
	printf("calculated width:");
	printf("%i \n", w);
	printf("calculated vis_width:");
	printf("%i \n", vis_w);
	
	// 2 dim. array
	int** arr = malloc( h*sizeof(int**) ); 
    if ( !arr ){ 
        printf("error: out of memory"); return; 
    } 

	int i;
    for ( i=0; i<h; i++ ) { 
        arr[i] = malloc( vis_w*sizeof(int)); 
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
	for(i = 0; i< h; i++){
		int k;
		for(k = 0; k<vis_w; k++){
			arr[k][i] = -1;
		}
	}
	//print_element(tree, h, arr, vis_w/2, 0);
	
	/*
	// array anzeigen
	for(i = 0; i< h; i++){
		int k;
		for(k = 0; k<vis_w; k++){
			if(arr[k][i]== -1)
				printf("#");
			else
				printf("%i", arr[k][i]);
		}
		printf("\n");
	}
	*/
	
}


int main(){
	Ptr tree = (Ptr) malloc(sizeof(Node));
	tree->left = NULL;
	tree->right = NULL;
	tree->key = 0;
	
	
	
	int i;
	for(i = 1; i<3; i++){
		einfuegen(&tree, i);
	}
		
	for(i = 0; i<3; i++){
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

