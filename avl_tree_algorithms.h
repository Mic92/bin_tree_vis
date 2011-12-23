#ifndef AVL_TREE_ALGORITHMS_H
#define AVL_TREE_ALGORITHMS_H

#include "bin_tree.h"

int balance(Ptr node);
void avl_einfuegen(Ptr *root, int x);
void avl_delete(Ptr *tree, int key);
int isInTree(Ptr root, Ptr node);


#endif
