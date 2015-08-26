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

private:
    Ui::MainWindow *ui;
    unsigned char** redsIm;
    unsigned char** greensIm;
    unsigned char** bluesIm;
    unsigned char** redsRe;
    unsigned char** greensRe;
    unsigned char** bluesRe;
    int rows;
    int cols;
    QString fileName;
};

#endif // MAINWINDOW_H
