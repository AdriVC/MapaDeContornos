#ifndef QUADTREE_H
#define QUADTREE_H

#include "nodo.h"


class QuadTree{
    Nodo* root;
public:
    QuadTree(int dato);
    ~QuadTree();
    Nodo* getParent(Nodo* n);
    Nodo* getLeftSon(Nodo* n);
    Nodo* getRightSon(Nodo* n);
    int getValue(Nodo* n);
    Nodo* getRoot();
    void insert(int valor);
    void Delete(Nodo* n);
    void inOrder();
};

#endif // QUADTREE_H
