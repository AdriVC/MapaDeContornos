#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <iostream>
#include <unistd.h>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
#pragma pack(1)

typedef int LONG;
typedef unsigned short WORD;
typedef unsigned int DWORD;
int controlador;

typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

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
        lecturaImagen();
        //procesarImagen();
        //para agregar la imagen procesada al label de output
        //QImage Raw(fileName);
        //ui->L_output->setPixmap(QPixmap::fromImage(Raw));

    }

}

void MainWindow::on_b_exportarImagen_clicked()
{
    char* FileBuffer;
    int BufferSize;

    FileBuffer = new char[controlador];

    std::ofstream write(fileName.split("/")[9].split(".")[0].append("Output.bmp").toUtf8().constData());

    if (!write) {
        cout << "Failed to write " << endl;
        return;
    }
    //BufferSize = BufferSizeControlador;
    BufferSize=349338;
    int count = 1;
    int extra = cols % 4; // The nubmer of bytes in a row (cols) will be a multiple of 4.
    for (int i = 0; i < rows; i++){
        count += extra;
        //count += 900;
        cout<<BufferSize<<endl;
        cout<<cols<<endl;
        cout<<rows<<endl;
        cout<<count<<endl;
        cout<<extra<<endl;
        for (int j = cols - 1; j >= 0; j--)
            for (int k = 0; k < 3; k++) {
                switch (k) {
                case 0: //reds
                    FileBuffer[BufferSize - count] = redsIm[i][j];
                    break;
                case 1: //green
                    FileBuffer[BufferSize - count] = greensIm[i][j];
                    break;
                case 2: //blue
                    FileBuffer[BufferSize - count] = bluesIm[i][j];
                    break;
                }
                count++;

            }
    }

    write.write(FileBuffer, BufferSize);

}

void MainWindow::lecturaImagen()
{
    char* buffer;
    int BufferSize;

    std::ifstream file(fileName.toUtf8().constData());
    file.seekg(0, std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer = new char[length];
    file.read(&buffer[0], length);

    PBITMAPFILEHEADER file_header;
    PBITMAPINFOHEADER info_header;

    file_header = (PBITMAPFILEHEADER) (&buffer[0]);
    info_header = (PBITMAPINFOHEADER) (&buffer[0] + sizeof(BITMAPFILEHEADER));
    rows = info_header->biHeight;
    cols = info_header->biWidth;
    BufferSize = file_header->bfSize;

    crearMatrizRGB(redsIm);
    crearMatrizRGB(greensIm);
    crearMatrizRGB(bluesIm);

    //cout << "buffer: " << buffer << endl;
    //cout << "length: " << length << endl;
    //cout << "buffer size: " << BufferSize << endl;
    cout << "rows: " << rows << endl;
    cout << "columns: " << cols << endl;

    int count = 1;
    int extra = cols % 4; // The nubmer of bytes in a row (cols) will be a multiple of 4.
    for (int i = 0; i < rows; i++){
        count += extra;
        for (int j = cols - 1; j >= 0; j--){
            for (int k = 0; k < 3; k++) {
                switch (k) {
                case 0:
                    redsIm[i][j] = buffer[BufferSize - count++];
                    break;
                case 1:
                    greensIm[i][j] = buffer[BufferSize - count++];
                    break;
                case 2:
                    bluesIm[i][j] = buffer[BufferSize - count++];
                    break;
                }
            }
        }
    }

}

void MainWindow::crearMatrizRGB(unsigned char** &matriz)
{
    matriz = new unsigned char*[rows];
    for(int i = 0; i < rows; i++){
        matriz[i] = new unsigned char[cols];
    }
}

void MainWindow::printMatrizRGB(unsigned char** &matriz)
{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void MainWindow::procesarImagen()
{

}
