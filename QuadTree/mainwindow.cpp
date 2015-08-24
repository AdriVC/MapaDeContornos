#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>

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
    ui->L_image->setText("Favor seleccione la \nimagen a procesar");
    ui->b_exportarImagen->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_fileOpen_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/Users/adrivega/Documents/UNITEC/2015-3 jul - sept/Estructura de Datos/P2-QuadTree/Imagenes", tr("Image Files (*.bmp)"));
    ui->LE_imagePath->setText(fileName.split("/")[9]);
    ui->L_image->setText("");
    QImage Raw(fileName);
    ui->L_image->setPixmap(QPixmap::fromImage(Raw));
}

void MainWindow::on_b_procesarImagen_clicked()
{
    if(ui->LE_imagePath->text() == "" || ui->sB_profundidad->value() == -1){
        QMessageBox msgbox;
        msgbox.setBaseSize(QSize(310, 150));
        msgbox.setWindowTitle("ERROR");
        msgbox.setText("Favor asegurese que haya \nseleccionado la imagen a procesar \ny la profundidad deseada.");
        msgbox.exec();
    }else{
        //ui->sB_profundidad->setValue(-1);
        ui->L_output->setText("");
        ui->b_exportarImagen->setEnabled(true);
        ui->LE_outputPath->setText(fileName.split("/")[9].split(".")[0].append("Output.bmp"));
        //para agregar la imagen procesada al label de output
        //QImage Raw(fileName);
        //ui->L_output->setPixmap(QPixmap::fromImage(Raw));

    }

}

void MainWindow::on_b_exportarImagen_clicked()
{

}
