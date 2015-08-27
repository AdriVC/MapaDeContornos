#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_b_exportarImagen_clicked();

    void procesarImagen();

    void lecturaImagen();

    void crearMatrizRGB(unsigned char** &matriz);

    void printMatrizRGB(unsigned char** &matriz);

    void RGB_Allocate(unsigned char**& dude);
    void ColorTest();
    void WriteOutBmp24(char* /*FileBuffer*/, const char* NameOfFileToCreate, int BufferSize);
    void GetPixlesFromBMP24(unsigned char** reds, unsigned char** greens, unsigned char** blues, int end, int rows, int cols, char* FileReadBuffer);
    bool FillAndAllocate(char*& buffer, const char* Picture, int& rows, int& cols, int& BufferSize);
    void on_all_clicked();

private:
    Ui::MainWindow *ui;
    //unsigned char** redsIm;
    //unsigned char** greensIm;
    //unsigned char** bluesIm;
    unsigned char** reds;
    unsigned char** greens;
    unsigned char** blues;
    unsigned char** redsRe;
    unsigned char** greensRe;
    unsigned char** bluesRe;
    int rows;
    int cols;
    int controlador;
    QString fileName;
};

#endif // MAINWINDOW_H
