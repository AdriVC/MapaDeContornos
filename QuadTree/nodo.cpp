#include "nodo.h"

Nodo::Nodo(int value, Nodo* &father){
    dato = value;
    sons = new Nodo*[4];
    for(int i = 0; i < 4; i++){
        sons[i]= 0;
    }
    parent = father;
}

Nodo::~Nodo()
{
    delete sons;
}

void Nodo::setDato(int value){
    dato = value;
}
int Nodo::getDato(){
    return dato;
}
void Nodo::setSon(Nodo* &son, int pos){
    sons[pos] = son;
}
Nodo* Nodo::getSon(int pos){
    return sons[pos];
}
void Nodo::setParent(Nodo* &par){
    parent = par;
}
Nodo* Nodo::getParent(){
    return parent;
}
