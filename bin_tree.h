#ifndef BIN_TREE_H
#define BIN_TREE_H

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
#endif
