#include "quadtree.h"
#include <iostream>

using namespace std;

QuadTree::QuadTree(int left, int top, int width, int height, int profundidad){
    this->root = new Nodo(left,top,width,height,0,-1);
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

int QuadTree::getDepth(){
    int depth = 0;
    int prueba = 0;
    Nodo* temp = root;
    for(int i = 0; i < 4; i++){
        while(temp->getSon(i) != 0){
            prueba++;
            temp = temp->getSon(i);
        }
        if(prueba > depth)
            depth = prueba;
    }
    return depth;
}
