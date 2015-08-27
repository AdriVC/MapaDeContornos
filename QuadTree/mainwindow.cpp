#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodo.h"
#include "quadtree.h"
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
int BufferSizeControlador;
char* FileBuffer; int BufferSize;
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_fileOpen_clicked()
{
    //#define Picture "ReadInPicture2.bmp"
    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/Users/adrivega/Documents/UNITEC/2015-3 jul - sept/Estructura de Datos/P2-QuadTree/Imagenes", tr("Image Files (*.bmp)"));
    //fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/isaac/Desktop/Trabajos/Estructura/proyectos/QuadTree/MapaDeContornos/Imagenes", tr("Image Files (*.bmp)"));
    ui->LE_imagePath->setText(fileName.split("/")[9]);
    ui->L_image->setText("");
    QImage Raw(fileName);
    ui->L_image->setPixmap(QPixmap::fromImage(Raw));
    //#define Picture "ReadInPicture2.bmp"

    //if (!InfoDeImagen(FileBuffer, fileName.toUtf8().constData(), rows, cols, BufferSize)){cout << "File read error" << endl; cout<<"Return 0";}
    /*if (!InfoDeImagen(FileBuffer, fileName.toUtf8().constData(), rows, cols, BufferSize)){cout << "File read error" << endl; cout<<"Return 0";}

    cout << "Rows: " << rows << " Cols: " << cols << endl;
    crearMatrizRGB(redsIm);
    crearMatrizRGB(greensIm);
    crearMatrizRGB(bluesIm);
    LecturaDeImagen( redsIm,  greensIm, bluesIm, redsRe,  greensRe, bluesRe,BufferSize, rows, cols, FileBuffer);*/

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
        ui->L_output->setText("");
        ui->LE_outputPath->setText(fileName.split("/")[9].split(".")[0].append("Output.bmp"));

        char* FileBuffer; int BufferSize;

        if (!InfoDeImagen(FileBuffer, fileName.toUtf8().constData(), rows, cols, BufferSize)){}

        crearMatrizRGB(redsIm);
        crearMatrizRGB(greensIm);
        crearMatrizRGB(bluesIm);
        crearMatrizRGB(redsRe);
        crearMatrizRGB(greensRe);
        crearMatrizRGB(bluesRe);
        LecturaDeImagen( redsIm,  greensIm, bluesIm, redsRe,  greensRe, bluesRe,BufferSize, rows, cols, FileBuffer);

        QuadTree* arbol = new QuadTree(0,0,cols,rows,-1);
        Nodo* temp = arbol->getRoot();

        procesarImagen(temp,0, redsIm, greensIm, bluesIm, redsRe, greensRe, bluesRe);

#define WriteOutFile "Output.bmp"
        EscrituraDeImagen(FileBuffer,  WriteOutFile,BufferSize);

        QMessageBox msgbox;
        msgbox.setBaseSize(QSize(310, 150));
        msgbox.setWindowTitle("Info");
        msgbox.setText("Su imagen Output.bmp se ha colocado en el folder de imagenes.");
        msgbox.exec();

        ui->L_image->setText("");
        QImage Raw("Output.bmp");
        ui->L_output->setPixmap(QPixmap::fromImage(Raw));

    }

}

void MainWindow::crearMatrizRGB(unsigned char**& matriz)
{
    matriz = new unsigned char*[rows];
    for(int i = 0; i < rows; i++){
        matriz[i] = new unsigned char[cols];
    }
}

void MainWindow::procesarImagen(Nodo* nodo,int depth,unsigned char** redsIm, unsigned char** greensIm, unsigned char** bluesIm, unsigned char** redsRe, unsigned char** greensRe, unsigned char** bluesRe)
{
    if(compararPixeles(nodo,redsIm, greensIm, bluesIm) && depth < ui->sB_profundidad->value()){
        nodo->insert();
        for(int i= nodo->getParam(0); i < nodo->getParam(2); i++){
            redsRe[nodo->getParam(1)+nodo->getParam(3)/2][i] = 0x00;
            greensRe[nodo->getParam(1)+nodo->getParam(3)/2][i] = 0x00;
            bluesRe[nodo->getParam(1)+nodo->getParam(3)/2][i] = 0x00;
        }
        for(int i= nodo->getParam(1); i < nodo->getParam(3); i++){
            redsRe[nodo->getParam(0)+nodo->getParam(2)/2][i] = 0x00;
            greensRe[nodo->getParam(0)+nodo->getParam(2)/2][i] = 0x00;
            bluesRe[nodo->getParam(0)+nodo->getParam(2)/2][i] = 0x00;
        }
        for(int i=0; i < 4; i++){
            procesarImagen(nodo->getSon(0),depth++,redsIm, greensIm, bluesIm, redsRe, greensRe, bluesRe);
        }
    }
}

bool MainWindow::compararPixeles(Nodo* nodo, unsigned char** redsIm, unsigned char** greensIm, unsigned char** bluesIm)
{
    bool nosolido = false;
    for(int i = nodo->getParam(1); i < nodo->getParam(3); i++){
        for(int j = nodo->getParam(0); j < nodo->getParam(2)-1; j++){
            if(redsIm[i][j] != redsIm[i][j+1] || greensIm[i][j] != greensIm[i][j+1] || bluesIm[i][j] != bluesIm[i][j+1])
                nosolido = true;
                break;
        }
        if(nosolido)
            break;

    }
    return nosolido;
}

bool MainWindow::InfoDeImagen(char*& buffer, const char* Picture, int& rows, int& cols, int& BufferSize) { //Returns 1 if executed sucessfully, 0 if not sucessfull
    std::ifstream file(Picture);

    if (file) {
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
        return 1;
    }
    else {
        cout << "File: " << Picture << " doesn't Exist!" << endl;
        return 0;
    }
}


void MainWindow::LecturaDeImagen(unsigned char** redsIm, unsigned char** greensIm, unsigned char** bluesIm, unsigned char** redsRe, unsigned char** greensRe, unsigned char** bluesRe, int end, int rows, int cols, char* FileReadBuffer) { // end is BufferSize (total size of file)
    int count = 1;
    int extra = cols % 4; // The nubmer of bytes in a row (cols) will be a multiple of 4.
    for (int i = 0; i < rows; i++){
        count += extra;
        for (int j = cols - 1; j >= 0; j--)
            for (int k = 0; k < 3; k++) {
                switch (k) {
                case 0:
                    redsIm[i][j] = FileReadBuffer[end - count++];
                    redsRe[i][j] = 0xFF;
                    break;
                case 1:
                    greensIm[i][j] = FileReadBuffer[end - count++];
                    greensRe[i][j] = 0xFF;
                    break;
                case 2:
                    bluesIm[i][j] = FileReadBuffer[end - count++];
                    bluesRe[i][j] = 0xFF;
                    break;
                }
            }
    }
}

void MainWindow::EscrituraDeImagen(char* FileBuffer, const char* NameOfFileToCreate, int BufferSize) {
    std::ofstream write(NameOfFileToCreate);
    if (!write) {
        cout << "Failed to write " << NameOfFileToCreate << endl;
        return;
    }
    int count = 1;
    int extra = cols % 4; // The nubmer of bytes in a row (cols) will be a multiple of 4.
    for (int i = 0; i < rows; i++){
        count += extra;
        for (int j = cols - 1; j >= 0; j--)
            for (int k = 0; k < 3; k++) {
                switch (k) {
                case 0: //redsIm
                    FileBuffer[BufferSize - count] = redsRe[i][j];
                    break;
                case 1: //green
                    FileBuffer[BufferSize - count] = greensRe[i][j];
                    break;
                case 2: //blue
                    FileBuffer[BufferSize - count] = bluesRe[i][j];
                    break;
                }
                count++;
            }
    }
    write.write(FileBuffer, BufferSize);
}

