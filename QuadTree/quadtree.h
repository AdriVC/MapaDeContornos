#ifndef QUADTREE_H
#define QUADTREE_H

#include "nodo.h"


class QuadTree{
    Nodo* root;
    int profundidad;
public:
    QuadTree(int left, int top, int length, int height, int profundidad);
    ~QuadTree();
    Nodo* getParent(Nodo* nodo);
    Nodo* getSon(Nodo* nodo, int pos);
    int* getParams(Nodo* nodo);
    int getParam(Nodo* nodo, int pos);
    Nodo* getRoot();
    void insert(int left, int top, int length, int height, Nodo* parent, int pos);
};

#endif // QUADTREE_H
