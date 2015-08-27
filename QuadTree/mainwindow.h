#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nodo.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_b_fileOpen_clicked();

    void on_b_procesarImagen_clicked();

    void procesarImagen(Nodo* nodo,int depth,unsigned char** redsIm, unsigned char** greensIm, unsigned char** bluesIm, unsigned char** redsRe, unsigned char** greensRe, unsigned char** bluesRe);

    bool compararPixeles(Nodo* nodo,unsigned char** redsIm, unsigned char** greensIm, unsigned char** bluesIm);

    void crearMatrizRGB(unsigned char** &matriz);

    void EscrituraDeImagen(char* /*FileBuffer*/, const char* NameOfFileToCreate, int BufferSize);
    void LecturaDeImagen(unsigned char** redsIm, unsigned char** greensIm, unsigned char** bluesIm, unsigned char** redsRe, unsigned char** greensRe, unsigned char** bluesRe, int end, int rows, int cols, char* FileReadBuffer);
    bool InfoDeImagen(char*& buffer, const char* Picture, int& rows, int& cols, int& BufferSize);

private:
    Ui::MainWindow *ui;
    unsigned char** redsIm;
    unsigned char** greensIm;
    unsigned char** bluesIm;
    //unsigned char** reds;
    //unsigned char** greens;
    //unsigned char** blues;
    unsigned char** redsRe;
    unsigned char** greensRe;
    unsigned char** bluesRe;
    int rows;
    int cols;
    int controlador;
    QString fileName;
};

#endif // MAINWINDOW_H
