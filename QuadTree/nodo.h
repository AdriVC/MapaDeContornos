#ifndef NODO_H
#define NODO_H


class Nodo{
    //parametros: [left,top,length,height]
    int* parametros;
    int posicion;
    Nodo** sons;
    Nodo* parent;
public:
    Nodo(int left, int top, int length, int height, Nodo* father, int pos);
    ~Nodo();
    void setParam(int dato,int pos);
    int getParam(int pos);
    int* getParams();
    void setSon(Nodo* son,int pos);
    Nodo* getSon(int pos);
    void setParent(Nodo* par);
    Nodo* getParent();
    void setPosicion(int pos);
    int getPosicion();
};

#endif // NODO_H
