#ifndef AVL_TREE_ALGORITHMS_H
#define AVL_TREE_ALGORITHMS_H

#include "bin_tree_vis.h"
#include "bin_search_tree_algorithms.h"

int balance(Ptr node);
void avl_einfuegen(Ptr t, int x);
void avl_delete(Ptr *tree, int key);

 
#endif
