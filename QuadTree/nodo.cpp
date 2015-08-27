#include "nodo.h"

Nodo::Nodo(int left, int top, int width, int height, Nodo* father, int pos){
    //parametros: [left,top,width,height]
    this->parametros[0] = left;
    this->parametros[1]= top;
    this->parametros[2] = width;
    this->parametros[3] = height;
    sons = new Nodo*[4];
    for(int i = 0; i < 4; i++){
        sons[i]= 0;
    }
    parent = father;
    this->posicion = pos;
}

Nodo::~Nodo()
{
    //delete parametros;
    for(int i = 0; i < 4; i++){
        delete sons[i];
    }
    delete sons;
}

void Nodo::setParam(int dato,int pos){
    this->parametros[pos] = dato;
}

int Nodo::getParam(int pos){
    return this->parametros[pos];
}

int* Nodo::getParams(){
    return this->parametros;
}

void Nodo::setSon(Nodo* son, int pos){
    sons[pos] = son;
}

Nodo* Nodo::getSon(int pos){
    return sons[pos];
}
void Nodo::setParent(Nodo* par){
    parent = par;
}
Nodo* Nodo::getParent(){
    return parent;
}

void Nodo::setPosicion(int pos){
    this->posicion = pos;
}

int Nodo::getPosicion(){
    return this->posicion;
}

void Nodo::insert(){
    for(int i=0; i<4; i++){
        switch(i){
        case 0:
            this->setSon(new Nodo(this->getParam(0),this->getParam(1),this->getParam(2)/2,this->getParam(3)/2,this,i),i);
            break;
        case 1:
            this->setSon(new Nodo(this->getParam(2)/2,this->getParam(1),this->getParam(2)/2,this->getParam(3)/2,this,i),i);
            break;
        case 2:
            this->setSon(new Nodo(this->getParam(0),this->getParam(3)/2,this->getParam(2)/2,this->getParam(3)/2,this,i),i);
            break;
        case 3:
            this->setSon(new Nodo(this->getParam(2)/2,this->getParam(3)/2,this->getParam(2)/2,this->getParam(3)/2,this,i),i);
            break;
        }
    }
}
