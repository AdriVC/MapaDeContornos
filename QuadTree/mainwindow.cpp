#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileName("")
{
    ui->setupUi(this);
    QPixmap bkgnd(":/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QImage Logo(":/flecha.png");
    ui->L_flecha->setPixmap(QPixmap::fromImage(Logo));

    QPixmap pix(":/open_file.png");
    pix = pix.scaled(ui->b_fileOpen->size(),Qt::IgnoreAspectRatio);
    QIcon icon(pix);
    ui->b_fileOpen->setIcon(icon);
    ui->b_fileOpen->setIconSize(pix.size());

    ui->LE_imagePath->setText("");
    ui->LE_outputPath->setText("");
    ui->L_output->setText("Favor seleccione la \nprofundidad y haga \nclick en \"Procesar\"");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_fileOpen_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/Users/adrivega/Documents/UNITEC/2015-3 jul - sept/Estructura de Datos/P2-QuadTree/Imagenes", tr("Image Files (*.bmp)"));
    ui->LE_imagePath->setText(fileName.split("/")[9]);
}
