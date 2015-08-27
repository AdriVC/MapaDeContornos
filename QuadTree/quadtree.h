#ifndef QUADTREE_H
#define QUADTREE_H

#include "nodo.h"


class QuadTree{
    Nodo* root;
    int profundidad;
public:
    QuadTree(int left, int top, int width, int height, int profundidad);
    ~QuadTree();
    Nodo* getParent(Nodo* nodo);
    Nodo* getSon(Nodo* nodo, int pos);
    int* getParams(Nodo* nodo);
    int getParam(Nodo* nodo, int pos);
    Nodo* getRoot();
    int getDepth();
};

#endif // QUADTREE_H
