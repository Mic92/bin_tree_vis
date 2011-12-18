#ifndef BIN_TREE_VIS_H
#define BIN_TREE_VIS_H


#include <stdio.h>
#include <stdlib.h>

/** 
 * Struktur kann auch für AVL Bäume verwendet werden.
 * Momentan wird balance einfach nicht benutzt.
*/
typedef struct Nodeelem *Ptr;
typedef struct Nodeelem{
	int key;
	int balance;
	Ptr parent, left, right;
	} Node;
	
 
void suche(Ptr, int);
void einfuegen(Ptr, int);
int  width(int);
void print_element(Ptr, int** , int, int, int);
int  height(Ptr tree);
void print(Ptr tree);

 
#endif
