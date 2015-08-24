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
    QString fileName;

private slots:
    void on_b_fileOpen_clicked();

    void on_b_procesarImagen_clicked();

    void on_b_exportarImagen_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
