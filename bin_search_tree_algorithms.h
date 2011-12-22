#ifndef BIN_SEARCH_TREE_ALGORITHMS_H
#define BIN_SEARCH_TREE_ALGORITHMS_H

#include "bin_tree_vis.h"
#include "config.h"

Ptr suche(Ptr t, int x);
void einfuegen(Ptr t, int x);
void delete(Ptr *tree, int key);
int max(Ptr tree);
int min(Ptr tree);
Ptr predecessor(Ptr tree, Ptr node);
 
#endif
