#include "quadtree.h"

QuadTree::QuadTree(int left, int top, int length, int height, int profundidad){
    this->root = new Nodo(left,top,length,height,0,0);
    this->profundidad = profundidad;
}

QuadTree::~QuadTree(){

}

Nodo* QuadTree::getParent(Nodo* nodo){
    return nodo->getParent();
}

Nodo* QuadTree::getSon(Nodo* nodo, int pos){
    return nodo->getSon(pos);
}

int* QuadTree::getParams(Nodo* nodo){
    return nodo->getParams();
}

int QuadTree::getParam(Nodo* nodo, int pos){
    return nodo->getParam(pos);
}

Nodo* QuadTree::getRoot(){
    return root;
}

void QuadTree::insert(int left, int top, int length, int height, Nodo* parent, int pos){
    parent->setSon(new Nodo(left,top,length,height,parent,pos),pos);
}
