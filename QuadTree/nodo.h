#ifndef NODO_H
#define NODO_H


class Nodo{
       int dato;
       Nodo** sons;
       Nodo* parent;
public:
    Nodo(int value, Nodo* &father);
    ~Nodo();
    void setDato(int value);
    int getDato();
    void setSon(Nodo* &son,int pos);
    Nodo* getSon(int pos);
    void setParent(Nodo* &par);
    Nodo* getParent();
};

#endif // NODO_H
